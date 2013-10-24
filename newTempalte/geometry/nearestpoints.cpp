double calc_dis(Point &a ,Point &b) {
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
bool operator<(const Point &a ,const Point &b) {
  if(a.y != b.y) return a.x < b.x;
  return a.x < b.x;
}
double Gao(int l ,int r ,Point pnts[]) {
  double ret = inf;
  if(l == r) return ret;
  if(l+1 ==r) {
    ret = min(calc_dis(pnts[l],pnts[l+1]) ,ret);
    return ret;
  }
  if(l+2 ==r) {
    ret = min(calc_dis(pnts[l],pnts[l+1]) ,ret);
    ret = min(calc_dis(pnts[l],pnts[l+2]) ,ret);
    ret = min(calc_dis(pnts[l+1],pnts[l+2]) ,ret);
    return ret;
  }

  int mid = l+r>>1;
  ret = min (ret ,Gao(l ,mid,pnts));
  ret = min (ret , Gao(mid+1, r,pnts));

  for(int c = l ; c<=r; c++)
    for(int d = c+1; d <=c+7 && d<=r; d++) {
      ret = min(ret , calc_dis(pnts[c],pnts[d]));
    }
  return ret;
}

