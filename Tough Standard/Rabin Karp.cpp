#define mod 99194853094755497LL
#define p 100003
#define p2 1000003
#define ll long long

class Solution {
    bool compare(string &s1, string &s2) {
        return s1.size() < s2.size();
    }
    ll neg(ll a) {
        return (mod - (a % mod)) % mod;
    }

    ll add(ll a, ll b) {
        return (a + b) % mod;
    }

    ll sub(ll a, ll b) {
        return add(a, neg(b));
    }

    ll mul(ll a, ll b) {
        __int128 a2 = a, b2 = b;
        return (ll)((a2 * b2) % mod);
    }

    ll powa(ll a, ll b) {
        ll ans = 1;
        a %= mod;
        while (b > 0) {
            if (b % 2)
                ans = mul(ans, a);
            a = mul(a, a);
            b /= 2;
        }
        return ans;
    }
    ll minv(ll a) {
        return powa(a, mod - 2);
    }

    ll pp[100001], ipp[100001];
    ll pp2[100001], ipp2[100001];

    vector<vector<ll>> hash;
    vector<vector<ll>> hash2;

    void init(vector<vector<int>>& paths, int sz) {
        pp[0] = 1;
        ipp[0] = 1;
        pp2[0] = 1;
        ipp2[0] = 1;

        for (ll i = 1; i < sz; i++) {
            pp[i] = mul(pp[i - 1], p);
            ipp[i] = minv(pp[i]);
            pp2[i] = mul(pp2[i - 1], p2);
            ipp2[i] = minv(pp2[i]);
        }
        hash.resize(paths.size());
        hash2.resize(paths.size());

        for (ll i = 0; i < paths.size(); i++) {
            hash[i].resize(paths[i].size());
            hash[i][0] = paths[i][0];
            for (ll j = 1; j < paths[i].size(); j++)
                hash[i][j] = add(hash[i][j - 1], mul(paths[i][j], pp[j]));
            hash2[i].resize(paths[i].size());
            hash2[i][0] = paths[i][0];
            for (ll j = 1; j < paths[i].size(); j++)
                hash2[i][j] = add(hash2[i][j - 1], mul(paths[i][j], pp2[j]));
        }
    }

    ll find_hash(ll idx, ll l, ll r) {
        ll ans = hash[idx][r];
        if (l == 0)
            return ans;
        return mul(sub(ans, hash[idx][l - 1]), ipp[l]);
    }

    ll find_hash2(ll idx, ll l, ll r) {
        ll ans = hash2[idx][r];
        if (l == 0)
            return ans;
        return mul(sub(ans, hash2[idx][l - 1]), ipp2[l]);
    }

    bool find(vector<vector<int>>& pt, ll len) {
        unordered_set<ll> s, tmp;
        ll i, j, k;

        for (i = 0; i + len - 1 < pt[0].size(); i++)
            s.insert(find_hash(0, i, i + len - 1));

        for (i = 1; i < pt.size(); i++) {
            tmp.clear();
            for (j = 0; j + len - 1 < pt[i].size(); j++) {
                k = find_hash(i, j, j + len - 1);
                if (s.find(k) != s.end())
                    tmp.insert(k);
            }
            if (tmp.size() == 0)
                return false;
            s = tmp;
        }
        return true;
    }

    bool find2(vector<vector<int>>& pt, ll len) {
        unordered_set<ll> s, tmp;
        ll i, j, k;

        for (i = 0; i + len - 1 < pt[0].size(); i++)
            s.insert(find_hash2(0, i, i + len - 1));

        for (i = 1; i < pt.size(); i++) {
            tmp.clear();
            for (j = 0; j + len - 1 < pt[i].size(); j++) {
                k = find_hash2(i, j, j + len - 1);
                if (s.find(k) != s.end())
                    tmp.insert(k);
            }
            if (tmp.size() == 0)
                return false;
            s = tmp;
        }
        return true;
    }

public:
    ll longestCommonSubpath(ll n, vector<vector<int>>& paths) {
        ll m, i, j, k, mx;
        ll s = 0;
        ll e = paths[0].size();
        mx = 0;
        for (i = 0; i < paths.size(); i++) {
            e = min(e, (ll)paths[i].size());
            mx = max(mx, (ll)paths[i].size());
        }
        init(paths, mx);
        while (s < e) {
            m = (s + e + 1) / 2;
            if (find(paths, m))
                s = m;
            else
                e = m - 1;
        }

        return s;
    }
};