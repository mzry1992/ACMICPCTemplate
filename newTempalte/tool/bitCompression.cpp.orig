int bit[5];
inline int getbit26(int sta, int pos) {
    return sta / bit[pos] % bit[1];
}
inline int setbit26(int sta, int pos, int val) {
    return sta / bit[pos + 1] * bit[pos + 1] + val * bit[pos] + sta % bit[pos];
}
//bin
inline int getbit(int sta, int pos) {
    return (sta >> pos) & 1;
}
inline int setbit(int sta, int pos, int val) {
    return ((sta >> (pos + 1)) << (pos + 1)) | (val << pos) | (sta & ((1 << pos) - 1));
}
