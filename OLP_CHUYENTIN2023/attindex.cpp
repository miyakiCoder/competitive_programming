#include <bits/stdc++.h>
using namespace std;

const int maxn = (int) 1e5 + 11;

int n, p;
string S;

void solve1() {
    vector<vector<long long>> cnt(n + 1, vector<long long>(10, 0));
    vector<vector<long long>> sum(n + 1, vector<long long>(10, 0));

    for(int i = 1; i <= n; i++) {
        for(int d = 0; d < 10; d++) {
            cnt[i][d] = cnt[i - 1][d];
            sum[i][d] = sum[i - 1][d];
        }

        cnt[i][S[i] - '0']++;
        sum[i][S[i] - '0'] += (long long) i;
    }

    int q;
    cin >> q;
    while(q--) {
        int l, r; cin >> l >> r;

        long long res = 0;

        for(int d = 0; d < 10; d++) if(d % p == 0) {
            res += sum[r][d] - sum[l - 1][d];
            res -= (long long) (cnt[r][d] - cnt[l - 1][d]) * (l - 1);
        }

        cout << res << "\n";
    }
}

const int BLZ = 320;

struct query {
    int l, r, id;

    bool operator < (const query &others) const {
        if((l / BLZ) != (others.l / BLZ)) return (l < others.l);
        return (r < others.r);
    }
};

int fpow(int a, int b) {
    if(b == 0) return 1;
    int res = fpow(a, b / 2);

    res = ((long long) res * res) % p;

    if(b % 2) res = ((long long) res * a) % p;

    return res;
}

void solve2() {
    int q; cin >> q;

    vector<query> qry;
    vector<long long> res(n + 1, 0);
    vector<long long> POW(n + 1, 0), sum(n + 1, 0);
    vector<long long> rem(n + 1, 0);

    POW[0] = 1;
    for(int i = 1; i <= n; i++) {
        POW[i] = (POW[i - 1] * 10) % p;
        sum[i] = (sum[i - 1] * 10 + (S[i] - '0')) % p;
    }

    for(int i = 0; i <= n; i++) {
        POW[i] = fpow(POW[i], p - 2);
    }

    vector<int> cpr;

    for(int i = 0; i <= n; i++) {
        int val = ((long long) sum[i] * POW[i]) % p;
        cpr.push_back(val);
    }

    sort(cpr.begin(), cpr.end()); cpr.resize(unique(cpr.begin(), cpr.end()) - cpr.begin());

    for(int i = 0; i <= n; i++ ){
        int val = ((long long) sum[i] * POW[i]) % p;
        rem[i] = lower_bound(cpr.begin(), cpr.end(), val) - cpr.begin() + 1;
    }

    vector<int> cnt((int) cpr.size() + 3, 0);

    for(int i = 1; i <= q; i++) {
        int l, r; cin >> l >> r;
        qry.push_back({l, r, i});
    }

    sort(qry.begin(), qry.end());

    for(auto &[l, r, id] : qry) --l;

    long long ans = 0;

    int L = 1, R = 0;
    for(auto [ql, qr, id] : qry) {
        while(ql > L) {
            cnt[rem[L]]--;
            ans -= (long long) cnt[rem[L]];
            L++;
        }
        while(ql < L) {
            L--;
            ans += (long long) cnt[rem[L]];
            cnt[rem[L]]++;
        }
        while(qr > R) {
            R++;
            ans += (long long) cnt[rem[R]];
            cnt[rem[R]]++;
        }
        while(qr < R) {
            cnt[rem[R]]--;
            ans -= (long long) cnt[rem[R]];
            R--;
        }
        res[id] = ans;
    }

    for(int i = 1; i <= q; i++) cout << res[i] << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    cin >> p >> S;

    n = (int) S.size(); S = " " + S;

    if(p == 2 || p == 5) solve1();
    else solve2();
}