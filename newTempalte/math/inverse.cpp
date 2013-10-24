void getInv2(int x) {
  inv[1]=1;
  for (int i=2; i<=x; i++)
    inv[i]=(mod-(mod/i)*inv[mod%i]%mod)%mod;
}
