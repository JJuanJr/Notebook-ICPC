int n, m; cin >> n >> m;
vector<int> ady[n];

form (i, m) {
  int v, u; cin >> v >> u;
  v--, u--;
  ady[v].pb(u);
}

vector<int> low(n), num(n, -1), comp(n);
stack<int> st;
int scc, cont;
scc = cont = 0;
const int INF = int(1e9);

function<void(int)> tarjan = [&](int v) {
  low[v] = num[v] = cont++;
  st.push(v);
  for (int &u : ady[v]) {
    if (num[u] == -1) tarjan(u);
    low[v] = min(low[v], low[u]);
  }

  if (low[v] == num[v]) {
    int u;
    do {
      u = st.top(); st.pop();
      low[u] = INF;
      comp[u] = scc;
    } while (u != v);
    scc++;
  }
};

forn (i, n) if (num[i] == -1) tarjan(i);
