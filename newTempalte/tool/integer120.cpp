struct integer {
  long long pa, pb;
  integer() {}
  integer(long long _pa, long long _pb) {
    pa = _pa;
    pb = _pb;
  }
  integer negate() {
    if (pa == 0 && pb == 0)
      return integer(pa, pb);
    else if (pa == 0)
      return integer(pa, -pb);
    else
      return integer(-pa, pb);
  }
  integer operator +(const integer& b) const {
    integer ret = integer(pa + b.pa, pb + b.pb);
    if (ret.pb >= MOD) {
      ret.pa += 1;
      ret.pb -= MOD;
    }
    return ret;
  }
  bool operator <(const integer& b) const {
    if (pa == b.pa)
      return pb < b.pb;
    return pa < b.pa;
  }
};
