const int N = 4e6 + 50;
int phi[N], ret[N];
void totient(int n) {
	phi[0] = 0;
	phi[1] = 1;
	for (int i = 2; i <= n; i++)
		phi[i] = i;

	for (int i = 2; i <= n; i++) {
		if (phi[i] == i) {
			for (int j = i; j <= n; j += i)
				phi[j] -= phi[j] / i;
		}
	}
}
void pre() {
	totient(N - 1);
	for (int i = 1; i < N; i++) {
		for (int j = i; j < N; j += i) {
			// i is divisor of j
			ret[j] += i * phi[j / i];
		}
	}
}