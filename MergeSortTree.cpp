class MergeSortTree {
public:
	MergeSortTree(vector<int>& arr) {
		this->n = arr.size();
		tree.resize(4 * n);
		sum.resize(4 * n);
		BuildTree(0, n - 1, 0, arr);
	}

	int Query(int low, int high, int node, int query_low, int query_high, int value) {
		if (low >= query_low && high <= query_high) {
			int index = upper_bound(tree[node].begin(), tree[node].end(), value) - tree[node].begin();
			return index == 0 ? 0 : sum[node][index - 1];
		}
		if (low > query_high || high < query_low ) return 0;
		int mid = low + (high - low) / 2;

		return Query(low, mid, Left(node), query_low, query_high, value) + Query(mid + 1, high, Right(node), query_low, query_high, value);
	}
private:
	int n;
	vector<vector<int>> tree; // Stores the elements in sorted order.
	vector<vector<int>> sum; // Stores the sum in sorted order.

	int Left(int node) {
		return 2 * node + 1;
	}

	int Right(int node) {
		return 2 * node + 2;
	}

	void BuildTree(int low, int high , int node, vector<int>& arr) {
		if (low == high) {
			tree[node].pb({arr[low]});
			sum[node].pb({arr[low]});
			return;
		}
		int mid = low + (high - low) / 2;
		BuildTree(low, mid, Left(node), arr);
		BuildTree(mid + 1, high, Right(node), arr);
		Merge(node);
	}
	void MergePending(vector<int>& to_node, vector<int>& to_sum, int from_pointer, vector<int>& from_node) {
		while (from_pointer < from_node.size()) {
			to_node.pb(from_node[from_pointer]);
			to_sum.pb(from_node[from_pointer]);
			from_pointer++;
			if (to_sum.size() >= 2) {
				to_sum.back() += to_sum[to_sum.size() - 2];
			}
		}
	}
	void Merge(int node) {
		vector<int>& left_node = tree[Left(node)];
		vector<int>& right_node = tree[Right(node)];
		int left_pointer = 0;
		int right_pointer = 0;

		vector<int>& curr_node = tree[node];
		vector<int>& curr_sum = sum[node];

		while (left_pointer < left_node.size() && right_pointer < right_node.size()) {
			if (left_node[left_pointer] <= right_node[right_pointer]) {
				curr_node.pb(left_node[left_pointer]);
				curr_sum.pb(left_node[left_pointer]);
				left_pointer++;
			} else {
				curr_node.pb(right_node[right_pointer]);
				curr_sum.pb(right_node[right_pointer]);
				right_pointer++;
			}
			if (curr_sum.size() >= 2) {
				curr_sum.back() += curr_sum[curr_sum.size() - 2];
			}
		}

		MergePending(curr_node, curr_sum, left_pointer, left_node);
		MergePending(curr_node, curr_sum, right_pointer, right_node);

	}
};