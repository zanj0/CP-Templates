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





------------------------------------


struct MergeSortTree
{
    int n;
    vector<vector<lli>> tree;
    vector<vector<lli>> pref;

    MergeSortTree() {}

    MergeSortTree(const vector<lli> &arr)
    {
        init(arr);
    }

    void init(const vector<lli> &arr)
    {
        n = (int)arr.size();
        tree.assign(4 * n, {});
        pref.assign(4 * n, {});
        if (n > 0)
            build(0, 0, n - 1, arr);
    }

    lli rangeSumLE(int ql, int qr, lli value) const
    {
        if (ql > qr)
            return 0;
        return querySum(0, 0, n - 1, ql, qr, value);
    }

    int rangeCountLE(int ql, int qr, lli value) const
    {
        if (ql > qr)
            return 0;
        return queryCount(0, 0, n - 1, ql, qr, value);
    }

private:
    void build(int node, int l, int r, const vector<lli> &arr)
    {
        if (l == r)
        {
            tree[node].push_back(arr[l]);
            pref[node].push_back(arr[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node + 1, l, mid, arr);
        build(2 * node + 2, mid + 1, r, arr);
        mergeNode(node);
    }

    void mergeNode(int node)
    {
        const auto &L = tree[2 * node + 1];
        const auto &R = tree[2 * node + 2];
        auto &C = tree[node];
        auto &P = pref[node];

        C.resize(L.size() + R.size());
        merge(L.begin(), L.end(), R.begin(), R.end(), C.begin());

        P.resize(C.size());
        lli now = 0;
        for (size_t i = 0; i < C.size(); ++i)
        {
            now += C[i];
            P[i] = now;
        }
    }

    lli querySum(int node, int l, int r, int ql, int qr, lli value) const
    {
        if (r < ql || l > qr)
            return 0;
        if (ql <= l && r <= qr)
        {
            const auto &v = tree[node];
            const auto &s = pref[node];
            auto it = upper_bound(v.begin(), v.end(), value);
            if (it == v.begin())
                return 0;
            int idx = int(it - v.begin()) - 1;
            return s[idx];
        }
        int mid = (l + r) / 2;
        return querySum(2 * node + 1, l, mid, ql, qr, value) +
               querySum(2 * node + 2, mid + 1, r, ql, qr, value);
    }

    int queryCount(int node, int l, int r, int ql, int qr, lli value) const
    {
        if (r < ql || l > qr)
            return 0;
        if (ql <= l && r <= qr)
        {
            const auto &v = tree[node];
            auto it = upper_bound(v.begin(), v.end(), value);
            return int(it - v.begin());
        }
        int mid = (l + r) / 2;
        return queryCount(2 * node + 1, l, mid, ql, qr, value) +
               queryCount(2 * node + 2, mid + 1, r, ql, qr, value);
    }
};