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

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    freopen("ROBOT.inp", "r", stdin);
    freopen("ROBOT.out", "w", stdout);

    int n, m, q, k; cin >> n >> m >> q >> k;

    vector<int> cpr;

    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        cin >> a[i][j]; a[i][j] %= k;
        cpr.push_back(a[i][j]);
    }

    vector<int> qry(q);
    for(auto &x : qry) {
        cin >> x;
        cpr.push_back(x);
    }

    sort(cpr.begin(), cpr.end());
    cpr.resize(unique(cpr.begin(), cpr.end()) - cpr.begin());

    vector<vector<array<int, 2>>> pos((int) cpr.size());

    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        int u = lower_bound(cpr.begin(), cpr.end(), a[i][j]) - cpr.begin();
        pos[u].push_back({i, j});
    }

    vector<int> res((int) cpr.size(), -1);

    for(auto &x : qry) {
        int val = lower_bound(cpr.begin(), cpr.end(), x) - cpr.begin();
        if(res[val] != -1) cout << res[val] << "\n";
        else {
            sort(pos[val].begin(), pos[val].end());

            vector<int> f((int) pos[val].size() + 1, INT_MAX);
            f[0] = INT_MIN;

            for(auto &[l, r] : pos[val]) {
                int d = upper_bound(f.begin(), f.end(), r) - f.begin();
                f[d] = r;
                res[val] = max(res[val], d);
            }
            cout << max(0, res[val]) << "\n";
        }
    }
    return 0;
}
