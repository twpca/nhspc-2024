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
    string t=s;
    sort(t.begin(),t.end());
    ll ans=LLONG_MAX;
    rep(_,2)
    {
        ll tot=0;
        rep(i,n)
        {
            if(t[i]!=t[0]) break;
            tot-=i;
        }
        rep(i,n) if(s[i]==t[0]) tot+=i;
        ans=min(ans,tot);
        reverse(t.begin(),t.end());
    }
    cout<<ans<<"\n";
}
