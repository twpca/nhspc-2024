#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;
using namespace std;

int main(){
    int m;
    cin >> m;
    vector<ll> st(m);
    vector<ll> ed(m);

    for(int i = 0; i < m; i++){
        cin >> st[i];
    }
    for(int i = 0; i < m; i++){
        cin >> ed[i];
    }

    sort(st.begin(), st.end());
    sort(ed.begin(), ed.end());

    ll ans = 0;

    for(int i = 0; i < m; i++){
        ans += abs(ed[i] - st[i]);
    }

    cout << ans << "\n";
}
