class SegmentTree {
public:
    int* tree;
    int* lazy;
    SegmentTree(int n) {
        tree = new int[4 * n + 5]();
        lazy = new int[4 * n + 5]();
    }
    int left(int x) {
        return 2 * x + 1;
    }
    int right(int x) {
        return 2 * x + 2;
    }
    int operate(int a, int b) {
        return a + b;
    }
    void pull(int node) {
        tree[node] = operate(tree[left(node)], tree[right(node)]);
    }
    void push(int low, int high, int node) {
        if (lazy[node] % 2) {
            tree[node] = -tree[node];
        }
        if (low != high) {
            lazy[left(node)] += lazy[node];
            lazy[right(node)] += lazy[node];
        }
        lazy[node] = 0;
    }
    void buildTree(int low, int high, int node, vector <int>& arr) {
        if (low == high) {
            tree[node] = arr[low];
            return;
        }
        int mid = low + (high - low) / 2;
        buildTree(low, mid, left(node), arr);
        buildTree(mid + 1, high, right(node), arr);
        pull(node);
    }
    int query(int low, int high, int node, int qlow, int qhigh) {
        push(low, high, node);
        if (qlow > high || qhigh < low) return 0;
        if (qlow <= low && qhigh >= high) {
            return tree[node];
        }
        int mid = low + (high - low) / 2;
        int l = query(low, mid, left(node), qlow, qhigh);
        int r = query(mid + 1, high, right(node), qlow, qhigh);
        return operate(l, r);
    }
    void update(int low, int high, int node, int ulow, int uhigh) {
        push(low, high, node);
        if (ulow > high || uhigh < low) return;
        if (ulow <= low && uhigh >= high) {
            lazy[node]++;
            push(low, high, node);
            return;
        }
        int mid = low + (high - low) / 2;
        update(low, mid, left(node), ulow, uhigh);
        update(mid + 1, high, right(node), ulow, uhigh);
        pull(node);

    }

};

class SegmentTree {
public:
    int* tree;
    SegmentTree(int n) {
        tree = new int[4 * n + 5]();
        for (int i = 0; i < (4 * n + 5); i++ ) tree[i] = -inf;

    }
    int left(int x) {
        return 2 * x + 1;
    }
    int right(int x) {
        return 2 * x + 2;
    }
    int operate(int a, int b) {
        return max(a, b);
    }
    void pull(int node) {
        tree[node] = operate(tree[left(node)], tree[right(node)]);
    }
    void buildTree(int low, int high, int node, vector <int>& arr) {
        if (low == high) {
            tree[node] = arr[low];
            return;
        }
        int mid = low + (high - low) / 2;
        buildTree(low, mid, left(node), arr);
        buildTree(mid + 1, high, right(node), arr);
        pull(node);
    }
    int query(int low, int high, int node, int qlow, int qhigh) {

        if (qlow > high || qhigh < low) return -inf;
        if (qlow <= low && qhigh >= high) {
            return tree[node];
        }
        int mid = low + (high - low) / 2;
        int l = query(low, mid, left(node), qlow, qhigh);
        int r = query(mid + 1, high, right(node), qlow, qhigh);
        return operate(l, r);
    }
    void update(int low, int high, int node, int idx, int val) {
        if (low == high) {
            tree[node] = max(val, tree[node]);
            return;
        }
        int mid = low + (high - low) / 2;
        if (mid >= idx)update(low, mid, left(node), idx, val);
        else update(mid + 1, high, right(node), idx, val);
        pull(node);

    }

};

************************

template<class T>
struct Segtree {
    vector<T>st;
    int n;
    T identity_element;
    Segtree(int n, T identity_element)
    {
        this->n = n;
        this->identity_element = identity_element;
        st.assign(4 * n, identity_element);
    }
    T combine(T l, T r)
    {
        // change this function as required.
        T ans = l + r;
        return ans;
    }
    void buildUtil(int v, int tl, int tr, vector<T>&a)
    {
        if (tl == tr)
        {
            st[v] = a[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        buildUtil(2 * v + 1, tl, tm, a);
        buildUtil(2 * v + 2, tm + 1, tr, a);
        st[v] = combine(st[2 * v + 1], st[2 * v + 2]);
    }
    T queryUtil(int v, int tl, int tr, int l, int r)
    {
        if (l > r)return identity_element;
        if (r < tl or l > tr)
        {
            return identity_element;
        }
        if (tl >= l and tr <= r)
        {
            return st[v];
        }
        int tm = (tl + tr) >> 1;
        return combine(queryUtil(2 * v + 1, tl, tm, l, r), queryUtil(2 * v + 2, tm + 1, tr, l, r));
    }
    T apply(T curr, T val)
    {
        // change this function if update is of some other kind.
        T ans = curr;
        ans = val;
        return ans;
    }
    void updateUtil(int v, int tl, int tr, int ind, T val)
    {
        if (tl == tr)
        {
            st[v] = apply(st[v], val);
            return;
        }
        int tm = (tl + tr) >> 1;
        if (ind <= tm)
        {
            updateUtil(2 * v + 1, tl, tm, ind, val);
        }
        else
        {
            updateUtil(2 * v + 2, tm + 1, tr, ind, val);
        }
        st[v] = combine(st[2 * v + 1], st[2 * v + 2]);
    }


    void build(vector<T>a)
    {
        assert(sz(a) == n);
        buildUtil(0, 0, n - 1, a);
    }
    T query(int l, int r)
    {
        return queryUtil(0, 0, n - 1, l, r);
    }
    void update(int ind, T val)
    {
        updateUtil(0, 0, n - 1, ind, val);
    }
};