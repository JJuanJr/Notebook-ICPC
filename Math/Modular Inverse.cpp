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