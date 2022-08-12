ll binpow(ll a, ll b, ll m) {
  a %= m;
  ll res = 1;
  while (b) {
    if (b & 1) res = res * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return res;
}
