//树上倍增求最近公共祖先
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 3e5 + 5;
const int INF = 0x3f3f3f3f;
const ll MOD = 998244353;

struct edge {
    int v,nex;
} ed[MAXN*2];
int head[MAXN],cnt;
void addedge(int u,int v) {
    cnt++;
    ed[cnt].v = v;
    ed[cnt].nex = head[u];
    head[u] = cnt;
}

int anc[MAXN][20],deep[MAXN],t;//anc祖先节点 deep节点深度 t倍增深度
//ll sum[MAXN][55];
queue<int> q;

void bfs() {
    q.push(1);
    deep[1] = 0;
    while(q.size()) {
        int x = q.front();
        q.pop();
        for(int i=head[x]; i; i=ed[i].nex) {
            int y = ed[i].v;
            if(deep[y]||y==1)continue;
            deep[y] = deep[x]+1;
//            ll base = deep[y];
//            for(int i=1;i<=50;i++){
//                sum[y][i] = (sum[x][i]+base)%MOD;
//                base=base*deep[y]%MOD;
//            }
            anc[y][0] = x;
            for(int j=1;j<=t;j++){
                anc[y][j] = anc[anc[y][j-1]][j-1];
            }
            q.push(y);
        }
    }
}

int lca(int x,int y) {
    if(deep[x]<deep[y])swap(x,y);
    for(int i=t; i>=0; i--)  //to same deep;
        if(deep[y]<=deep[anc[x][i]])
            x = anc[x][i];
    if(x==y)return x; //
    for(int i=t; i>=0; i--)
        if(anc[x][i]!=anc[y][i]) {
            x = anc[x][i];
            y = anc[y][i];
        }
    return anc[x][0]; //
}

int main() {
//    IN_LB();
    int n;
    scanf("%d",&n);
    t = (int)(log(n)/log(2))+1;
	//init
	//memset(head,0,sizeof head);
	//cnt = 0;
	//build tree
    for(int i=0; i<n-1; i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    bfs();
	//answer question
    int m;
    scanf("%d",&m);
    for(int i=0; i<m; i++) {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        int la = lca(x,y);
        printf("%lld\n",(sum[x][k]+sum[y][k]-sum[la][k]-sum[anc[la][0]][k]+MOD+MOD)%MOD);
    }
    return 0;
}