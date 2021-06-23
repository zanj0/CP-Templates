pair <int, int> operator -(const pair <int, int>& a, const pair <int, int>& b) {
	return {a.ff - b.ff, a.ss - b.ss};
}
int cross(const pair <int, int>& a, const pair <int, int>& b) {
	return a.ff * b.ss - a.ss * b.ff;
}


== == == == == == == == == == == == == == == == == == == == == == == == == == == =
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
#define MOD             1000000007
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
pair <int, int> operator -(const pair <int, int>& a, const pair <int, int>& b) {
	return {a.ff - b.ff, a.ss - b.ss};
}
int cross(const pair <int, int>& a, const pair <int, int>& b) {
	return a.ff * b.ss - a.ss * b.ff;
}
const int N = 1e5 + 5;
int n;
pair <int, int> pts[N];
bool used[N];
bool check() {
	int i1 = -1, i2 = -1;
	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		if (i1 == -1) i1 = i;
		else if (i2 == -1) i2 = i;
	}
	if (i2 == -1) return true;
	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		if (cross(pts[i2] - pts[i1], pts[i] - pts[i1]) != 0) return false;
	}
	return true;
}
bool check2(pair <int, int>& a, pair <int, int>& b) {
	for (int i = 0; i < n; i++) used[i] = 0;
	for (int i = 0; i < n; i++) {
		if (cross(b - a, pts[i] - a) == 0) {
			used[i] = true;
		}
	}
	return check();
}
void solve() {

	cin >> n;
	if (n <= 2) {
		cout << "YES" << endl;
		return;
	}
	for (int i = 0; i < n; i++) {
		cin >> pts[i].ff >> pts[i].ss;
	}
	if (check2(pts[0], pts[1]) || check2(pts[0], pts[2]) || check2(pts[1], pts[2])) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}
int32_t main()
{
	zanj0();
	solve();
	timetaken;
	return 0;
}