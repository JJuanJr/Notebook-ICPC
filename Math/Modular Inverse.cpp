int inv[MAXN];

void modular_inverse_range(int m){
    inv[0] = 0;  inv[1] = 1;
    forab(i, 2, MAXN)
        inv[i] = (-(m/i)*inv[m%i] + m) % m;
}

int modular_inverse_binpow(int a, int m){
    return binpow(a, phi(m)-1, m);
}

int modular_inverse_extEuclid(int a, int m){
    int x, y;
    int g = extEuclid(a, m, x, y);
    if(g != 1)
        return -1;
    x = (x % m + m) % m;
    return x;
}

vi inversos(vi a, int m){
    vi inv;
    int v = 1;
    forn(i, sz(a)){
        inv.pb(v);
        v = (v * a[i]) % m;
    }

    int x, y;
    extEuclid(v, m, x, y);
    x = (x % m + m) % m;

    rforn(i, sz(a)){
        inv[i] = inv[i] * x;
        x = (x * a[i]) % m;
    }
    return inv;
}
