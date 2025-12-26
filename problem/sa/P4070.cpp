//これも運命じゃないか
#include<bits/stdc++.h>
using namespace std;
#define int long long
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
int n;
const int N = 2e5 + 10;
int sa[N], rk[N];
int hg[N];
int tmp[N];
int a[N];
void get_sa(){
    for(int i = 1; i <= n; i++){
        sa[i] = i;
        rk[i] = a[i];
    }
    for(int len = 1; len <= n; len <<= 1){
        sort(sa + 1, sa + 1 + n, [&](int x, int y){
            return (rk[x] != rk[y]) ? (rk[x] < rk[y]) : (rk[x + len] < rk[y + len]);
        });
        for(int i = 1; i <= n; i++){
            tmp[i] = rk[i];
        }
        int tot = 0;
        for(int i = 1; i <= n; i++){
            if(tmp[sa[i]] != tmp[sa[i - 1]] || tmp[sa[i] + len] != tmp[sa[i - 1] + len]){
                tot ++;
            }
            rk[sa[i]] = tot;
        }
    }
}
void get_hg(){
    int now = 0;
    for(int i = 1; i <= n; i++){
        int j = sa[rk[i] - 1];
        if(now) now --;
        while(i + now <= n && j + now <= n && a[i + now] == a[j + now]){
            now ++;
        }
        hg[rk[i]] = now;
    }
}
int st[N][30];
int pre[N];
void prework(){
    pre[0] = pre[1] = 0;
    for(int i = 2; i <= n; i++){
        pre[i] = pre[i / 2] + 1;
    }
}
int ask(int l, int r){
    int step = pre[r - l + 1];
    return min(st[l][step], st[r - (1ll << step) + 1][step]);
}
set<int>se;
signed main() {
#ifndef Air
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    n = read();
    for(int i = 1; i <= n; i++){
        a[n - i + 1] = read();
    }
    prework();
    get_sa();
    get_hg();
    for(int i = 1; i <= n; i++){
        st[i][0] = hg[i];
    }
    for(int j = 1; j <= 20; j++){
        for(int i = 1; i + (1ll << j) - 1 <= n; i++){
            st[i][j] = min(st[i][j - 1], st[i + (1ll << (j - 1))][j - 1]);
        }
    }
    int tp = 0;
    for(int i = n; i >= 1; i--){
        int nrk = rk[i];
        auto nt = se.lower_bound(nrk);
        int l = 0, r = 0;
        if(se.size() && (*se.rbegin()) > nrk){
            r = (*nt);
        }
        if(se.size() && nt != se.begin()){
            nt --;
            l = (*nt);
        }
        if(l && r){
            tp -= ask(l + 1, r);
        }
        if(l){
            tp += ask(l + 1, nrk);
        }
        if(r){
            tp += ask(nrk + 1, r);
        }
        int id = (n - i +  1);
        se.insert(nrk);
        cout << id * (id + 1) / 2 - tp << '\n';
    }
    return 0;
}
