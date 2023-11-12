#include<bits/stdc++.h>
using namespace std;

#define tcs() int __TC; cin >> __TC; while(__TC--)
#define pb push_back
#define f first
#define s second
#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>
#define all(a) a.begin(), a.end()
#define coutv(v) for(auto __a: v) cout << __a << ' '
#define cinv(v) for(int __i=0; __i<v.size(); __i++) cin >> v[__i]

mt19937 gen;

double P(ll val, ll nval, double t){
    if(val < nval) return 1.0;
    else if(t == 0) return 0;
    else return exp(((double)(nval - val) / t));
}

double temp = 1000000, alpha = .98;
double T(double fact){
    //temp *= .98;
    return temp*fact*fact;
}

ll anealing(int n, vll &w, vector<vll> &mat, ll cap, vll m, vll out, vll val, ll v, ll curr){
    uniform_int_distribution<long long> dm, dout;
    uniform_real_distribution<double> rnd(0, 1);
    
    int k = 1e3;
    for(int i=0; i<k && out.size(); i++){
        double t = T(1.0 - ((double)(i+1)))/((double)k);
        dout = uniform_int_distribution<long long>(0, out.size()-1);
        int nx = dout(gen);
        
        if(curr + w[out[nx]] <= cap){
            v += val[out[nx]];
            curr += w[out[nx]];
            for(int i=0; i<n; i++) if(i != out[nx]) val[i] += mat[i][out[nx]];
            m.pb(out[nx]);
            out.erase(out.begin()+nx);

            continue;
        }

        dm = uniform_int_distribution<long long>(0, m.size()-1);
        int sw = dm(gen);
        bool swapped = 0;
        for(int i=0; i<20; i++){
            if(curr - w[m[sw]] + w[out[nx]] > cap) continue;

            ll nv = v - val[m[sw]] + val[out[nx]] - mat[out[nx]][m[sw]];
            if(P(v, nv, t) > rnd(gen)){
                swapped = 1;
                v = nv;
                curr += w[out[nx]] - w[m[sw]];
                for(int i=0; i<n; i++){
                    if(i != out[nx]) val[i] += mat[i][out[nx]];
                    if(i != m[sw]) val[i] -= mat[i][m[sw]];
                }
                m.pb(out[nx]);
                out.erase(out.begin()+nx);
                out.pb(m[sw]);
                m.erase(m.begin()+sw);
            }   
        }

        if(swapped) continue;
        
        ll nv = v - val[m[sw]];
        if(P(v, nv, t) > rnd(gen)){
            v = nv;
            curr -= w[m[sw]];
            for(int i=0; i<n; i++) if(i != m[sw]) val[i] -= mat[i][m[sw]];
            out.pb(m[sw]);
            m.erase(m.begin()+sw);
        }
    }
    return v;
}

int main(){
    string f_name;
    cin >> f_name;
    ifstream f(f_name);

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    gen.seed((unsigned ll)seed);

    int n;
    ll cap;
    f >> n >> cap;

    vll w(n);
    vector<vll> mat(n, vll(n));
    for(int i=0; i<n; i++) f >> w[i];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++) f >> mat[i][j];
    
    // initial solution
    vll m(n), out, val(n);
    ll v = 0, curr = 0;
    
    for(int i=0; i<n; i++){
        m[i] = i;
        curr += w[i];
    }

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            val[i] += mat[i][j];
            if(j >= i) v += mat[i][j];
        }

    while(curr > cap){
        int ix = -1;
        double mn = LONG_MAX;
        for(int i = 0; i<m.size(); i++) if(((double)val[m[i]]) / ((double) min(curr-cap, w[m[i]])) < mn){
            mn = ((double)val[m[i]]) / ((double) min(curr-cap, w[m[i]]));
            ix = i;
        }

        v -= val[m[ix]];
        curr -= w[m[ix]];
        for(int i=0; i<n; i++) if(i != m[ix]) val[i] -= mat[i][m[ix]];
        out.pb(m[ix]);
        m.erase(m.begin() + ix);
    }

    ll mn = LONG_MAX, mx = 0, r;
    double mean = 0;
    int it = 500;
    vector<ll> res(it);
    for(int i=0; i<it; i++){
        res[i] = anealing(n, w, mat, cap, m, out, val, v, curr);
        mn = min(mn, res[i]);
        mx = max(mx, res[i]);
        mean += (double)res[i] * (1.0/(double)it);
    }
    double diviation = 0, variance = 0;
    for(int i=0; i<it; i++){
        variance += (((double)res[i])-mean) * (((double)res[i])-mean) / ((double)it);
    }
    diviation = sqrt(variance);

    cout << mean << ' ' << mx << ' ' << mn << ' ' << diviation << '\n';
}