const int N = 1e5 + 5;
const int K = 17;
int table[N][K];
int bin_log[N];
void preSparse(vector <int>& v) {
	int n = v.size();
	for (int i = 0; i < n; i++) {
		table[i][0] = v[i];
	}
	for (int i = 2; i < N; i++) {
		bin_log[i] = bin_log[i / 2] + 1;
	}
	for (int j = 1; j < K; j++) {
		for (int i = 0; i + (1 << (j - 1)) < n; i++) {
			table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
		}
	}
}
int query(int l, int r) {
	int ret = 0;
	int len = r - l + 1;
	int segment = bin_log[len];
	ret = min(table[l][segment], table[r - (1 << segment) + 1][segment]);
	return ret;
}


---------------------------------

 
const int L = 18, N = 1 << L;
 
int lg[N];
template <typename T, typename F = std::function<T(const T&, const T&)>> struct SPARSE {
	vector<T> st[L];
	F op;
 
	SPARSE(const vector<T> &a, F operation): op(operation) {
		int n = a.size();
		if(!lg[N - 1]) for(int i = 2; i < N; i++) lg[i] = lg[i >> 1] + 1;
		for(int i = 0; i < L; i++) st[i].resize(n);
		for(int i = 0; i < n; i++) st[0][i] = a[i];
		for(int i = 1; i < L; i++)
			for(int j = 0; j + (1 << i) <= n; j++)
				st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
	}
 
	T query(int i, int j) {
		int k = lg[j - i + 1]
		return op(st[k][i], st[k][j - (1 << k) + 1]);
	}
};

Usage: https://codeforces.com/contest/2121/submission/324888101