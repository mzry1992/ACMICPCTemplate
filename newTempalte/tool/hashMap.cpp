struct hash_map {
  int head[MOD];
  struct hash_tables {
    int key1, key2;
    long long val;
    int next;
  } ele[ELE];
  int N;
  int getHash(int key1, int key2) {
    return (key1 * 1000000 + key2) % MOD;
  }
  void init() {
    memset(head, -1, sizeof(head));
    N = 0;
  }
  void clear() {
    for (int i = 0; i < N; i++)
      head[getHash(ele[i].key1, ele[i].key2)] = -1;
    N = 0;
  }
  int fint(int key1, int key2) {
    for (int i = head[getHash(key1, key2)]; i != -1; i = ele[i].next) {
      if (ele[i].key1 == key1 && ele[i].key2 == key2)
        return i;
    }
    return -1;
  }
  void insert(int key1, int key2) {
    int tmp = getHash(key1, key2);
    ele[N].key1 = key1;
    ele[N].key2 = key2;
    ele[N].val = 0;
    ele[N].next = head[tmp];
    head[tmp] = N++;
  }
  long long get(int key1, int key2) {
    int tmp = fint(key1, key2);
    if (tmp == -1) {
      insert(key1, key2);
      return ele[N - 1].val;
    } else
      return ele[tmp].val;
  }
  void set(int key1, int key2, long long val) {
    int tmp = fint(key1, key2);
    if (tmp == -1) {
      insert(key1, key2);
      ele[N - 1].val = val;
    } else
      ele[tmp].val = val;
  }
  void add(int key1, int key2, long long val) {
    int tmp = fint(key1, key2);
    if (tmp == -1) {
      insert(key1, key2);
      ele[N - 1].val += val;
    } else
      ele[tmp].val += val;
  }
};
