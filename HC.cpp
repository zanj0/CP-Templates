/*
    JAI JAGANNATH!
*/
//@Author : zanj0

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// #define LOCAL  // ← enable locally via -DLOCAL; keep commented for OJ
#define ff first
#define ss second
#define pb push_back
#define MOD 1000000007
#define inf 1000000000000000000LL
#define ps(x, y) fixed << setprecision(y) << x
#define w(x)  \
    int x;    \
    cin >> x; \
    while (x--)
#define endl "\n"
#define timetaken cerr << "Time : " << 1000 * (long double)clock() / (long double)CLOCKS_PER_SEC << "ms\n"

typedef long long int lli;

#ifdef LOCAL
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
#else
#define dbg(x) ((void)0)
#endif

void zanj0()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

/*
────────────────────────────────────────────────────────────────────────
    Problem Statement:

    Observations:

    Claims:

────────────────────────────────────────────────────────────────────────
*/

void Solve()
{
}

int32_t main()
{
    zanj0();
    lli t;
    cin >> t;
    for (lli i = 1; i <= t; i++)
    {
        cout << "Case #" << i << ": ";
        Solve();
    }
    timetaken;
    return 0;
}

/*
    GOLDEN RULES
    • Solutions are simple.
    • Proofs are simple.
    • Implementations are simple.
*/
