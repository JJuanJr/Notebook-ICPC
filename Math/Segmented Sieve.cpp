vector<int> prime; // sqrt(MAXR)

vector<ll> segmented_criba(ll l, ll r) {
  l = max(l, 2ll);
  vector<bool> vis(r - l + 1);
  for (int &pp : prime) {
    if ((ll) pp * pp > r) break;
    ll mn = (l + pp - 1) / pp;
    if (mn == 1ll) mn++;
    mn *= pp;
    for (ll i = mn; i <= r; i += pp) {
      vis[i - l] = true;
    } 
  }
  vector<ll> ans;
  forn (i, sz(vis)) if (!vis[i]) ans.push_back(l + i);
  return ans;
}
