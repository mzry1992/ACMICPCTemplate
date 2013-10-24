bool check(int u) {
  for (int i=head[u]; i!=-1; i=edge[i].next) {
    int v=edge[i].to;
    if (!use[v]) {
      use[v]=1;
      if (pre[v]==-1 || check(pre[v])) {
        pre[v]=u;
        return 1;
      }
    }
  }
  return 0;
}
int match() {
  int ret=0;
  memset(pre,-1,sizeof(pre));
  for (int u=1; u<=N; u++) {
    memset(use,0,sizeof(use));
    if (check(u))
      ret++;
  }
  return ret;
}
