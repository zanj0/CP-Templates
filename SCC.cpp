const int N = 3e5 + 5;
vector<int> graph[N];
bool onStack[N], visited[N];
int low[N], disc[N], d;
stack<int> st;
map<int, int> component;
int componentNum = 1;
void dfs(int node, int par = -1) {
	visited[node] = true;
	onStack[node] = true;
	st.push(node);
	low[node] = disc[node] = d;
	d++;
	for (auto& it : graph[node]) {
		if (it == par) continue; // Remove this for directed graph.
		if (!visited[it]) {
			dfs(it, node);
			low[node] = min(low[node], low[it]);
		} else if (onStack[it]) {
			low[node] = min(low[node], disc[it]);
		}
	}
	if (low[node] == disc[node]) {
		while (1) {
			int curr = st.top();
			st.pop();
			component[curr] = componentNum;
			onStack[curr] = false;
			if (node == curr) break;
		}
		componentNum++;
	}
}