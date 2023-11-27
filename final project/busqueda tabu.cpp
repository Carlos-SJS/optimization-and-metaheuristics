#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define ll long long
#define pb push_back
#define all(a) a.begin(), a.end()

double const PI = 3.14159265359;

// KD-Tree implementation to find nearest point in a set to a given point
// given a set of points, answer queries of nearest point in O(log(n))
struct pt{
	double x,y;
	pt(double x, double y):x(x),y(y){}
	pt(){}
	double norm2(){return *this**this;}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator /(double t){return pt(x/t,y/t);}
	double operator*(pt p){return x*p.x+y*p.y;}
	bool operator<(pt p)const{return x<p.x|(x==p.x&&y<p.y);}
	bool operator==(pt p)const{return p.x==x&&p.y==y;}
};

double INF=1e9;

bool onx(pt a, pt b){return a.x<b.x;}
bool ony(pt a, pt b){return a.y<b.y;}
struct Node {
	pt pp;
	double x0=INF, x1=-INF, y0=INF, y1=-INF;
	Node *first=0, *second=0;
	double distance(pt p){
		double x=min(max(x0,p.x),x1);
		double y=min(max(y0,p.y),y1);
		return (pt(x,y)-p).norm2();
	}
	Node(vector<pt>&& vp):pp(vp[0]){
		for(pt p:vp){
			x0=min(x0,p.x); x1=max(x1,p.x);
			y0=min(y0,p.y); y1=max(y1,p.y);
		}
		if(vp.size()>1){
			sort(all(vp),x1-x0>=y1-y0?onx:ony);
			int m=vp.size()/2;
			first=new Node({vp.begin(),vp.begin()+m});
			second=new Node({vp.begin()+m,vp.end()});
		}
	}
};
struct KDTree {
	Node* root;
    KDTree(){}
	KDTree(const vector<pt>& vp):root(new Node({all(vp)})) {}
	pair<double,pt> search(pt p, Node *node){
		if(!node->first){
			//avoid query point as answer
			//if(p==node->pp) {INF,pt()};
			return {(p-node->pp).norm2(),node->pp};
		}
		Node *f=node->first, *s=node->second;
		double bf=f->distance(p), bs=s->distance(p);
		if(bf>bs)swap(bf,bs),swap(f,s);
		auto best=search(p,f);
		if(bs<best.f) best=min(best,search(p,s));
		return best;
	}
	pair<double,pt> nearest(pt p){return search(p,root);}
};

struct accident{
    pt pos;
    int weight;

    accident(pt pos, int w): pos(pos), weight(w){}
};

vector<pt> hospitals;
vector<accident*> accidents;

KDTree kd_hospitals;
KDTree kd_ambulances;

int get_weight(int heridas, int muertes, int tipo){
    return 1;
}

pt lat_lon_to_cartesian(double lat, double lon){
    double lon_origin = -102.283387471420;
    double lat_origin = 21.882583053608;
    //Convert latitude and longitude from degrees to radians
    lat = lat * PI / 180.0;
    lon = lon * PI / 180.0;
    lat_origin = lat_origin * PI / 180.0;
    lon_origin = lon_origin * PI / 180.0;

    //Radius of the Earth in kilometers (mean value)
    double R = 6371.0;

    //Equirectangular projection
    double x = R * (lon - lon_origin) * cos(0.5 * (lat + lat_origin));
    double y = R * (lat - lat_origin);

    return pt(x, y);
}

pair<double, double> caretsian_to_lat_lon(pt p){
    //Radius of the Earth in kilometers (mean value)
    double R = 6371.0;
    double lon_origin = -102.283387471420;
    double lat_origin = 21.882583053608;

    double lat = p.y / R + lat_origin;
    double lon = (p.x / R) / cos(0.5 * (lat + lat_origin)) + lon_origin;

    lat = lat*180/PI;
    lon = lon*180/PI;

    return {lat, lon};
}

// Load Accident and Hospital data from the csv files and save it in vectors to use later
void load_data(){
    ifstream f("accident_data.csv");
    string s;
    double lat, lon, heridas, muertes, tipo;
    getline(f, s);

    while(f >> heridas >> muertes >> tipo >> lon >> lat){
        pt point = lat_lon_to_cartesian(lat, lon);
        accident* a = new accident(point, get_weight(heridas, muertes, tipo));
        accidents.pb(a);
    }

    f.close();

    ifstream f2("hospital_data.csv");
    getline(f2, s);

    while(f2 >> lon >> lat){
        pt point = lat_lon_to_cartesian(lat, lon);
        hospitals.pb(point);
    }

    kd_hospitals = KDTree(hospitals);
    f2.close();
}

// Generate initial solution placing all ambulances equally spaced
// in a circle arround the average accident point, using average distance to the center point as radius
void gen_initial_solution(vector<pt> &amb, int k){
    double d_angle = 2*PI / (double)k, angle = 0, radius = 4.049577795121;
    for(int i=0; i<k; i++){
        amb[i] = {sin(angle)*radius, cos(angle)*radius};
    }
}

double evaluate(vector<pt> &amb, double &min_d, double &max_d){
    kd_ambulances = KDTree(amb);

    double total_cost = 0;
    for(auto a : accidents){
        double dist_ambulance = kd_ambulances.nearest(a->pos).f;
        double dist_hospital = kd_hospitals.nearest(a->pos).f;

        double cost = sqrt(dist_ambulance) + sqrt(dist_hospital);
        min_d = min(cost, min_d);
        max_d = max(cost, max_d);
        total_cost += cost;
    }

    return total_cost;
}

double cuad_evaluate(vector<pt> &amb){
    kd_ambulances = KDTree(amb);

    double total_cost = 0;
    for(auto a : accidents){
        double dist_ambulance = kd_ambulances.nearest(a->pos).f;
        double dist_hospital = kd_hospitals.nearest(a->pos).f;

        double cost = sqrt(dist_ambulance) + sqrt(dist_hospital);
        total_cost += cost*cost*a->weight;
    }

    return total_cost;
}

pair<size_t, size_t> hash_vector(std::vector<pt> vec) {
    std::hash<double> hasher;
    size_t result1 = 0, result2 = 0;
    sort(all(vec), [](pt &a, pt &b){
        return a.x<b.x|(a.x==b.x&&a.y<b.y);
    });
    for (const auto& value : vec) {
        // Combine hash values using bitwise XOR
        result1 ^= hasher(value.x) + 0x9e3779b9 + (result1 << 6) + (result1 >> 2);
        result1 ^= hasher(value.y) + 0x9e3779b9 + (result1 << 6) + (result1 >> 2);
        result2 ^= hasher(value.x) + 0x2e3279f1 + (result2 << 6) + (result2 >> 2);
        result2 ^= hasher(value.y) + 0x2e3279f1 + (result2 << 6) + (result2 >> 2);
    }

    return {result1, result2};
}

// K is the number of ambulances to place
// it is the allowed number of iterations
vector<pt> tabu_search(int k, int it, vector<pt> ambulances, double a_dist){
    cout << k << " " << a_dist << '\n';
    const int directions = 16;
    const double rotation_angle = 2*PI/((double)directions); // Number of directions an ambulance can go for finding neighbors

    vector<pt> dirs(directions);
    for(int i=0; i<directions; i++) dirs[i] = pt(sin(i*rotation_angle)*a_dist, cos(i*rotation_angle)*a_dist);

    vector<pt> best_ambulances = ambulances;

    double best, current;
    best = current = cuad_evaluate(ambulances);


    set<pair<size_t, size_t>> tabu_tbl;
    tabu_tbl.insert(hash_vector(ambulances));

    while(it--){
        double best_neighbor = LONG_LONG_MAX, nw = -1;
        pair<int, int> best_dir;
        pair<size_t, size_t> best_h;
        for(int j=0; j<k; j++){
            pt cp = ambulances[j];
            for(int i=0; i<directions; i++){
                ambulances[j] = ambulances[j] + dirs[i];
                pair<size_t, size_t> h = hash_vector(ambulances);
                if(tabu_tbl.count(h)){
                    ambulances[j] = cp;
                    continue;
                }
                nw = cuad_evaluate(ambulances);
                ambulances[j] = cp;

                if(nw < best_neighbor){
                    best_neighbor = nw;
                    best_dir = {j, i};
                    best_h = h;
                }
            }
        }

        if(nw == -1) break;

        ambulances[best_dir.f] = ambulances[best_dir.f] + dirs[best_dir.s];
        current = best_neighbor;
        tabu_tbl.insert(best_h);

        if(current < best){
            best = current;
            best_ambulances = ambulances;
            //cout << best << '\n';
        }
    }
    return best_ambulances;
}

void tabu_search(int k, vector<pt> &ambulances){
    gen_initial_solution(ambulances, k);
    ambulances = tabu_search(k, 200, ambulances, 1);
    ambulances = tabu_search(k, 100, ambulances, .5);
    ambulances = tabu_search(k, 20, ambulances, 1);
    ambulances = tabu_search(k, 100, ambulances, .1);
    ambulances = tabu_search(k, 20, ambulances, 1);
    ambulances = tabu_search(k, 100, ambulances, .05);
    ambulances = tabu_search(k, 20, ambulances, 1);
    ambulances = tabu_search(k, 100, ambulances, .01);
    ambulances = tabu_search(k, 20, ambulances, 1);
    ambulances = tabu_search(k, 100, ambulances, .001);
    ambulances = tabu_search(k, 20, ambulances, 1);
}

int main(){
    load_data();
    
    int k = 15;
    vector<pt> ambulances(k);
    tabu_search(k, ambulances);

    double min_dist = LONG_LONG_MAX, max_dist = LONG_LONG_MIN;
    double distance_sum = evaluate(ambulances, min_dist, max_dist);
    
    cout << "Suma de distancias (amulancia->accidente + accidente->hospital): " << distance_sum << '\n';
    cout << "Minima distancia: " << min_dist << '\n';
    cout << "Maxima distancia: " << max_dist << '\n';
    cout << "Distancia promedio: " << distance_sum/(double)accidents.size() << '\n';
    cout << '\n';

    cout << "Ambulancias (Longitud, Latitud): \n";
    for(int i=0; i<k; i++){
        auto p = caretsian_to_lat_lon(ambulances[i]);
        cout << p.s << ", " << p.f << '\n';
    }
}

// 1 5 10 15 25 50 75 