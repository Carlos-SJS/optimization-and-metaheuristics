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

double const PI = 3.14159265359;
struct pt{
	double x,y;
	pt(double x, double y):x(x),y(y){}
	pt(){}
	double norm2(){return *this**this;}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator /(double t){return pt(x/t,y/t);}
	double operator*(pt p){return x*p.x+y*p.y;}
	bool operator<(pt p)const{return x<p.x|(x==p.x&&y<p.y);}
};

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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    freopen("accident_data.csv", "r", stdin);
    freopen("data_info.txt", "w", stdout);

    string s;
    getline(cin, s);

    double lat, lon;
    int h, m, t;

    double minLat = LONG_MAX, minLon = LONG_MAX, maxLat = LONG_MIN, maxLon = LONG_MIN, avgLat = 0, avgLon = 0, avgH = 0, avgM = 0;
    int cnt = 0, totH = 0, totM = 0;

    vector<pair<double, double>> acc;

    while(cin >> h >> m >> t >> lon >> lat){ 
        minLat = min(lat, minLat);
        maxLat = max(lat, maxLat);
        minLon = min(lon, minLon);
        maxLon = max(lon, maxLon);

        avgLat += lat;
        avgLon += lon;

        totH += h;
        totM += m;

        cnt++;

        acc.pb({lon, lat});
    }

    avgLat /= (double)cnt;
    avgLon /= (double)cnt;
    avgH /= totH/(double)cnt;
    avgM /= totM/(double)cnt;

    cout << fixed << setprecision(12);

    cout << "Max Latitude: " << maxLat << '\n';
    cout << "Min Latitude: " << minLat << '\n';
    cout << "Max Longitude: " << maxLon << '\n';
    cout << "Min Longitude: " << minLon << '\n';

    cout << "AVG. point (Lat, Lon): " << avgLat << ", " << avgLon << '\n';
    pt avg = lat_lon_to_cartesian(avgLat, avgLon);
    cout << "Average point (Cartesian): " << avg.x << ", " << avg.y << '\n';

    double avgDis = 0;
    for(auto a: acc){
        pt pa = lat_lon_to_cartesian(a.s, a.f);
        avgDis += sqrt((pa.x-avg.x)*(pa.x-avg.x) + (pa.y-avg.y)*(pa.y-avg.y));
    }

    avgDis /= (double)cnt;
    cout << "Average distance to avg point (Km): " << avgDis << '\n';
}