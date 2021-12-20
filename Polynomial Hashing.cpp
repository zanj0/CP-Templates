const int MOD = 1e9 + 7;
int mul(int a, int b, int MOD) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
int sub(int a, int b, int MOD) {
	return ((a % MOD) - (b % MOD) + MOD) % MOD;
}
int add(int a, int b, int MOD) {
	return ((a % MOD) + (b % MOD)) % MOD;
}
//Also called polynomial hashing.
//Use double hashing to avoid getting hacked.
struct StringHash {
	int base = 255;

	string s;
	int n;
	vector<int> pre; //hash of prefix of length i.
	vector<int> powb; //base ^ i (MOD MODs)

	//O(n)
	StringHash(string _s = "") : s(_s) {
		n = s.size();
		pre.resize(n + 1);
		powb.resize(n + 1);
		pre[0] = 0;
		powb[0] = 1;
		for (int i = 0; i < n; i++) {
			pre[i + 1] = add(mul(pre[i], base, MOD), s[i], MOD);
			powb[i + 1] = mul(powb[i], base, MOD);
		}
	}

	//Returns hash of the substring of length len starting at pos. i
	//O(1)
	int hash(int i, int len) {
		if (!len) return 0;
		len = min(len, n - i);   //Note
		int j = i + len - 1;
		int ans;
		ans = sub(pre[j + 1], mul(pre[i], powb[len], MOD), MOD);
		return ans;
	}
};

------------------
// Link: https://codeforces.com/contest/7/submission/139715116
/*
	JAI JAGANNATH!
*/
//@Author : zanj0

#include<bits/stdc++.h>
using namespace std;

#define int 			long long int
#define LOCAL
#define ff              first
#define ss              second
#define pb              push_back
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define w(x)            int x; cin>>x; while(x--)
#define endl       		"\n"
#define timetaken cerr<<"Time : "<<1000*(long double)clock()/(long double)CLOCKS_PER_SEC<<"ms\n"

void zanj0()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}
const int MOD = 1e9 + 7;
int mul(int a, int b, int MOD) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
int sub(int a, int b, int MOD) {
	return ((a % MOD) - (b % MOD) + MOD) % MOD;
}
int add(int a, int b, int MOD) {
	return ((a % MOD) + (b % MOD)) % MOD;
}
//Also called polynomial hashing.
//Use double hashing to avoid getting hacked.
struct StringHash {
	int base = 255;

	string s;
	int n;
	vector<int> pre; //hash of prefix of length i.
	vector<int> powb; //base ^ i (MOD MODs)

	//O(n)
	StringHash(string _s = "") : s(_s) {
		n = s.size();
		pre.resize(n + 1);
		powb.resize(n + 1);
		pre[0] = 0;
		powb[0] = 1;
		for (int i = 0; i < n; i++) {
			pre[i + 1] = add(mul(pre[i], base, MOD), s[i], MOD);
			powb[i + 1] = mul(powb[i], base, MOD);
		}
	}

	//Returns hash of the substring of length len starting at pos. i
	//O(1)
	int hash(int i, int len) {
		if (!len) return 0;
		len = min(len, n - i);   //Note
		int j = i + len - 1;
		int ans;
		ans = sub(pre[j + 1], mul(pre[i], powb[len], MOD), MOD);
		return ans;
	}
};
void solve() {
	string s;
	cin >> s;
	string r = s;
	reverse(r.begin(), r.end());
	int n = s.size();
	int ret = 0;
	vector<int> dp(n);
	StringHash hashS(s);
	StringHash hashR(r);
	for (int i = 0; i < n; i++) {
		int hs = hashS.hash(0, i + 1);
		int ht = hashR.hash(n - i - 1, i + 1);
		if (hs == ht) {
			dp[i] = dp[(i - 1) / 2] + 1;
		}
		ret += dp[i];
	}
	cout << ret << endl;

}
int32_t main()
{
	zanj0();
	solve();
	timetaken;
	return 0;
}