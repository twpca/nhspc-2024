#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define F first
#define S second
#define pb push_back

const int C=2e7+5;
const int MOD=1e9+7;

ll fac[C],in[C];
ll fpow(ll a,ll b)
{
    ll ans=1;
    for(ll cur=a;b>0;b>>=1,cur=cur*cur%MOD) if(b%2==1) ans=ans*cur%MOD;
    return ans;
}
ll inv(ll a){return fpow(a,MOD-2);}


signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);

    fac[0]=1;
    rep1(i,C-1) fac[i]=fac[i-1]*i%MOD;
    in[C-1]=inv(fac[C-1]);
    for(int i=C-1;i>=1;i--) in[i-1]=in[i]*i%MOD;

    int n,X;
    cin>>n>>X;
    ll ans=fac[X];
    rep1(i,n)
    {
        int a;
        cin>>a;
        ans=ans*fac[a+X]%MOD*in[X]%MOD;
    }
    cout<<ans<<"\n";
}
