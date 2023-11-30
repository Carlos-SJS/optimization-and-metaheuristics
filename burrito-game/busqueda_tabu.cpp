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

vector<int> to_vec(ll v){
    vector<int> vec(15);
    for(int i=0; i<15; i++) vec[i] = v&1, v>>=1;
    return vec;
}

vector<int> busqueda_tabu(int it){
    vector<int> best, ans(t_pos.size(), 0);
    double best_v, val = eval(ans);
    best = ans, best_v = val;
    set<ll> tabu_table;
    tabu_table.insert(to_ll(ans));

    queue<ll> q;
    q.push(to_ll(ans));
    while(it--){
        double bn_val = LONG_LONG_MIN;
        int bn_ix = -1;
        for(int i=0; i<t_pos.size(); i++){
            ans[i] ^= 1;
            ll h = to_ll(ans);
            if(tabu_table.count(h)){
                ans[i] ^= 1;
                continue;
            }

            double nw = eval(ans);
            if(nw > bn_val){
                bn_val = nw;
                bn_ix = i;
            }
            ans[i] ^= 1;
        }

        if(bn_ix == -1){
            if(to_ll(ans) == q.front()) q.pop();
            ans = to_vec(q.front());
            break;
        }

        ans[bn_ix] ^= 1;
        val = bn_val; 
        tabu_table.insert(to_ll(ans));


        if(val > best_v){
            best_v = val;
            best = ans;
        }
    }
    return best;
}


int main(){
    srand(time(NULL));
    load_data();

    vector<int> ans = busqueda_tabu(1000);
    cout << "Expected gain: " << eval(ans) << "\nBurrito vector: ";
    for(int b: ans) cout << b << ' ';
    cout << '\n';
}