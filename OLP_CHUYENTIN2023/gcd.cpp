#include <bits/stdc++.h>
using namespace std;

long long a, b, M;

long long mul(long long a, long long b) {
    if(b == 0) return 0;
    long long res = mul(a, b / 2);

    res = (res + res) % M;

    if(b % 2) res = (res + a) % M;

    return res;
}

struct matrix {
    long long val[3][3];

    matrix() {
        memset(val, 0, sizeof val);
    }

    matrix operator * (const matrix &other) const {
        matrix res;

        for(int i = 1; i <= 2; i++) {
            for(int j = 1; j <= 2; j++) {
                for(int k = 1; k <= 2; k++) {
                    res.val[i][j] = (res.val[i][j] + mul(val[i][k], other.val[k][j])) % M;
                }
            }
        }
        return res;
    }

    matrix operator ^ (const long long &k) const {
        matrix a = *this;

        if(k == 1) return a;

        matrix res = a ^ (k / 2);

        res = res * res;

        if(k % 2) res = res * a;
        
        return res;
    }
};

long long getFib(long long k) {
    if(k <= 1) return 1 % M;

    matrix a;
    a.val[1][1] = 1, a.val[1][2] = 1;
    a.val[2][1] = 1, a.val[2][2] = 0;

    a = a ^ (k - 1);

    return a.val[1][1];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> a >> b >> M;

    cout << getFib(__gcd(a, b));
}