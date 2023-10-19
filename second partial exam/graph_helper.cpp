#include <bits/stdc++.h>
using namespace std;

string file = "gradient_decent/logs_p2.txt";

int main(){
    ifstream f(file);
    int ct = 0;
    string s;
    cout << '[';
    while(!f.eof()){
        getline(f, s);
        getline(f, s);
        if(ct) cout << ", ";
        else ct = 1;
        cout << s;
        getline(f, s);
    }
    cout << "]\n";
    f.close();
}
