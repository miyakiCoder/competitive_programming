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

const int mod = (int) 1e9 + 7;

int POW(int a, int b) {
    if(b == 0) return 1;
    int res = POW(a, b / 2);
    res = ((long long) res * res) % mod;
    if(b % 2) res = ((long long) res * a) % mod;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    freopen("DOANTOT.inp", "r", stdin);
    freopen("DOANTOT.out", "w", stdout);

    int n; cin >> n;

    long long res;

    set<array<int, 3>> s;

    auto add = [&](int l, int r) {
        if(s.empty()) {
            res = 1;
            s.insert({l, r, 1});
            return;
        }
        auto lf = s.upper_bound({l, -1});
        auto rt = s.upper_bound({r, mod});

        if(lf != s.begin()) {
            --lf;
            if((*lf)[1] < l) ++lf;
        }

        vector<array<int, 3>> remove;

        while(lf != rt) {
            remove.push_back(*lf);
            ++lf;
        }

        int sum = 1, temp = 1;

        for(auto x : remove) {
            sum += x[2];
            temp = ((long long) temp * x[2]) % mod;
            l = min(l, x[0]);
            r = max(r, x[1]);
            s.erase(x);
        }

        temp = POW(temp, mod - 2);
        res = (res * temp) % mod;
        res = (res * sum) % mod;

        s.insert({l, r, sum});
    };

    for(int i = 1; i <= n; i++) {
        int l, r; cin >> l >> r;
        add(l, r);
        cout << res << "\n";
    }

    return 0;
}
