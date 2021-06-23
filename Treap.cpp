const int N = 1e5 + 5;
class  Treap {
public:
	int data, priority;
	Treap* kids[2];
	int subtreeSize, sum, toProp;
	Treap(int data) {
		this->data = data;
		priority = rand() % N;
		recalc(this);
	}
	vector <Treap*> split(Treap* node, int nInLeft) {

	}
};

int main() {
	return 0;
}