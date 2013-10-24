int lcp(int x,int y) {
  if (x > y)	swap(x,y);
  if (x == y)
    return len-sa[x];//NOTICE!
  x++;
  int k = lent[y-x+1];
  return min(f[x][k],f[y-(1<<k)+1][k]);
}
//Interval
void getinterval(int pos,int comlen,int& pl,int& pr) {
  int l,r,mid,cp;
  l = 0;
  r = pos;
  while (l < r) {
    mid = l+r>>1;
    cp = lcp(mid,pos);
    if (cp < comlen)
      l = mid+1;
    else
      r = mid;
  }
  pl = l;
  l = pos;
  r = len-1;
  while (l < r) {
    mid = l+r+1>>1;
    cp = lcp(pos,mid);
    if (cp < comlen)
      r = mid-1;
    else
      l = mid;
  }
  pr = l;
}

