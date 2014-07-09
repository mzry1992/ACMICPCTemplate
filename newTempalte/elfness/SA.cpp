#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
typedef long long LL;
const int N=100100;
char s[N];  /// 长度+1，对于非字符串，加一个小于最小值的元素，
int sa[N];  /// 倍增算法，结果 下标  1-n，第  i 大的是  sa[i]
int rk[N];  /// 第  i 位开始的后缀，的排名为  rk[i]
int wa[N],wb[N],wv[N],rmq[20][N];
int sn,to[N];
bool cmp(int *y,int a,int b,int L) {
  return y[a]==y[b]&&y[a+L]==y[b+L];
}
void da(char *s,int *sa,int len,int dn) {
  int i,j,p;
  int *x,*y,*t;
  x=wa;
  y=wb;
  for(i=0; i<dn; i++)rk[i]= 0;
  for(i=0; i<len; i++)rk[x[i]=s[i]]++;
  for(i=0; i<dn; i++)rk[i+1]+=rk[i];
  for(i=len-1; i>=0; i--)sa[--rk[x[i]]]=i;
  for(j=1,p=1; p<len; j*=2,dn=p) {
    for(p=0; p<j; p++)y[p]=len-j+p;
    for(i=0; i<len; i++)if(sa[i]>=j)y[p++]=sa[i]-j;
    for(i=0; i<len; i++)wv[i]=x[y[i]];
    for(i=0; i<dn; i++)rk[i]=0;
    for(i=0; i<len; i++)rk[wv[i]]++;
    for(i=0; i<dn; i++)rk[i+1]+=rk[i];
    for(i=len-1; i>=0; i--)sa[--rk[wv[i]]]=y[i];
    swap(x,y);
    x[sa[0]]=0;
    for(p=i=1; i<len; i++) {
      p+=!cmp(y,sa[i],sa[i-1],j);
      x[sa[i]]=p-1;
    }
  }
}
void find_height(char *s,int *sa,int len) {
  int *h=rmq[0];
  int i,j,k=0;
  for(i=1; i<=len; i++)
    rk[sa[i]] = i;
  for(i=0; i<len; i++) {
    if(k>0)k--;
    j=sa[rk[i]-1];
    while(s[i+k]==s[j+k])k++;
    h[rk[i]]=k;
  }
}
void RMQ(int n) {
  int i,j;
  int rn=(int)floor(log(n*2.0)/log(2.0));
  for(i=1; i<rn; i++)
    for(j=0; j<n+2-(1<<(i-1)); j++)
      rmq[i][j]=min(rmq[i-1][j],rmq[i-1][j+(1<<(i-1))]);
}
int askRMQ(int a,int b) { /// [a,b]闭区间
  int rq=to[b-a];
  return min(rmq[rq][a],rmq[rq][b+1-(1<<rq)]);
}
void PT(char *s,int *sa) {
  int i,sn;
  sn=strlen(s);
  for(i=0; i<sn; i++)
    puts(s+sa[i+1]);
  puts("");
  for(i=0; i<sn; i++)
    printf("rank %d = %d\n",i,rk[i]);
}
int lcp(int a,int b,int len) {
  if(a==b)
    return len-a;
  a=rk[a];
  b=rk[b];
  if(a>b)swap(a,b);
  return askRMQ(a+1,b);
}
void pre_log() {
  int i;
  to[0]=to[1]=0;
  for(i=1; i*2<N; i++)
    to[i*2]=to[i*2+1]=to[i]+1;
}
int main() {
  int T,_=0;
  pre_log();
  while(~scanf("%s",s)) {
    sn=strlen(s);
    da(s,sa,sn+1,128);
    find_height(s,sa,sn);
    RMQ(sn);
    PT(s,sa);
    scanf("%d",&T);
    while(T--) {
      int a,b;
      scanf("%d%d",&a,&b);
      a--,b--;/// 求原串的  a b 开始的后缀的公共前缀
      printf("lcp = %d\n",lcp(a,b,sn));
    }
  }
  return 0;
}