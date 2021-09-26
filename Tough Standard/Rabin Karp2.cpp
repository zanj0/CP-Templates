/*
	JAI JAGANNATH!
*/
//@Author : zanj0

#include<bits/stdc++.h>
using namespace std;

#define int long long int
#define LOCAL
#define ff              first
#define ss              second
#define pb              push_back
#define MOD             1000000007
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define w(x)            int x; cin>>x; while(x--)
#define endl       		"\n"
#define timetaken cerr<<"Time : "<<1000*(long double)clock()/(long double)CLOCKS_PER_SEC<<"ms\n"

void zanj0()
{

#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}


void out(vector<int>& v) {
	for (int i : v) {
		cout << i << " ";
	}
	cout << endl;
}
char s[2048], sbeg[2048], send[2048];
int H1[2048][2048], H2[2048][2048];
int big = 1e9 + 10, m1 = 1e9 + 7, m2 = 1e9 + 9, base = 727;
void solve() {

	scanf("%s%s%s", s, sbeg, send);
	int n = strlen(s), n1 = strlen(sbeg), n2 = strlen(send);
	vector<int> v1(n);
	vector<int> v2(n);
	for (int i = 0; i + n1 <= n; i++)
		if (!strncmp(s + i, sbeg, n1))
			v1[i] = 1;
	for (int i = 0; i + n2 <= n; i++)
		if (!strncmp(s + i, send, n2))
			v2[i + n2 - 1] = 1;
	int ret = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (i == j) H1[i][j] = H2[i][j] = s[i] - 'a' + 1;
			else {
				H1[i][j] = (H1[i][j - 1] * base + s[j] - 'a' + 1) % m1;
				H2[i][j] = (H2[i][j - 1] * base + s[j] - 'a' + 1) % m2;
			}
		}
	}
	unordered_set<int> st;
	for (int i = 0; i < v1.size(); i++) {
		if (!v1[i]) continue;
		for (int j = i; j < v2.size(); j++) {


			if (v2[j] && (j - i + 1) >= max(n1, n2)) {
				st.insert(H1[i][j] * big + H2[i][j]);

			}
		}
	}
	ret = st.size();
	cout << ret << endl;
}
int32_t main()
{
	zanj0();
	solve();
	timetaken;
	return 0;
}