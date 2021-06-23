const int MAT = 103;
struct M {
  int t[MAT][MAT];
  int n;
  M(int n) {
    this->n = n;
    memset(t, 0, sizeof(t));
  }
  M operator* (const M& a) const {
    M c = M(n);
    signed long long mo2 = (int)4 * MOD * MOD;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++ ) {
        for (int k = 0; k < n; k++) {
          c.t[i][k] += t[i][j] * a.t[j][k];
          if (c.t[i][k] > mo2) c.t[i][k] -= mo2;
        }
      }
    }
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) c.t[i][j] %= MOD;
    return c;
  }
};
M fastPow(int n, M base, int power) {
  M ret = M(n);
  for (int i = 0; i < n; i++) ret.t[i][i] = 1;
  while (power > 0) {
    if (power & 1) {
      ret = ret * base;
    }
    base = base * base;
    power >>= 1;
  }
  return ret;
}
