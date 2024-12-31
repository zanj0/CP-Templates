// Refer: https://atcoder.jp/contests/abc375/submissions/58841326

template <class T>
using must_int = enable_if_t<is_integral<T>::value, int>;
template <unsigned umod>
struct modint {
    static constexpr int mod = umod;
    unsigned v;
    modint() : v(0) {}
    template <class T, must_int<T> = 0>
    modint(T _v) {int x = _v % (int)umod; v = x < 0 ? x + umod : x;}
    modint operator+() const { return *this; }
    modint operator-() const { return modint() - *this; }
    friend int raw(const modint &self) { return self.v; }
    friend ostream &operator<<(ostream &os, const modint &self) { return os << raw(self);}
    modint &operator+=(const modint &rhs) {v += rhs.v; if (v >= umod) v -= umod; return *this;}
    modint &operator-=(const modint &rhs) {v -= rhs.v; if (v >= umod) v += umod; return *this;}
    modint &operator*=(const modint &rhs) {v = 1ull * v * rhs.v % umod; return *this;}
    modint &operator/=(const modint &rhs) { return *this *= rhs.inv(); }
    modint inv() const {
        assert(v);
        static unsigned lim = 1 << 21;
        static vector<modint> inv{0, 1};
        if (v >= lim) return qpow(*this, mod - 2);
        inv.reserve(v + 1);
        while (v >= inv.size()) {
            int m = inv.size();
            inv.resize(m << 1);
            for (int i = m; i < m << 1; i++)inv[i] = (mod - mod / i) * inv[mod % i];
        }
        return inv[v];
    }
    template <class T, must_int<T> = 0>
    friend modint qpow(modint a, T b) {modint r = 1; for (; b; b >>= 1, a *= a)if (b & 1) r *= a; return r;}
    friend modint operator+(modint lhs, const modint &rhs) { return lhs += rhs; }
    friend modint operator-(modint lhs, const modint &rhs) { return lhs -= rhs; }
    friend modint operator*(modint lhs, const modint &rhs) { return lhs *= rhs; }
    friend modint operator/(modint lhs, const modint &rhs) { return lhs /= rhs; }
    friend bool operator==(const modint &lhs, const modint &rhs) { return lhs.v == rhs.v; }
    friend bool operator!=(const modint &lhs, const modint &rhs) { return lhs.v != rhs.v; }
};
using m1 = modint<998244353>;
using m2 = modint<1000000007>;
using m3 = modint<1000000009>;