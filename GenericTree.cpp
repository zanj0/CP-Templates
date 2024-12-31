//URL : https://atcoder.jp/contests/abc375/submissions/58700027
struct Tree {
    vector<vector<int>> adj, lift;
    vector<int> d, tin, tout, par;
    int n, timer;
    bool initialized = false;
    bool dfsed = false;

    void init(int nn) {
        n = nn;
        adj.resize(n + 1);
        d.resize(n + 1);
        lift.resize(n + 1);
        tin.resize(n + 1);
        tout.resize(n + 1);
        par.resize(n + 1);
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 0; i <= n; i++) lift[i].resize(20, 0);
        initialized = true;
    }

    void addEdge(int u, int v) {
        if (!initialized) {
            cout << "STUPID INITIALIZE\n";
            exit(0);
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build() {
        for (int j = 1; j < 20; j++) {
            for (int i = 1; i <= n; i++) {
                lift[i][j] = lift[lift[i][j - 1]][j - 1];
            }
        }
    }

    void dfs(int u, int par1) {
        par[u] = par1;
        tin[u] = ++timer;
        for (int v : adj[u]) {
            if (v != par1) {
                d[v] = d[u] + 1;
                lift[v][0] = u;
                dfs(v, u);
            }
        }
        tout[u] = timer;
    }

    void dfs(int root = 1) {
        if (!initialized) {
            cout << "STUPID INITIALIZE\n";
            exit(0);
        }
        d[root] = 0;
        timer = 0;
        dfs(root, 0);
        build();
        dfsed = true;
    }

    int jump(int x, int depth) {
        for (int i = 0; i < 20; i++) if (depth >> i & 1) {
                x = lift[x][i];
            }
        return x;
    }

    int lca(int a, int b) {
        if (!dfsed) {
            cout << "STUPID DFS\n";
            exit(0);
        }
        if (d[a] < d[b]) swap(a, b);
        int del = d[a] - d[b];
        for (int i = 0; i < 20; i++) if (del >> i & 1) a = lift[a][i];

        if (a == b) return a;

        for (int i = 19; i >= 0; i--) if (lift[a][i] != lift[b][i]) {
                a = lift[a][i];
                b = lift[b][i];
            }
        return lift[a][0];
    }

    int dist(int a, int b) {
        return d[a] + d[b] - 2 * d[lca(a, b)];
    }

    bool anc(int x, int y) {
        return tin[x] <= tin[y] && tout[x] >= tout[y];
    }
};