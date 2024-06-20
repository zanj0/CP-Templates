// Reference: https://zhtluo.com/cp/splay-tree-one-tree-to-rule-them-all.html
/*
	JAI JAGANNATH!
*/
//@Author : zanj0

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set =  __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define LOCAL
#define ff              first
#define ss              second
#define pb              push_back
#define MOD             1000000007
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define w(x)            int x; cin>>x; while(x--)
#define endl       		"\n"
#define timetaken cerr<<"Time : "<<1000*(long double)clock()/(long double)CLOCKS_PER_SEC<<"ms\n"

typedef long long int lli;

void zanj0()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}
namespace Allocator {

// Array Allocator.
template <class T, int MAXSIZE>
struct array {
	T v[MAXSIZE], *top;
	array() : top(v) {}
	T *alloc(const T &val = T()) { return &(*top++ = val); }
	void dealloc(T *p) {}
};

// Stack-based array Allocator.
template <class T, int MAXSIZE>
struct stack {
	T v[MAXSIZE];
	T *spot[MAXSIZE], **top;
	stack() {
		for (int i = 0; i < MAXSIZE; ++i) spot[i] = v + i;
		top = spot + MAXSIZE;
	}
	T *alloc(const T &val = T()) { return &(**--top = val); }
	void dealloc(T *p) { *top++ = p; }
};

}  // namespace Allocator

namespace splay {

// Abstract node struct.
template <class T>
struct node {
	T *f, *c[2];
	int size;
	node() {
		f = c[0] = c[1] = nullptr;
		size = 1;
	}
	void push_down() {}
	void update() {
		size = 1;
		for (int t = 0; t < 2; ++t)
			if (c[t]) size += c[t]->size;
	}
};

// Abstract reversible node struct.
template <class T>
struct reversible_node : node<T> {
	int r;
	reversible_node() : node<T>() { r = 0; }
	void push_down() {
		node<T>::push_down();
		if (r) {
			for (int t = 0; t < 2; ++t)
				if (node<T>::c[t]) node<T>::c[t]->reverse();
			r = 0;
		}
	}
	void update() { node<T>::update(); }
	// Reverse the range of this node.
	void reverse() {
		std::swap(node<T>::c[0], node<T>::c[1]);
		r = r ^ 1;
	}
};

template < class T, int MAXSIZE = 500000,
           class alloc = Allocator::array < T, MAXSIZE + 2 >>
struct tree {
	alloc pool;
	T *root;
	// Get a new node from the pool.
	T *new_node(const T &val = T()) { return pool.alloc(val); }
	tree() {
		root = new_node(), root->c[1] = new_node(), root->size = 2;
		root->c[1]->f = root;
	}
	// Helper function to rotate node.
	void rotate(T *n) {
		int v = n->f->c[0] == n;
		T *p = n->f, *m = n->c[v];
		if (p->f) p->f->c[p->f->c[1] == p] = n;
		n->f = p->f, n->c[v] = p;
		p->f = n, p->c[v ^ 1] = m;
		if (m) m->f = p;
		p->update(), n->update();
	}
	// Splay n so that it is under s (or to root if s is null).
	void splay(T *n, T *s = nullptr) {
		while (n->f != s) {
			T *m = n->f, *l = m->f;
			if (l == s)
				rotate(n);
			else if ((l->c[0] == m) == (m->c[0] == n))
				rotate(m), rotate(n);
			else
				rotate(n), rotate(n);
		}
		if (!s) root = n;
	}
	// Get the size of the tree.
	int size() { return root->size - 2; }
	// Helper function to walk down the tree.
	int walk(T *n, int &v, int &pos) {
		n->push_down();
		int s = n->c[0] ? n->c[0]->size : 0;
		(v = s < pos) && (pos -= s + 1);
		return s;
	}
	// Insert node n to position pos.
	void insert(T *n, int pos) {
		T *c = root;
		int v;
		++pos;
		while (walk(c, v, pos), c->c[v] && (c = c->c[v]))
			;
		c->c[v] = n, n->f = c, splay(n);
	}
	// Find the node at position pos. If sp is true, splay it.
	T *find(int pos, int sp = true) {
		T *c = root;
		int v;
		++pos;
		while ((pos < walk(c, v, pos) || v) && (c = c->c[v]))
			;
		if (sp) splay(c);
		return c;
	}
	// Find the range [posl, posr) on the splay tree.
	T *find_range(int posl, int posr) {
		T *r = find(posr), *l = find(posl - 1, false);
		splay(l, r);
		if (l->c[1]) l->c[1]->push_down();
		return l->c[1];
	}
	// Insert nn of size nn_size to position pos.
	void insert_range(T **nn, int nn_size, int pos) {
		T *r = find(pos), *l = find(pos - 1, false), *c = l;
		splay(l, r);
		for (int i = 0; i < nn_size; ++i) c->c[1] = nn[i], nn[i]->f = c, c = nn[i];
		for (int i = nn_size - 1; i >= 0; --i) nn[i]->update();
		l->update(), r->update(), splay(nn[nn_size - 1]);
	}
	// Helper function to dealloc a subtree.
	void dealloc(T *n) {
		if (!n) return;
		dealloc(n->c[0]);
		dealloc(n->c[1]);
		pool.dealloc(n);
	}
	// Remove from position [posl, posr).
	void erase_range(int posl, int posr) {
		T *n = find_range(posl, posr);
		n->f->c[1] = nullptr, n->f->update(), n->f->f->update(), n->f = nullptr;
		dealloc(n);
	}
};

}  // namespace splay

// TODO:
// 1. Define a node inheriting from splay::node<node> or splay::reversible_node<node>.
// 2. Add the values you want to use.
// 3. Overload the constructor, push_down, update, (potentially) reverse.
// (Do not forget to call the base method.)
// 4. Add whatever operations you want.
// 5. Define a tree with splay::tree<node, MAXSIZE, Allocator::stack<node, MAXSIZE + 2>> t;
// 6. Profit.

// Template ends here.

const int MAXSIZE = 200000;

struct node: splay::reversible_node<node> {
	long long val, val_min, label_add;
	node(long long v = 0) : splay::reversible_node<node>(), val(v) { val_min = label_add = 0; }
	// Add v to the subtree.
	void add(long long v) {
		val += v;
		val_min += v;
		label_add += v;
	}
	void push_down() {
		splay::reversible_node<node>::push_down();
		for (int t = 0; t < 2; ++t) if (c[t]) c[t]->add(label_add);
		label_add = 0;
	}
	void update() {
		splay::reversible_node<node>::update();
		val_min = val;
		for (int t = 0; t < 2; ++t) if (c[t]) val_min = std::min(val_min, c[t]->val_min);
	}
};

splay::tree < node, MAXSIZE, Allocator::stack < node, MAXSIZE + 2 >> t;
void Solve() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		lli val;
		cin >> val;
		t.insert(t.new_node(node(val)), t.size());

	}

	int q;
	cin >> q;
	while (q--) {
		string type;
		cin >> type;
		if (type == "ADD") {
			lli low, high, val;
			cin >> low >> high >> val;
			t.find_range(low - 1, high)->add(val);
		} else if (type == "REVERSE") {
			lli low, high;
			cin >> low >> high;
			t.find_range(low - 1, high)-> reverse();
		} else if (type == "REVOLVE") {
			lli low, high, count;
			cin >> low >> high >> count;
			lli len = high  - low + 1;
			count %= len;
			if (count > 0) {
				node* right = t.find_range(high - count, high);
				right->f->c[1] = nullptr;
				right->f->update();
				right->f->f->update();
				right->f = nullptr;
				t.insert(right, low - 1);
			}
		} else if (type == "INSERT") {
			int x; lli p;
			cin >> x >> p;
			t.insert(t.new_node(node(p)), x);
		} else if (type == "DELETE") {
			lli x;
			cin >> x;
			t.erase_range(x - 1, x);
		} else if (type == "MIN") {
			lli x, y;
			cin >> x >> y;
			cout << t.find_range(x - 1, y)->val_min << endl;
		}
	}
}
int32_t main()
{
	zanj0();
	Solve();
	timetaken;
	return 0;
}