class TrieNode {
public:
	TrieNode* child[2];
	lli counter;

	TrieNode() {
		for (lli i = 0; i < 2; i++) {
			child[i] = NULL;
		}
		counter = 0;
	}

	void insertNode(lli num) {
		TrieNode* curr = this;
		for (lli i = 32 ; i >= 0; i--) {
			lli bit = 1 & (num >> i);
			if (!curr->child[bit]) {
				curr->child[bit] = new TrieNode();
			}
			curr = curr->child[bit];
			curr->counter++;
		}
	}

	TrieNode* deleteNode(TrieNode* node, lli num, lli bit) {
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

	lli query(lli x) {
		lli ret = 0;
		TrieNode* curr = this;
		for (lli i = 32 ; i >= 0; i--) {
			lli bit = 1 & (x >> i);
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