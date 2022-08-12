int n, S;
vector<int> arr, block;

void preCalc() {
  S = sqrt(n);
  block.assign(n / S + 1, 0);
  forn (i, n) {
    block[i / S] += arr[i];
  }
}

int query(int l, int r) {
  int sum = 0;
  int b_l = l / S, b_r = r / S;
  if (b_l == b_r) {
    form (i, l, r + 1, 1) sum += arr[i];
  } else {
    for (int i = l, end = (b_l + 1) * S - 1; i <= end; ++i) sum += arr[i];
    form (i, b_l + 1, b_r, 1) sum += block[i];
    form (i, b_r * S, r + 1, 1) sum += arr[i];
  }
  return sum;
}

void update(int i, int new_val) {
  block[i / S] += new_val - arr[i];
  arr[i] = new_val;
}
