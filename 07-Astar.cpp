//第k短路
//题意：给一个有向图，询问s到e第k短路是否大于t
#define IN_PC() freopen("C:\\Users\\hz\\Desktop\\in.txt","r",stdin)
#define IN_LB() freopen("C:\\Users\\acm2018\\Desktop\\in.txt","r",stdin)
#define OUT_PC() freopen("C:\\Users\\hz\\Desktop\\out.txt","w",stdout)
#define OUT_LB() freopen("C:\\Users\\acm2018\\Desktop\\out.txt","w",stdout)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e3 + 5;
const int MAXE = 1e4 + 5;
const int INF = 0x3f3f3f3f;

struct Graph {
    struct edge {
        int v,w,nex;
    } ed[MAXE];
    int tot,head[MAXN];
    void addedge(int u,int v,int w) {
        tot++;
        ed[tot].v = v;
        ed[tot].w = w;
        ed[tot].nex = head[u];
        head[u] = tot;
    }
    void init() {
        tot = 0;
        memset(head,0,sizeof head);
    }
} G1,G2;

struct node {
    int ind,dis;
};
bool operator <(node a,node b) {
    return a.dis>b.dis;
}
int d[MAXN];
bool vis[MAXN];
priority_queue<node> q;
void dijkstra(int st,Graph G) {
    memset(d,0x3f,sizeof d);
    memset(vis,0,sizeof vis);
    d[st] = 0;
    q.push({st,0});
    while(q.size()) {
        int u = q.top().ind;
        q.pop();
        if(vis[u])
            continue;
        vis[u] = 1;
        for(int i = G.head[u]; i; i=G.ed[i].nex) {
            int v = G.ed[i].v,w = G.ed[i].w;
            if(d[v]>d[u]+w) {
                d[v] = d[u]+w;
                q.push({v,d[v]});
            }
        }
    }
}

struct anode {
    int to;
    int f,g;
    bool operator < (const anode &t) const {
        if(t.f==f)
            return t.g < g;
        return t.f < f;
    }
};
int Astar(int st,int et,int k) {
    int cnt = 0;
    priority_queue<anode> pq;
    if(st==et)
        k++;
    if(d[st] == INF)
        return -1;
    pq.push({st,d[st],0});
    while(pq.size()){
        anode u = pq.top();
        if(u.g>100000000)return -1;
        pq.pop();
        if(u.to==et)cnt++;
        if(cnt==k)return u.g;
        for(int i = G1.head[u.to];i;i=G1.ed[i].nex){
            anode v;
            v.to = G1.ed[i].v;
            v.g = u.g + G1.ed[i].w;
            v.f = v.g + d[v.to];
            pq.push(v);
        }
    }
    return -1;
}

int main() {
//    IN_LB();
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF) {
        int st,et,k,t;
        scanf("%d%d%d%d",&st,&et,&k,&t);
        G1.init();
        G2.init();
        for(int i=0; i<m; i++) {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            G1.addedge(u,v,w);
            G2.addedge(v,u,w);
        }
        dijkstra(et,G2);//在反图上跑Dijkstra
        int ans = Astar(st,et,k);//在正图上跑Astar
        if(ans!=-1&&ans<=t)printf("yareyaredawa\n");
        else printf("Whitesnake!\n");
    }
    return 0;
}