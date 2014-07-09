#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
const int V=1200;
const int En=21000;
const int oo=1000000000;
struct Edge {
  int num,ne,w;
} e[En];
int p[V],K;
void add(int x,int y,int z) {
  e[K].num=y;
  e[K].w=z;
  e[K].ne=p[x];
  p[x]=K++;
}
bool sx[V],sy[V];
int lx[V],ly[V],mat[V];
bool path(int u) {
  sx[u]=true;
  for(int i=p[u]; i!=-1; i=e[i].ne) {
    int v=e[i].num;
    if(!sy[v]&&lx[u]+ly[v]==e[i].w) {
      sy[v]=true;
      if(mat[v]==-1||path(mat[v])) {
        mat[v]=u;
        return true;
      }
    }
  }
  return false;
}
int N;
int KM() {
  int i,j;
  for(i=0; i<N; i++) {
    lx[i]=-oo;
    for(j=p[i]; j!=-1; j=e[j].ne)
      lx[i]=max(lx[i],e[j].w);
  }
  for(i=0; i<N; i++)ly[i]=0,mat[i]=-1;
  for(int u=0; u<N; u++)
    while(1) {
      for(i=0; i<N; i++)sx[i]=0,sy[i]=0;
      if(path(u))break;
      int dx=oo;
      for(i=0; i<N; i++)if(sx[i])
          for(j=p[i]; j!=-1; j=e[j].ne)
            if(!sy[e[j].num])
              dx=min(dx,lx[i]+ly[e[j].num]-e[j].w);
      if(dx==oo)return -1;
      for(i=0; i<N; i++)if(sx[i])lx[i]-=dx;
      for(i=0; i<N; i++)if(sy[i])ly[i]+=dx;
    }
  int ret=0;
  for(i=0; i<N; i++)ret+=lx[i]+ly[i];
  return -ret;
}
int _,ca,n,m,i,x,y,z,te;
int main() {
  scanf("%d",&_);
  ca=0;
  while(_--) {
    ca++;
    scanf("%d%d",&n,&m);
    N=n;
    for(i=0; i<n; i++)p[i]=-1;
    K=0;
    for(i=0; i<m; i++) {
      scanf("%d%d%d",&x,&y,&z);
      x--;
      y--;
      add(x,y,-z);
      add(y,x,-z);
    }
    te=KM();
    printf("Case %d: ",ca);
    if(te==-1)puts("NO");
    else printf("%d\n",te);
  }
}