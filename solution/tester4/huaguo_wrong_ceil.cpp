#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define F first
#define S second
#define pb push_back

void solve()
{
    ll n,k;
    cin>>n>>k;
    k%=n;
    ll g=__gcd(n,k);
    vector<ll> a(n);
    ll sum=0;
    rep(i,n)
    {
        cin>>a[i];
        sum+=a[i];
    }
    if(sum%g!=0||k==0)
    {
        cout<<"poor monkeys\n";
        return;
    }
    ll t=max(a.back(),(sum-k*a[0])/(n-k));
    while((n*t-sum)%k!=0) t++;
    ll ans=(n*t-sum)/k;
    cout<<ans<<"\n";
}

signed main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}

