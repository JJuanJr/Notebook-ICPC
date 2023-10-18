int phi(int n){
    int result = n;
    for(int i=2; i*i<=n; ++i){
        if(n%i) continue;
        while(n%i == 0)
            n /= i;
        result -= result/i;
    }

    if(n > 1)
        result -= result/n;
    return result;
}

vi phi_1_to_n(int n){
    vector<int> phi;
    forne(i, n) phi.pb(i);

    for(int i = 2; i <= n; ++i){
        if(phi[i] != i) continue;

        for(int j = i; j <= n; j += i)
            phi[j] -= phi[j]/i;
    }
    return phi;
}

vi phi_1_to_n2(int n){
    vector<int> phi;
    forne(i, n) phi.pb(i-1);
    phi[1] = 1;

    for(int i = 2; i <= n; ++i){
        for(int j = i*2; j <= n; j += i)
            phi[j] -= phi[i];
    }
    return phi;
}
