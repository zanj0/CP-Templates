// https://atcoder.jp/contests/abc340/tasks/abc340_g
/*
	JAI JAGANNATH!
*/
//@Author : zanj0

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set =  __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;


#define int 			long long int
#define LOCAL
#define ff              first
#define ss              second
#define pb              push_back
#define MOD             998244353
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
vector<int> graph[N], virtual_tree[N];
const int K = 20;
int level[N], dp[N][K], low[N], high[N], dfs_time = 0, n, colour[N];
map<int, set<int>> colour_to_nodes;
void Dfs(int node, int par = 0) {
	dp[node][0] = par;
	dfs_time++;
	low[node] = dfs_time;
	for (auto& it : graph[node]) {
		if (it == par) continue;
		level[it] = level[node] + 1;
		Dfs(it,  node);
	}
	dfs_time++;
	high[node] = dfs_time;
}

void Pre() {
	Dfs(1);
	for (int j = 1; j < K; j++) {
		for (int i = 1; i <= n; i++) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
	}
}
int GetBit(int mask, int idx) {
	return (mask >> idx) & 1;
}
int GetKthParent(int node, int distance) {
	int ret = node;
	for (int i = 0; i < K; i++) {
		if (GetBit(distance, i)) ret = dp[ret][i];
	}
	return ret;
}
bool IsAncestor(int parent, int child) {
	return low[parent] <= low[child] && high[parent] >= high[child];
}
int GetLca(int u, int v) {
	if (level[u] < level[v]) swap(u, v);
	u = GetKthParent(u, level[u] - level[v]);
	if ( u == v) return u;
	for (int i = K - 1; i >= 0; i--) {
		if (dp[u][i] != dp[v][i]) {
			u = dp[u][i];
			v = dp[v][i];
		}
	}
	return dp[u][0];
}
void BuildVirtualTree(vector<int>& nodes) {
	auto SortByDfsTime = [&](int node_1, int node_2) {
		return low[node_1] < low[node_2];
	};
	sort(nodes.begin(), nodes.end(), SortByDfsTime);
	int node_size = nodes.size();
	for (int i = 0; i < node_size - 1; i++) {
		nodes.pb(GetLca(nodes[i], nodes[i + 1]));
	}
	sort(nodes.begin(), nodes.end(), SortByDfsTime);
	nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

	node_size = nodes.size();
	for (int i = 0; i < node_size - 1; i++) {
		int u = GetLca(nodes[i], nodes[i + 1]);
		int v = nodes[i + 1];
		virtual_tree[u].pb(v);
		virtual_tree[v].pb(u);
	}

}

// void BuildVirtualTree2(vector<int>& nodes) {
// 	auto SortByDfsTime = [&](int node_1, int node_2) {
// 		return low[node_1] < low[node_2];
// 	};
// 	sort(nodes.begin(), nodes.end(), SortByDfsTime);
// 	int node_size = nodes.size();
// 	for (int i = 0; i < node_size - 1; i++) {
// 		nodes.pb(GetLca(nodes[i], nodes[i + 1]));
// 	}
// 	sort(nodes.begin(), nodes.end(), SortByDfsTime);
// 	nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
// 	stack<int> node_stack;
// 	node_size = nodes.size();
// 	node_stack.push(nodes[0]);
// 	for (int i = 1; i < node_size; i++) {
// 		while (node_stack.size() >= 2 && !IsAncestor(node_stack.top(), nodes[i])) {
// 			int u = node_stack.top();
// 			node_stack.pop();
// 			int v = node_stack.top();
// 			virtual_tree[u].pb(v);
// 			virtual_tree[v].pb(u);
// 		}
// 		node_stack.push(nodes[i]);
// 	}
// 	while (node_stack.size() >= 2) {
// 		int u = node_stack.top();
// 		node_stack.pop();
// 		int v = node_stack.top();
// 		virtual_tree[u].pb(v);
// 		virtual_tree[v].pb(u);
// 	}
// }
int Add(int a, int b) {
	return ((a % MOD) + (b % MOD)) % MOD;
}
int Mul(int a, int b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
int Sub(int a, int b) {
	return ((a % MOD) - (b % MOD) + MOD) % MOD;
}
int ret = 0;
int Dfs2(int node, int par, set<int>& coloured_nodes) {
	int now = 1;
	int sum = 0;
	for (auto& it : virtual_tree[node]) {
		if (it == par) continue;
		int temp = Dfs2(it, node, coloured_nodes);
		sum = Add(sum, temp);
		now = Mul(now, Add(1, temp));
	}

	if (coloured_nodes.count(node)) {
		ret = Add(ret, now);

	} else {
		now = Sub(now, 1);
		ret = Add(ret, Sub(now, sum));
	}
	return now;
}

void Solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> colour[i];
		colour_to_nodes[colour[i]].insert(i);
	}
	for (int i = 1, u, v; i <= n - 1; i++) {
		cin >> u >> v;
		graph[u].pb(v);
		graph[v].pb(u);
	}
	Pre();
	ret = 0;
	for (int i = 1; i <= n; i++) {
		set<int> nodes = colour_to_nodes[i];
		if (nodes.empty()) continue;
		vector<int> nodes_vector = vector<int>(nodes.begin(), nodes.end());
		BuildVirtualTree(nodes_vector);
		Dfs2(nodes_vector[0], 0, nodes);
		for (auto& it : nodes_vector) virtual_tree[it].clear();
	}
	cout << ret << endl;
}
int32_t main()
{
	zanj0();
	Solve();
	timetaken;
	return 0;
}