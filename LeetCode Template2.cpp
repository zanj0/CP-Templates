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

class Solution
{
public:
    int cntGood(int n, int k)
    {
        
        return 0;
    }
};

#ifdef LOCAL
int main()
{
    zanj0();

    // Solution sol;
    // cout << sol.cntGood(5, 2) << endl;
    cout << "Compiled Successfully!" << endl;

    return 0;
}
#endif

/*
    GOLDEN RULES
    • Solutions are simple.
    • Proofs are simple.
    • Implementations are simple.
*/
