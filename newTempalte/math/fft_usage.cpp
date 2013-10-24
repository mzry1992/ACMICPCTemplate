vir x1[MAXN], x2[MAXN];
void solve(long long *a, int lena, long long *b, int lenb, long long *ret, int& len) {
  int len1 = lena << 1;
  int len2 = lenb << 1;
  len = 1;
  int loglen = 0;
  while (len < len1 || len < len2) {
    len <<= 1;
    loglen++;
  }
  for (int i = 0; i < lena; i++)
    x1[i] = vir(a[i], 0);
  for (int i = lena; i < len; i++)
    x1[i] = vir(0, 0);
  for (int i = 0; i < lenb; i++)
    x2[i] = vir(b[i], 0);
  for (int i = lenb; i < len; i++)
    x2[i] = vir(0, 0);
  fft(x1, len, loglen);
  fft(x2, len, loglen);
  for (int i = 0; i < len; i++)
    x1[i] = x1[i] * x2[i];
  dit_fft(x1, len, loglen);
  for (int i = 0; i < len; i++)
    ret[i] = (long long)(x1[i].re + 0.5);
}

