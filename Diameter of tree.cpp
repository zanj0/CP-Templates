const int N = 3e5 + 5;
set<int> graph2[N];
int hero, dist;
void dfs2(int node, int par = -1, int d = 0) {
	if (dist < d) {
		dist = d;
		hero = node;
	}
	for (auto& it : graph2[node]) {
		if (it == par) continue;
		dfs2(it, node, d + 1);
	}
}
int getDiameter() {
	hero = 1;
	dfs2(1);
	dist = 0;
	dfs2(hero);
	return dist;
}