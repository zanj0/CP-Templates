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

typedef int lli;

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

    Find all the subsequences of given elements -> Find AND

    Now we need to find the XOR of 2 subsequences of the remaining elements.

    Let's XOR of a subset of remaining sequence be XOR(A).
    Other XOR will be XOR(B) if S is the total XOR then
    XOR(A) + XOR(B) = XOR(A) + (S ^ XOR(A))

    XOR(A) = x
    Total XOR = s
    XOR(B) = s ^ x

    a + b = (a ^ b) + 2(a & b)

    x + s^x = (x ^ (s ^ x)) + 2 (x & (s ^ x))
    = s + 2 (x & (s ^ x))
    = s + 2 (x & s!)


    Total = AND + s + 2 (x & s!)

    Claims:

────────────────────────────────────────────────────────────────────────
*/

const lli K = 31;
lli GetBit(lli mask, lli idx)
{
    return (mask >> idx) & 1;
}
void Insert(lli value, vector<lli> &basis)
{
    for (int i = K - 1; i >= 0; i--)
    {
        if (!GetBit(value, i))
            continue;
        if (!basis[i])
        {
            basis[i] = value;
            return;
        }
        value ^= basis[i];
    }
}
lli GetBestXor(vector<int> &nums, lli mask)
{
    lli complimentary_mask = ~mask;
    vector<lli> basis(K, 0);

    for (auto &it : nums)
        Insert(it & complimentary_mask, basis);

    lli ret = 0;
    for (int i = K - 1; i >= 0; --i)
        if ((ret ^ basis[i]) > ret)
            ret ^= basis[i];
    return ret;
}
class Solution
{
public:
    long long maximizeXorAndXor(vector<int> &nums)
    {
        long long ret = 0;
        lli n = nums.size();
        for (lli and_mask = 0; and_mask < (1 << n); and_mask++)
        {
            lli and_value = -1;
            lli xor_value = 0;
            vector<int> xor_candidates;
            for (int i = 0; i < n; i++)
            {
                if (GetBit(and_mask, i))
                {
                    if (and_value == -1)
                        and_value = nums[i];
                    else
                        and_value &= nums[i];
                }
                else
                {
                    xor_value ^= nums[i];
                    xor_candidates.pb(nums[i]);
                }
            }

            if (and_value == -1)
                and_value = 0;

            long long now = (long long)and_value + (long long)xor_value + 2L * (long long)GetBestXor(xor_candidates, xor_value);
            ret = max(ret, now);
        }
        return ret;
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