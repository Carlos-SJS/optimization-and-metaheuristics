#include <bits/stdc++.h>
using namespace std;

double h = 1e-5;
double eps = 1e-9;

string log_file = "levenberg/logs_p4.txt";

double f(vector<double> x){
    for(int i=0; i<x.size(); i++) x[i] = min(max(x[i], -8.0-2e-5), 8.0+2e-5);
    double ret = 0;
    for(int i=0; i<x.size(); i++) ret += (1.0/3.0)*(x[i]*x[i]*x[i]*x[i] - 16*x[i]*x[i] + 5*x[i]);
    return ret;
}

double df(vector<double> x, vector<int> var){
    x[var[0]] += h;
    
    double f1, f2;

    if(var.size() == 1) f1 = f(x);
    else f1 = df(x, vector<int>(var.begin()+1, var.end()));
    
    x[var[0]] -= 2*h;
    if(var.size() == 1) f2 = f(x);
    else f2 = df(x, vector<int>(var.begin()+1, var.end()));

    return (f1 - f2) / (2*h);
}

vector<double> gradient(vector<double> &x){
    vector<double> g(x.size());
    for(int i=0; i<x.size(); i++) g[i] = df(x, {i});
    return g;
}

vector<vector<double>> hessian(vector<double> x){
    vector<vector<double>> h(x.size(), vector<double>(x.size()));

    for(int i=0; i<x.size(); i++){
        for(int j=0; j<x.size(); j++)
            h[i][j] = df(x, {i,j});
    }

    return h;
}

vector<double> mult(vector<double> v, vector<vector<double>> mat){
    vector<double> res(v.size(), 0);
    for(int i=0; i<v.size(); i++){
        for(int j=0; j<v.size(); j++){
            res[i] += mat[i][j]*v[j];
        }
    }
    return res;
}

void mult(double v, vector<vector<double>> &mat){
    for(int i=0; i<mat.size(); i++){
        for(int j=0; j<mat[i].size(); j++){
            mat[i][j] *= -1;
        }
    }
}

void mult(double v, vector<double> &vec){
    for(double &val: vec) val*=v;
}

double det(vector<vector<double>> &mat){
    if(mat.size() == 1) return mat[0][0];
    
    double dt = 0;
    vector<vector<double>> new_mat(mat.size()-1, vector<double>(mat.size()-1));
    for(int i=0; i<mat.size(); i++){
        for(int j=0; j<mat.size(); j++) if(j != i)
            for(int k=1; k<mat.size(); k++)
                new_mat[k-1][j-(j > i? 1:0)] = mat[k][j];
        dt += mat[0][i] * det(new_mat);
    }
    return dt;
}

vector<vector<double>> inv(vector<vector<double>> &mat){
    double idt = 1/det(mat);
    for(vector<double> &r: mat)
        for(double &v: r)
                v *= idt;
    return mat;
}

void log_x(vector<double> &x, ofstream &of, int it){
    of << "iteration: " << it << "\n[";
    for(int i=0; i<x.size(); i++){
        if(i) of << ", ";
        of << x[i];
    }
    of << "]\nf(x) = " << f(x) << '\n';
}

vector<double> levenberg_marquadt(){
    ofstream of(log_file);

    vector<double> x{-8, -8, -8};
    double lambda = 1;

    int its = 0;

    while(1){
        its++;

        double fx = f(x);
        vector<vector<double>> hs = hessian(x);
        vector<double> gd = gradient(x);
        
        for(int i=0; i<hs.size(); i++) hs[i][i] += hs[i][i]*lambda;
        hs = inv(hs);   

        vector<double> s = mult(gd, hs);
        for(int i=0; i<x.size(); i++) x[i] -= s[i];
        for(int i=0; i<x.size(); i++) x[i] = max(min(x[i], 8.0), -8.0);

        if(f(x) < fx) lambda /= 2.0;
        else lambda *= 2.0;
        
        log_x(x, of, its);
        //cout << fx << " - " << f(x) << " = " << fx-f(x) << '\n';
        if(abs(f(x)-fx) < eps) break;
    }

    cout << "Iterations: " << its << '\n';
    of.close();
    return x;
}

int main(){
    vector<double> x = levenberg_marquadt();
    cout << "x = [";
    for(int i=0; i<x.size(); i++){
        if(i) cout << ", ";
        cout << x[i];
    }
    cout << "]\nf(x) = " << f(x) << '\n';
}
