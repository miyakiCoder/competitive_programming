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

    int n; cin >> n;

    string s; cin >> s;
    s = " " + s;

    vector<int> up(n + 1, 0);
    vector<int> low(n + 1, 0);
    vector<int> digit(n + 1, 0);

    for(int i = 1; i <= n; i++) {
        up[i] = up[i - 1] + (s[i] >= 'A' && s[i] <= 'Z');
        low[i] = low[i - 1] + (s[i] >= 'a' && s[i] <= 'z');
        digit[i] = digit[i - 1] + (s[i] >= '0' && s[i] <= '9');
    }

    auto check = [&](int l, int r) {
        return ((up[r] - up[l - 1] >= 1) && (low[r] - low[l - 1] >= 1) && (digit[r] - digit[l - 1] >= 1));
    };

    long long res = 0;

    for(int i = 1; i <= n - 5; i++) {
        int l = i + 5, r = n, pos = -1;

        while(r - l >= 0) {
            int mid = (l + r) >> 1;

            if(check(i, mid)) pos = mid, r = mid - 1;
            else l = mid + 1;
        }

        if(pos != -1) {
            res += (long long) (n - pos + 1);
        }
    }

    cout << res;
    return 0;
} 