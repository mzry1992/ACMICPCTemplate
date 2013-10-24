bool Div[MaxN];
void BuildKD(int deep,int l, int r, Point p[]) {
  if (l > r) return;
  int mid = l + r >> 1;
  int minX, minY, maxX, maxY;
  minX = min_element(p + l, p + r + 1, cmpX)->x;
  minY = min_element(p + l, p + r + 1, cmpY)->y;
  maxX = max_element(p + l, p + r + 1, cmpX)->x;
  maxY = max_element(p + l, p + r + 1, cmpY)->y;
  Div[mid] = (maxX - minX >= maxY - minY);
  nth_element(p + l, p + mid, p + r + 1, Div[mid] ? cmpX : cmpY);
  BuildKD(l, mid - 1, p);
  BuildKD(mid + 1, r, p);
}
long long res;
void Find(int l, int r, Point a, Point p[]) {
  if (l > r)  return;
  int mid = l + r >> 1;
  long long dist = dist2(a, p[mid]);
  if (dist > 0)//NOTICE
    res = min(res, dist);
  long long d = Div[mid] ? (a.x - p[mid].x) : (a.y - p[mid].y);
  int l1, l2, r1, r2;
  l1 = l, l2 = mid + 1;
  r1 = mid - 1, r2 = r;
  if (d > 0)
    swap(l1, l2), swap(r1, r2);
  Find(l1, r1, a, p);
  if (d * d < res)
    Find(l2, r2, a, p);
}

