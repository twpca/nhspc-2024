#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define pb push_back

const int N=105;

string s[N];

signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);

    int n;
    cin>>n;
    int mx=0;
    rep(i,n)
    {
        cin>>s[i];
        mx=max(mx,(int)s[i].size());
    }
    map<vector<int>,int> cnt;
    rep(i,n)
    {
        vector<int> tmp(10,0);
        for(char c:s[i]) tmp[c-'0']++;
        tmp[0]+=mx-s[i].size();
        cnt[tmp]++;
    }
    int ans=0;
    for(auto [_,sz]:cnt) ans=max(ans,sz);

    cout<<cnt.size()<<" "<<ans<<"\n";
}
