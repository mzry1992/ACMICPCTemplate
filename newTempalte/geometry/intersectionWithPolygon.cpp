bool InCircle(Point a,double r) {
  return cmp(a.x*a.x+a.y*a.y,r*r) <= 0;
  //`$\epsilon$` should big enough
}
double CalcArea(Point a,Point b,double r) {
  Point p[4];
  int tot = 0;
  p[tot++] = a;
  Point tv = Point(a,b);
  Line tmp = Line(Point(0,0),Point(tv.y,-tv.x));
  Point near = LineToLine(Line(a,b),tmp);
  if (cmp(near.x*near.x+near.y*near.y,r*r) <= 0) {
    double A,B,C;
    A = near.x*near.x+near.y*near.y;
    C = r;
    B = C*C-A;
    double tvl = tv.x*tv.x+tv.y*tv.y;
    double tmp = sqrt(B/tvl);
    p[tot] = Point(near.x+tmp*tv.x,near.y+tmp*tv.y);
    if (OnSeg(Line(a,b),p[tot]) == true)	tot++;
    p[tot] = Point(near.x-tmp*tv.x,near.y-tmp*tv.y);
    if (OnSeg(Line(a,b),p[tot]) == true)	tot++;
  }
  if (tot == 3) {
    if (cmp(Point(p[0],p[1]).Length(),Point(p[0],p[2]).Length()) > 0)
      swap(p[1],p[2]);
  }
  p[tot++] = b;
  double res = 0.0,theta,a0,a1,sgn;
  for (int i = 0; i < tot-1; i++) {
    if (InCircle(p[i],r) == true && InCircle(p[i+1],r) == true) {
      res += 0.5*xmult(p[i],p[i+1]);
    } else {
      a0 = atan2(p[i+1].y,p[i+1].x);
      a1 = atan2(p[i].y,p[i].x);
      if (a0 < a1)	a0 += 2*pi;
      theta = a0-a1;
      if (cmp(theta,pi) >= 0) theta = 2*pi-theta;
      sgn = xmult(p[i],p[i+1])/2.0;
      if (cmp(sgn,0) < 0) theta = -theta;
      res += 0.5*r*r*theta;
    }
  }
  return res;
}
area2 = 0.0;
for (int i = 0; i < resn; i++) //counterclockwise
  area2 += CalcArea(p[i],p[(i+1)%resn],r);
