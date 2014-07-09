#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
void e_kmp(char *s,char *t,int *has,int *e_has) {
  int sp,p,mx,tn;
  for(sp=p=mx=0; s[p]>0; p++) {
    if(mx==p||p+e_has[p-sp]>=mx ) {
      for(tn=mx-p; s[mx]==t[tn]; tn++)mx++;
      has[sp=p]=mx-p;
      if(mx==p)sp=++mx;
    } else has[p]=e_has[p-sp];
  }
}
const int V=1001000;
char t[V],s[V];
int e_has[V],has[V],tn;
int main() {
  scanf("%s%s",s,t);
  tn=strlen(t);
  t[tn]=-1;
  e_has[0] = tn;
  e_kmp(t+1,t,e_has+1,e_has);
  e_kmp(s,t,has,e_has);
}