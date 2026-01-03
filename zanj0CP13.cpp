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

// -----------------------------------------------------------------------------
// 🧩 UTILITY HELPERS
// -----------------------------------------------------------------------------

// ---- min/max assign ----
template <typename T>
inline bool ckmin(T &a, const T &b)
{
    if (b < a)
    {
        a = b;
        return true;
    }
    return false;
}
template <typename T>
inline bool ckmax(T &a, const T &b)
{
    if (a < b)
    {
        a = b;
        return true;
    }
    return false;
}

// ---- power (generic / mod) ----
template <typename T>
T binpow(T a, long long e, T mod = (T)MOD)
{
    T r = 1 % mod;
    a %= mod;
    while (e)
    {
        if (e & 1)
            r = (r * a) % mod;
        a = (a * a) % mod;
        e >>= 1;
    }
    return r;
}

// ----------------- Math Helpers -----------------
inline lli gcdll(lli a, lli b) { return b ? gcdll(b, a % b) : a; }
inline lli lcmll(lli a, lli b) { return (a / gcdll(a, b)) * b; }

inline lli mod_add(lli a, lli b, lli m = MOD)
{
    a %= m;
    b %= m;
    lli s = a + b;
    if (s >= m)
        s -= m;
    return s;
}
inline lli mod_sub(lli a, lli b, lli m = MOD)
{
    a %= m;
    b %= m;
    lli d = a - b;
    if (d < 0)
        d += m;
    return d;
}
inline lli mod_mul(lli a, lli b, lli m = MOD)
{

    return ((a % m) * (b % m)) % m;
}
inline lli mod_pow(lli a, lli e, lli m = MOD)
{
    lli r = 1 % m;
    a %= m;
    while (e)
    {
        if (e & 1)
            r = mod_mul(r, a, m);
        a = mod_mul(a, a, m);
        e >>= 1;
    }
    return r;
}
inline lli mod_inv(lli a, lli m = MOD) { return mod_pow(a, m - 2, m); }

// ----------------- Combinatorics -----------------
struct Comb
{
    vector<lli> fact, invfact;
    int n;
    Comb(int N = 0) { init(N); }
    void init(int N)
    {
        n = N;
        fact.assign(n + 1, 1);
        invfact.assign(n + 1, 1);
        for (int i = 2; i <= n; i++)
            fact[i] = (fact[i - 1] * i) % MOD;
        invfact[n] = mod_inv(fact[n]);
        for (int i = n - 1; i >= 1; i--)
            invfact[i] = (invfact[i + 1] * (i + 1)) % MOD;
    }
    lli nCr(int a, int b)
    {
        if (b < 0 || b > a)
            return 0;
        return (((fact[a] * invfact[b]) % MOD) * invfact[a - b]) % MOD;
    }
};

// ----------------- Random Generator -----------------
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
inline lli rnd(lli l, lli r)
{
    uniform_int_distribution<lli> dist(l, r);
    return dist(rng);
}

// ----------------- Vector Helpers -----------------
template <typename T>
inline void printv(const vector<T> &v)
{
    for (const auto &x : v)
        cout << x << " ";
    cout << endl;
}
template <typename T>
inline void readv(vector<T> &v)
{
    for (auto &x : v)
        cin >> x;
}

// ----------------- Coordinate Compression -----------------
template <typename T>
struct Compressor
{
    vector<T> vals;
    void add(const T &x) { vals.pb(x); }
    void build()
    {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }
    int get(const T &x) { return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin()); }
    int idx_of(const T &x)
    {
        auto it = lower_bound(vals.begin(), vals.end(), x);
        return (it != vals.end() && *it == x) ? int(it - vals.begin()) : -1;
    }
    int size() const { return (int)vals.size(); }
};

// ----------------- Primality (basic) -----------------
inline bool isPrime(lli n)
{
    if (n < 2)
        return false;
    for (lli i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

// ----------------- DSU (Disjoint Set Union) -----------------
struct DSU
{
    vector<int> p, sz;
    DSU() {}
    DSU(int n) { init(n); }
    void init(int n)
    {
        p.resize(n);
        sz.assign(n, 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) { return (p[x] == x ? x : p[x] = find(p[x])); }
    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

// ----------------- Prefix Sum (1D) -----------------
template <typename T>
struct PrefixSum
{
    vector<T> pref;
    PrefixSum() {}
    PrefixSum(const vector<T> &v) { build(v); }
    void build(const vector<T> &v)
    {
        int n = (int)v.size();
        pref.assign(n + 1, 0);
        for (int i = 1; i <= n; i++)
            pref[i] = pref[i - 1] + v[i - 1];
    }
    T query(int l, int r)
    { // inclusive l..r
        if (l > r)
            return 0;
        return pref[r + 1] - pref[l];
    }
};

// ----------------- Prefix Sum (2D) -----------------
template <typename T>
struct Prefix2D
{
    vector<vector<T>> pref;
    Prefix2D() {}
    Prefix2D(const vector<vector<T>> &g) { build(g); }
    void build(const vector<vector<T>> &g)
    {
        if (g.empty() || g[0].empty())
        {
            pref.assign(1, vector<T>(1, 0));
            return;
        }
        int n = (int)g.size(), m = (int)g[0].size();
        pref.assign(n + 1, vector<T>(m + 1, 0));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                pref[i][j] = g[i - 1][j - 1] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }
    T query(int x1, int y1, int x2, int y2)
    { // inclusive
        return pref[x2 + 1][y2 + 1] - pref[x1][y2 + 1] - pref[x2 + 1][y1] + pref[x1][y1];
    }
};

// ----------------- Fenwick Tree (BIT) -----------------
template <typename T>
struct Fenwick
{
    int n;
    vector<T> bit;
    Fenwick() {}
    Fenwick(int n) { init(n); }
    void init(int n_)
    {
        n = n_ + 1;
        bit.assign(n, 0);
    }
    void update(int i, T val)
    {
        for (++i; i < n; i += i & -i)
            bit[i] += val;
    }
    T query(int i)
    {
        T s = 0;
        for (++i; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }
    T range(int l, int r)
    {
        if (r < l)
            return 0;
        return query(r) - query(l - 1);
    }
};

// ----------------- Segment Tree (sum) -----------------
template <typename T>
struct SegTree
{
    int n;
    vector<T> st;
    SegTree() {}
    SegTree(int n) { init(n); }
    void init(int n_)
    {
        n = n_;
        st.assign(4 * n, T());
    }
    void build(vector<T> &a, int p, int l, int r)
    {
        if (l == r)
        {
            st[p] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, 2 * p, l, m);
        build(a, 2 * p + 1, m + 1, r);
        st[p] = st[2 * p] + st[2 * p + 1];
    }
    void update(int p, int l, int r, int idx, T val)
    {
        if (l == r)
        {
            st[p] = val;
            return;
        }
        int m = (l + r) / 2;
        if (idx <= m)
            update(2 * p, l, m, idx, val);
        else
            update(2 * p + 1, m + 1, r, idx, val);
        st[p] = st[2 * p] + st[2 * p + 1];
    }
    T query(int p, int l, int r, int ql, int qr)
    {
        if (qr < l || r < ql)
            return T(); // neutral for sum
        if (ql <= l && r <= qr)
            return st[p];
        int m = (l + r) / 2;
        return query(2 * p, l, m, ql, qr) + query(2 * p + 1, m + 1, r, ql, qr);
    }
};

// ----------------- Grid Directions -----------------
int dx4[4] = {1, -1, 0, 0};
int dy4[4] = {0, 0, 1, -1};
int dx8[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy8[8] = {1, 0, -1, 1, -1, 1, 0, -1};

// ----------------- Lambda DFS Pattern (example) -----------------
// auto dfs = [&](auto self, int u, int p) -> void {
//     for(int v : adj[u]) if(v != p) self(self, v, u);
// };

// ----------------- Custom Hash (anti-hack) -----------------
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// ----------------- Pair Hash -----------------
struct pair_hash
{
    template <class A, class B>
    size_t operator()(const pair<A, B> &p) const
    {
        return std::hash<A>()(p.first) ^ (std::hash<B>()(p.second) << 1);
    }
};

// ----------------- String Helpers -----------------
vector<string> split(const string &s, char delim)
{
    vector<string> res;
    string tmp;
    for (char c : s)
    {
        if (c == delim)
        {
            res.pb(tmp);
            tmp.clear();
        }
        else
            tmp.pb(c);
    }
    res.pb(tmp);
    return res;
}

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
#else
#define dbg(x) ((void)0)
#endif

// -----------------------------------------------------------------------------
// 📌 EXAMPLE USAGE PLACEHOLDERS (copy/paste into Solve() when needed)
// -----------------------------------------------------------------------------
// /*
// // 1) DSU
// DSU dsu(n);
// dsu.unite(u, v);
// int comp = dsu.find(u);

// // 2) Prefix Sum 1D
// vector<long long> a(n);
// PrefixSum<long long> pref(a);
// long long sum_lr = pref.query(l, r);

// // 3) Prefix Sum 2D
// vector<vector<int>> g(n, vector<int>(m));
// Prefix2D<int> P(g);
// int box = P.query(x1,y1,x2,y2);

// // 4) Fenwick
// Fenwick<long long> bit(n);
// bit.update(idx, +val);
// long long prefk = bit.query(k);
// long long range = bit.range(l, r);

// // 5) Segment Tree (sum)
// SegTree<long long> st(n);
// st.build(a, 1, 0, n-1);
// st.update(1, 0, n-1, pos, newVal);
// long long got = st.query(1, 0, n-1, L, R);

// // 6) Compressor
// Compressor<long long> C;
// for(auto &x: a) C.add(x);
// C.build();
// int id = C.get(x);

// // 7) Combinatorics
// Comb comb(Nmax);
// long long ways = comb.nCr(n, k);

// // 8) Random
// long long rnum = rnd(1, (lli)1e12);

// // 9) Ordered Set (PBDS)
// ordered_set<int> os;
// os.insert(x);
// os.erase(x);
// int kth = *os.find_by_order(k);     // 0-indexed
// int lt  = os.order_of_key(x);       // count of < x

// // 10) String split
// auto tokens = split(s, ',');

// // 11) Debug
// dbg(var); dbg(vectorVar);
// */

// -----------------------------------------------------------------------------
// ⚙️ I/O BOOTSTRAP
// -----------------------------------------------------------------------------
void zanj0()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
}

// -----------------------------------------------------------------------------
// 🧠 THINKING SCAFFOLD
// -----------------------------------------------------------------------------
/*
    ─────────────────────────────────────────────────────────────────────
    Problem Statement:
    • (1–2 lines) What is being asked? What are input/output formats?

    Constraints:
    • n ≤ ?, m ≤ ?, time/memory limits?
    • Sum over tests? Special structure (tree, grid, mod)?

    Small Observations:
    • Trivial / base cases.
    • Parity, ordering, prefix/suffix, symmetry, invariants.

    Key Reformulation:
    • View as prefix-sum / graph / DP / greedy / math?
    • Any state transitions / monotonicity?

    Approach Sketch:
    • Step 1 → Step 2 → Step 3
    • Core structure: array / set / heap / segtree / etc.
    • Why it works (1–2 bullets of proof intuition)

    Edge Cases:
    • n=1, all equal, strictly inc/dec, overflow, modulo, sign, etc.

    Complexity:
    • Time: O( … )   Space: O( … )

    Implementation Plan:
    • Variables & DS.
    • Precomputation.
    • Main loop & outputs.

    Test Plan:
    • Minimal (n=1), borderline (max), random, adversarial.
    ─────────────────────────────────────────────────────────────────────
*/

// -----------------------------------------------------------------------------
// 🚀 SOLUTION FUNCTION
// -----------------------------------------------------------------------------
void Solve()
{
    /*
        Implementation Notes:
        ---------------------
        1. Read inputs.
        2. Apply transformations / precomputations.
        3. Implement main logic.
        4. Output the result.
    */

    // your code here
}

// -----------------------------------------------------------------------------
// 🏁 MAIN DRIVER
// -----------------------------------------------------------------------------
int32_t main()
{
    zanj0();

    // For multiple test cases:
    // w(t) Solve();

    // For single test case:
    // Solve();

    timetaken;
    return 0;
}

/*
    GOLDEN RULES
    • Solutions are simple.
    • Proofs are simple.
    • Implementations are simple.
*/
