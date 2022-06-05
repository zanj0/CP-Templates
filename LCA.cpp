const int N = 1e5 + 5;
const int K = 25;
int level[N];
int dp[K][N];
int subtreeSize[N];
int n, u, v, l;
vector <int> graph[N];
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