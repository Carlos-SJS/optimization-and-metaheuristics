#include <bits/stdc++.h>
using namespace std;
#define eps .0000000000001
#define ff first
#define ss second
// types: 0 -> operator, 1 -> number (including x)
//{type, index}
vector<pair<int, int>> terms;
//{op id, herarchy}
vector<pair<int, int>> operators;
//types: 0 -> constant, 1 -> variable (x)
//{type, value}
vector<pair<int, double>> numbers;

double f(double x){
    //return pow((double)exp(1.0), x) - 1/x;
    stack<double> nms;
    stack<pair<int, int>> ops;
    double val;
    int i = 0, rnk, op;
    double a, b;
    while(i < terms.size() || !ops.empty()){
        op = 6;
        if(i < terms.size()){
            if(terms[i].ff == 0){
                if(ops.empty() || operators[terms[i].ss].ss >=ops.top().ss || operators[terms[i].ss].ff == 5){
                    ops.push(operators[terms[i].ss]);
                    i++;
                    continue;
                }else{
                    op = operators[terms[i].ss].ff;
                    rnk = operators[terms[i].ss].ss;
                    i++;
                }
            }else{
                if(numbers[terms[i].ss].ff == 0)
                    nms.push(numbers[terms[i].ss].ss);
                else
                    nms.push(x * numbers[terms[i].ss].ss);
                i++;
                continue;
            }
        }
        while(!ops.empty() && ops.top().ff != 5){
            b = nms.top();
            nms.pop();
            a = nms.top();
            nms.pop();
            switch(ops.top().ff){
                case 0:
                    a += b;
                    break;
                case 1:
                    a -= b;
                    break;
                case 2:
                    a *= b;
                    break;
                case 3:
                    if(b == 0){
                        cout << "ERROR: DIVISION BY ZERO :(\n";
                        exit(-2);
                    }
                    a /= b;
                    break;
                case 4:
                    //cout << a << " " << b << " " << x << '\n';
                    a = pow(a, b);
                    break;
            }
            ops.pop();
            nms.push(a);
        }
        if(!ops.empty() && ops.top().ff == 5 && op == 6) ops.pop();
        if(op != 6) ops.push({op, rnk});
    }
    //cout << nms.top() << " " << nms.size() << '\n';
    return nms.top();
}

double f_prime(double x){
    return 2*x;
    double h = 1e-5;
    return (f(x+h) - f(x))/(x+h-x);
}

bool handle_number(string &s, int sgn){
    terms.push_back({1, numbers.size()});
    numbers.push_back({0, (double)sgn*stod(s)});
    return 1;
}

bool handle_word(string &s, int sgn){
    terms.push_back({1, numbers.size()});
    if(s == "e") numbers.push_back({0, (double)sgn*exp(1.0)});
    else if(s == "pi") numbers.push_back({0,(double)sgn*3.14159265359});
    else if(s == "x") numbers.push_back({1, (double)sgn});
    else return 0;
    return 1;
}

bool parse_function(string &s){
    int st, state, pts = 0, prev = -1;
    int sgn = 1;
    // 0 -> operator, 1 -> number, 2 -> word
    string w;
    map<char, int> ops = {{'+', 0}, {'-',1}, {'*',2}, {'/',3}, {'(',5},
    {')',6}, {'^',4}};
    vector<int> rnk{0, 0, 1, 1, 2, -1, -2};
    set<char> nms = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9','.'};
    for(int i=0 ;i<s.size(); i++){
        state = 1;
        if(!nms.count(s[i])) state = 0;
        if(s[i] == '.') pts++;
        if(pts > 1) return 0;
        if(state == 0)
        if(!ops.count(s[i])) state = 2;
        if(state == 0){
            if(s[i] != '(' && s[i] != ')' && i == s.size()-1) return 0;
            if(state != prev && prev != -1){
                if(prev == 1){
                    string w = s.substr(st, i-st);
                    if(!handle_number(w, sgn)) return 0;
                    sgn = 1;
                }else if(prev == 2){
                    string w = s.substr(st, i-st);
                    if(!handle_word(w, sgn)) return 0;
                    sgn = 1;
                }
            }else if(prev == state){
                if(s[i] == '-' && !ops.count(s[i+1]) && s[i-1] != '(' && s[i-1] != ')') sgn = -1;
                else if(s[i] == '(' && (s[i-1] == ')') || !ops.count(s[i-1])){
                    terms.push_back({0, operators.size()});
                    operators.push_back({2, 1});
                    terms.push_back({0, operators.size()});
                    operators.push_back({ops[s[i]], rnk[ops[s[i]]]});
                }
                else if(s[i-1] == '(' && s[i] != ')')
                    return 0;
                else if(s[i] != '(' && s[i] != ')' && s[i-1] != ')')
                    return 0;
                else{
                    terms.push_back({0, operators.size()});
                    operators.push_back({ops[s[i]], rnk[ops[s[i]]]});
                }
            }
            if(prev!=state){
                terms.push_back({0, operators.size()});
                operators.push_back({ops[s[i]], rnk[ops[s[i]]]});
            }
        }else if(state == 1){
            if(prev != state){
                if(prev == 2){
                    string w = s.substr(st, i-st);
                    if(!handle_word(w, 1)) return 0;
                    terms.push_back({0, operators.size()});
                    operators.push_back({2, 1});
                }
                st = i;
            }
        }else if(state == 2){
            if(prev != state){
                if(prev == 1){
                    string w = s.substr(st, i-st);
                    if(!handle_number(w, 1)) return 0;
                    terms.push_back({0, operators.size()});
                    operators.push_back({2, 1});
                }
                st = i;
            }
        }
        prev = state;
    }
    if(prev == 1){
        string w = s.substr(st, s.size()-st);
        if(!handle_number(w, sgn)) return 0;
    }else if(prev == 2){
        string w = s.substr(st, s.size()-st);
        if(!handle_word(w, sgn)) return 0;
    }
    return 1;
}

double newton_raphson(){
    double p = -5, tol = 1e-8, fx, fx_prime;
    int i = 0, max_iter = 10;
    while(i < max_iter){
        fx = f(p);
        fx_prime = f_prime(p);
        p = p - fx/fx_prime;

        cout << i+1 << ": " << p << '\n';

        if(abs(fx) < tol || abs(fx_prime) < tol)
        return p;
        i++;
    }
    return p;
}

int main(){
    string fx;
    double a, b, rt;
    cout << "Ingresa una funcion que dependa de x:\n";
    cin >> fx;
    cout << "\n";
    if(!parse_function(fx)){
        cout << "La funcion indicada no es una funcion valida,\nrecuerda que tu funcion tiene que depender solo de x,\ny puede contener los operadores/valores (+,-,*,/,^,(,),e,pi)\n";
        return -1;
    }
    rt = newton_raphson();
    cout << "Raiz ";
    if(rt < 0 && abs(rt) > 1e-8) cout << " ";
    for(int i=0; i<(int)log10(abs(rt))+1; i++) cout << " ";
    cout << "f(raiz)\n";
    cout << setprecision(10) << fixed << (abs(rt) < 1e-11? 0: rt) << "(" << scientific << rt << "): ";
    cout << fixed << (abs(f(rt)) < 1e-11? 0: f(rt)) << scientific << "(" << f(rt) << ")\n";
}