#include <bits/stdc++.h>
using namespace std;

double w1 = .5;
double w2 = .5;

// Define the function for the partial sums methode
double f(double x1, double x2){
    return (pow(abs(x1), .8) + 5*sin(x1*x1*x1) + pow(abs(x2), .8) + 5*sin(x2*x2*x2));
    return .5*(-10*exp(-0.2*sqrt(x1*x1+x2*x2))) + .5 * (pow(abs(x1), .8) + 5*sin(x1*x1*x1) + pow(abs(x2), .8) + 5*sin(x2*x2*x2));
}

int main(){
    // Find the minimum of the function in some range (Bruteforce)
    double step = .000001;
    double min = f(-5, -5), minix = -5, minjx = -5;
    for(double i = -1.1528; i<= -1.1527; i+=step)
    for(double j = -1.1538; j<= -1.1527; j+=step)
        if(f(i, j) < min) min = f(i, j), minix = i, minjx = j;

    // Print the best point found
    cout << fixed << setprecision(10) << minix << ", " << minjx << ": " << min << '\n';
}