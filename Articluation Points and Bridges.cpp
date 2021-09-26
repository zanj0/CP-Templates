/*
    JAI JAGANNATH!
*/
//@Author : zanj0
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef long long int lli;
#define ff              first
#define ss              second
#define pb              push_back
#define mp              make_pair
#define pii             pair<lli,lli>
#define vi              vector<lli>
#define mii             map<lli,lli>
#define pqb             priority_queue<lli>
#define pqs             priority_queue<lli,vi,greater<lli> >
#define setbits(x)      __builtin_popcountll(x)
#define zrobits(x)      __builtin_ctzll(x)
#define mod             1000000007
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define mk(arr,n,type)  type *arr=new type[n];
#define w(x)            lli x; cin>>x; while(x--)
mt19937                 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef tree<lli, null_type, less<lli>, rb_tree_tag, tree_order_statistics_node_update> pbds;


void zanj0()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

}
const lli N = 11;
vector <lli> graph[N + 1];
vector <lli> disc(N + 1);
vector <lli> low(N + 1);
lli d = 0;
lli n, m;
vector < vector <lli> > bridges;
vector <lli> artPoints(N + 1);
vector <lli> visited(N + 1);
bool cmp(vector <lli>& a, vector <lli>& b) {
	return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
}
void outV(vector <lli>& v) {
	for (lli i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}
void outVV(vector < vector <lli> >& v) {
	for (lli i = 0; i < v.size(); i++) {
		cout << v[i][0] << " " << v[i][1] << endl;
	}
	cout << endl;
}
void dfs(lli node, lli par, lli root, lli& outEdgeCnt) {
	if (par == root) outEdgeCnt++;
	visited[node] = 1;
	low[node] = disc[node] = d;
	d++;
	for (lli x : graph[node]) {
		if (x == par) continue;
		if (!visited[x]) {
			dfs(x, node, root, outEdgeCnt);
			low[node] = min(low[node], low[x]);
			if (disc[node] <= low[x]) {
				artPoints[node] = 1;
				if (disc[node] < low[x]) {
					bridges.push_back({node, x});
				}
			}
		} else  {
			low[node] = min(low[node], disc[x]);
		}
	}
}
void solve() {
	cin >> n >> m;
	for (lli i = 0, x, y; i < m; i++) {
		cin >> x >> y;
		graph[x].pb(y);
		graph[y].pb(x);
	}
	for (lli i = 0; i < n; i++) {
		if (!visited[i]) {
			lli outEdgeCnt = 0;
			dfs(i, -1, i, outEdgeCnt);
			artPoints[i] = outEdgeCnt > 1;
		}
	}
	vector <lli> art;
	for (lli i = 0; i < N; i++) {
		if (artPoints[i]) {
			art.push_back(i);
		}
	}
	cout << art.size() << endl;
	outV(art);
	sort(bridges.begin(), bridges.end(), cmp);
	cout << bridges.size() << endl;
	outVV(bridges);
}
int main()
{
	zanj0();
	solve();
	return 0;
}