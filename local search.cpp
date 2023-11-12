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

int main(){
    string f_name;
    cin >> f_name;
    ifstream f(f_name);

    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int n;
    ll cap, ans = 0, curr = 0;
    f >> n >> cap;

    vll w(n), val(n);
    vi m(n), out;
    for(int i=0; i<n; i++){
        m[i] = i;
        f >> w[i];
        curr += w[i];
    }

    vector<vll> mat(n, vll(n));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            f >> mat[i][j];
            val[i] += mat[i][j];
            if(j >= i) ans += mat[i][j];
        }

    while(curr > cap){
        int ix = -1;
        double mn = LONG_MAX;
        for(int i = 0; i<m.size(); i++) if(((double)val[m[i]]) / ((double) min(curr-cap, w[m[i]])) < mn){
            mn = ((double)val[m[i]]) / ((double) min(curr-cap, w[m[i]]));
            ix = i;
        }

        ans -= val[m[ix]];
        curr -= w[m[ix]];
        for(int i=0; i<n; i++) if(i != m[ix]) val[i] -= mat[i][m[ix]];
        out.pb(m[ix]);
        m.erase(m.begin() + ix);
    }



    while(1){
        ll mx = LONG_MIN;
        int ix = -1, jx = -1;

        for(int i=0; i<m.size(); i++){
            for(int j=0; j<out.size(); j++){
                if(val[out[j]] - mat[m[i]][out[j]] - val[m[i]] > mx && curr - w[m[i]] + w[out[j]] <= cap){
                    mx = val[out[j]] - mat[m[i]][out[j]] - val[m[i]];
                    ix = i, jx = j;
                }
            }
        }
        
        if(mx <= 0) break;

        ans -= val[m[ix]];
        curr += w[out[jx]] - w[m[ix]]; 
        for(int k=0; k<n; k++){
            if(m[ix] != k) val[k] -= mat[k][m[ix]];
            if(out[jx] != k) val[k] += mat[k][out[jx]];
        }
        ans += val[out[jx]];
        out.pb(m[ix]);
        m.pb(out[jx]);
        m.erase(m.begin() + ix);
        out.erase(out.begin() + jx);
    }

    cout << ans << '\n';
}