//Intersecting segment between `$[la, lb]$`
int Gao(int la,int lb,Line line) {
  if (la > lb)
    lb += n;
  int l = la,r = lb,mid;
  while (l < r) {
    mid = l+r+1>>1;
    if (cmp((line.e-line.s)*(p[la]-line.s),0)*cmp((line.e-line.s)*(p[mid]-line.s),0) >= 0)
      l = mid;
    else
      r = mid-1;
  }
  return l%n;
}
double theta[maxn];
void Gettheta() {
  for (int i = 0; i < n; i++) {
    Point v = p[(i+1)%n]-p[i];
    theta[i] = atan2(v.y,v.x);
  }
  for (int i = 1; i < n; i++)
    if (theta[i-1] > theta[i]+eps)
      theta[i] += 2*pi;
}
void Calc(Line l) {
  double tnow;
  Point v = l.e-l.s;
  tnow = atan2(v.y,v.x);
  if (cmp(tnow,theta[0]) < 0)	tnow += 2*pi;
  int pl = lower_bound(theta,theta+n,tnow)-theta;
  tnow = atan2(-v.y,-v.x);
  if (cmp(tnow,theta[0]) < 0)	tnow += 2*pi;
  int pr = lower_bound(theta,theta+n,tnow)-theta;
  //Farest points with `$l$` on polygon
  pl = pl%n;
  pr = pr%n;
  if (cmp(v*(p[pl]-l.s),0)*cmp(v*(p[pr]-l.s),0) >= 0)
    return 0.0;
  int xa = Gao(pl,pr,l);
  int xb = Gao(pr,pl,l);
  if (xa > xb)	swap(xa,xb);
  //Intersecting with line `$P_{xa}\rightarrow P_{xa+1}$` and `$P_{xb}\rightarrow P_{xb+1}$`
  if (cmp(v*(p[xa+1]-p[xa]),0) == 0)  return 0.0;
  if (cmp(v*(p[xb+1]-p[xb]),0) == 0)  return 0.0;
  Point pa,pb;
  //Intersections
  pa = Line(p[xa],p[xa+1])&l;
  pb = Line(p[xb],p[xb+1])&l;
}

