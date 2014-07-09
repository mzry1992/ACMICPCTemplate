/*
 * nearestPointPair.cpp
 *
 *  Created on: 2011-10-10
 *      Author: Fish
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const int MaxN = 120000;
const int Log = 20;

struct Point {
  double x, y;
  Point() {
  }
  Point(double x, double y) :
    x(x), y(y) {
  }
  Point operator-(const Point& p) const {
    return Point(x - p.x, y - p.y);
  }
  double norm() const {
    return hypot(x, y);
  }
  void init() {
    scanf("%lf%lf", &x, &y);
  }
} p[MaxN];
int x[MaxN], y[Log][MaxN], tmp[MaxN], n;
bool vst[MaxN];

bool comp_x(const int& i, const int& j) {
  return p[i].x < p[j].x;
}

bool comp_y(const int& i, const int& j) {
  return p[i].y < p[j].y;
}

double dfs(int k, int l, int r) {
  double ret = 1e100;
  if (r - l <= 2) {
    for (int i = l; i < r; i++)
      for (int j = i + 1; j <= r; j++)
        ret = min(ret, (p[x[i]] - p[x[j]]).norm());
    return ret;
  }

  int mid = (l + r) >> 1;
  int lp = l, rp = mid + 1;
  for (int i = l; i <= r; i++)
    vst[x[i]] = i <= mid;
  for (int i = l; i <= r; i++)
    if (vst[y[k][i]])
      y[k + 1][lp++] = y[k][i];
    else
      y[k + 1][rp++] = y[k][i];
  double lhs = dfs(k + 1, l, mid);
  double rhs = dfs(k + 1, mid + 1, r);
  double mx = (p[x[mid + 1]].x + p[x[mid]].x) / 2.0;
  ret = min(lhs, rhs);

  lp = 0;
  for (int i = l; i <= r; i++)
    if (fabs(mx - p[y[k][i]].x) < ret)
      tmp[lp++] = y[k][i];

  for (int i = 0; i < lp; i++)
    for (int j = 1; j < 8 && i + j < lp && (p[tmp[i + j]].y - p[tmp[i]].y) < ret; j++)
      ret = min(ret, (p[tmp[i]] - p[tmp[i + j]]).norm());

  return ret;
}

int main() {
#ifdef __FISH__
  freopen("data.in", "r", stdin);
  freopen("nlogn.out", "w", stdout);
#endif
  while (scanf("%d", &n) == 1 && n) {
    for (int i = 0; i < n; i++) {
      p[i].init();
      x[i] = y[0][i] = i;
    }
    sort(x, x + n, comp_x);
    sort(y[0], y[0] + n, comp_y);
    printf("%.2f\n", dfs(0, 0, n - 1) / 2.0);
    // printf("%.6f\n", dfs(0, 0, n - 1));
  }

  return 0;
}
