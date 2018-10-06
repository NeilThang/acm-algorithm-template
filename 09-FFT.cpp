//FFT
//多项式乘法
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn=100050;
const ll MOD=998244353;
const double Pi=acos(-1);
struct Complex
{
    double x,y;
    Complex(double x=0,double y=0):x(x),y(y){}
    Complex operator +(const Complex&t)const
    {
        return Complex(x+t.x,y+t.y);
    }
    Complex operator -(const Complex&t)const
    {
        return Complex(x-t.x,y-t.y);
    }
    Complex operator *(const Complex&t)const
    {
        return Complex(x*t.x-y*t.y,x*t.y+y*t.x);
    }
    Complex &operator /=(const double&t)
    {
        x/=t,y/=t;
        return *this;
    }

}a[1<<22],b[1<<22],t[1<<22];
void rev(Complex *a,int n)
{
    for(int i = 0; i < n; ++i)
    {
        int base=(n>>1),idx=0;
        for(int j = 0; base; ++j)
        {
            if(i&(1<<j)) idx+=base;
            base>>=1;
        }
        t[idx]=a[i];
    }
    for(int i = 0; i < n; ++i) a[i]=t[i];
}
void fft(Complex *a,int n,int op)
{
    rev(a,n);
    Complex wn;
    for(int i = 2; i <= n; i<<=1)
    {
        double phi=Pi*2/i*op;
        wn=Complex(cos(phi),sin(phi));
        for(int j = 0; j < n; j+=i)
        {
            Complex w(1,0);
            for(int k = j; k < j+(i>>1); ++k)
            {
                Complex u=a[k],v=a[k+(i>>1)];
                a[k]=u+w*v;
                a[k+(i>>1)]=u-w*v;
                w=w*wn;
            }
        }
    }
    if(op==-1)
    {
        for(int i = 0; i < n; ++i) a[i]/=n;
    }
}
int main()
{
    int n,m;
    scanf("%d%d", &n,&m);
    for(int i = 0; i <= n; ++i) scanf("%lf",&a[i].x);
    for(int i = 0; i <= m; ++i) scanf("%lf",&b[i].x);
    int N=1;
    while(N<n+m+1) N<<=1;
    fft(a,N,1);

    fft(b,N,1);
    for(int i = 0; i < N; ++i) a[i]=a[i]*b[i];
    fft(a,N,-1);
    for(int i = 0; i <= n+m; ++i)
    {
        int x=int(a[i].x+0.5);
        printf("%d%s", x,i==n+m?"\n":" ");
    }
    return 0;
}
//例题 Rock Paper Scissors
//给两个仅由RPS构成的字符串，长短不一，问你把短串从长串某个位置开始一一匹配字符，最多可以匹配多少位。
//可以对每一种字符单独计算答案，把字符匹配的过程看做卷积和，则当前要匹配的字符对应1，否则为0，把其中一个串反转，就只要算这两个01数列的卷积和即可。利用FFT算出每种字符匹配对答案的贡献，最后相加取最大值即可。
#include<bits/stdc++.h>
#define CLR(a,b) memset((a),(b),sizeof((a)))
using namespace std;
typedef long long ll;
const int N = 1<<20;
const double PI = acos(-1.0);
int n, m;
struct Complex {
    double x,y;
    Complex(double _x = 0.0,double _y = 0.0){
        x = _x; y = _y;
    }
    Complex operator -(const Complex &b)const{
        return Complex(x-b.x,y-b.y);
    }
    Complex operator +(const Complex &b)const{
        return Complex(x+b.x,y+b.y);
    }
    Complex operator *(const Complex &b)const{
        return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
    }
    Complex operator * (const double &b)const{
        return Complex(x * b,y * b);
    }
    Complex operator / (const double &b)const{
        return Complex(x / b,y / b);
    }
};
void change(Complex y[], int len) {
    int i, j, k;
    for(i = 1, j = len/2;i <len-1;i++) {
        if(i < j)swap(y[i],y[j]);
        k = len/2;
        while(j >= k) {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}
void fft(Complex y[],int len,int on) {
    change(y,len);
    for(int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0;j < len;j+=h) {
            Complex w(1,0);
            for(int k = j;k < j+h/2;k++) {
                Complex u = y[k];
                Complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++)
            y[i].x /= len;
}
Complex a[N], b[N], c[N];
char s[N], t[N];
int sum[N];
int main() {
    int i, ans = 0, ma, nn;
    scanf("%d%d%s%s", &n,&m,s, t);
    reverse(t, t+m);
    ma = max(n, m);  nn = 1;
    while(nn < 2 * ma) nn<<=1;
    CLR(c, 0); CLR(sum, 0);
    //R vs S
    CLR(a, 0); CLR(b, 0);
    for(i = 0; i < n; ++i) a[i].x = (s[i]=='S');
    for(i = 0; i < m; ++i) b[i].x = (t[i]=='R');
    fft(a, nn, 1); fft(b, nn, 1);
    for(i = 0; i < nn ;++i) c[i] = a[i] * b[i];
    fft(c, nn, -1);
    for(i = m-1; i < n+m-1; ++i)
        sum[i] += (int)(c[i].x+0.5);
    //P vs R
    CLR(a, 0); CLR(b, 0);
    for(i = 0; i < n; ++i) a[i].x = (s[i]=='R');
    for(i = 0; i < m; ++i) b[i].x = (t[i]=='P');
    fft(a, nn, 1); fft(b, nn, 1);
    for(i = 0; i < nn ;++i) c[i] = a[i] * b[i];
    fft(c, nn, -1);
    for(i = m-1; i < n+m-1; ++i)
        sum[i] += (int)(c[i].x+0.5);
    //S vs P
    CLR(a, 0); CLR(b, 0);
    for(i = 0; i < n; ++i) a[i].x = (s[i]=='P');
    for(i = 0; i < m; ++i) b[i].x = (t[i]=='S');
    fft(a, nn, 1); fft(b, nn, 1);
    for(i = 0; i < nn ;++i) c[i] = a[i] * b[i];
    fft(c, nn, -1);
    for(i = m-1; i < n+m-1; ++i)
        sum[i] += (int)(c[i].x+0.5);
 
    for(i = m-1; i < n+m-1; ++i) ans = max(ans, sum[i]);
    printf("%d\n", ans);
    return 0;
}