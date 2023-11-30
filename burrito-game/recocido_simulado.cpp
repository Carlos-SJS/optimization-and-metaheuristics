#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define x first
#define y second
#define f first
#define s second
#define pb push_back

double gain, t_cost;
vector<pair<double, double>> t_pos;
vector<pair<double, double>> d_pos;
vector<vector<pair<ll, ll>>> t_dem;
vector<ll> d_dem;

map<string, int> t_id, d_id;
mt19937 gen;


double P(ll val, ll nval, double t){
    if(val < nval) return 1.0;
    else if(t == 0) return 0;
    else return exp(((double)(nval - val) / t));
}

void load_data(){
    string st, id;
    pair<double, double> pt;
    ll dem, ix = 0;

    ifstream f("data/demand_node.txt");
    getline(f, st);
    while(f >> id >> st >> pt.x >> pt.y >> dem){
        d_pos.pb(pt), d_dem.pb(dem);
        d_id[id] = ix;
        ix++;
    }

    f.close();
    f.open("data/problem_data.txt");
    getline(f, st);
    double v;
    f >> gain >> v >> t_cost;
    gain -= v;


    ix = 0;
    f.close();
    f.open("data/truck_node.txt");
    getline(f, st);
    while(f >> id >> pt.x >> pt.y){
        t_pos.pb(pt);
        t_id[id] = ix;
        ix++;    
    }

    t_dem.resize(t_pos.size());
    f.close();
    f.open("data/demand_truck.txt");
    getline(f, st);
    //cout << s << '\n';
    while(f >> st >> id >> v >> dem){
        t_dem[t_id[id]].pb({d_id[st], dem});
    }

}

double eval(vector<int> &sol){
    vector<int> used(d_dem.size(), 0);
    double ev = 0;
    for(int i=0; i<sol.size(); i++){
        if(sol[i]){
            ev -= t_cost;
            for(auto p: t_dem[i]){
                int cnt = min(d_dem[p.f]-used[p.f], p.s);
                ev += gain*cnt;
                used[p.f] += cnt;
            }
        }
    }
    return ev;
}

ll to_ll(vector<int> &vec){
    ll ret = 0;
    for(int v: vec) ret <<= 1, ret += v;
    return ret;
}

vector<int> to_vec(ll v){
    vector<int> vec(15);
    for(int i=0; i<15; i++) vec[i] = v&1, v>>=1;
    return vec;
}

vector<int> recocido(){
    vector<int> ans(t_pos.size(), 0), best;
    double v = eval(ans), best_v;
    best = ans, best_v = v;
    int k = 10000;

    uniform_real_distribution<double> rnd(0, 1);

    double t = 3000, alpha = .99;

    for(int i=0; i<10000; i++){
        int ix = rand()%ans.size();

        ans[ix] ^= 1;
        ll nv = eval(ans);

        if(P(v, nv, t) > rnd(gen)){
            v = nv;
            if(v > best_v) best_v = v, best = ans;
        }else ans[ix] ^= 1;

        t *= alpha;
    }

    return ans;
}


int main(){
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    gen.seed(seed);
    srand(time(NULL));
    load_data();

    double mx = LONG_LONG_MIN, mn = LONG_LONG_MAX, mean = 0;
    int its = 100;
    for(int i=0; i<its; i++){
        vector<int> ans = recocido();
        double v = eval(ans);
        mn = min(mn, v);
        mx = max(mx, v);
        mean += v/((double)its);
    }

    cout << "Max: " << mx << '\n';
    cout << "Min: " << mn << '\n';
    cout << "Mean: " << mean << '\n';
}