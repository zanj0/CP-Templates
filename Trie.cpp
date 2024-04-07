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