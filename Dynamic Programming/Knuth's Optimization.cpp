// https://cses.fi/problemset/task/2088/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
#define pb push_back
#define ff first
#define ss second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define forn(i, n) for (int i = 0; i < n; ++i)
#define rforn(i, n) for (int i = n; i >= 0; --i)
#define form(i, n, m, x) for (int i = n; i < m; i += x)
#define rform(i, n, m, x) for (int i = n; i >= m; i -= x)

#ifdef LOCAL
  #include "/debug.h"
#else
  #define dbg(x...)
  #define endl '\n'
#endif

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n; cin >> n;
  int a[n];
  forn (i, n) cin >> a[i];
  
  ll p[n + 1];
  p[0] = 0;
  forn (i, n) p[i + 1] = p[i] + a[i];

  const ll INF = 1e18;
  ll dp[n + 1][n + 1];
  int opt[n + 1][n + 1];
  forn (len, n) {
    forn (l, n - len) {
      int r = l + len;
      if (l == r) {
        opt[l][r] = l;
        dp[l][r] = 0;
        continue;
      }
      dp[l][r] = INF;
      form (k, opt[l][r - 1], min(r, opt[l + 1][r] + 1), 1) {
        ll cost = dp[l][k] + dp[k + 1][r] + (p[r + 1] - p[l]);
        if (dp[l][r] > cost) {
          dp[l][r] = cost;
          opt[l][r] = k;
        }
      }
    }
  }
  cout << dp[0][n - 1] << endl;
  return 0;
}