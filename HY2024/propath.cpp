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

const int maxn = (int) 1e5 + 11;

int n;
int vs[maxn], c_par[maxn], s[maxn];
vector<int> adj[maxn];

int getSize(int u, int par) {
    s[u] = 1;
    for(int v : adj[u]) if(v != par && !vs[v]) s[u] += getSize(v, u);
    return s[u];
}

int getCentroid(int u, int par, int n) {
    for(int v : adj[u]) if(v != par && !vs[v]) {
        if(2 * s[v] >= n) return getCentroid(v, u, n);
    }
    return u;
}

unordered_map<int, int> dist[maxn];

void cal(int cur, int u, int par, int depth) {
    dist[cur][u] = depth;
    for(int v : adj[u]) if(v != par && !vs[v]) cal(cur, v, u, depth + 1);
}

void dfs(int u = 1, int par = -1) {
    int n = getSize(u, par);
    vs[u = getCentroid(u, par, n)] = 1;

    if(par != -1) c_par[u] = par;

    cal(u, u, par, 0);
    for(int v : adj[u]) if(v != par && !vs[v]) dfs(v, u);
}

array<int, 2> d1[maxn], d2[maxn];

void update_c(int u, int d, int p) {
    if(d >= d1[u][0]) {
        if(p == d1[u][1]) d1[u][0] = d;
        else {
            d2[u] = d1[u];
            d1[u] = {d, p};
        }
    }
    else if(d > d2[u][0]) {
        if(p == d1[u][1]) return;
        else {
            d2[u] = {d, p};
        }
    }
}

void update(int u) {
    for(int v = u, p = v; v; p = v, v = c_par[v]) {
        update_c(v, dist[v][u], p);
    }
}

int get(int u) {
    int ans = 0;
    for(int v = u, p = v; v; p = v, v = c_par[v]) {
        ans = max(ans, dist[v][u] + (p != d1[v][1] ? d1[v][0] : d2[v][0]));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n;

    vector<array<int, 2>> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
        a[i][1] = i + 1;
    }

    sort(a.begin(), a.end(), greater<array<int, 2>>());

    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs();

    for(int i = 1; i <= n; i++) {
        d1[i] = d2[i] = {(int) -1e9, (int) -1e9};
    }

    long long ans = 0;

    for(auto [w, u] : a) {
        update(u);

        int d = get(u);

        ans = max(ans, (long long) w * d);
    }

    cout << ans;

    return 0;
} 