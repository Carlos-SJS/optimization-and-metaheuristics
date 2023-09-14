#include<bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define ll long long

// Create random distribution objects used to generate random variables
int low = 0;
int upp = 1;
std::uniform_int_distribution<int> unif(low,upp);
std::default_random_engine re;

// Evaluate the function with the given vector
ll f(vi x){
    ll ret = 30, ac=0;

    for(int v: x) ac += v;
    ret -= ac;

    ac = 1;
    for(int v: x) ac *= v;
    ret += (30+1)*ac;

    return ret;
}

// Generate a new random vector
vi genx(){
    vi x(30);
    for(int i=0; i<30; i++) x[i] = unif(re);
    return x;
}

// Variables to store the current minimum found and the value for x
vi minx = genx();
ll minv = f(minx);
int it = 0;

int main(){
    // Infinite loop so it can run indefinetly to find the best possible solution so the user can chose when to stop it
    while(1){
        it++;

        // Generate a new random vector x
        vi x = genx();
        ll v = f(x);

        // Check if the new vector is better tahn the best vector found yet
        if(v < minv){
            // Update the values for the best solution found so far
            minv = v;
            minx = x;

            // Print the new values
            cout << "[" << it << "]  " << v << ": ";
            for(int va: x) cout << va << ' ';
            cout << '\n';
        }
    }
}