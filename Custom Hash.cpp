#include "bits/stdc++.h"
using namespace std;
#define ll long long
const int areTests = 1, MOD = 998244353;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

template <typename K, typename V, typename Hash = custom_hash>
using hash_map = gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = custom_hash>
using hash_set = hash_map<K, null_type, Hash>;




void run_test(int testcase) {
	ll n, x, ans = 0;
	cin >> n;

	hash_map <int, ll> dp0, dp1;
	dp0[-1] = 1;
	for (int i = 0; i < n; i++) {
		cin >> x;

		dp0[x] = (2 * dp0[x] + dp0[x - 1]) % MOD;
		dp1[x] = (2 * dp1[x] + dp0[x - 2]) % MOD;
		dp1[x + 2] = (2 * dp1[x + 2]) % MOD;
	}

	for (int i = 0; i <= n + 2; i++) {
		//cout << "! " << i << " " << dp0[i] << " " << dp1[i] << endl;
		ans = (ans + dp0[i]) % MOD;
		ans = (ans + dp1[i]) % MOD;
	}

	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(0);
#ifndef DUSH1729
	cin.tie(0);
#endif
	cout << fixed << setprecision(10);

	int t = 1;
	if (areTests) cin >> t;
	for (int i = 1; i <= t; i++) {
		run_test(i);
	}
}