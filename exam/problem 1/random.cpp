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

// Initialize some values
vector<double> min_x {0,0,0};
double min_val = f(min_x);

// Generate a new random vector following the ocnstraints given by the problem
vector<double> gen_x(){
    vector<double> ret(3);
    for(int i=0; i<3; i++) ret[i] = unif(re);
    return ret;
}

int main(){
    // Inifnite loop so the program can find the best value possible and the user can chose when to stop
    while(1){
        // Generate a new random vector x
        vector<double> x = gen_x();
        double v = f(x);

        // Check if the new vector is better than the previous
        if(v < min_val){
            // Update values
            min_val = v;
            min_x = x;

            cout << v << ": ";
            for(double vl: x) cout << vl << " ";
            cout << '\n';
        } 
    }
}