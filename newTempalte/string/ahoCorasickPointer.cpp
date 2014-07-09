const int CHAR=26;
const int TOTLEN=500000;
const int MAXLEN=1000000;
struct Vertex {
  Vertex *fail,*next[CHAR];
  Vertex() {}
  Vertex(bool flag) { //为什么要这样写？
    fail=0;
    memset(next,0,sizeof(next));
  }
};
int size;
Vertex vertex[TOTLEN+1];
void init() {
  vertex[0]=Vertex(0);
  size=1;
}
void add(Vertex *pos,int cha) {
  vertex[size]=Vertex(0);
  pos->next[cha]=&vertex[size++];
}
void add(vector<int> s) {
  int l=s.size();
  Vertex *pos=&vertex[0];
  for (int i=0; i<l; i++) {
    if (pos->next[s[i]]==NULL)
      add(pos,s[i]);
    pos=pos->next[s[i]];
  }
}
void bfs() {
  queue<Vertex *> que;
  Vertex *u=&vertex[0];
  for (int i=0; i<CHAR; i++)
    if (u->next[i]!=NULL) {
      que.push(u->next[i]);
      u->next[i]->fail=u;
    } else
      u->next[i]=u;
  u->fail=NULL;
  while (!que.empty()) {
    u=que.front();
    que.pop();
    for (int i=0; i<CHAR; i++)
      if (u->next[i]!=NULL) {
        que.push(u->next[i]);
        u->next[i]->fail=u->fail->next[i];
      } else
        u->next[i]=u->fail->next[i];
  }
}

