//Self match
int j;
p [0] = j = -1;
for ( int i = 1; i < lb; i++) {
  while (j >= 0 && b[j + 1] != b[i]) j = p[j];
  if (b[j + 1] == b[i]) j ++;
  p[i] = j;
}
//Match
j = -1;
for ( int i = 0; i < la; i++) {
  while (j >= 0 && b[j + 1] != a[i]) j = p[j];
  if (b[j + 1] == a[i]) j ++;
  KMP[i] = j + 1;
}
