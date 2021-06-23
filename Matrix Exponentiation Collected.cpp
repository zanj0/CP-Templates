/*
    JAI JAGANNATH!
*/
//@Author : zanj0

#include<bits/stdc++.h>
using namespace std;

#define int             long long int
#define LOCAL
#define ff              first
#define ss              second
#define pb              push_back
#define MOD             1000000007
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define w(x)            int x; cin>>x; while(x--)
#define endl            "\n"
#define timetaken cerr<<"Time : "<<1000*(long double)clock()/(long double)CLOCKS_PER_SEC<<"ms\n"
void zanj0()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
const int MAT = 103;
struct M {
    int t[MAT][MAT];
    int n;
    M(int n) {
        this->n = n;
        memset(t, 0, sizeof(t));
    }
    M operator* (const M& a) const {
        M c = M(n);
        signed long long mo2 = (int)4 * MOD * MOD;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++ ) {
                for (int k = 0; k < n; k++) {
                    c.t[i][k] += t[i][j] * a.t[j][k];
                    if (c.t[i][k] > mo2) c.t[i][k] -= mo2;
                }
            }
        }
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) c.t[i][j] %= MOD;
        return c;
    }
};
M fastPow(int n, M base, int power) {
    M ret = M(n);
    for (int i = 0; i < n; i++) ret.t[i][i] = 1;
    while (power > 0) {
        if (power & 1) {
            ret = ret * base;
        }
        base = base * base;
        power >>= 1;
    }
    return ret;
}
void solve() {
    int n, m;
    cin >> n >> m;
    if (n < m) {
        cout << 1 << endl;
    } else {
        M base = M(m);
        base.t[0][0] = base.t[0][m - 1] = 1;
        for (int i = 1; i < m; i++) base.t[i][i - 1] = 1;
        M ret = fastPow(m, base, n - (m - 1));
        int ans = 0;
        for (int i = 0; i < m; i++) ans += ret.t[0][i];
        cout << ans % MOD << endl;
    }
}
int32_t main()
{
    zanj0();
    solve();
    timetaken;
    return 0;
}