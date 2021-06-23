const int N = 1e6 + 5;
const int Q = 2e6 + 5;
const int M = 1e6 + 5;
unordered_map <int, int> idx;
const int SZ = sqrt(N) + 1;

struct data
{
	int l, r, idx;
} qr[Q];

int n, q, a[N];
int freq[M];
long long ans[Q];
long long cur = 0;

bool comp(struct data &d1, struct data &d2)
{
	int b1 = d1.l / SZ;
	int b2 = d2.l / SZ;
	if (b1 != b2)
		return b1 < b2;
	else
		return d1.r < d2.r ;
}

inline void add(int x)
{
	if (freq[idx[x]] > 0 && freq[idx[x]] % 2 == 0) {
		cur ^= x;
	}
	freq[idx[x]]++;
	if (freq[idx[x]] > 0 && freq[idx[x]] % 2 == 0) {
		cur ^= x;
	}
}

inline void remove(int x)
{
	if (freq[idx[x]] > 0 && freq[idx[x]] % 2 == 0) {
		cur ^= x;
	}
	freq[idx[x]]--;
	if (freq[idx[x]] > 0 && freq[idx[x]] % 2 == 0) {
		cur ^= x;
	}
}

void mo()
{
	sort(qr + 1, qr + q + 1, comp);
	int l = qr[1].l, r = l;
	add(a[l]);
	cur = 0;
	for (int i = 1; i <= q; i++)
	{
		while (l < qr[i].l) {
			remove(a[l]);
			l++;
		}
		while (l > qr[i].l) {
			l--;
			add(a[l]);
		}
		while (r < qr[i].r) {
			r++;
			add(a[r]);
		}
		while (r > qr[i].r) {
			remove(a[r]);
			r--;
		}
		ans[qr[i].idx] = cur;
	}
}