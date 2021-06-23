#include <bits/stdc++.h>
using namespace std;

template<typename T, T minX, T maxX, T defVal>
struct DynamicLiChaoTree {
private:
  struct Line {
    T a, b;
    inline T calc(T x) const { return a * x + b; }
  };
  struct Node {
    Line val = {0, defVal};
    Node *lt = nullptr, *rt = nullptr;
  };
  Node* root;
  void update(Node* cur, T l, T r, Line nw) {
    T mid = (l + r) >> 1;
    if (cur->val.calc(l) >= nw.calc(l)) swap(cur->val, nw);
    if (cur->val.calc(r) <= nw.calc(r)) {
      cur->val = nw;
      return;
    }
    if (nw.calc(mid) >= cur->val.calc(mid)) {
      if (!cur->rt) cur->rt = new Node();
      update(cur->rt, mid + 1, r, cur->val);
      cur->val = nw;
    } else {
      if (!cur->lt) cur->lt = new Node();
      update(cur->lt, l, mid, nw);
    }
  }
  T query(Node* cur, T l, T r, T x) {
    T res = cur->val.calc(x);
    T mid = (l + r) >> 1;
    if (x <= mid && cur->lt)
      res = max(res, query(cur->lt, l, mid, x));
    else if (x > mid && cur-> rt)
      res = max(res, query(cur->rt, mid + 1, r, x));
    return res;
  }
public:
  void addLine(T a, T b) {
    update(root, minX, maxX, {a, b});
  }
  T query(T x) {
    return query(root, minX, maxX, x);
  }
  void init() {
    root = new Node;
  }
};

using ll = long long;
const int N = 1e5 + 5;

struct machine {
  int d, p, r, g;
} mac[N];

int n, c, D, tcase;
ll dp[N];
DynamicLiChaoTree < ll, 1, (ll)1e9 + 10, -1 > lct;

void solve() {
  for (int i = 1; i <= n; ++i) cin >> mac[i].d >> mac[i].p >> mac[i].r >> mac[i].g;
  sort(mac + 1, mac + 1 + n, [&](const machine & x, const machine & y) { return x.d < y.d; });
  lct.init(); lct.addLine(0, c);
  for (int i = 1; i <= n; ++i) {
    ll tmp = lct.query(mac[i].d);
    if (tmp >= mac[i].p) {
      dp[i] = tmp + mac[i].r - mac[i].p;
      lct.addLine(mac[i].g, dp[i] - 1LL * mac[i].g * (mac[i].d + 1));
    }
  }
  cout << "Case " << (++tcase) << ": " << lct.query(D + 1) << "\n";
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  while (true) {
    cin >> n >> c >> D;
    if (n == 0) break;
    solve();
  }
  return 0;
}









== == == == == == == == == == == == =
// MIN

  /*
    JAI JAGANNATH!
  */
//@Author : zanj0

#include<bits/stdc++.h>
  using namespace std;

#define int       long long int
#define LOCAL
#define ff              first
#define ss              second
#define pb              push_back
#define MOD             1000000007
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define w(x)            int x; cin>>x; while(x--)
#define endl          "\n"
#define timetaken cerr<<"Time : "<<1000*(long double)clock()/(long double)CLOCKS_PER_SEC<<"ms\n"

void zanj0()
{
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
}
template<typename T, T minX, T maxX, T defVal>
struct DynamicLiChaoTree {
private:
  struct Line {
    T a, b;
    inline T calc(T x) const { return a * x + b; }
  };
  struct Node {
    Line val = {0, defVal};
    Node *lt = nullptr, *rt = nullptr;
  };
  Node* root;
  void update(Node* cur, T l, T r, Line nw) {
    T mid = (l + r) >> 1;
    if (cur->val.calc(l) >= nw.calc(l)) swap(cur->val, nw);
    if (cur->val.calc(r) <= nw.calc(r)) {
      cur->val = nw;
      return;
    }
    if (nw.calc(mid) >= cur->val.calc(mid)) {
      if (!cur->rt) cur->rt = new Node();
      update(cur->rt, mid + 1, r, cur->val);
      cur->val = nw;
    } else {
      if (!cur->lt) cur->lt = new Node();
      update(cur->lt, l, mid, nw);
    }
  }
  T query(Node* cur, T l, T r, T x) {
    T res = cur->val.calc(x);
    T mid = (l + r) >> 1;
    if (x <= mid && cur->lt)
      res = max(res, query(cur->lt, l, mid, x));
    else if (x > mid && cur-> rt)
      res = max(res, query(cur->rt, mid + 1, r, x));
    return res;
  }
public:
  void addLine(T a, T b) {
    update(root, minX, maxX, {a, b});
  }
  T query(T x) {
    return query(root, minX, maxX, x);
  }
  void init() {
    root = new Node;
  }
};
void out(vector <int>& v) {
  for (int i : v) {
    cout << i << " ";
  }
  cout << endl;
}
void solve() {
  int n;
  cin >> n;
  vector <int> a(n), b(n);
  DynamicLiChaoTree < int, 1, (int)1e9 + 10, (int) - 1e18 > lct;
  lct.init();

  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  vector <int> dp(n);
  lct.addLine(-b[0], dp[0]);
  for (int i = 1; i < n; i++) {
    dp[i] = -lct.query(a[i]);
    lct.addLine(-b[i], -dp[i]);
  }
  // out(dp);
  cout << dp.back() << endl;
}
int32_t main()
{
  zanj0();
  solve();
  timetaken;
  return 0;
}