#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define pb push_back

signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    
    string s;
    cin>>s;
    int n=s.size();
    vector<int> id(52,-1);
    vector<vector<int> > pos;
    int sz=0;
    rep(i,n)
    {
        int c;
        if(s[i]>='A'&&s[i]<='Z') c=s[i]-'A';
        else c=s[i]-'a'+26;
        if(id[c]==-1)
        {
            id[c]=sz;
            pos.pb({});
            sz++;
        }
        pos[id[c]].pb(i);
    }
    
    vector<vector<ll> > dist(sz,vector<ll>(sz,0));
    rep(i,sz) rep(j,sz) if(i!=j)
    {
        int cur=0;
        for(int x:pos[j])
        {
            while(cur<pos[i].size()&&pos[i][cur]<=x) cur++;
            dist[i][j]+=cur;
        }
    }

    vector<int> ord(sz);
    iota(ord.begin(),ord.end(),0);
    ll ans=LLONG_MAX;
    do
    {
        ll tot=0;
        rep(i,sz) rep(j,i)
        {
            tot+=dist[ord[j]][ord[i]];
        }
        ans=min(ans,tot);
    } while(next_permutation(ord.begin(),ord.end()));
    cout<<ans<<"\n";
}
