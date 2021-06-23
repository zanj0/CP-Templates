typedef long double ld;
class GaussElimination {
	vector < vector < ld > > matrix;
	int r;
	int c;
public:
	GaussElimination(vector < vector < ld > > mat) {
		matrix = mat;
		r = mat.size();
		c = mat[0].size();
	}
	void addRow(int j, int i) {
		ld val = matrix[j][i] / matrix[i][i];
		val *= -1;

		for (int col = 0; col < c; col++) {
			matrix[j][col] += (val * matrix[i][col]);
		}

	}
	void mulRow(int i, ld val) {
		for (int col = 0; col < c; col++) {
			matrix[i][col] *= val;
		}
	}
	void simpleAdd(int i, int j) {
		int k = (i + 1) % r;
		while (i != k) {
			if (matrix[k][j] != 0)break;
			k = (k + 1) % r;
		}
		for (int l = 0; l < r; ++l) {
			matrix[i][l] += matrix[k][l];
		}

	}
	vector <ld> getX() {
		vector <ld> ret;
		for (int i = r - 1, stop = c - 2 ; i >= 0;  i--) {
			ld sum = matrix[i][c - 1];
			int idx = 0;
			int j;
			for (j = c - 2; j > stop; j--) {
				sum -= matrix[i][j] * ret[idx];
				idx++;
			}
			ret.push_back(sum / matrix[i][stop]);
			stop--;
		}
		return ret;
	}
	void out() {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	vector <ld> compute() {
		for (int i = 0; i < r; i++) {
			if (matrix[i][i] == 0) {
				simpleAdd(i, i);
			}
			mulRow(i, 1 / matrix[i][i]);
			for (int j = i + 1; j < r; j++) {
				addRow(j, i);
			}
		}
		return getX();
	}
};