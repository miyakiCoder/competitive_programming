#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int ntest; cin >> ntest;

    while(ntest--) {
        int n; cin >> n;

        vector<array<int, 2>> a(n);
        for(auto &[x, w] : a) cin >> x >> w;

        int L, P; cin >> L >> P;

        for(auto &[x, w] : a) x = L - x;

        int LOG = log2(n);
        vector<vector<array<int, 2>>> mx(LOG + 1, vector<array<int, 2>>(n + 1));

        for(int i = 1; i <= n; i++) mx[0][i] = {a[i - 1][1] - a[i - 1][0], i};
        for(int i = 1; i <= LOG; i++) {
            for(int j = 1; j + (1 << i) - 1 <= n; j++) {
                mx[i][j] = max(mx[i - 1][j], mx[i - 1][j + (1 << (i - 1))]);
            }
        }

        auto get = [&](int l, int r) {
            int k = log2(r - l + 1);
            return max(mx[k][l], mx[k][r - (1 << k) + 1]);
        };

        int res = 0, can_go = 1;
        int cur = 0, aim = L, pos = 1;
        long long energy = P;

        while(cur + energy < aim) {
            int l = pos, r = n, ans = -1;

            while(r - l >= 0) {
                int mid = (l + r) >> 1;

                if(cur + energy >= a[mid - 1][0]) ans = mid, l = mid + 1;
                else r = mid - 1;
            }
            if(ans == -1) {
                can_go = 0;
                break;
            }
            else {
                auto d = get(pos, ans);
                energy += (long long) d[0];
                ++res;
                cur = a[d[1] - 1][0];
                pos = d[1] + 1;
            }
         }
         cout << (can_go ? res : -1) << "\n";
    }

    return 0;
}
