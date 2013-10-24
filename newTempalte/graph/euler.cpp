//Directed graph
void solve(int x) {
  int i;
  if (!match[x]) {
    path[++l]=x;
    return ;
  }
  for (i=1; i<=n; i++)
    if (b[x][i]) {
      b[x][i]--;
      match[x]--;
      solve(i);
    }
  path[++l]=x;
}
//Undirected graph
void solve(int x) {
  int i;
  if (!match[x]) {
    path[++l]=x;
    return ;
  }
  for (i=1; i<=n; i++)
    if (b[x][i]) {
      b[x][i]--;
      b[i][x]--;
      match[x]--;
      match[i]--;
      solve(i);
    }
  path[++l]=x;
}
