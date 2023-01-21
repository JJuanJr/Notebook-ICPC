ll mulmod(ll a, ll b, ll mod) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ll binpow(ll a, ll b, ll m) {
  a %= m;
  ll res = 1;
  while (b) {
    if (b & 1) res = mulmod(res,a,m);
    a = mulmod(a,a,m);
    b >>= 1;
  }
  return res;
}
