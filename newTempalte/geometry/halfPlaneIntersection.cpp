bool HPIcmp(Line a, Line b) {
  if (fabs(a.k - b.k) > EPS)  return a.k < b.k;
  return ((a.s - b.s) * (b.e - b.s)) < 0;
}
Line Q[MAXN];
void HPI(Line line[], int n, Point res[], int &resn) {
  int tot = n;
  sort(line, line + n, HPIcmp);
  tot = 1;
  for (int i = 1; i < n; i++)
    if (fabs(line[i].k - line[i - 1].k) > EPS)
      line[tot++] = line[i];
  int head = 0, tail = 1;
  Q[0] = line[0];
  Q[1] = line[1];
  resn = 0;
  for (int i = 2; i < tot; i++) {
    if (fabs((Q[tail].e - Q[tail].s) * (Q[tail - 1].e - Q[tail - 1].s)) < EPS ||
        fabs((Q[head].e - Q[head].s) * (Q[head + 1].e - Q[head + 1].s)) < EPS)
      return;
    while (head < tail && (((Q[tail] & Q[tail - 1]) - line[i].s) * (line[i].e - line[i].s)) > EPS)
      tail--;
    while (head < tail && (((Q[head] & Q[head + 1]) - line[i].s) * (line[i].e - line[i].s)) > EPS)
      head++;
    Q[++tail] = line[i];
  }
  while (head < tail && (((Q[tail] & Q[tail - 1]) - Q[head].s) * (Q[head].e - Q[head].s)) > EPS)
    tail--;
  while (head < tail && (((Q[head] & Q[head + 1]) - Q[tail].s) * (Q[tail].e - Q[tail].s)) > EPS)
    head++;
  if (tail <= head + 1)   return;
  for (int i = head; i < tail; i++)
    res[resn++] = Q[i] & Q[i + 1];
  if (head < tail + 1)
    res[resn++] = Q[head] & Q[tail];
}
