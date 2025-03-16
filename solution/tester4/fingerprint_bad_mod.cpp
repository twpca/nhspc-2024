#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define F first
#define S second
#define pb push_back

const int N=1e6+5;
const int MOD=1e9+7;

vector<int> ed[N];
ll cnt[N],tot[N],tot2[N];
ll ans=0;

void dfs(int u,int p)
{
    ll sum2=0;
    for(int v:ed[u]) if(v!=p)
    {
        dfs(v,u);
        cnt[u]+=cnt[v];
        ll tmp1=(tot[v]+cnt[v]);
        tot[u]+=tmp1;
        ll tmp2=(tot2[v]+tot[v]*2+cnt[v]);
        tot2[u]+=tmp2;

        sum2+=tmp1*tmp1;

        ans+=tmp2*(-cnt[v]);
        ans%=MOD;

        cnt[u]%=MOD;
        tot[u]%=MOD;
        tot2[u]%=MOD;
    }
    if(cnt[u]==0)
    {
        cnt[u]=1;
        tot[u]=0;
        tot2[u]=0;
    }
    else
    {
        ans+=tot2[u]*cnt[u]%MOD;
        ans%=MOD;

        ans+=(tot[u]*tot[u]%MOD-sum2)%MOD;
        ans%=MOD;
    }
}

signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);

    int n;
    cin>>n;
    rep(i,n-1)
    {
        int u,v;
        cin>>u>>v;
        ed[u].pb(v);
        ed[v].pb(u);
    }
    if(n==2)
    {
        cout<<"1\n";
        return 0;
    }
    int r=1;
    while(ed[r].size()==1) r++;
    dfs(r,0);
    cout<<ans<<"\n";
}
