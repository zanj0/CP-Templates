class LCA {
public:
	lli* level;
	lli** dp;
	vector < vector <lli> > graph;
	lli l;
	lli n;
	LCA(lli l, lli n, vector < vector <lli> > graph) {
		this->l = l;
		this->n = n;
		this->graph = graph;
		level = new lli [n + 5];
		dp = new lli* [l + 5];
		for (lli i = 0; i <= l; i++) {
			dp[i] = new lli[n + 5];
		}
	}
	void dfs0(lli node, lli parent) {
		dp[0][node] = parent;
		for (auto& it : graph[node]) {
			if (it == parent) continue;
			level[it] = 1 + level[node];
			dfs0(it, node);
		}
	}
	lli getp(lli node, lli k) {
		for (lli i = 0; i <= l; i++) {
			if ((k & (1 << i))) node = dp[i][node];
		}
		return node;
	}
	lli lca(lli x, lli y) {
		if (x == y) return x;
		if (level[x] > level[y]) {
			swap(x, y);
		}
		y = getp(y, level[y] - level[x]);
		if (x == y) return x;
		for (lli i = l; i > -1; i--) {
			if (dp[i][x] != dp[i][y]) {
				x = dp[i][x];
				y = dp[i][y];
			}
		}
		return dp[0][x];
	}
	void pre() {
		for (lli i = 0; i <= l; i++) {
			for (lli j = 0; j <= n; j++ ) {
				dp[i][j] = -1;
			}
		}

		dfs0(1, 0);
		for (lli i =	1; i <= l; i++) {
			for (lli j = 1; j <= n; j++) {
				if (dp[i - 1][j] != -1) {
					dp[i][j] = dp[i - 1][dp[i - 1][j]];
				}
			}
		}

	}
};