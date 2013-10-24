struct SplayTree {
  void Pushup(Node *x) {
    if (x == nil)   return;
    Pushdown(x);
    Pushdown(x->c[0]);
    Pushdown(x->c[1]);
    x->size = x->c[0]->size + x->c[1]->size + 1;
  }
  void Pushdown(Node *x) {
    if (x == nil)   return;
    if (x->rev) {
      x->rev = 0;
      x->c[0]->rev ^= 1;
      x->c[1]->rev ^= 1;
      swap(x->c[0], x->c[1]);
    }
  }
  bool isRoot(Node *x) {
    return (x == nil) || (x->p->c[0] != x && x->p->c[1] != x);
  }
  void Rotate(Node *x, int f) {
    if (isRoot(x))   return;
    Node *y = x->p;
    y->c[f ^ 1] = x->c[f], x->p = y->p;
    if (x->c[f] != nil)
      x->c[f]->p = y;
    if (y != nil) {
      if (y == y->p->c[1])
        y->p->c[1] = x;
      else if (y == y->p->c[0])
        y->p->c[0] = x;
    }
    x->c[f] = y, y->p = x;
    Pushup(y);
  }
  void Splay(Node *x) {
    static Node *stack[MaxN];
    int top = 0;
    stack[top++] = x;
    for (Node *y = x; !isRoot(y); y = y->p)
      stack[top++] = y->p;
    while (top)
      Pushdown(stack[--top]);
    while (!isRoot(x)) {
      Node *y = x->p;
      if (isRoot(y))
        Rotate(x, x == y->c[0]);
      else {
        int fd = y->p->c[0] == y;
        if (y->c[fd] == x)
          Rotate(x, fd ^ 1), Rotate(x, fd);
        else
          Rotate(y, fd), Rotate(x, fd);
      }
    }
    Pushup(x);
  }
  Node *Access(Node *u) {
    Node *v = nil;
    while (u != nil) {
      Splay(u);
      v->p = u;
      u->c[1] = v;
      Pushup(u);
      u = (v = u)->p;
      if (u == nil)
        return v;
    }
  }
  Node *LCA(Node *u, Node *v) {
    Access(u);
    return Access(v);
  }
  Node *Link(Node *u, Node *v) {
    Access(u);
    Splay(u);
    u->rev = true;
    u->p = v;
  }
  void ChangeRoot(Node *u) {
    Access(u)->rev ^= 1;
  }
  Node *GetRoute(Node *u, Node *v) {
    ChangeRoot(u);
    return Access(v);
  }
};
