/*
	JAI JAGANNATH!

	Regex to select alternate lines: .*\n.*\n
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
void Solve() {
	string s;
	set<string> followers;
	bool follow = false;
	while (getline(cin, s)) {
		// cout << s << endl;
		if (s == "***") {
			follow = true;
			continue;
		}
		if (follow) {
			if (!followers.count(s)) {
				cout << s << endl;
			}
		} else {
			followers.insert(s);
		}

	}
}
int32_t main()
{
	zanj0();
	Solve();
	timetaken;
	return 0;
}