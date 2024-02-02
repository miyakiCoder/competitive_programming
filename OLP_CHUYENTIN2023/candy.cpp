#include <bits/stdc++.h>
using namespace std;

const int maxn = (int) 2e5 + 11;

int n, q;
int a[maxn];

struct segmentTree {
    long long seg[4 * maxn][10];

    void update(int u, int node = 1, int l = 1, int r = n) {
        if(l == r) {
            int pos = l, val = a[l];

            vector<bool> exist(10, 0);

            int temp = pos;
            while(temp) exist[temp % 10] = 1, temp /= 10;

            for(int i = 1; i < 10; i++) {
                if(exist[i] || (pos % i == 0)) {
                    seg[node][i] = (long long) 2 * val;
                }
                else seg[node][i] = (long long) val;
            }

            return;
        }
        int mid = (l + r) >> 1;

        if(mid >= u) update(u, node << 1, l, mid);
        else update(u, node << 1 | 1, mid + 1, r);

        for(int i = 1; i < 10; i++) {
            seg[node][i] = seg[node << 1][i] + seg[node << 1 | 1][i];
        }
    }

    long long get(int u, int v, int k, int node = 1, int l = 1, int r = n) {
        if(u > r || v < l) return 0;
        if(l >= u && r <= v) return seg[node][k];
        int mid = (l + r) >> 1;
        return get(u, v, k, node << 1, l, mid) + get(u, v, k, node << 1 | 1, mid + 1, r);
    }
} SEG;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];

    for(int i = 1; i <= n; i++) SEG.update(i);

    while(q--) {
        int op; cin >> op;

        if(op == 1) {
            int i, c; cin >> i >> c;
            a[i] = c;
            SEG.update(i);
        }
        else {
            int l, r, k; cin >> l >> r >> k;
            cout << SEG.get(l, r, k) << "\n";
        }
    }
}