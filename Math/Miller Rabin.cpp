bool probably_prime(ll n, ll a, ll d, int s){
    ll x = binpow(a, d, n);
    if(x == 1 || x+1 == n) return true;
    forn(r, s){
        x = mulmod(x,x,n);
        if(x == 1) return false;
        if(x+1 == n) return true;
    }
    return false;
}

bool miller_rabin(ll n){//check (n is prime)?
    if(n < 2) return false;
    const int a[] = {2,3,5,7,11,13,17,19,23};
    int s = -1;
    ll d = n-1;
    while(!d&1) d >>= 1, s++;

    forn(i, 9){
        if(n == a[i]) return true;
        if(!probably_prime(n, a[i], d, s))
            return false;
    }
    return true;
}
