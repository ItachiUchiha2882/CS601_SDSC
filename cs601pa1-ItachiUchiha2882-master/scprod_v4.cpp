#include"scprod_v4.h"
double cs601::ddot(int dim, double vec1[], double vec2[]) {
	double result=0.;
	for(int i=0;i<dim;i++) {
		result += (vec1[i] * vec2[i]);
	}
	return result;
}

