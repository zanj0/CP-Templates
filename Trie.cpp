class TrieNode {
public:
	TrieNode* child[2];
	int counter;

	TrieNode() {
		for (int i = 0; i < 2; i++) {
			child[i] = NULL;
		}
		counter = 0;
	}

	void insertNode(int num) {
		TrieNode* curr = this;
		for (int i = 32 ; i >= 0; i--) {
			int bit = 1 & (num >> i);
			if (!curr->child[bit]) {
				curr->child[bit] = new TrieNode();
			}
			curr = curr->child[bit];
			curr->counter++;
		}
	}

	TrieNode* deleteNode(TrieNode* node, int num, int bit) {
		if (!node) return NULL;
		node->counter--;
		TrieNode* ret = node;
		if (bit >= 0) {
			node->child[1 & (num >> bit)] = deleteNode(node->child[1 & (num >> bit)], num, bit - 1);
		}
		if (node->counter == 0) {
			ret = NULL;
		}
		return ret;
	}

	int query(int x) {
		int ret = 0;
		TrieNode* curr = this;
		for (int i = 32 ; i >= 0; i--) {
			int bit = 1 & (x >> i);
			bit = !bit;
			if (curr->child[bit]) {
				ret |= (1 << i);
			} else {
				bit = !bit;
			}
			curr = curr->child[bit];
		}
		return ret;
	}

};

**************


const int logn = 31;
const int N = 1e5 + 5;
int ptr;
int nxt[logn * N * 5][2], cnt[logn * N * 5];

int getBit(int val, int i) {
	return ((val >> i) & 1);
}

void add(int val) {
	int curr = 0;
	for (int i = logn; i >= 0; i--) {
		int bit = getBit(val, i);
		if (!nxt[curr][bit]) nxt[curr][bit] = ++ptr;
		curr = nxt[curr][bit];
		cnt[curr]++;
	}
}

void rem(int val) {
	int curr = 0;
	for (int i = logn; i >= 0; i--) {
		int bit = getBit(val, i);
		if (!nxt[curr][bit]) nxt[curr][bit] = ++ptr;
		curr = nxt[curr][bit];
		cnt[curr]--;
	}
}

int query(int k, int l) {
	int curr = 0;
	int ret = 0;
	for (int i = logn; i >= 0; i--) {
		int x = getBit(k, i);
		int y = getBit(l, i);
		if (y) {
			if (nxt[curr][x]) {
				ret += cnt[nxt[curr][x]];
			}
			if (nxt[curr][!x]) {
				curr = nxt[curr][!x];
			} else {
				return ret;
			}
		} else {
			if (nxt[curr][x]) {
				curr = nxt[curr][x];
			} else {
				return ret;
			}
		}
	}
	return ret;
}

************

const int K = 63;
class TrieNode {
public:
	TrieNode* child[2];
	int counter;

	TrieNode() {
		for (int i = 0; i < 2; i++) {
			child[i] = NULL;
		}
		counter = 0;
	}

	void insertNode(int num) {
		TrieNode* curr = this;
		for (int i = K ; i >= 0; i--) {

			int bit = (int)1 & (num >> i);
			if (!curr->child[bit]) {
				curr->child[bit] = new TrieNode();
			}
			curr = curr->child[bit];
			curr->counter++;
		}
	}
	TrieNode* deleteNode(TrieNode* node, int num, int bit) {
		if (!node) return NULL;
		node->counter--;
		TrieNode* ret = node;
		if (bit >= 0) {
			node->child[1 & (num >> bit)] = deleteNode(node->child[1 & (num >> bit)], num, bit - 1);
		}
		if (node->counter == 0) {
			ret = NULL;
		}
		return ret;
	}

	int query(int x) {
		int ret = 0;
		TrieNode* curr = this;
		for (int i = K ; i >= 0; i--) {
			int bit = 1 & (x >> i);
			bit = !bit;
			if (curr->child[bit]) {
				ret |= ((int)1 << i);
			} else {
				bit = !bit;
			}
			curr = curr->child[bit];
		}
		return ret;
	}

};

**************

const int K = 26;
class TrieNode {
public:
	TrieNode* child[K];
	int counter;
	bool complete;

	TrieNode() {
		for (int i = 0; i < K; i++) {
			child[i] = NULL;
		}
		counter = 0;
		complete = false;
	}

	void insertNode(string& s) {
		TrieNode* curr = this;
		for (auto& it : s) {
			if (curr->child[it - 'a'] == NULL) {
				curr->child[it - 'a'] = new TrieNode();
			}
			curr = curr->child[it - 'a'];
		}
		curr->complete = true;
	}



	bool query(string s) {
		TrieNode* curr = this;
		for (auto& it : s) {
			if (curr->child[it - 'a'] == NULL) {
				return false;
			}
			curr = curr->child[it - 'a'];
			if (curr->complete) return false;
		}
		return curr->complete;
	}

};

--------------------------

// Refer usage: https://leetcode.com/submissions/detail/1493539082/
const int K = 26;
struct TrieNode {
	lli len = 0, suffix = 0, dictionary = 0, cost = inf;
	array<lli, K> nxt;
};

struct Trie {
	static constexpr lli unassigned = 0, root = 1;

	vector<TrieNode> tree;

	int newNode(TrieNode node) {
		tree.pb(node);
		return tree.size() - 1;
	}

	Trie() {
		tree.assign(2, {});
		tree[unassigned].len = -1;
		tree[unassigned].nxt.fill(1);
	}

	void addWord(string& s, lli cost) {
		int u_id = root;

		for (auto& c : s) {
			int x = c - 'a';
			if (tree[u_id].nxt[x] == unassigned) {
				tree[u_id].nxt[x] = newNode({.len = tree[u_id].len + 1});
			}
			u_id = tree[u_id].nxt[x];
		}
		tree[u_id].cost = min(tree[u_id].cost, cost);
	}

	tuple<TrieNode*, lli> ref(int id) {
		return {&tree[id], id};
	}

	TrieNode* operator[](int id) {
		return &tree[id];
	}

	void ahoCorasick() {
		queue<int> q;
		q.push(root);

		while (!q.empty()) {
			auto [u, u_id] = ref(q.front());
			q.pop();

			for (int x = 0; x < K; x++) {
				auto [v, v_id]  = ref(u->nxt[x]);
				auto [suffix, suffix_id]  = ref(tree[u->suffix].nxt[x]);
				if (v_id == unassigned) {
					u->nxt[x] = suffix_id;
				} else {
					v->suffix = suffix_id;
					v->dictionary = suffix->cost != inf ? suffix_id : suffix->dictionary;
					q.push(v_id);
				}
			}
		}
	}
};
--------------------------