#define IN_LB() freopen("C:\\Users\\acm2018\\Desktop\\in.txt","r",stdin)
#define OUT_LB() freopen("C:\\Users\\acm2018\\Desktop\\out.txt","w",stdout)
#define IN_PC() freopen("C:\\Users\\hz\\Desktop\\in.txt","r",stdin)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 200005;

ll fac[maxn],MOD = 1e9+7;

void init() {
    int i;
    fac[0] =1;
    for(i =1; i <= (int)2e5+10; i++) //modify
        fac[i] = fac[i-1]*i % MOD;
}

ll fastpow(ll a, ll b) {
    ll tmp = a % MOD, ans =1;
    while(b) {
        if(b &1)
            ans = ans * tmp % MOD;
        tmp = tmp*tmp % MOD;
        b >>=1;
    }
    return ans;
}

ll comb(ll n, ll m) {
    return  m>n ? 0 : fac[n]*fastpow(fac[m]*fac[n-m], MOD-2) % MOD;
}

ll Lucas(ll n, ll m) {
    return m ? (comb(n%MOD, m%MOD)*Lucas(n/MOD, m/MOD))%MOD : 1;
}

int main() {
//    IN_LB();
    ll n,m;
    cin>>n>>m;
    init();
    cout<<Lucas(n,m)<<endl;
    return 0;
}
