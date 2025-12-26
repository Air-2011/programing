//これも運命じゃないか
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define uint unsigned long long
#define double long double
#define Air
namespace io{
    inline int read(){
        int f = 1, t = 0; char ch = getchar();
        while(ch < '0' || ch > '9'){if(ch == '-') f = -f; ch = getchar();}
        while(ch >= '0' && ch <= '9'){t = t * 10 + ch - '0'; ch = getchar();}
        return t * f;
    }
    inline void write(int x){
        if(x < 0){putchar('-'); x = -x;}
        if(x >= 10){write(x / 10);}
        putchar(x % 10 + '0');
    }
}
using namespace io;
const int N = 2e6 + 10;
int n;
string s;
struct Data{
    int son[26], fa;
    int len;
}sam[N];
int tot = 1;
int lst = 1;
ll dp[N];
void add(int c){
    int p = lst;
    int np = ++tot;
    lst = tot;
    dp[np] = 1;
    sam[np].len = sam[p].len + 1;
    for(; p && !sam[p].son[c]; p = sam[p].fa){
        sam[p].son[c] = np;
    } 
    if(!p){
        sam[np].fa = 1;
        return ;
    }
    else{
        int t = sam[p].son[c];
        if(sam[p].len + 1 == sam[t].len){
            sam[np].fa = t;
        }
        else{
            int nt = ++tot;
            sam[nt] = sam[t];
            sam[nt].len = sam[p].len + 1;
            sam[t].fa = sam[np].fa = nt;
            for(; p && sam[p].son[c] == t; p = sam[p].fa) {
                sam[p].son[c] = nt;
            }
        }
    }
}
vector<int>e[N];
ll ans;
void dfs(int now){
    for(auto y: e[now]){
        dfs(y);
        dp[now] += dp[y];
    }
    // cerr << now << ' '<< sam[now].len << '\n';
    if(dp[now] > 1){
        ans = max(ans, dp[now] * sam[now].len);
    }
}
signed main() {
#ifndef Air
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> s;
    s = ' ' + s;
    n = s.size() - 1;
    for(int i = 1; i <= n; i++){
        add(s[i] - 'a');
    }
    for(int i = 2; i <= tot; i++){
        e[sam[i].fa].push_back(i);
    }
    dfs(1);
    cout << ans << '\n';
    return 0;
}
