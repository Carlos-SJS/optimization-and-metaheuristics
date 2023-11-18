#include<bits/stdc++.h>
using namespace std;

#define tcs() int _TC; cin >> __TC; while(_TC--)
#define pb push_back
#define f first
#define s second
#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>
#define all(a) a.begin(), a.end()
#define coutv(v) for(auto __a: v) cout << __a << ' '
#define cinv(v) for(int _i=0; __i<v.size(); __i++) cin >> v[_i]

double local_search(int n, int k, ll min_w, ll max_w, vll w, vector<vector<double>> mat, vector<pair<ll, int>> its){
    vector<vi> g(k);
    vll gw(k, 0);
    vector<double> gb(k, 0), val(n, 0);

    priority_queue<pair<ll, int>> pq;
    for(int i=0; i<k; i++) pq.push({min_w, i});

    for(int i=0; i<n; i++){
        auto ct = pq.top();
        pq.pop();
        g[ct.second].pb(its[i].s);
        ct.f -= its[i].f;
        pq.push(ct);
    }

    if(pq.top().f > 0) cout << "f'd up!\n";
    double ans = 0;
    for(int i=0; i<k; i++){
        for(int j=0; j<g[i].size(); j++){
            gw[i] += w[g[i][j]];
            for(int l=j+1; l<g[i].size(); l++)
                gb[i] += mat[g[i][j]][g[i][l]];
        }
        cout << gw[i] << ' ' << gb[i] << '\n';
        ans += gb[i];
    }

    for(int i=0; i<500; i++){
        int gix = rand()%k;
        int eix = -1;
        for(int j=0; j<20; j++){
            int ix = rand()%g[gix].size();
            if(gw[gix] - w[g[gix][ix]] < min_w) continue;
            eix = ix;
            break;
        }

        if(eix == -1) continue;
        for(int j=0; j<500; j++){
            int g2ix = rand()%k;
            if(g2ix == gix || gw[g2ix] + w[g[gix][eix]] > max_w) continue;
            gw[gix] -= w[g[gix][eix]];
            gw[g2ix] += w[g[gix][eix]];
            g[g2ix].pb(g[gix][eix]);
            g[gix].erase(g[gix].begin() + eix);
            break;
        }
    }
    
    ans = 0;
    for(int i=0; i<k; i++){
        gw[i] = 0, gb[i] = 0;
        for(int j=0; j<g[i].size(); j++){
            gw[i] += w[g[i][j]];
            for(int l=j+1; l<g[i].size(); l++)
                gb[i] += mat[g[i][j]][g[i][l]];
        }
        ans += gb[i];
    }

    cout << "Ready to roll\n";

    while(1){
        double best_v = 0;
        bool single = 0;
        pair<int, int> a, b;
        for(int i=0; i<k; i++){
            for(int j=0; j<g[i].size(); j++)
                for(int l=0; l<k; l++)
                    if(l != i){
                        for(int m=0; m<g[l].size(); m++){
                            // swap {i, j} -> {l, m}
                            ll wa = gw[i] + w[g[l][m]] - w[g[i][j]], wb = gw[l] + w[g[i][j]] - w[g[l][m]];
                            if(wa > max_w || wb > max_w || wa < min_w || wb < min_w) continue;
                            
                            double ex = ans;
                            for(int o=0; o<g[i].size(); o++) if(o != j) ex += mat[g[l][m]][g[i][o]] - mat[g[i][j]][g[i][o]];
                            for(int o=0; o<g[l].size(); o++) if(o != m) ex += mat[g[i][j]][g[l][o]] - mat[g[l][m]][g[l][o]];
                            if(ex > best_v){
                                best_v = ex;
                                single = 0;
                                a = {i, j}, b = {l, m};
                            }
                        }
                    
                        ll wa = gw[i] - w[g[i][j]], wb = gw[l] + w[g[i][j]];
                        if(wa < min_w || wb < min_w || wa > max_w || wb > max_w) continue;

                        double ex = ans;
                        for(int m=0; m<g[i].size(); m++) ex -= mat[g[i][j]][g[i][m]];
                        for(int m=0; m<g[l].size(); m++) ex += mat[g[i][j]][g[l][m]];

                        if(ex > best_v){
                            best_v = ex;
                            single = 1;
                            a = {i, j}, b = {l, 0};
                        }
                    }
        }

        if(best_v < ans) break;
        ans = best_v;

        if(single){
            gw[a.f] -= w[g[a.f][a.s]], gw[b.f] += w[g[a.f][a.s]];
            g[b.f].pb(g[a.f][a.s]);
            g[a.f].erase(g[a.f].begin() + a.s);
            continue;
        }
        gw[a.f] += w[g[b.f][b.s]] - w[g[a.f][a.s]];
        gw[b.f] += w[g[a.f][a.s]] - w[g[b.f][b.s]];
        
        //cout << ans << '\n';
        g[b.f].pb(g[a.f][a.s]);
        g[a.f].pb(g[b.f][b.s]);
        g[a.f].erase(g[a.f].begin() + a.s);
        g[b.f].erase(g[b.f].begin() + b.s);
    }
    
    for(int i=0; i<k; i++){
        cout << "(" << g[i].size() << "): ";
        for(int j=0; j<g[i].size(); j++) cout << g[i][j] << ' ';
        cout << '\n';
    }

    cout << "Expected ans: " << ans << '\n';
    ans = 0;
    for(int i=0; i<k; i++){
        ll exw = gw[i];
        gw[i] = 0; gb[i] = 0;
        for(int j=0; j<g[i].size(); j++){
            gw[i] += w[g[i][j]];
            for(int l=j+1; l<g[i].size(); l++)
                gb[i] += mat[g[i][j]][g[i][l]];
        }
        if(exw != gw[i]) cout << "(f'd weight) ";
        cout << gw[i] << ' ' << gb[i] << '\n';
        ans += gb[i];
    }
    //cout << fixed << setprecision(10) << ans << '\n';
    return ans;
}

int main(){
    cout << fixed << setprecision(10);
    freopen("input/case1.txt", "r", stdin);
    srand(time(NULL));
    int n, k;
    cin >> n >> k;

    ll min_w, max_w;
    cin >> min_w >> max_w;

    vector<pair<ll, int>> its(n);
    vll w(n);
    for(int i=0; i<n; i++){
        cin >> w[i];
        its[i] = {w[i], i};
    }

    vector<vector<double>> mat(n, vector<double>(n, 0));
    int u, v;
    double b;
    while(cin >> u >> v >> b) mat[u][v] += b, mat[v][u] += b;

    sort(all(its));
    reverse(all(its));

    double mean = 0, max_ans = LONG_LONG_MIN, min_ans = LONG_LONG_MAX;
    int it = 100;
    for(int i=0; i<it; i++){
        double r = local_search(n, k, min_w, max_w, w, mat, its);
        //cout << r << '\n';
        max_ans = max(max_ans, r);
        min_ans = min(min_ans, r);
        mean = 1.0/((double)it) * r;
    }
    cout << "Mean: " << mean << '\n';
    cout << "Max: " << max_ans << '\n';
    cout << "Min: " << min_ans << '\n';
}