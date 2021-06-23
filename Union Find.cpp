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


class UnionFind {
	vector<int> component;
	vector<int> rank;
	int distinctComponents;
public:
	/*
	 *   Initially all 'n' nodes are in different components.
	 *   e.g. component[2] = 2 i.e. node 2 belong to component 2.
	 */
	UnionFind(int n) {
		distinctComponents = n;
		for (int i = 0; i <= n; i++) {
			component.push_back(i);
			rank.push_back(0);
		}
	}

	/*
	 *   Returns true when two nodes 'a' and 'b' are initially in different
	 *   components. Otherwise returns false.
	 */
	bool unite(int a, int b) {
		int rootA = findComponent(a);
		int rootB = findComponent(b);
		if (rootA == rootB) {
			return false;
		}
		if (rank[rootA] < rank[rootB]) {
			component[rootA] = rootB;
		} else {
			if (rank[rootA] == rank[rootB]) {
				rank[rootA]++;
			}
			component[rootB] = rootA;
		}

		distinctComponents--;
		return true;
	}

	/*
	 *   Returns what component does the node 'a' belong to.
	 */
	int findComponent(int a) {
		if (component[a] != a) {
			component[a] = findComponent(component[a]);
		}
		return component[a];
	}

	/*
	 * Are Node a and Node b connected? i.e. in same component?
	 */

	bool connected(int a, int b) {
		return findComponent(a) == findComponent(b);
	}

	/*
	 *   Are all nodes united into a single component?
	 */
	bool united() {
		return distinctComponents == 1;
	}
};