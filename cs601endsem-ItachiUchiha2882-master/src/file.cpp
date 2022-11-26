#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double pi = 3.14159265358979323846;

double Exp(double x)
{
  double result = double(pi * x) / 2.0;
  return cos(result);
}

int main()
{
  /* Assumptions: 
      we have changed weights w1, w2 are still w1 and w2. w3's value becomes w4 and w4 becomes w3.
      for zeta,
        zeta1 is zeta2 now, zeta2 is zeta1 now and others are still same.
      This changes are made with reference to wikipedia.
  */  
  long double w1 = 0.347854845;
  long double w4 = w1;
  long double w2 = 0.652145155;
  long double w3 = w2;
  long double x3 = 0.3399810435;
  long double x4 = 0.8611363116;
  long double integral = 0.0;

  integral = w1 * Exp(-x4) + w2 * Exp(-x3) + w3 * Exp(x3) + w4 * Exp(x4);

  cout << setprecision(10);

  double trueval = 1.273239544735163; // 4/pi
  double approxval = integral;
  double abserror = fabs(trueval - approxval);
  double percenterror = (abserror)*100.0 / trueval;
  // cout << "pi: " << pi << endl;
  cout << "Integrating over [-1, 1], we get value: " << approxval << endl;
  cout << "Actual value: " << trueval << endl;
  cout << "Absolute error: " << abserror << endl;
  cout << "Percent error: " << percenterror << endl;

  return 0;
}