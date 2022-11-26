//code to compute the root of x-cosx
#include<sstream>
#include<iostream>
#include"scprod_v4.h"
using namespace std;
int main(int argc, char* argv[]) {
	int dim;
	//if the vector dimension is not supplied through command-line arguments then accept it from keyboard.
	
	/*atoi returns 0 in case of invalid numbers entered as well as when a 0 is entered. 
	* Hence, to differentiate between the two scenarios and provide meaningful feedback to the
	* user, we use stringstreams. */

	if(argc != 2){
		cout << "Enter the vector dimension"<<endl;
		string dimstr;
		cin>>dimstr;
		istringstream ss;
		ss.str(dimstr);
		if(!(ss>>dim)) {
			cerr<<"Invalid number: "<<dimstr<<endl;
			return EXIT_FAILURE;
		} else if(!(ss.eof())) {
			cerr<<"Trailing characters present after the number: "<<dimstr<<endl;
			return EXIT_FAILURE;
		} 
		//cin >> dim;
	}
	else {
		istringstream ss(argv[1]);
		if(!(ss>>dim)) {
			cerr<<"Invalid number: "<<argv[1]<<endl;
			return EXIT_FAILURE;
		} else if(!(ss.eof())) {
			cerr<<"Trailing characters present after the number: "<<argv[1]<<endl;
			return EXIT_FAILURE;
		}
	}

	cout << "Value of dimension entered: "<<dim<<endl;
	
	double* vector1, *vector2;
	//allocate memory for vectors
	vector1 = new double[dim];
	vector2 = new double[dim];

	//initialize vectors
	for(int i=0;i<dim;i++) {
		vector1[i] = i+1;
		vector2[i] = i+1;
	}

	//multiply vectors and store the result in a new vector: call the function scprod
	/* The main function only needs to know how the function is called. Need not know how it is implemented.
	 * Hence, consult scprod_v4.h to know how the function is called. */
	double result=0.;
	result = cs601::ddot(dim, vector1, vector2);

	//print the product vector
	cout<<"Product of two vectors: "<<result<<endl;
	return 0;
}
