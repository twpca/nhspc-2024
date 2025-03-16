#include<bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0)
#define mkp make_pair
#define pb push_back
#define int long long
#define ll long long

using namespace std;

int K = 0;
map<char, int> c2i;
vector<char> i2c;
vector<int> arr;
vector<vector<int>> mat;

vector<int> status;

int solve(int level){
    if(level == K){
        return 0;
    }
    int Min = LLONG_MAX;
    for(int i = 0; i < K; i++){
        if(!status[i]){
            status[i] = 1;
            int tmp = solve(level+1);
            for(int j = 0; j < K; j++){
                if(!status[j]){
                    tmp += mat[i][j];
                }
            }
            Min = min(Min, tmp);
            status[i] = 0;
        }
    }
    return Min;
}

signed main(){
    fast_io;
    string input;
    cin >> input;


    for(char c: input){
        if(c2i.find(c) == c2i.end()){
            c2i.insert(mkp(c, K++));
            i2c.pb(c);
        }
    }
    
    arr.resize(K, 0);
    mat.resize(K, vector<int>(K, 0));
    
    for(char c: input){
        int index = c2i[c];
        arr[index]++;
        for(int i = 0; i < K; i++){
            mat[index][i] += arr[i];
        }
    }

    status.resize(K, 0);

    int ans = solve(0);
    cout << ans << endl;
    
    return 0;
}
