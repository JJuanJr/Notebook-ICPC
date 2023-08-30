map<ll, int> factors;

ll rho(ll n){
    if((n&1) == 0) return 2;
    ll t = 2, h = 2, g = 1;
    ll c = (rand() % n) + 1;
    while(g == 1){
        t = (mulmod(t, t, n) + c) % n;
        h = (mulmod(h, h, n) + c) % n;
        h = (mulmod(h, h, n) + c) % n;
        if(t > h) g = __gcd(t - h, n);
        else g = __gcd(h - t, n);
    }
    return (g!=n)? g:rho(n);
}

void fact_rho(ll n){//use for n > 10^12
    if(n == 1) return;
    if(miller_rabin(n)){
        factors[n]++;
        return;
    }
    ll f = rho(n);
    fact_rho(f);
    fact_rho(n/f);
}
