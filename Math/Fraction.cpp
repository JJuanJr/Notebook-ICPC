struct fraction {
  int num, den;

  fraction(int _num, int _den) {
    num = _num;
    den = _den;
    simplify();
  }

  void simplify() {
    int mcd = __gcd(abs(num), abs(den));
    num /= mcd;
    den /= mcd;
  }

  fraction operator + (const fraction &x) const {
    return fraction(num * x.den + den * x.num, den * x.den);
  }

  fraction operator - (const fraction &x) const {
    return fraction(num * x.den - den * x.num, den * x.den);
  }

  fraction operator * (const fraction &x) const {
    return fraction(num * x.num, den * x.den);
  }

  fraction operator / (const fraction &x) const {
    return fraction(num * x.den, den * x.num);
  }

  friend ostream &operator << (ostream &os, const fraction &x) {
    return os << x.num << " / " << x.den;
  }
};
