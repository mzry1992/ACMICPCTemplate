struct vir {
  long double re, im;
  vir(long double a = 0, long double b = 0) {
    re = a;
    im = b;
  }
  vir operator +(const vir& b) const {
    return vir(re + b.re, im + b.im);
  }
  vir operator -(const vir& b) const {
    return vir(re - b.re, im - b.im);
  }
  vir operator *(const vir& b) const {
    return vir(re * b.re - im * b.im, re * b.im + im * b.re);
  };
};
void change(vir *x, int len, int loglen) {
  int i, j, k, t;
  for (i = 0; i < len; i++) {
    t = i;
    for (j = k = 0; j < loglen; j++, t >>= 1)
      k = (k << 1) | (t & 1);
    if (k < i) {
      vir wt = x[k];
      x[k] = x[i];
      x[i] = wt;
    }
  }
}
void fft(vir *x, int len, int loglen) {
  int i, j, t, s, e;
  change(x, len, loglen);
  t = 1;
  for (i = 0; i < loglen; i++, t <<= 1) {
    s = 0;
    e = s + t;
    while (s < len) {
      vir a, b, wo(cos(PI / t), sin(PI / t)), wn(1, 0);
      for (j = s; j < s + t; j++) {
        a = x[j];
        b = x[j + t] * wn;
        x[j] = a + b;
        x[j + t] = a - b;
        wn = wn * wo;
      }
      s = e + t;
      e = s + t;
    }
  }
}
void dit_fft(vir *x, int len, int loglen) {
  int i, j, s, e, t = 1 << loglen;
  for (i = 0; i < loglen; i++) {
    t >>= 1;
    s = 0;
    e = s + t;
    while (s < len) {
      vir a, b, wn(1, 0), wo(cos(PI / t), -sin(PI / t));
      for (j = s; j < s + t; j++) {
        a = x[j] + x[j + t];
        b = (x[j] - x[j + t]) * wn;
        x[j] = a;
        x[j + t] = b;
        wn = wn * wo;
      }
      s = e + t;
      e = s + t;
    }
  }
  change(x, len, loglen);
  for (i = 0; i < len; i++)
    x[i].re /= len;
}
