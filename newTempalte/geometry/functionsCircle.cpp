//Common area of two circle
double area(int x1,int y1,int x2,int y2,double r1,double r2) {
  double s=dis(x2-x1,y2-y1);
  if(r1+r2<s) return 0;
  else if(r2-r1>s) return PI*r1*r1;
  else if(r1-r2>s) return PI*r2*r2;
  double q1=acos((r1*r1+s*s-r2*r2)/(2*r1*s));
  double q2=acos((r2*r2+s*s-r1*r1)/(2*r2*s));
  return (r1*r1*q1+r2*r2*q2-r1*s*sin(q1));
}
