#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main(){
    int m;
    cin >> m;
    vector<int> st(m);
    vector<int> ed(m);

    for(int i = 0; i < m; i++){
        cin >> st[i];
    }
    for(int i = 0; i < m; i++){
        cin >> ed[i];
    }

    sort(st.begin(), st.end());
    sort(ed.begin(), ed.end());

    int ans = 0;

    for(int i = 0; i < m; i++){
        ans += abs(ed[i] - st[i]);
    }

    cout << ans << endl;
    return 0;
}
