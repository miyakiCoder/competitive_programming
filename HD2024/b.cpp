#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    long long n, a; cin >> n >> a;

    long long res = n + a * ((n * (n - 1)) / 2);

    cout << res;

    return 0;
}
