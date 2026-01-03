// https://codeforces.com/contest/342/submission/159531558

const int N = 1e5 + 5;
set <int> graph[N];
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



------------------------------------------------------


const int N = 1e5 + 5;
set <int> graph[N];
char arr[N];

int sz[N];
void dfs0(int node, int par) {
	sz[node] = 1;
	for (auto& it : graph[node]) {
		if (it == par) continue;
		dfs0(it, node);
		sz[node] += sz[it];

	}
}
int getCentroid(int node, int par, int currSize) {
	for (auto& it : graph[node]) {
		if (it != par && sz[it] > currSize / 2) return getCentroid(it, node, currSize);
	}
	return node;
}
void dfs1(int node, int par, char curr = 'A') {
	dfs0(node, 0);
	int currSize = sz[node];
	int centroid = getCentroid(node, par, currSize);
	arr[centroid] = curr;
	set <int> children = graph[centroid];
	for (auto& it : children) {
		graph[centroid].erase(it);
		graph[it].erase(centroid);
		dfs1(it, centroid, curr + 1);
	}

}

-------------------------------------------

Usage: https://cses.fi/paste/685d697bf0f130d8ec8f37/

/*Centroid Decomposition - Start*/
lli n, k;
const lli N = 2e5 + 5;
vector<lli> graph[N];
bool dead[N];
lli subtree_size[N];
lli ret = 0;

void DfsSize(lli node, lli par)
{
    subtree_size[node] = 1;
    for (auto &it : graph[node])
    {
        if (it == par || dead[it])
            continue;
        DfsSize(it, node);
        subtree_size[node] += subtree_size[it];
    }
}

void DfsCollectDistance(lli node, lli par, lli distance, vector<lli> &distances)
{
    if (distance > k)
        return;
    distances.pb(distance);

    for (auto &it : graph[node])
    {
        if (it == par || dead[it])
            continue;
        DfsCollectDistance(it, node, distance + 1, distances);
    }
}

lli GetCentroid(lli node, lli parent, lli size)
{
    for (auto &it : graph[node])
    {
        if (it == parent || dead[it])
            continue;
        if (subtree_size[it] > size / 2)
            return GetCentroid(it, node, size);
    }
    return node;
}

void Decompose(lli node)
{
    DfsSize(node, -1);
    lli centroid = GetCentroid(node, -1, subtree_size[node]);

    vector<lli> cnt(min(k, subtree_size[node]) + 1);
    cnt[0] = 1;

    for (auto &it : graph[centroid])
    {
        if (dead[it])
            continue;
        vector<lli> distances;
        DfsCollectDistance(it, centroid, 1, distances);

        for (auto &distance : distances)
        {
            lli need = k - distance;
            if (need >= 0 && need < cnt.size())
            {
                ret += cnt[need];
            }
        }

        for (auto &distance : distances)
        {
            if (distance < cnt.size())
                cnt[distance]++;
        }
    }

    dead[centroid] = 1;
    for (auto &it : graph[centroid])
    {
        if (dead[it])
            continue;
        Decompose(it);
    }
}
/*Centroid Decomposition - End*/