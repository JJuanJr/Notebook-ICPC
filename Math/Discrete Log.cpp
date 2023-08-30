// Returns minimum x for which a ^ x % m = b % m, a and m are coprime.
int discrete_log_coprime(int a, int b, int m){
    int n = sqrt(m) + 1, an = 1;
    unordered_map<int, int> mapa;

    forn(i, n) an = (an * a) % m;

    int aq = b, anp = 1;
    forne(q, n){
        mapa[aq] = q;
        aq = (aq*a) % m;
    }

    forabe(p, 1, n){
        anp = (anp*an) % m;
        if(mapa.count(anp))
            return n*p-mapa[anp];
    }
    return -1;
}

int discrete_log_nocoprime(int a, int b, int m){
    if(a == 0) return (b == 0)? 1 : -1;

    a %= m;  b %= m;
    int k = 1, add = 0, g;
    while((g = __gcd(a, m)) > 1){
        if(b == k) return add;
        if(b % g) return -1;
        b /= g;  m /= g;  add++;
        k = (k*a/g) % m;
    }

    int n = sqrt(m) + 1, an = 1, aq = b, anp = k;
    unordered_map<int, int> mapa;

    forn(i, n) an = (an * a) % m;

    forne(q, n){
        mapa[aq] = q;
        aq = (aq*a) % m;
    }

    forabe(p, 1, n){
        anp = (anp*an) % m;
        if(mapa.count(anp))
            return n*p-mapa[anp] + add;
    }
    return -1;
}
