struct Node {
	pair<int, int > line;
	Node *left, *right;
	Node(pair<int, int > l) {
		left = right = NULL;
		line = l;
	}
};
struct LiChaoTree {
public:
	Node* root;
	int low, high, defValue;
	int f(pair<int, int > line, int x) {
		int ret = line.ff * x + line.ss;
		return ret;
	}
	LiChaoTree(int n) {
		defValue = -inf;
		low = 1;
		high = n + 1; // [low, high)
		root = new Node({0, defValue});
	}
	void insertLine(pair<int, int > line) {
		insert(root, line, low, high);
	}
	void insert(Node* curr, pair<int, int > line, int low, int high) {
		int m = low + (high - low) / 2;
		bool l = f(line, low) > f(curr->line, low);
		bool mid = f(line, m) > f(curr->line, m);
		if (mid)swap(curr->line, line);
		if (high - low == 1) return;
		if (l != mid) {
			if (!curr->left) curr ->left = new Node({0, defValue});
			insert(curr->left, line, low, m);
		} else {
			if (!curr->right) curr ->right = new Node({0, defValue});
			insert(curr->right, line, m, high);
		}
	}
	int queryLine(int x) {
		return query(root, x, low, high);
	}
	int query(Node* curr, int x, int low, int high) {
		int m = low + (high - low) / 2;
		int ret = f(curr->line, x);
		if (high - low == 1) return ret;
		if (x < m && curr->left) ret = max(ret, query(curr->left, x, low, m));
		else if (x >= m && curr->right)ret = max(ret, query(curr->right, x, m, high));
		return ret;
	}
};

/*

Can be used when the dp transitions have value like y = mx + c.
dp[x] = some_value + (mj * x + cj)

Example: https://codeforces.com/problemset/problem/1083/E
Tutorial: https://codeforces.com/blog/entry/63823
*/