using namespace std;
#define inf 100000000
bool visit[502],com[502];
int map[502][502],W[502],s,t;
int maxadj(int N,int V) {
  int CUT;
  memset(visit,0,sizeof(visit));
  memset(W,0,sizeof(W));
  for(int i=0; i<N; i++) {
    int Num=0,Max=-inf;
    for(int j=0; j<V; j++)
      if(!com[j]&&!visit[j]&&W[j]>Max) {
        Max=W[j];
        Num=j;
      }
    visit[Num]=true;
    s=t;
    t=Num;
    CUT=W[t];
    for(int j=0; j<V; j++)
      if(!com[j]&&!visit[j])W[j]+=map[Num][j];
  }
  return CUT;
}
int stoer(int V) {
  int Mincut=inf;
  int N=V;
  memset(com,0,sizeof(com));
  for(int i=0; i<V-1; i++) {
    int Cut;
    s=0,t=0;
    Cut=maxadj(N,V);
    N--;
    if(Cut<Mincut)Mincut=Cut;
    com[t]=true;
    for(int j=0; j<V; j++)
      if(!com[j]) {
        map[j][s]+=map[j][t];
        map[s][j]+=map[t][j];
      }
  }
  return Mincut;
}