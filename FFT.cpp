/*
    JAI JAGANNATH!
*/
//@Author : zanj0

#include <bits/stdc++.h>
using namespace std;

// #define LOCAL  // ← enable locally via -DLOCAL; keep commented for LeetCode
#define ff first
#define ss second
#define pb push_back
#define MOD 1000000007
#define inf 1000000000000000000LL
#define ps(x, y) fixed << setprecision(y) << x

typedef long long int lli;

#ifdef LOCAL
// --------------------------- Debug Utilities ---------------------------
#define dbg(x) cerr << "[DBG] " << #x << " = " << (x) << '\n'

template <class A, class B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ',' << p.second << ')'; }

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << '[';
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ',';
        os << v[i];
    }
    return os << ']';
}

template <class T>
ostream &operator<<(ostream &os, const vector<vector<T>> &m)
{
    os << '[';
    for (size_t i = 0; i < m.size(); ++i)
    {
        if (i)
            os << ',';
        os << m[i];
    }
    return os << ']';
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &mp)
{
    os << '{';
    bool first = true;
    for (const auto &kv : mp)
    {
        if (!first)
            os << ',';
        first = false;
        os << kv.first << ':' << kv.second;
    }
    return os << '}';
}

template <class K, class V>
ostream &operator<<(ostream &os, const unordered_map<K, V> &mp)
{
    os << '{';
    bool first = true;
    for (const auto &kv : mp)
    {
        if (!first)
            os << ',';
        first = false;
        os << kv.first << ':' << kv.second;
    }
    return os << '}';
}

// Timer (LOCAL only)
struct __Timer
{
    chrono::high_resolution_clock::time_point t0;
    __Timer() : t0(chrono::high_resolution_clock::now()) {}
    ~__Timer()
    {
        auto t1 = chrono::high_resolution_clock::now();
        long double ms = chrono::duration<long double, std::milli>(t1 - t0).count();
        cerr << "Time : " << ms << "ms\n";
    }
} __timer_guard__;
// ----------------------------------------------------------------------
#else
#define dbg(x) ((void)0)
#endif

inline void zanj0()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

/*
────────────────────────────────────────────────────────────────────────
    Problem Statement:


    Observations:


    Claims:


────────────────────────────────────────────────────────────────────────
*/

class Solution {
    using cd = complex<double>;
    const double PI = acos(-1.0);

    void fft(vector<cd> &a, bool invert) {
        int n = (int)a.size();

        // Bit-reversal permutation
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) {
                swap(a[i], a[j]);
            }
        }

        // Iterative Cooley–Tukey
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2.0 * PI / len * (invert ? -1.0 : 1.0);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1.0, 0.0);
                for (int j = 0; j < len / 2; ++j) {
                    cd u = a[i + j];
                    cd v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (int i = 0; i < n; ++i) {
                a[i] /= n;
            }
        }
    }

public:
    vector<long long> multiply(vector<int>& poly1, vector<int>& poly2) {
        int n1 = (int)poly1.size();
        int n2 = (int)poly2.size();

        int need = n1 + n2 - 1;
        int n = 1;
        while (n < need) n <<= 1;

        vector<cd> fa(n), fb(n);

        for (int i = 0; i < n1; ++i) fa[i] = cd(poly1[i], 0);
        for (int i = 0; i < n2; ++i) fb[i] = cd(poly2[i], 0);

        
        fft(fa, false);
        fft(fb, false);

        
        for (int i = 0; i < n; ++i) {
            fa[i] *= fb[i];
        }

        
        fft(fa, true);

        vector<lli> ret(need);
        for (int i = 0; i < need; ++i) {
            ret[i] = llround(fa[i].real());
        }

        return ret;
    }
};

#ifdef LOCAL
int main()
{
    zanj0();

   
    return 0;
}
#endif

/*
    GOLDEN RULES
    • Solutions are simple.
    • Proofs are simple.
    • Implementations are simple.
*/
