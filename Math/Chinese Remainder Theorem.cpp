//a === b1 % m1
//a === b2 % m2
ll CRT(ll b1, ll b2, ll m1, ll m2) {
    ll x, y;
    ll c = gcd(m1, m2, x, y);
    ll a = b2 * x * m1 + b1 * y * m2;
    ll mod = m1 * m2;
    a = a % mod;
    if (a < 0) a += mod;
    return a;
}
//ff -> b, ss -> m, all m are coprimes
int CRT_general(vector<ii> &c){
    int a = 0, M = 1;
    forn(i, sz(c))
        M *= c[i].ss;
    forn(i, sz(c))
        a = (a + modular_inverse(M/c[i].ss, c[i].ss)
             * c[i].ff * (M/c[i].ss)) % M;
    return a;
}
