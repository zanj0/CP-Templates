/*
	JAI JAGANNATH!
*/
//@Author : zanj0

#include<bits/stdc++.h>
using namespace std;

typedef long long int lli;

#define ff              first
#define ss              second
#define pb              push_back
#define mod             1000000007
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define w(x)            lli x; cin>>x; while(x--)


const lli N = 2e5 + 5;
vector <lli> edges[N];
lli tree[4 * N];
lli start[N], finish[N], tme[N];
lli a[N], b[305];
lli p;
bool flag = false;
bool check(lli x) {
	for (lli i = 3; i * i <= x; i += 2) {
		if (x % i == 0) return false;
	}
	return true;
}
void pre() {

	flag = true;
	lli x = 1ll;
	b[2] = 1;
	for (lli i = 3; i <= 300; i += 2) {
		if (check(i)) {
			b[i] = (1ll << x);
			x++;
		}
	}
}
void clean(lli n) {
	for (lli i = 0; i <= n; i++) {
		edges[i].clear();
		a[i] = 0;
		start[i] = 0;
		finish[i] = 0;
		tme[i] = 0;
		tree[i] = 0;
	}
	p = 0;
	for (lli i = n + 1; i <=  4 * n; i++) {
		tree[i] = 0;
	}
}
void dfs(lli node, lli parent) {
	//cout << node << " " << parent << endl;
	p++;
	start[node] = p;
	tme[p] = node;
	for (auto& it : edges[node]) {
		if (it != parent) dfs(it, node);
	}
	finish[node] = p;
}
void build(lli i, lli l, lli r) {
	if (l == r) {
		tree[i] = a[tme[l]];
		return;
	}
	lli m = (l + r) >> 1;
	build(i + i, l, m);
	build(i + i + 1, m + 1, r);
	tree[i] = tree[i + i] | tree[(i + i) + 1];
}
void update(lli i, lli l, lli r, lli x, lli val) {
	if (l == r) {
		tree[i] = val;
		return;
	}
	lli m = (l + r) >> 1;
	if (x >= l && x <= m) {
		update(i + i, l, m, x, val);
	} else {
		update(i + i + 1, m + 1, r, x, val);
	}
	tree[i] = tree[2 * i] | tree[(2 * i) + 1];
}
lli query(lli i, lli l, lli r, lli x, lli y) {
	if (r < x || l > y || l > r) return 0ll;
	if (x <= l && y >= r) return tree[i];
	lli m = (l + r) >> 1;
	return (query(i + i, l, m, x, y)) | (query(i + i + 1, m + 1, r, x, y));
}
vector<int> Solution :: solve(int n, vector<int> &arr, vector<vector<int> > &C, vector<vector<int> > &q) {
	vector <int> ret;
	pre();
	clean(n);
	for (auto& it : C) {
		//cout << it[0] << " " << it[1] << endl;
		edges[it[0]].pb(it[1]);
		edges[it[1]].pb(it[0]);
	}
	for (lli i = 0; i < n; i++) {
		a[i + 1] = b[arr[i]];
	}
	dfs(1, 0);
	build(1, 1, n);
	for (lli i = 0; i < q.size(); i++) {
		lli type = q[i][0];
		if (type == 0) {
			lli index = start[q[i][1]];
			lli val = b[(q[i][2])];
			update(1, 1, n, index, val);
			ret.pb(-1);
		} else {
			lli y = query(1, 1, n, start[q[i][1]], finish[q[i][1]]);
			lli val = __builtin_popcountll(y);
			ret.pb(val);
		}
	}
	return ret;
}
