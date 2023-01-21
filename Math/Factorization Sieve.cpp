int primediv[MAX];//10^6
vector<ll> primes;

void sieve() {
    forn(i, MAX) primediv[i] = i;
    int root = sqrt(MAX) + 1;
    forab(i, 2, MAX) {
        if(primediv[i] != i) continue;
        primes.pb(i);
        if(i > root) continue;
        form(j, i * i, MAX, i) primediv[j] = i;
    }
}

map<ll, int> factorize(ll n){//n <= 10^12
    map<ll, int> factors;
    for(int i=0; i<primes.size() && n>=MAX; ++i){
        while(n%primes[i]==0){
            factors[primes[i]]++;
            n /= primes[i];
        }
    }
    if(n >= MAX){
        factors[n]++;
        return factors;
    }
    while(n > 1){
        factors[primediv[n]]++;
        n /= primediv[n];
    }
    return factors;
}
