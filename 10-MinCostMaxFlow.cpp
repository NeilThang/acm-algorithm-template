#define IN_PC() freopen("C:\\Users\\hz\\Desktop\\in.txt","r",stdin)
#define IN_TEST() freopen("","r",stdin)
#define IN_LB() freopen("C:\\Users\\acm2018\\Desktop\\in.txt","r",stdin)
#define OUT_PC() freopen("C:\\Users\\hz\\Desktop\\out.txt","w",stdout)
#define OUT_LB() freopen("C:\\Users\\acm2018\\Desktop\\out.txt","w",stdout)
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000;//modify
const int MAXM = 10000;//modify
const int INF = 0x3f3f3f3f;

struct Edge{
    int to,nex,cap,flow,cost;
}edge[MAXM];

int head[MAXN],tol;
int pre[MAXN],dis[MAXN];

bool vis[MAXN];
int N;//the number of all nodes and (index: 0~N-1)

void init(int n){
    N = n;
    tol = 0;
    memset(head,-1,sizeof head);
}

void addedge(int u,int v,int cap,int cost){
    edge[tol].to = v;
    edge[tol].cap = cap;
    edge[tol].cost = cost;
    edge[tol].flow = 0;
    edge[tol].nex = head[u];
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = 0;
    edge[tol].cost = -cost;
    edge[tol].flow = 0;
    edge[tol].nex = head[v];
    head[v] = tol++;
}

bool spfa(int s,int t){
    queue<int> q;
    for(int i=0;i<N;i++){
        dis[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = 1;
    q.push(s);
    while(q.size()){
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for(int i=head[u];i!=-1;i=edge[i].nex){
            int v = edge[i].to;
            if(edge[i].cap>edge[i].flow&&dis[v]>dis[u]+edge[i].cost){
                dis[v] = dis[u]+edge[i].cost;
                pre[v] = i;
                if(!vis[v]){
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t]==-1)return false;
    else return true;
}
//return MaxFlow,cost:minCost
int minCostMaxFlow(int s,int t,int &cost){
    int flow = 0;
    cost = 0;
    while(spfa(s,t)){
        int Min = INF;
        for(int i = pre[t];i!=-1;i=pre[edge[i^1].to]){
            if(Min>edge[i].cap-edge[i].flow){
                Min = edge[i].cap - edge[i].flow;
            }
        }
        for(int i = pre[t];i!=-1;i=pre[edge[i^1].to]){
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost*Min;
        }
        flow += Min;
    }
    return flow;
}

int main() {
//    IN_PC();
    int T;
    for(scanf("%d",&T);T;T--){
        int n,m,k;
        scanf("%d%d%d",&n,&m,&k);
        init(n+m+2);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int cost;
                scanf("%d",&cost);
                addedge(i,n+j,1,-cost);
            }
        }
        int s = n+m,t = n+m+1;
        for(int i=0;i<n;i++){
            addedge(s,i,1,0);
        }
        for(int i=0;i<m;i++){
            addedge(i+n,t,k,0);
        }
        int ans = 0;
        minCostMaxFlow(s,t,ans);
        printf("%d\n",-ans);
    }
    return 0;
}
