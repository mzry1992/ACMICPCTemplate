#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
const int V=1200;
const int En=2100000;
struct Elf {
  int u,v,len;
} b[En];
const int oo=1000000000;
int ret;
int N,M,Root;//点数，边数，根，默认从0开始
int id[V],pre[V],cnt,vis[V];
int in[V];
bool TreeMST() {
  ret=0;
  int i,u,v;
  while(1) {
    for(i=0; i<N; i++)
      in[i]=oo;
    memset(pre,-1,sizeof(pre));
    for(i=0; i<M; i++) {
      u=b[i].u;
      v=b[i].v;
      if(b[i].len<in[v]&&u!=v) {
        pre[v]=u;
        in[v]=b[i].len;
      }
    }
    for(i=0; i<N; i++) {
      if(i==Root)continue;
      if(pre[i]==-1)return false;
    }
    in[Root]=0;
    cnt=0;
    memset(id,-1,sizeof(id));
    memset(vis,-1,sizeof(vis));
    for(i=0; i<N; i++) {
      ret+=in[i];
      v=i;
      while(vis[v]!=i&&id[v]==-1&&v!=Root) {
        vis[v]=i;
        v=pre[v];
      }
      if(v!=Root&&id[v]==-1) {
        for(u=pre[v]; u!=v; u=pre[u])
          id[u]=cnt;
        id[v]=cnt++;
      }
    }
    if(cnt==0)return true;
    for(i=0; i<N; i++)
      if(id[i]==-1)id[i]=cnt++;
    for(i=0; i<M; i++) {
      v=b[i].v;
      b[i].u=id[b[i].u];
      b[i].v=id[b[i].v];
      if(b[i].u!=b[i].v)
        b[i].len-=in[v];
    }
    N=cnt;
    Root=id[Root];
  }
  return true;
}