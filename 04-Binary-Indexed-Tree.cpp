//求和
int lowbit(int x) {
    return x & -x;
}

void add(int pos, int val) {
    for(int i = pos; i <= n; i += lowbit(i)) {
        b[i] += val;
    }
}

int getsum(int pos) {
    int res = 0;
    for(int i = pos; i; i -= lowbit(i)) {
        res += b[i];
    }
    return res;
}
//求逆序数
int judge() {
    memset(b, 0, sizeof b);
    int res = 0;
    for(int i = 0; i < n; i++) {
        int datain;
        scanf("%d", &datain);
        if(!datain)continue;
        res += getsum(n) - getsum(datain);
        add(datain, 1);
    }
    return res;
}