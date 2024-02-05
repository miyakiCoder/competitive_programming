#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../headers/debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    long long a, b, c; cin >> a >> b >> c;

    long long res = a * b - c * a - c * b + c * c;

    cout << res;

    return 0;
}
