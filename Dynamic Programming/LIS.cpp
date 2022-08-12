int lis(const vector<int> &arr) {
  int n = sz(arr);
  vector<int> d(n, 1);
  forn (i, n) {
    forn (j, i) {
      if (arr[j] < arr[i]) {
        d[i] = max(d[i], d[j] + 1);
      }
    }
  }
  int ans = d[0];
  form (i, 1, n, 1) {
    ans = max(ans, d[i]);
  }
  return ans;
}

vector<int> lis_subeq(const vector<int> &arr) {
  int n = sz(arr);
  vector<int> d(n, 1), p(n, -1);
  forn (i, n) {
    forn (j, i) {
      if (arr[j] < arr[i] && d[i] < d[j] + 1) {
        d[i] = d[j] + 1;
        p[i] = j;
      }
    }
  }
  int ans = d[0], pos = 0;
  form (i, 1, n, 1) {
    if (d[i] > ans) {
      ans = d[i];
      pos = i;
    }
  }
  vector<int> subseq;
  while (pos != -1) {
    subseq.pb(a[pos]);
    pos = p[pos];
  }
  reverse(all(subseq));
  return subseq;
}

int lis_bin(const vector<int> &arr) {
  int n = sz(arr);
  const int INF = int(1e9);
  vector<int> d(n + 1, INF);
  d[0] = -INF;
  forn (i, n) {
    int j = int(upper_bound(all(d), arr[i]) - d.begin());
    if (d[j - 1] < arr[i] && arr[i] < d[j]) {
      d[j] = arr[i];
    }
  }
  int ans = 0;
  rforn (i, n) {
    if (d[i] < INF) {
      ans = i;
      break;
    }
  }
  return ans;
}
