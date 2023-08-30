int initial_dp(int i){
    //... process
    forabe(j, a, b)
        ans += dp(x + j);
    //... process
}

int dp(int i){
    //... process
    ans = prefix(x - a) - prefix(x - b - 1);
    //... process
    return memo[i] = ans;
}

double prefix(int x) {
    if (P[x] != -1) return P[x];
    return P[x] = dp(x) + prefix(x - 1);
}
