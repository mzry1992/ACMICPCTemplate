double Simp(double l,double r) {
  double h = (r-l)/2.0;
  return h*(calc(l)+4*calc((l+r)/2.0)+calc(r))/3.0;
}
double rSimp(double l,double r) {
  double mid = (l+r)/2.0;
  if (abs((Simp(l,r)-Simp(l,mid)-Simp(mid,r)))/15 < eps)
    return Simp(l,r);
  else
    return rSimp(l,mid)+rSimp(mid,r);
}
