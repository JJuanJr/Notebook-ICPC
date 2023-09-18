vector<vector<pair<int, int>>> ady;
int n, m, target;
const int N = 18;
const int MASK = 1 << N;
const int INF = int(1e7);
int dp[N][MASK];

int solve(int v, int mask) {
  if (mask == target) return 0;
  int &ans = dp[v][mask];
  if (ans != -1) return ans;
  ans = INF;
  for (auto &u : ady[v]) {
    if (!(mask & (1 << u.first))) {
      ans = min(ans, solve(u.first, mask | (1 << u.first)) + u.second);
    }
  }
  return ans;
}

cin >> n >> m;
target = (1 << n) - 1;
ady.assign(n, {});
forn (i, m) {
  int v, u, w; cin >> v >> u >> w;
  v--, u--;
  ady[v].push_back({u, w});
  ady[u].push_back({v, w});
}
memset(dp, -1, sizeof dp);
cout << solve(0, 1) << endl;
