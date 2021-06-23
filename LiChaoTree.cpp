struct Node {
	vector <int> line;
	Node *left, *right;
	Node(vector <int> l) {
		left = right = NULL;
		line = l;
	}
};
struct LiChaoTree {
public:
	Node* root;
	int low, high, defValue;
	int f(vector <int> line, int x) {
		int ret = line[0] * x + line[1];
		return ret;
	}
	LiChaoTree(int n) {
		defValue = -inf;
		low = 1;
		high = n + 1; // [low, high)
		root = new Node({0, defValue});
	}
	void insertLine(vector <int> line) {
		insert(root, line, low, high);
	}
	void insert(Node* curr, vector <int> line, int low, int high) {
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
