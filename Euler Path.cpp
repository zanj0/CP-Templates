const int N = 1e5 + 5;
int n;
set <pair<int, int>> graph[N];
map<int, int> in, out;
vector<int> path;
void dfs(int node) {
	while (graph[node].size()) {
		auto it = *(graph[node].begin());
		graph[node].erase(graph[node].begin());
		dfs(it.first);
	}
	path.push_back(node); // Use dfs(getStart());reverse(path.begin(), path.end());

}
bool possible() {
	int start = 0;
	int end = 0;
	for (int i = 0; i < n; i++) {
		if (abs(in[i] - out[i] > 1)) return false;
		if (in[i] - out[i] == 1)end++;
		else if (out[i] - in[i] == 1)start++;
	}
	return (end == 0 && start == 0) || (start == 1 && end == 1);
}
int getStart() {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (out[i] - in[i] == 1) return i;
		if (out[i] > 0) ret = i;
	}
	return ret;
}
*********************

const int N = 1e5 + 5;
int n;
set <pair<int, int>> graph[N];
map<int, int> in, out;
vector<int> path;
void dfs(int node) {
	while (graph[node].size()) {
		auto it = *(graph[node].begin());
		graph[node].erase(graph[node].begin());
		dfs(it.first);
	}
	path.push_back(node); // Use dfs(getStart());reverse(path.begin(), path.end());

}
bool possible() {
	int start = 0;
	int end = 0;
	for (int i = 0; i < n; i++) {
		if (abs(in[i] - out[i] > 1)) return false;
		if (in[i] - out[i] == 1)end++;
		else if (out[i] - in[i] == 1)start++;
	}
	return (end == 0 && start == 0) || (start == 1 && end == 1);
}
int getStart() {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (out[i] - in[i] == 1) return i;
		if (out[i] > 0) ret = i;
	}
	return ret;
}

class Solution {
public:

	map<int, vector<int>> idToEdge;
	map<int, int> nodeToId, idToNode;

	void pre() {
		out.clear();
		in.clear();
		path.clear();
		for (int i = 0; i < n; i++) {
			graph[i].clear();
		}
	}

	void populateGraph(vector<vector<int>>& v) {
		for (auto& it : v) {
			nodeToId[it[0]] = 0;
			nodeToId[it[1]] = 0;
		}
		int curr = 0;
		for (auto& it : nodeToId) {
			it.second = curr;
			curr++;
			idToNode[it.second] = it.first;
		}
		n = curr;
		pre();
		for (int i = 0; i < v.size(); i++) {
			idToEdge[i] = v[i];
			int x = nodeToId[v[i][0]];
			int y = nodeToId[v[i][1]];
			graph[x].insert({y, i});
			out[x]++;
			in[y]++;
		}
	}

	vector<vector<int>> validArrangement(vector<vector<int>>& v) {
		vector<vector<int>> ret;
		populateGraph(v);
		dfs(getStart());
		reverse(path.begin(), path.end());
		for (int i = 0; i + 1 < path.size(); i++) {
			ret.push_back({idToNode[path[i]], idToNode[path[i + 1]]});
		}
		return ret;
	}
};

Link: https://leetcode.com/contest/weekly-contest-270/problems/valid-arrangement-of-pairs/