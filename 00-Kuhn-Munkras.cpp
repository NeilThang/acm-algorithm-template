//二分图带权匹配
#define IN_LB() freopen("C:\\Users\\acm2018\\Desktop\\in.txt","r",stdin)
#define OUT_LB() freopen("C:\\Users\\acm2018\\Desktop\\out.txt","w",stdout)
#define IN_PC() freopen("C:\\Users\\hz\\Desktop\\in.txt","r",stdin)
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100;
int weight[maxn][maxn];
int lx[maxn], ly[maxn];
bool vx[maxn], vy[maxn];
int match[maxn];
int n, delta;

bool search_path(int u) {
    vx[u] = true;
    for(int v = 1; v <= n; v++)
        if(!vy[v]) {
            if(lx[u] + ly[v] == weight[u][v]) {
                vy[v] = true;
                if(!match[v] || search_path(match[v])) {
                    match[v] = u;
                    return true;
                }
            } else
                delta = min(delta, lx[u] + ly[v] - weight[u][v]);
        }
    return false;
}

int Kuhn_Munkras(bool max_weight) {
    if(!max_weight)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                weight[i][j] = -weight[i][j];
    for(int i = 1; i <= n; i++) {
        ly[i] = 0;
        lx[i] = -0x7fffffff;
        for(int j = 1; j <= n; j++)
            lx[i] = max(lx[i], weight[i][j]);
    }
    for(int u = 1; u <= n; u++)
        while(true) {
            memset(vx, 0, sizeof vx);
            memset(vy, 0, sizeof vy);
            delta = 0x7fffffff;
            if(search_path(u))
                break;
            for(int i = 1; i <= n; i++) {
                if(vx[i])
                    lx[i] -= delta;
                if(vy[i])
                    ly[i] += delta;
            }
        }
    int ans = 0;
    for(int i = 1; i <= n; i++)
        ans += weight[match[i]][i];
    if(!max_weight)
        ans = -ans;
    return ans;
}

int main() {
    IN_LB();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%d", &weight[i][j]);
    printf("%d\n", Kuhn_Munkras(true));
    return 0;
}
