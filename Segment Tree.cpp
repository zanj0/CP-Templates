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
***********************************

struct Node {
    lli selected[2][2];
    Node() {
        selected[0][0] = 0;
        selected[0][1] = 0;
        selected[1][0] = 0;
        selected[1][1] = 0;
    }
};

class SegmentTree {
public:
    vector<Node> tree;
    SegmentTree(lli n) {
        tree = vector<Node>(4 * n + 5);
        for (lli i = 0; i < (4 * n + 5); i++ ) {
            tree[i].selected[0][0] = 0;
            tree[i].selected[0][1] = 0;
            tree[i].selected[1][0] = 0;
            tree[i].selected[1][1] = 0;
        }

    }
    lli left(lli x) {
        return 2 * x + 1;
    }
    lli right(lli x) {
        return 2 * x + 2;
    }
    Node operate(Node& a, Node& b) {
        Node ret;
        ret.selected[0][0] = max({a.selected[0][0] + b.selected[0][0], a.selected[0][1] + b.selected[0][0], a.selected[0][0] + b.selected[1][0]});
        ret.selected[0][1] = max({a.selected[0][0] + b.selected[0][1], a.selected[0][1] + b.selected[0][1], a.selected[0][0] + b.selected[1][1]});
        ret.selected[1][0] = max({a.selected[1][0] + b.selected[0][0], a.selected[1][1] + b.selected[0][0], a.selected[1][0] + b.selected[1][0]});
        ret.selected[1][1] = max({a.selected[1][0] + b.selected[0][1], a.selected[1][1] + b.selected[0][1], a.selected[1][0] + b.selected[1][1]});
        return ret;
    }
    void pull(lli node) {
        tree[node] = operate(tree[left(node)], tree[right(node)]);
    }

    Node query(lli low, lli high, lli node, lli qlow, lli qhigh) {

        if (qlow > high || qhigh < low) {
            Node temp;
            return temp;
        }
        if (qlow <= low && qhigh >= high) {
            return tree[node];
        }
        lli mid = low + (high - low) / 2;
        Node l = query(low, mid, left(node), qlow, qhigh);
        Node r = query(mid + 1, high, right(node), qlow, qhigh);
        return operate(l, r);
    }
    void update(lli low, lli high, lli node, lli idx, lli val) {
        if (low == high) {
            tree[node].selected[1][1] = val;
            return;
        }
        lli mid = low + (high - low) / 2;
        if (mid >= idx)update(low, mid, left(node), idx, val);
        else update(mid + 1, high, right(node), idx, val);
        pull(node);

    }

};



***********************************



typedef long long int lli;
lli Add(lli a, lli b) {
    return ((a % MOD) + (b % MOD)) % MOD;

}
lli Mul(lli a, lli b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}
const lli N = 2e5 + 5;

struct Node {
    lli len, sum_a, sum_b, sum_ab;

    void Put(lli a, lli b) {
        sum_ab = Add(sum_ab, Mul(b, sum_a));
        sum_ab = Add(sum_ab, Mul(a, sum_b));
        sum_ab = Add(sum_ab, Mul(len, Mul(a, b)));

        sum_a = Add(sum_a, Mul(a, len));

        sum_b = Add(sum_b, Mul(b, len));
    }

    void Up(Node& left, Node& right) {
        len = Add(left.len , right.len);
        sum_ab = Add(left.sum_ab , right.sum_ab);
        sum_a = Add(left.sum_a , right.sum_a);
        sum_b = Add(left.sum_b , right.sum_b);
    }
};

Node segment_tree[4 * N + 5];
lli sum_a[4 * N + 5], sum_b[4 * N + 5];

void Put(lli node, lli len, lli a, lli b) {
    segment_tree[node].Put(a, b);
    segment_tree[node].len = len;

    sum_a[node] = Add(sum_a[node], a);
    sum_b[node] = Add(sum_b[node], b);
}
lli Left(lli node) {
    return 2 * node;
}
lli Right(lli node) {
    return 2 * node + 1;
}
void Down(lli node, lli len) {
    Put(Left(node), (len + 1) / 2, sum_a[node], sum_b[node]);
    Put(Right(node), len / 2, sum_a[node], sum_b[node]);
    sum_a[node] = sum_b[node] = 0;
}

void Update(lli update_left, lli update_right, lli a, lli b, lli node = 1, lli low = 1, lli high = N - 1) {
    if (low >= update_left && high <= update_right) {
        Put(node, high - low + 1, a, b);
        return;
    }
    Down(node, high - low + 1);
    lli mid = low + (high - low) / 2;
    if (update_left <= mid) {
        Update(update_left, update_right, a, b, Left(node), low, mid);
    }
    if (update_right > mid) {
        Update(update_left, update_right, a, b, Right(node), mid + 1, high);
    }
    segment_tree[node].Up(segment_tree[Left(node)], segment_tree[Right(node)]);
}


lli Query(lli query_left, lli query_right, lli node = 1, lli low = 1, lli high = N - 1) {
    if (low >= query_left && high <= query_right) {
        return segment_tree[node].sum_ab;
    }
    Down(node, high - low + 1);
    lli mid = low + (high - low) / 2;
    lli ret = 0;
    if (query_left <= mid) {
        ret = Add(Query(query_left, query_right, Left(node), low, mid), ret);
    }
    if (query_right > mid) {
        ret = Add(Query(query_left, query_right, Right(node), mid + 1, high), ret);
    }
    return ret;
}