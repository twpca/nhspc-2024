#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define pb push_back

const int N=105;

vector<int> ed[N];
string s[N];
bool vis[N];

void dfs(int u,int &cnt)
{
    vis[u]=1;
    cnt++;
    for(int v:ed[u]) if(!vis[v]) dfs(v,cnt);
}

signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);

    int n;
    cin>>n;
    rep(i,n)
    {
        cin>>s[i];
        reverse(s[i].begin(),s[i].end());
    }

    rep(i,n) rep(j,i)
    {
        int len=max(s[i].size(),s[j].size());
        vector<pair<char,char> > pos;
        rep(k,len)
        {
            char x=(k<s[i].size()?s[i][k]:'0');
            char y=(k<s[j].size()?s[j][k]:'0');
            if(x!=y) pos.pb({x,y});
        }
        if(pos.size()==1||pos.size()>2) continue;
        if(pos.size()==2)
        {
            swap(pos[1].first,pos[1].second);
            if(pos[0]!=pos[1]) continue;
        }
        ed[i].pb(j);
        ed[j].pb(i);
    }

    int tot=0,mx=0;
    rep(i,n) if(!vis[i])
    {
        tot++;
        int cnt=0;
        dfs(i,cnt);
        mx=max(mx,cnt);
    }
    cout<<tot<<" "<<mx<<"\n";
}
