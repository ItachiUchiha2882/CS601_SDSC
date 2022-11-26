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
	if (argc != 2)
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

	int n = atoi(argv[1]);

	// int s= atoi(argv[2]);
	double **A = new double *[n];
	double **B = new double *[n];
	double **C = new double *[n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
		B[i] = new double[n];
		C[i] = new double[n];
	}

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

	struct timeval tv_before, tv_after;
	// col-wise
	gettimeofday(&tv_before, NULL);

#ifdef PAPI
	retval = PAPI_start(EventSet);
	if (retval != PAPI_OK)
		handle_error(retval);
#endif

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				C[i][j] += A[i][k] * B[k][j];

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
