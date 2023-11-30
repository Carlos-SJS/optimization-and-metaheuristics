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


int main(){
    srand(time(NULL));
    load_data();

    double mx = 0;
    vector<int> vec(15, 0);
    for(ll i = 0; i<(1<<15); i++){
        ll cp = i;
        for(int j = 0; j<15; j++) vec[j] = cp&1, cp>>=1;
        mx = max(mx, eval(vec));
    }

    cout << "Absolute maximum: " << mx << '\n';
}