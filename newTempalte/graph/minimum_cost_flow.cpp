#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
const int MAXN = 2003;
const int MAXM = 2000 * 1999 / 2 + 2000 * 3;
int N, L;
int head[MAXN];
struct Edge {
  int to, next, flow, cost;
} edge[MAXM * 2];
int h[MAXN], dis[MAXN], pre[MAXN];
struct Heap {
  int value[MAXN + 1], id[MAXN + 1];
  int pos[MAXN];
  int size;
  void init() {
    size = 1;
  }
  void swap2(int p, int q) {
    swap(value[p], value[q]);
    swap(id[p], id[q]);
    pos[id[p]] = p;
    pos[id[q]] = q;
  }
  void push_up(int p) {
    while (p > 1 && value[p / 2] > value[p]) {
      swap2(p, p / 2);
      p /= 2;
    }
  }
  void push_down(int p) {
    while (p * 2 < size) {
      int best = p;
      if (p * 2 < size && value[p] > value[p * 2])
        best = p * 2;
      if (p * 2 + 1 < size && value[best] > value[p * 2 + 1])
        best = p * 2 + 1;
      if (p == best)
        break;
      swap2(p, best);
      p = best;
    }
  }
  void push(int _value, int _id) {
    value[size] = _value;
    id[size] = _id;
    pos[_id] = size;
    push_up(size++);
  }
  int top() {
    return id[1];
  }
  void pop() {
    value[1] = value[size - 1];
    id[1] = id[--size];
    pos[id[1]] = 1;
    push_down(1);
  }
  void update(int _value, int _id) {
    int p = pos[_id];
    value[p] = _value;
    push_up(p);
  }
} heap;
bool inque[MAXN];
void init(int n) {
  N = n;
  L = 0;
  memset(head, -1, 4 * n);
}
void add_edge(int u, int v, int flow, int cost) {
  edge[L].to = v;
  edge[L].flow = flow;
  edge[L].cost = cost;
  edge[L].next = head[u];
  head[u] = L++;
  edge[L].to = u;
  edge[L].flow = 0;
  edge[L].cost = -cost;
  edge[L].next = head[v];
  head[v] = L++;
}
void spfa(int s) {
  memset(dis, 63, 4 * N);
  memset(inque, 0, N);
  memset(pre, -1, 4 * N);
  dis[s] = 0;
  queue <int> que;
  que.push(s);
  while (!que.empty()) {
    int u = que.front();
    inque[u] = 0;
    que.pop();
    for (int i = head[u]; i != -1; i = edge[i].next)
      if (edge[i].flow) {
        int v = edge[i].to;
        if (dis[v] > dis[u] + edge[i].cost) {
          dis[v] = dis[u] + edge[i].cost;
          pre[v] = i;
          if (!inque[v]) {
            inque[v] = 1;
            que.push(v);
          }
        }
      }
  }
}
void dijkstra(int s) {
  for (int i = 0; i < N; ++i)
    h[i] += dis[i];
  memset(dis, 63, 4 * N);
  memset(pre, -1, 4 * N);
  memset(inque, 0, N);
  dis[s] = 0;
  inque[s] = 1;
  heap.init();
  heap.push(0, s);
  while (heap.size > 1) {
    int u = heap.top();
    heap.pop();
    for (int i = head[u]; i != -1; i = edge[i].next)
      if (edge[i].flow) {
        int v = edge[i].to;
        if (dis[v] > dis[u] + edge[i].cost + h[u] - h[v]) {
          dis[v] = dis[u] + edge[i].cost + h[u] - h[v];
          pre[v] = i;
          if (!inque[v]) {
            heap.push(dis[v], v);
            inque[v] = 1;
          } else
            heap.update(dis[v], v);
        }
      }
  }
}
int minimumCostFlow(int s, int t, int &cost) {
  int flow = 0;
  memset(h, 0, 4 * N);
  for (spfa(s); pre[t] != -1; dijkstra(s)) {
    int maxs = edge[pre[t]].flow;
    for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to])
      maxs = min(maxs, edge[i].flow);
    for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
      edge[i].flow -= maxs;
      edge[i ^ 1].flow += maxs;
      cost += edge[i].cost * maxs;
    }
    flow += maxs;
  }
  return flow;
}
int main() {
  return 0;
}
