//find g -> (g^k = a mod m) for all a -> gcd(a, m)=1
int primitive_root(int m){
    int phin = phi(m);
    map<int, int> factors = factorize(phin);

    forabe(i, 1, m){
        bool ok = true;
        for(auto it : factors){
            ok = ok && binpow(i, phin/it.ff, m) != 1;
            if(!ok) break;
        }
        if(ok) return i;
    }
    return -1;
}
