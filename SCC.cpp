const int N = 3e5 + 5;
vector<int> graph[N];
bool onStack[N], visited[N];
int low[N], disc[N], d;
stack<int> st;
map<int, int> component;
int componentNum = 1;
map<int, int> componentSize;
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
			componentSize[componentNum]++;
			onStack[curr] = false;
			if (node == curr) break;
		}
		componentNum++;
	}
}

void Pre(int n) {
	for (int i = 0; i <= n; i++) {
		graph[i].clear();
		onStack[i] = false;
		visited[i] = false;
		low[i] = 0;
		disc[i] = 0;
		component[i] = 0;
		componentNum = 1;
		componentSize[i] = 0;
	}
	while (!st.empty()) st.pop();
}