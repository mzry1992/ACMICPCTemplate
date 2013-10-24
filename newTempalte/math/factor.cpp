const int TIME = 8;
int factor[100],fac_top = -1;
//GCD of bint
bint gcd(bint small,bint big) {
  while(small) {
    swap(small,big);
    small%=big;
  }
  return abs(big);
}
//ret = (a*b)%n (n<2^62)
bint muti_mod(bint a,bint b,bint n) {
  bint exp = a%n, res = 0;
  while(b) {
    if(b&1) {
      res += exp;
      if(res>n) res -= n;
    }
    exp <<= 1;
    if (exp>n) exp -= n;
    b>>=1;
  }
  return res;
}
// ret = (a^b)%n
bint mod_exp(bint a,bint p,bint m) {
  bint exp=a%m, res=1;
  while(p>1) {
    if(p&1)
      res=muti_mod(res,exp,m);
    exp = muti_mod(exp,exp,m);
    p>>=1;
  }
  return muti_mod(res,exp,m);
}
//miller-rabin
bool miller_rabin(bint n, int times) {
  if(n==2)return 1;
  if(n<2||!(n&1))return 0;
  bint a, u=n-1, x, y;
  int t=0;
  while(u%2==0) {
    t++;
    u/=2;
  }
  srand(time(0));
  for(int i=0; i<times; i++) {
    a = rand() % (n-1) + 1;
    x = mod_exp(a, u, n);
    for(int j=0; j<t; j++) {
      y = muti_mod(x, x, n);
      if ( y == 1 && x != 1 && x != n-1 )
        return false; //must not
      x = y;
    }
    if( y!=1) return false;
  }
  return true;
}
bint pollard_rho(bint n,int c) {
  bint x,y,d,i = 1,k = 2;
  srand(time(0));
  x = rand()%(n-1)+1;
  y = x;
  while(true) {
    i++;
    x = (muti_mod(x,x,n) + c) % n;
    d = gcd(y-x, n);
    if (1 < d && d < n) return d;
    if( y == x) return n;
    if(i == k) {
      y = x;
      k <<= 1;
    }
  }
}
void findFactor(bint n,int k) {
  if(n==1)return;
  if(miller_rabin(n, TIME)) {
    factor[++fac_top] = n;
    return;
  }
  bint p = n;
  while(p >= n)
    p = pollard_rho(p,k--);
  findFactor(p,k);
  findFactor(n/p,k);
}

