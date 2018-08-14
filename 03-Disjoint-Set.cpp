int DisjointSetFa[MAXN];
void DisjointSetInit() {
    for(int i=1; i<=n; i++)//
        DisjointSetFa[i] = i;
}
   
int DisjointSetGet(int x) {
    if(x==DisjointSetFa[x])
        return x;
    return DisjointSetFa[x] = DisjointSetGet(DisjointSetFa[x]);
}
   
void DisjointSetMerge(int x,int y) {
    DisjointSetFa[DisjointSetGet(x)] = DisjointSetGet(y);
}
//多个并查集
void init(int number_p,int *setName){
    for(int i=1;i<=number_p;i++){
        setName[i] = i;
    }
}

int query(int x,int *setName){
    return setName[x]==x?setName[x]:setName[x] = query(setName[x],setName);
}

void combine(int x,int y,int *setName){
    query(x,setName)!=query(y,setName)?setName[query(x,setName)]=query(y,setName):0;
}