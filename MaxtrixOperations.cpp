template <class T> struct CumSum {
	vector<vector<T>> data;
	bool is_built = false;

	CumSum(int W, int H) : data(W + 1, vector<T>(H + 1, 0)) {}

	void add(int x, int y, T z) {
		++x, ++y;
		if (x >= data.size() || y >= data[0].size()) return;
		data[x][y] += z;
	}

	void build() {
		for (int i = 1; i < data.size(); i++) {
			for (int j = 1; j < data[i].size(); j++) { data[i][j] += data[i][j - 1] + data[i - 1][j] - data[i - 1][j - 1]; }
		}
		is_built = true;
	}

	T query(int sx, int sy, int gx, int gy) {
		assert(is_built);
		return (data[gx][gy] - data[sx][gy] - data[gx][sy] + data[sx][sy]);
	}
};
template <typename T>
std::vector<std::vector<T>> rot90(const std::vector<std::vector<T>> &A) {
	if (A.empty()) return A;
	const int N = A.size(), M = A[0].size();
	std::vector<std::vector<T>> B(M, std::vector<T>(N));
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) B[j][i] = A[i][M - j - 1];
	return B;
}
std::vector<std::string> rot90(const std::vector<std::string> &A) {
	if (A.empty()) return A;
	const int N = A.size(), M = A[0].size();
	std::vector<std::string> B(M, std::string(N, '\0'));
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) B[j][i] = A[i][M - j - 1];
	return B;
}
void Out(vector<vector<int>>& v) {
	for (auto& it : v) {
		for (auto& it2 : it) {
			cout << it2 << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Sample submission: https://atcoder.jp/contests/abc347/submissions/52047819