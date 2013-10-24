//Use stack instead of queue when get TLE
int L,N;
int K;
struct edges {
  int to,next,cap,flow,cost;
} edge[MAXM];
struct nodes {
  int dis,pre,head;
  bool visit;
} node[MAXN];
void init(int n) {
  N=n;
  L=0;
  for (int i=0; i<N; i++)
    node[i].head=-1;
}
void add_edge(int x,int y,int cap,int cost) {
  edge[L].to=y;
  edge[L].cap=cap;
  edge[L].cost=cost;
  edge[L].flow=0;
  edge[L].next=node[x].head;
  node[x].head=L++;
  edge[L].to=x;
  edge[L].cap=0;
  edge[L].cost=-cost;
  edge[L].flow=0;
  edge[L].next=node[y].head;
  node[y].head=L++;
}
bool spfa(int s,int t) {
  queue <int> q;
  for (int i=0; i<N; i++) {
    node[i].dis=0x3fffffff;
    node[i].pre=-1;
    node[i].visit=0;
  }
  node[s].dis=0;
  node[s].visit=1;
  q.push(s);
  while (!q.empty()) {
    int u=q.front();
    node[u].visit=0;
    for (int i=node[u].head; i!=-1; i=edge[i].next) {
      int v=edge[i].to;
      if (edge[i].cap>edge[i].flow &&
          node[v].dis>node[u].dis+edge[i].cost) {
        node[v].dis=node[u].dis+edge[i].cost;
        node[v].pre=i;
        if (!node[v].visit) {
          node[v].visit=1;
          q.push(v);
        }
      }
    }
    q.pop();
  }
  if (node[t].pre==-1)
    return 0;
  else
    return 1;
}
int mcmf(int s,int t,int &cost) {
  int flow=0;
  while (spfa(s,t)) {
    int max=inf;
    for (int i=node[t].pre; i!=-1; i=node[edge[i^1].to].pre) {
      if (max>edge[i].cap-edge[i].flow)
        max=edge[i].cap-edge[i].flow;
    }
    for (int i=node[t].pre; i!=-1; i=node[edge[i^1].to].pre) {
      edge[i].flow+=max;
      edge[i^1].flow-=max;
      cost+=edge[i].cost*max;
    }
    flow+=max;
  }
  return flow;
}

