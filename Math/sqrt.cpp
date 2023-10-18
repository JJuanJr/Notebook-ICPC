ll int_sqrt (ll x) {
	ll ans = 0;
	for (ll k = 1LL << 30; k != 0; k /= 2)
		if ((ans + k) * (ans + k) <= x)
			ans += k;
	return ans;
}