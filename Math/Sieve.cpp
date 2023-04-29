const int MAX = int(1e6);
bitset<MAX + 5> bs;
vector<int> prime;

void sieve() {
  bs.set();
  bs[0] = bs[1] = 0;
  form (i, 2, MAX + 1, 1) {
    if (bs[i]) {
      prime.pb(i);
      for (ll j = (ll) i * i; j <= MAX; j += i) {
        bs[j] = 0;
      }
    }
  }
}
