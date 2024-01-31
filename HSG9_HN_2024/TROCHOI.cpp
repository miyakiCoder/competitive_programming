#include <bits/stdc++.h>
using namespace std;
// debugger
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef DEBUG
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

bool comp(const array<int, 2> &x, const array<int, 2> &y) {
    return (x[0] + x[1] > y[0] + y[1]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    freopen("TROCHOI.inp", "r", stdin);
    freopen("TROCHOI.out", "w", stdout);

    int n, m; cin >> n >> m;

    vector<array<int, 2>> a(n);

    int mx = 0;

    for(auto &[x, y] : a) {
        cin >> x >> y;
        mx = max(mx, y);
    }

    sort(a.begin(), a.end(), comp);

    long long res = 0;

    for(auto &[x, y] : a) {
        if(m <= 0) break;
        if(x + y > mx) {
            res += (long long) x + y;
            --m;
        }
    }

    if(m >= 1) {
        res += (long long) m * mx;
    }

    cout << res;
    return 0;
}
