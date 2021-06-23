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