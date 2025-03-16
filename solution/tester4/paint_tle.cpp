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
    int sz=0;
    rep(i,n)
    {
        int c;
        if(s[i]>='A'&&s[i]<='Z') c=s[i]-'A';
        else c=s[i]-'a'+26;
        if(id[c]==-1)
        {
            id[c]=sz;
            sz++;
        }
    }

    vector<int> ord(sz);
    iota(ord.begin(),ord.end(),0);
    ll ans=LLONG_MAX;
    do
    {
        ll tot=0;
        vector<int> cnt(sz,0);
        rep(i,n)
        {
            int x;
            if(s[i]>='A'&&s[i]<='Z') x=s[i]-'A';
            else x=s[i]-'a'+26;
            x=ord[id[x]];

            for(int y=x+1;y<sz;y++) tot+=cnt[y];
            cnt[x]++;
        }
        ans=min(ans,tot);
    } while(next_permutation(ord.begin(),ord.end()));
    cout<<ans<<"\n";
}
