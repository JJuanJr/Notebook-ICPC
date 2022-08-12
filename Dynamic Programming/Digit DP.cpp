// - Descripción: Cuenta la cantidad de numeros entre [a, b] que no tienen digitos iguales seguidos
// - Complejidad: O(NUM_E * NUM_T)

const int MOD = 998244353;
int tam, NUM[55], dp[55][2][2][11];

int solve(int i, bool menor, bool ncero, int last) {
  if (i == tam) return 1;
  int &ans = dp[i][menor][ncero][last];
  if (ans != -1) return ans;
  ans = 0;
  forn (dig, 10) {
    if (dig == last && (ncero || dig)) continue;
    if (menor || dig <= NUM[i]) {
      ans = (ans + solve(i + 1, menor || dig < NUM[i], ncero || dig, dig)) % MOD;
    }
  }
  return ans;
}

bool g(string s) {
  forn (i, sz(s) - 1) {
    if (s[i] == s[i + 1]) return false;
  }
  return true;
}

int build(string s) {
  tam = sz(s);
  forn (i, sz(s)) {
    NUM[i] = s[i] - '0';
  }
  memset(dp, -1, sizeof dp);
  return solve(0, false, false, 10);
}

int main() {
  string l, r;
  while (cin >> l >> r) {
    cout << ((build(r) - build(l) + MOD) % MOD + g(l)) % MOD << endl;
  }
  return 0;
}
