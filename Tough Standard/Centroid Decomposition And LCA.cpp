// Link: https://codeforces.com/contest/342/submission/159531558
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
const int N = 1e5 + 5;
const int B = 320;

const int K = 25;
int level[N];
int dp[K][N];
int subtreeSize[N];
int n, u, v, l, q;
set <int> graph[N];
int dist[N];
void dfs0(int node, int parent) {
	dp[0][node] = parent;
	subtreeSize[node] = 1;
	for (auto& it : graph[node]) {
		if (it == parent) continue;
		level[it] = 1 + level[node];
		dfs0(it, node);
		subtreeSize[node] += subtreeSize[it];
	}
}
int getp(int node, int k) {
	for (int i = 0; i < K; i++) {
		if ((k & (1 << i))) node = dp[i][node];
	}
	return node;
}
int lca(int x, int y) {
	if (x == y) return x;
	if (level[x] > level[y]) {
		swap(x, y);
	}
	y = getp(y, level[y] - level[x]);
	if (x == y) return x;
	for (int i = K - 1; i > -1; i--) {
		if (dp[i][x] != dp[i][y]) {
			x = dp[i][x];
			y = dp[i][y];
		}
	}
	return dp[0][x];
}
void pre() {
	memset(dp, -1, sizeof dp);
	dfs0(1, 0);
	for (int i =	1; i < K; i++) {
		for (int j = 1; j <= n; j++) {
			if (dp[i - 1][j] != -1) {
				dp[i][j] = dp[i - 1][dp[i - 1][j]];
			}
		}
	}
}
int GetDistance(int u, int v) {
	int l = lca(u, v);
	return level[u] + level[v] - 2 * level[l];
}

int parent[N];
int sz[N];
void dfs2(int node, int par) {
	sz[node] = 1;
	for (auto& it : graph[node]) {
		if (it == par) continue;
		dfs2(it, node);
		sz[node] += sz[it];

	}
}
int getCentroid(int node, int par, int currSize) {
	for (auto& it : graph[node]) {
		if (it != par && sz[it] > currSize / 2) return getCentroid(it, node, currSize);
	}
	return node;
}
void dfs1(int node, int par) {
	dfs2(node, 0);
	int currSize = sz[node];
	int centroid = getCentroid(node, par, currSize);
	parent[centroid] = par;
	set <int> children = graph[centroid];
	for (auto& it : children) {
		graph[centroid].erase(it);
		graph[it].erase(centroid);
		dfs1(it, centroid);
	}

}

void Solve() {
	cin >> n;
	cin >> q;
	for (int i = 1; i <= n; i++) {
		dist[i] = inf;
	}
	for (int i = 0, u, v; i < n - 1; i++) {
		cin >> u >> v;
		graph[u].insert(v);
		graph[v].insert(u);
	}
	pre(); // Calculate LCA.
	dfs1(1, 0); // Centroid decomposition.
	dist[1] = 0;
	for (int i = 2; i <= n; i++) {
		dist[i] = GetDistance(i, 1);
	}
	for (int i = 0, type, x; i < q; i++) {
		cin >> type >> x;
		if (type == 1) {
			dist[x] = 0;
			int curr = x;
			curr = parent[curr];
			while (curr) {
				dist[curr] = min(dist[curr], GetDistance(curr, x));
				curr = parent[curr];
			}
		} else {
			int ret = dist[x];
			int curr = x;
			curr = parent[curr];
			while (curr) {
				ret = min(ret, dist[curr] + GetDistance(curr, x));
				curr = parent[curr];
			}
			cout << ret << endl;

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