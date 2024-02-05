#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, k; cin >> n >> k;

    vector<int> a(n), b(n);

    for(auto &x : a) cin >> x;
    for(auto &y : b) cin >> y;

    vector<long long> dp(n, 0), pre(n, 0);

    dp[0] = b[0];
    pre[0] = dp[0];
    for(int i = 1; i < n; i++) {
        dp[i] = b[i];
        int u = upper_bound(a.begin(), a.end(), a[i] - k) - a.begin() - 1;
        if(u >= 0) {
            dp[i] = max(dp[i], pre[u] + (long long) b[i]);
        }
        pre[i] = max(pre[i - 1], dp[i]);
    }

    cout << *max_element(dp.begin(), dp.end());

    return 0;
}
