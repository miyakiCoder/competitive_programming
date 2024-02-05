#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin >> n;

    vector<int> a(n);

    for(auto &x : a) cin >> x;

    sort(a.begin(), a.end());

    int q; cin >> q;

    while(q--) {
        int l, r; cin >> l >> r;

        int u = lower_bound(a.begin(), a.end(), l) - a.begin();
        int v = upper_bound(a.begin(), a.end(), r) - a.begin() - 1 ;

        cout << max(0, v - u + 1) << "\n";
    }

    return 0;
}
