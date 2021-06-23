const int N = 2e7;
int arr[N];
void pre() {
	for (int i = 0; i < N; i++) {
		arr[i] = i;
	}
	for (int i = 2; i * i <  N; i++) {
		if (arr[i] == i) {
			for (int j = i * i; j < N; j += i) {
				arr[j] = i;
			}
		}
	}
}