const int MAX = 1e3 + 5;
int fac[MAX], finv[MAX];
int inv[MAX];
int nCr(int n, int r) {
	int ret = 1;
	for (int i = 1; i <= r; i++) {
		ret = ret  * (n - i + 1);
		ret /= i;
	}
	return ret;
}


void COMinit() {
	fac[0] = fac[1] = 1;
	finv[0] = finv[1] = 1;
	inv[1] = 1;
	for (int i = 2; i < MAX; i++) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
		finv[i] = finv[i - 1] * inv[i] % MOD;
	}
}
int COM(int n, int k) {
	if (n < k) return 0;
	if (n < 0 || k < 0) return 0;
	return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}
int add(int a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
	return a;
}
int mul(int a, int b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
int fastPow(int base, int p) {
	int ret = 1;
	while (p) {
		if (p & 1) ret = mul(ret, base);
		base = mul(base, base);
		p >>= 1;
	}
	return ret;
}

== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
const int N = 1e5 + 5;
int fact[N], inv[N];
int mul(int a, int b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
int fastPow(int base, int power) {
	int ret = 1;
	while (power > 0) {
		if (power & 1) {
			ret = mul(ret, base);
		}
		base = mul(base, base);
		power >>= 1;
	}
	return ret;
}
void pre() {
	fact[0] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = mul(fact[i - 1], i);
	}
	inv[N - 1] = fastPow(fact[N - 1], MOD - 2);
	for (int i = N - 2; i >= 0; i--) {
		inv[i] = mul(i + 1, inv[i + 1]);
	}
}
int nCr(int n, int r) {
	if ( r > n || r < 0) return 0;
	int ret = fact[n];
	ret = mul(ret, inv[r]);
	ret = mul(ret, inv[n - r]);
	return ret;
}
