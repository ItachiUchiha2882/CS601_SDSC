//code to compute the root of x-cosx
//trying commit with tag.
#include<cstdlib>
#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	int dim;
	//if the vector dimension is not supplied through command-line arguments then accept it from keyboard.
	if(argc != 2){
		cout << "Enter the vector dimension"<<endl;
		cin >> dim;
	}
	else {
		dim = atoi(argv[1]);
	}
	cout << "Value of dimension entered: "<<dim<<endl;
	
	int* vector1, *vector2;
	//allocate memory for vectors
	vector1 = new int[dim];
	vector2 = new int[dim];

	//initialize vectors
	for(int i=0;i<dim;i++) {
		vector1[i] = i+1;
		vector2[i] = i+1;
	}

	//multiply vectors and store the result in a int
	int result=0;
	for(int i=0;i<dim;i++) {
		int temp = (vector1[i] * vector2[i]);
		result = result + temp;
	}

	//print the product vector
	cout<<"Product of two vectors: "<<result<<endl;
	return 0;
}
