#include <bits/stdc++.h>
using namespace std;

const int maxn = (int) 2e5 + 11;
const int mod = (int) 1e9 + 7;

void add(int &a, int b) {
    a += b;
    if(a >= mod) a -= mod;
    if(a < 0) a += mod;
}

void mul(int &a, int b) {
    long long res = ((long long) a * b) % mod;
    a = res;
}

int n, t;
int h[maxn], vs[maxn], s[maxn];
vector<int> adj[maxn];

void dfs(int u, int par, int lim) {
    s[u] = 1;
    vs[u] = 1;
    for(int v : adj[u]) if(v != par && h[v] <= lim) {
        dfs(v, u, lim);
        s[u] += s[v];
    }
}

int cal(int u, int par, int lim, int numNode) {
    int res = 0;

    int value = s[u];
    mul(value, (numNode - s[u]));
    mul(value, (numNode - 2));
    add(res, value);

    for(int v : adj[u]) if(v != par && h[v] <= lim) {
        add(res, cal(v, u, lim, numNode));
    }
    return res;
}

int f(int lim) {
    for(int i = 1; i <= n; i++) vs[i] = 0;

    int res = 0;

    for(int i = 1; i <= n; i++) if(!vs[i] && h[i] <= lim) {
        dfs(i, -1, lim);
        add(res, cal(i, -1, lim, s[i]));
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> t;
    for(int i = 1; i <= n; i++) cin >> h[i];

    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int res = f(t);
    add(res, -f(t - 1));

    cout << res;
}