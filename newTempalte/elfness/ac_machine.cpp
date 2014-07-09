#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
struct tree {
  tree *ne[26],*fail;
  int ct;
} tr[500100],VD,*root,*Q[500100];
int tn;
void init() {
  tr[tn=0]=VD;
  root=tr+(tn++);
}
char s[1000100];
void build() {
  tree *p=root;
  for(int i=0; s[i]; i++) {
    if(p->ne[s[i]-'a']==NULL) {
      tr[tn]=VD;
      p->ne[s[i]-'a']=tr+(tn++);
    }
    p=p->ne[s[i]-'a'];
  }
  p->ct++;
}
void pre() {
  int i,top,tail;
  tree *p,*q;
  top=0;
  tail=0;
  for(i=0; i<26; i++)
    if(root->ne[i]!=NULL) {
      Q[++tail]=root->ne[i];
      root->ne[i]->fail=root;
    } else root->ne[i]=root;
  while(top<tail) {
    p=Q[++top];
    for(i=0; i<26; i++)
      if(p->ne[i]!=NULL) {
        q=p->ne[i];
        Q[++tail]=q;
        q->fail=p->fail->ne[i];
        if(q->fail==NULL)q->fail=root;
      } else p->ne[i]=p->fail->ne[i];
  }
}
int doit() {
  int ret=0;
  tree *p=root,*q;
  for(int i=0; s[i]; i++) {
    p=p->ne[s[i]-'a'];
    q=p;
    while(root!=q&&q->ct!=-1) {
      ret+=q->ct;
      q->ct=-1;
      q=q->fail;
    }
  }
  return ret;
}
int i,n,_;
int main() {
  for(i=0; i<26; i++)VD.ne[i]=NULL;
  VD.ct=0;
  scanf("%d",&_);
  while(_--) {
    scanf("%d",&n);
    init();
    for(i=0; i<n; i++) {
      scanf("%s",s);
      build();
    }
    pre();
    scanf("%s",s);
    printf("%d\n",doit());
  }
}