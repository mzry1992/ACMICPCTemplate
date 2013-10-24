int getEuler(int x) {
  getFactor(x);
  int ret=x;
  for (int i=0; i<N; i++)
    ret = ret/fac[i]*(fac[i]-1);
  return ret;
}
void getEuler2() {
  memset(euler,0,sizeof(euler));
  euler[1] = 1;
  for (int i = 2; i <= 3000000; i++) {
    if (!euler[i]) {
      for (int j = i; j <= 3000000; j += i) {
        if (!euler[j])
          euler[j] = j;
        euler[j] = euler[j]/i*(i-1);
      }
    }
  }
}
