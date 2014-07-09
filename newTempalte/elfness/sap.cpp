#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
const int V=220;
const int En=200000;
const int oo=0x3f3f3f3f;
struct Edge {
  int num,ne,c;
} e[En];
int d[V],p[V],pre[V],low[V];
int gap[V],cur[V];
int N,K,st,ed;
void add(int x,int y,int c) {
  e[K].num=y;
  e[K].c=c;
  e[K].ne=p[x];
  p[x]=K++;
  e[K].num=x;
  e[K].c=0;
  e[K].ne=p[y];
  p[y]=K++;
}
int sap() {
  int ret=0;
  bool fail;
  for(int i=0; i<=N; i++) {
    low[i]=gap[i]=d[i]=0;
    cur[i]=p[i];
  }
  low[st]=oo;
  gap[0]=N;
  int u=st;
  while(d[st]<N) {
    fail=true;
    for(int i=cur[u]; i!=-1; i=e[i].ne) {
      int v=e[i].num;
      cur[u]=i;
      if(e[i].c&&d[u]==d[v]+1) {
        pre[v]=i;
        low[v]=min(low[u],e[i].c);
        u=v;
        if(u==ed) {
          do {
            e[pre[u]].c-=low[ed];
            e[pre[u]^1].c+=low[ed];
            u=e[pre[u]^1].num;
          } while(u!=st);
          ret+=low[ed];
        }
        fail=false;
        break;
      }
    }
    if(fail) {
      gap[d[u]]--;
      if(!gap[d[u]])return ret;
      d[u]=N;
      for(int i=p[u]; i!=-1; i=e[i].ne)
        if(e[i].c)d[u]=min(d[u],d[e[i].num]+1);
      gap[d[u]]++;
      cur[u]=p[u];
      if(u!=st)u=e[pre[u]^1].num;
    }
  }
  return ret;
}