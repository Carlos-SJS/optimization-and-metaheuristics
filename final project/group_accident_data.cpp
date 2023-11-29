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

    void delete_tree(Node* n){
        if(n->first!=0) delete_tree(n->first);
        if(n->second!=0) delete_tree(n->second);
        delete(n);
    }
    void delete_tree(){delete_tree(root);}
};

struct accident{
    pt pos;
    int weight;

    accident(pt pos, int w): pos(pos), weight(w){}
};

vector<pt> hospitals;
vector<accident*> accidents;
vector<pt> amb;

int get_weight(int heridas, int muertes, int tipo){
    return 1;
}

// Covert lat,lon to x,y in Km
pt lat_lon_to_cartesian(double lat, double lon){
    double lon_origin = -102.283387471420;
    double lat_origin = 21.882583053608;

    lat = lat * PI / 180.0;
    lon = lon * PI / 180.0;
    lat_origin = lat_origin * PI / 180.0;
    lon_origin = lon_origin * PI / 180.0;

    double R = 6371.0;

    double x = R * (lon - lon_origin) * cos(0.5 * (lat + lat_origin));
    double y = R * (lat - lat_origin);

    return pt(x, y);
}

// Convert x,y to lat lon
pair<double, double> caretsian_to_lat_lon(pt p){
    double R = 6371.0;
    double lon_origin = -102.283387471420;
    double lat_origin = 21.882583053608;
    lat_origin = lat_origin * PI / 180.0;
    lon_origin = lon_origin * PI / 180.0;

    double lat = p.y / R + lat_origin;
    double lon = (p.x / R) / cos(0.5 * (lat + lat_origin)) + lon_origin;

    lat = lat*180.0/PI;
    lon = lon*180.0/PI;

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

    f2.close();

    ifstream f3("amb_data.csv");

    while(f3 >> lon >> lat){
        pt point = lat_lon_to_cartesian(lat, lon);
        amb.pb(point);
    }

    f3.close();
}


int main(){
    load_data();
    cout << "data loaded!\n";

    vector<ofstream> of(amb.size());
    for(int i=0; i<of.size(); i++){
        of[i] = ofstream("results/ambulance_plot_data/amb_" + to_string(i+1) + ".csv");
        of[i] << fixed, setprecision(10);
        of[i] << "LONGITUD,LATITUD\n";
    }

    cout << "ofstreams ready\n";

    for(auto ac: accidents){
        double dist = LONG_MAX;
        int ix = -1;
        for(int i=0; i<amb.size(); i++){
            pt am = amb[i];
            double d = (am.x - ac->pos.x)*(am.x - ac->pos.x) + (am.y - ac->pos.y)*(am.y - ac->pos.y);
            if(d < dist){
                dist = d;
                ix = i;
            }
        }

        pair<double, double> cds = caretsian_to_lat_lon(ac->pos);
        of[ix] << cds.s << "," << cds.f << '\n';
    }

    for(int i=0; i<of.size(); i++) of[i].close();
    cout << "DONE :)\n";
}

// 1 5 10 15 25 50 75 