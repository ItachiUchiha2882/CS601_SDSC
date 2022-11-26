#include <iostream>

using namespace std;

class domain
{
public:
    int elementindex;
    double xa;
    double xb;
    double k[2][2];
    double b[2];
    double k2[2][2];
    double b2[2];

public:
    // parameterized constructor to initialize variables
    void domainfoo(double x_a, double x_b, double le, int index, double E, double a, double fba)
    {
        xa = x_a;
        xb = x_b;
        double d = xb - xa;
        // k[0][0]=(E*a/(le*le))*(xb-xa);
        //k[0][0] = (E * a / (le * le)) * d;
        k[0][0] =E * a * integrate(xa,xb,&I,&func_dn,&func_dn,0,1,1,le);
        // k[0][1]=-1*(E*a/(le*le))*(xb-xa);
        //k[0][1] = -1 * (E * a / (le * le)) * d;
        k[0][1] =E * a * integrate(xa,xb,&I,&func_dn,&func_dn,0,1,2,le);
        k[1][0] = k[0][1];
        k[1][1] = k[0][0];
        // k[1][0]=-1*(E*a/(le*le))*(xb-xa);
        // k[1][1]=(E*a/(le*le))*(xb-xa);

        //b[0] = fba * (1 - (xb + xa) / 2 * le) * d;
        b[0] = fba*integrate(xa,xb,&I,&I,&func_n,0,1,1,le);
        //b[1] = fba * ((xb + xa) / 2 * le) * d;
        b[1] = fba*integrate(xa,xb,&I,&I,&func_n,0,1,2,le);
        //for linear area
        k2[0][0] =E * a *integrate(xa,xb,&areaf,&func_dn,&func_dn,0,1,1,le);
        k2[0][1] =E * a *integrate(xa,xb,&areaf,&func_dn,&func_dn,0,1,2,le);
        k2[1][0] = k[0][1];
        k2[1][1] = k[0][0];
        b2[0] = fba*integrate(xa,xb,&areaf,&I,&func_n,0,1,1,le);
        b2[1] = fba*integrate(xa,xb,&areaf,&I,&func_n,0,1,2,le);
    }
};
