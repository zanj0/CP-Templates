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
const int N = 2e5 + 5;
const int K = 25;
int level[N];
int dp[K][N];
int maxWeight[K][N];
int subtreeSize[N];
int n, u, v, l, m;
int ret[N];
vector < pair <int, int> > graph[N];
void dfs0(int node, int parent, int wt) {
	dp[0][node] = parent;
	maxWeight[0][node] = wt;

	subtreeSize[node] = 1;
	for (auto& it : graph[node]) {
		if (it.ff == parent) continue;
		level[it.ff] = 1 + level[node];
		dfs0(it.ff, node, it.ss);
		subtreeSize[node] += subtreeSize[it.ff];
	}
}

int lca(int x, int y) {
	int ret = 0;
	if (x == y) return 0;
	if (level[x] > level[y]) {
		swap(x, y);
	}
	int diff = level[y] - level[x];
	for (int i = 0; i < K; i++) {
		if ((diff & (1 << i))) {
			ret = max(ret, maxWeight[i][y]);
			y = dp[i][y];
		}
	}
	if (x == y) return ret;
	for (int i = K - 1; i > -1; i--) {
		if (dp[i][x] != dp[i][y]) {
			ret = max(ret, maxWeight[i][x]);
			ret = max(ret, maxWeight[i][y]);
			x = dp[i][x];
			y = dp[i][y];
		}
	}
	if (x != y) {
		ret = max(ret, maxWeight[0][x]);
		ret = max(ret, maxWeight[0][y]);
		x = dp[0][x];
		y = dp[0][y];
	}
	return ret;
}

void pre() {
	memset(dp, -1, sizeof dp);
	dfs0(1, 0, 0);
	for (int i =	1; i < K; i++) {
		for (int j = 1; j <= n; j++) {
			if (dp[i - 1][j] != -1) {
				dp[i][j] = dp[i - 1][dp[i - 1][j]];
				maxWeight[i][j] = max(maxWeight[i - 1][j], maxWeight[i - 1][dp[i - 1][j]]);
			}
		}
	}
}
class UnionFind {
public:
	int* rank;
	int* parent;
	int n;
	UnionFind(int n) {
		this->n = n;
		parent = new int[n];
		rank = new int[n];
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			rank[i] = 1;
		}
	}
	int getParent(int x) {
		if (parent[x] == x) return x;
		return parent[x] = getParent(parent[x]);
	}
	bool unite(int a, int b) {
		int parA = getParent(a);
		int parB = getParent(b);
		if (parA == parB) return false;
		if (rank[parA] >= rank[parB]) {
			rank[parA] += rank[parB];
			parent[parB] = parA;
		} else {
			rank[parB] += rank[parA];
			parent[parA] = parB;
		}
		return true;
	}
};
bool cmp(vector <int>& a, vector <int>& b) {
	return a[0] < b[0];
}
void solve() {

	cin >> n >> m;
	UnionFind uf = UnionFind(n + 5);
	vector < vector <int> > edges, org;
	for (int i = 0, u, v, w; i < m; i++) {
		cin >> u >> v >> w;
		edges.pb({w, u, v, i});
	}
	org = edges;
	sort(edges.begin(), edges.end(), cmp);
	int mst = 0;
	for (auto& it : edges) {
		int u = it[1];
		int v = it[2];
		if (uf.unite(u, v)) {
			ret[it.back()] = -1;
			mst += it[0];
			graph[u].pb({v, it[0]});
			graph[v].pb({u, it[0]});
		}
	}
	for (int i = 0; i < m; i++) {
		if (ret[i] == -1) ret[i] = mst;
	}
	pre();

	for (int i = 0; i < m; i++) {

		if (ret[i] != mst) {
			int maxEdgeWeight = lca(org[i][1], org[i][2]);
			// cout << org[i][1] << " " << org[i][2] << " " << maxEdgeWeight << endl;
			int newCost = mst - maxEdgeWeight + org[i][0];
			ret[i]  = newCost;
		}
	}
	for (int i = 0; i < m; i++) {
		cout << ret[i] << endl;
	}
}
int32_t main()
{
	zanj0();
	solve();
	timetaken;
	return 0;
}