//二分图最大匹配 _增广路算法
#define IN_LB() freopen("C:\\Users\\acm2018\\Desktop\\in.txt","r",stdin)
#define OUT_LB() freopen("C:\\Users\\acm2018\\Desktop\\out.txt","w",stdout)
#define IN_PC() freopen("C:\\Users\\hz\\Desktop\\in.txt","r",stdin)
#include <bits/stdc++.h>
using namespace std;

const int maxn = 505;

struct edge {
    int v,w,nex;
} ed[maxn*maxn];

int head[maxn],cnt,n,vis[maxn],match[maxn];

void addedge(int u,int v,int w) {
    cnt++;
    ed[cnt].v = v;
    ed[cnt].w = w;
    ed[cnt].nex = head[u];
    head[u] = cnt;
}

bool dfs(int u) {
    for(int i=head[u]; i; i=ed[i].nex) {
        int v = ed[i].v;
        if(!vis[v]) {
            vis[v] = 1;
            if(!match[v]||dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int figure_maximun_match() {
    memset(match,0,sizeof match);
    int cnt = 0;
    for(int i=1; i<=n; i++) {
        memset(vis,0,sizeof vis);
        if(dfs(i))
            cnt++;
    }
    return cnt;
}

int main() {
//    IN_LB();
    scanf("%d",&n);
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            int weight;
            scanf("%d",&weight);
            addedge(i,j,weight);
        }
    }
    printf("%d\n",figure_maximun_match());
    return 0;
}
