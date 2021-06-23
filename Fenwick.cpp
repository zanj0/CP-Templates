class Fenwick {
public:
	int* arr;
	int n;
	Fenwick(int n) {
		arr = new int[n]();
		this->n = n;
	}
	void add(int idx, int val) {
		while (idx < n) {
			arr[idx] += val;
			idx += idx & -idx;
		}
	}
	int query(int idx) {
		int ret  = 0;
		while (idx > 0) {
			ret += arr[idx];
			idx -= idx & (-idx);
		}
		return ret;
	}
};

class Fenwick {
public:
	int* arr;
	int n;
	int offSet = 1;
	Fenwick(int n) {
		arr = new int[n]();
		this->n = n;
	}
	void add(int idx, int val) {
		idx += offSet;
		while (idx < n) {
			arr[idx] += val;
			idx += idx & -idx;
		}
	}
	int query(int idx) {
		idx += offSet;
		int ret  = 0;
		while (idx > 0) {
			ret += arr[idx];
			idx -= idx & (-idx);
		}
		return ret;
	}
	void clearFenwick(int i) {
		add(i, -query(i));
	}
};