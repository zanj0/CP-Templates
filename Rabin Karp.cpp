typedef long long int lli;
const int HASH = 3137;
const int MOD = 1e9 + 7;
lli pows[200005];
bool init = false;
void genPows() {
	if (init) return;
	init = true;
	pows[0] = 1;
	for (int i = 1; i <= 200000; i++) {
		pows[i] = (pows[i - 1] * HASH) % MOD;
	}
}
lli hashval[200005];
lli getHash(lli lhs, lli rhs) {
	lli val = hashval[rhs] - (hashval[lhs] * pows[rhs - lhs]);
	val %= MOD;
	if (val < 0) val += MOD;
	return val;
}
bool match(int s1, int s2, int len) {
	return getHash(s1, s1 + len) == getHash(s2, s2 + len);
}

genPows();

for (int i = 0; i < 2 * n; i++) {
	hashval[i + 1] = (hashval[i] * HASH + s[i % n]) % MOD;
}