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
