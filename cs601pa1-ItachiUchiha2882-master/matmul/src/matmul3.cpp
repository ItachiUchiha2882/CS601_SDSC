#include <iostream>
#include <cstdlib>
#include<stdio.h>
#include <sys/time.h>

using namespace std;

#ifdef PAPI
#include "papi.h"

// for handling error messages
inline void handle_error(int retval)
{
	printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
	exit(1);
}
#endif

int min(int x, int y)
{
	if (y < x)
		return y;
	return x;
}
void display(double **C, int n)
{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{

			cout << C[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		exit(0);
	}

#ifdef PAPI
	int retval, EventSet = PAPI_NULL;
	long long values[4] = {(long long)0, (long long)0, (long long)0, (long long)0};

	retval = PAPI_library_init(PAPI_VER_CURRENT);
	if (retval != PAPI_VER_CURRENT)
		handle_error(retval);

	retval = PAPI_create_eventset(&EventSet);
	if (retval != PAPI_OK)
		handle_error(retval);

	// Add event L1 Total Cache Misses
	retval = PAPI_add_event(EventSet, PAPI_L1_TCM);
	if (retval != PAPI_OK)
		handle_error(retval);

	// Add event L2 Total cache misses
	retval = PAPI_add_event(EventSet, PAPI_L2_TCM);
	if (retval != PAPI_OK)
		handle_error(retval);

	// TOTAL cycles
	retval = PAPI_add_event(EventSet, PAPI_TOT_CYC);
	if (retval != PAPI_OK)
		handle_error(retval);

	// TOTAL instructions
	retval = PAPI_add_event(EventSet, PAPI_TOT_INS);
	if (retval != PAPI_OK)
		handle_error(retval);
#endif

	// n is the dimention of matrices
	// s is the block size
	int n = atoi(argv[1]);
	int s = atoi(argv[2]);
	// int s = 128;
	double **A = new double *[n];
	double **B = new double *[n];
	double **C = new double *[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
		B[i] = new double[n];
		C[i] = new double[n];
	}

	// Initializing appropriate values to A, B AND C
	int ctr = 1;
	for (int i = 0; i < n; i++)
	{
		ctr = 1;
		for (int j = 0; j < n; j++)
		{
			A[i][j] = ctr;
			B[i][j] = n - ctr;
			C[i][j] = 0;
			ctr++;
		}
	}

	// ptr_blk is pointer to the block
	// ptr_in_blk_A is pointer in  the block in A
	// ptr_in_blk_B is pointer in  the block in B
	int N = n / s;
	if (N * s != n)
		N++;
	double temp = 0;

	struct timeval tv_before, tv_after;
	// col-wise
	gettimeofday(&tv_before, NULL);

#ifdef PAPI
	retval = PAPI_start(EventSet);
	if (retval != PAPI_OK)
		handle_error(retval);
#endif

	for (int ptr_blk = 0; ptr_blk < N; ptr_blk++)
	{
		for (int ptr_in_blk_A = 0; ptr_in_blk_A < n; ptr_in_blk_A++)
		{
			for (int ptr_in_blk_B = 0; ptr_in_blk_B < n; ptr_in_blk_B++)
			{

				temp = 0;
				for (int k = 0; k < s; k++)
				{
					if (s * ptr_blk + k == n)
						break;
					temp += A[ptr_in_blk_A][s * ptr_blk + k] * B[s * ptr_blk + k][ptr_in_blk_B];
					// cout<<ptr_in_blk_A<<" "<<s*ptr_blk+k<<" & "<<s*ptr_blk+k<<" "<<ptr_in_blk_B<<", ";
				}
				// cout<<endl;
				C[ptr_in_blk_A][ptr_in_blk_B] += temp;
			}
			// cout<<endl;
		}
		//  cout<<endl;
		// display(C,n);
	}

#ifdef PAPI
	retval = PAPI_stop(EventSet, values);
	if (retval != PAPI_OK)
		handle_error(retval);
#endif
	gettimeofday(&tv_after, NULL);
	printf("Col-wise time(n=%d): %ld (us)\n", n, ((tv_after.tv_sec - tv_before.tv_sec) * 1000000L + tv_after.tv_usec) - tv_before.tv_usec);

#ifdef PAPI
	float ratio = values[0] / (float)(values[1]);
	printf("total L1 misses:%lld total L2 misses:%lld total instructions:%lld total cycles:%lld\n", values[0], values[1], values[3], values[2]);
#endif

	// display function to display values of C
	display(C, n);

	for (int i = 0; i < n; i++)
	{
		delete[] A[i];
		delete[] B[i];
		delete[] C[i];
	}
	delete[] A;
	delete[] B;
	delete[] C;
}