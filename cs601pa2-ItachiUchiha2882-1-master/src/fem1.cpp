#include <iomanip>
#include <cmath>
#include <iostream>
#include <fstream>
#include <functional>
using namespace std;
double integrate(double a, double b, function<double(int, double, double)> f1,function<double(int, double, double)> f2,function<double(int, double, double)> f3,int i1,int i2,int i3,double le){
       //Here we implement gauss quadriture rule using 3 part functions namly f1,f2,f3
    double p = (b - a) / 2;
    double q = (b + a) / 2;

    double sum = 0;

    sum += f1(i1,p * sqrt(1 / 3) + q,le)*f2(i2,p * sqrt(1 / 3) + q,le)*f3(i3,p * sqrt(1 / 3) + q,le);
    sum += f1(i1,-1 * p * sqrt(1 / 3) + q,le)*f2(i2,p * sqrt(1 / 3) + q,le)*f3(i3,p * sqrt(1 / 3) + q,le);

    return p * sum;
}

double func_n(int i, double x, double le){
        //function for N i.e. shape function 
    if(i==1) return 1-x/le;
    if(i==2) return x/le;
    return 0;
}
double areaf(int i, double x, double le){
    //function for variable area function 
    return 1+x/(le*i);  
}
double I(int i, double x, double le){
    //for identity function
    return 1;
}

double func_dn(int i, double x, double le){
    //function for dN i.e. differentiated shape function
    if(i==1) return -1/le;
    if(i==2) return 1/le;
    return 0;
}
double func_anlitical_soln_const_area(double x, double f,double a, double y){
    //func to generate analitical solution with constant area
    return f*x/(a*y);
}
double func_anlitical_soln_var_area(double x, double f,double a, double y,double l){
            //func to generate analitical solution with variable area

    return f*l*log(1+x/l)/(a*y);
}
// create a class
class domain
{
//class  for element

public:
    int elementindex;
    double xa;
    //starting x
    double xb;
    //ending x
    double k[2][2];
    //stiffness matrix
    double b[2];
    //body force vector
   

public:
    void domainfoo(double x_a, double x_b, double le, int index, double E, double a, double fba)
    {
        //for 
        xa = x_a;
        xb = x_b;
        // double d = xb - xa;
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
       
       
    }
    
};
int N=8;
// function to find rms value
double rmsValue(double arr1[], double arr2[])
{
	// double square1 = 0.0, square2 = 0.0;
	double diff = 0.0, root = 0.0;
	// Calculate square.
	
	for (int i = 0; i < N; i++) {
		diff += pow(arr1[i] - arr2[i], 2);
	}

	// Calculate Root.
	root = sqrt(diff);
	return root;
}

int main()
{ 
    // creating the file called 'file.txt'.
    ofstream MyFile("../file.txt");
    //N: number of nodes
    int N = 9;
    //length of rod
    double L = 0.5;
    //length of element
    double le = L / (N-1);
    double l_a = 0;
    double l_b = le;
    //youngs modulus
    double E = 70000000000;
    //area
    double A = 0.00125;
    //force at x=0
    double f = 5000;

    domain rod_element[N-1];
    int i = 0;
    double temp=le;
    cout<<"For node1, x is 0"<<endl;
    MyFile<<"For node1, x is 0"<<endl;
    while (i < N-1)
    {
        // rod_element[i].elementindex = 42;
        // rod_element[i].xa = 30.8;
        // rod_element[i].xb = 19.2;
       
        cout<<"For node"<<i+2<<", x is "<<temp<<endl;
        MyFile<<"For node"<<i+2<<", x is "<<temp<<endl;
        
        temp+=le;
        i++;
    }
    cout<<"\n";
    MyFile<<"\n";
    i=0;
    while (i < N-1)
    {
        rod_element[i].domainfoo(l_a, l_b, le, i, E, A, f);
        cout<<"For element index "<<i+1<<", xa & xb are "<<l_a<<" & "<<l_b<<endl;
        MyFile<<"For element index "<<i+1<<", xa & xb are "<<l_a<<" & "<<l_b<<endl;
        l_a += le;
        l_b += le;
        i++;
    }
    cout<<"\n";
    MyFile<<"\n";
    // assign values to data members
    double kg[N][N];
    //stiffness matrix global 
    double bg[N];
    //body force vector global
    i = 0;
    while (i < N)
    {
        int j = 0;
        while (j < N)
        {
            kg[i][j] = 0;
            j++;
        }
        bg[i] = 0;
        i++;
    }
    double x[N - 1];
    //displacement array
    // double fg[n];
    double f1 = 5000;
    // double u[N];
    double a[N - 1][N];
    //the matrix for applying gauss elimination
    int m = 0;
    while (m < N)
    {
        //copying elemental k and b into global respectivly
        kg[m][m] += rod_element[m].k[0][0];
        kg[m][m + 1] += rod_element[m].k[0][1];
        kg[m + 1][m] += rod_element[m].k[1][0];
        kg[m + 1][m + 1] += rod_element[m].k[1][1];
        bg[m] += rod_element[m].b[0];
        bg[m + 1] += rod_element[m].b[1];
        m++;
    }
   //copying global K matix in a workspace matrix
    i = 0;
    while (i < N - 1)
    {
        int j = 0;
        while (j < N - 1)
        {
            a[i][j] = kg[i][j];
            // cout << a[i][j] << setw(16);
            // MyFile << a[i][j] << setw(16);
        
            j++;
        }
        // cout << "\n";
        // MyFile << "\n";
        i++;
    }
    // cout << "\n";
    // MyFile << "\n";
    //copying global B matrix in a workspace matrix
    int j = 0;
    while (j < N - 1)
    {
        a[j][N - 1] = bg[j];
        j++;
    }
    //adding force to matrix a
    a[0][N-1]+=f1;
    //...........
    //doing GAUSS Elimination
    int n = N - 1;
    int k;
    for (i = 0; i < n; i++) // Pivotisation
        for (k = i + 1; k < n; k++)
            if (abs(a[i][i]) < abs(a[k][i]))
                for (j = 0; j <= n; j++)
                {
                    double temp = a[i][j];
                    a[i][j] = a[k][j];
                    a[k][j] = temp;
                }
    cout << "The matrix after Pivotisation is:\n";
    MyFile << "The matrix after Pivotisation is:\n";
    for (i = 0; i < n; i++) // print the new matrix
    {
        for (j = 0; j <= n; j++){
            cout << a[i][j] << setw(16);
            MyFile << a[i][j] << setw(16);
        }
        cout << "\n";
        MyFile << "\n";
    }
    for (i = 0; i < n - 1; i++) // loop to perform the gauss elimination
        for (k = i + 1; k < n; k++)
        {
            double t = a[k][i] / a[i][i];
            for (j = 0; j <= n; j++)
                a[k][j] = a[k][j] - t * a[i][j]; // make the elements below the pivot elements equal to zero or elimnate the variables
        }

    cout << "\n\nThe matrix after gauss-elimination is as follows:\n";
    MyFile << "\n\nThe matrix after gauss-elimination is as follows:\n";
    for (i = 0; i < n; i++) // print the new matrix
    {
        for (j = 0; j <= n; j++){
            cout << a[i][j] << setw(16);
            MyFile << a[i][j] << setw(16);
        }
        cout << "\n";
        MyFile << "\n";
    }
    for (i = n - 1; i >= 0; i--) // back-substitution
    {                            // x is an array whose values correspond to the values of displacement/delta L
        x[i] = a[i][n];          // make the variable to be calculated equal to the rhs of the last equation
        for (j = i + 1; j < n; j++)
            if (j != i) // then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
                x[i] = x[i] - a[i][j] * x[j];
        x[i] = x[i] / a[i][i]; // now finally divide the rhs by the coefficient of the variable to be calculated
    }
    cout << "\nThe values of the variables(U) are as follows:\n";
    MyFile << "\nThe values of the variables(U) are as follows:\n";
    for (i = 0; i < n; i++){
        cout << x[i] << endl; 
        MyFile << x[i] << endl;
    }
    //.......
    double anlitcal_sol_cont_area[N];
    double anlitcal_sol_var_area[N];
    
    double temp_x=L;
           cout << "N:"<< N<<endl;
           MyFile << "N:"<< N<<endl;

    for (i = 0; i < N; i++) // print the  Analytical solution  For constant and variable area
    {
        anlitcal_sol_cont_area[i]=func_anlitical_soln_const_area(temp_x,f1,A,E);
        anlitcal_sol_var_area[i]=func_anlitical_soln_var_area(temp_x,f1,A,E,L);
        temp_x-=le;
       cout <<  anlitcal_sol_cont_area[i] <<"   "<< anlitcal_sol_var_area[i]<<endl;
       MyFile <<  anlitcal_sol_cont_area[i] <<"   "<< anlitcal_sol_var_area[i]<<endl;
    }
   // Calculation Norm2 / ROOT MEAN SQUARE ERROR FOR Analitical and numerical solution
    cout <<"\n"<<"RMS error: " << rmsValue(anlitcal_sol_cont_area, anlitcal_sol_var_area)<<endl;
    MyFile <<"\n"<<"RMS error: " << rmsValue(anlitcal_sol_cont_area, anlitcal_sol_var_area)<<endl;

    // closing the file
    MyFile.close();
    return 0;
}