#include<bits/stdc++.h>
using namespace std;

// Define objects to get random values
double low = 0;
double upp = 1;
std::uniform_real_distribution<double> unif(low,upp);
std::default_random_engine re;

// Define the values given by the problem statemnt
vector<double> alpha {1.0, 1.2, 3.0, 3.2};
vector<vector<double>> a {
    {3.0, 10, 30},
    {0.1, 10, 35},
    {3.0, 10, 30},
    {0.1, 10, 35}
};

vector<vector<double>> p {
    {3689, 1170, 2673},
    {4699, 4387, 7470},
    {1091, 8732, 5547},
    {381, 5743, 8828}
};

double pm = 1e-4;


// Evaluate the function f with the given vector x
double f(vector<double> x){
    double ret = 0;
    for(int i=0; i<4; i++){
        double tmp = 0;
        for(int j=0; j<3; j++){
            tmp += a[i][j]*(x[j]-pm*p[i][j])*(x[j]-pm*p[i][j]);
        }
        ret = exp(-tmp)*alpha[i];
    }
    return -ret;
}

// Generate a new random vector following the ocnstraints given by the problem
vector<double> gen_x(){
    vector<double> ret(3);
    for(int i=0; i<3; i++) ret[i] = unif(re);
    return ret;
}

// Initializa some values
vector<double> x = gen_x(), xh(3);
vector<double> b{0,0,0};
vector<double> d;

double min_val = f(x);

int main(){
    // Inifnite loop so the program can find the best value possible and the user can chose when to stop
    while(1){

        //Do the stuff that random localized search should do
        d = gen_x();
        bool valid = 1;
        for(int i=0; i<3; i++){
            xh[i] = x[i] + b[i] + d[i];
            if(xh[i] < 0 || xh[i] > 1){
                valid = 0;
                break;
            }
        }
        if(!valid) continue;

        double v = f(xh);

        // Check if x hat is better than the previos best x found
        if(v < min_val){
            // Update data acording to localized search algoritm
            min_val = v;
            x = xh;
            for(int i=0; i<3; i++) b[i] = .2*b[i] + .4*d[i];

            cout << v << ": ";
            for(double vl: x) cout << vl << " ";
            cout << '\n';
        }
    }
}