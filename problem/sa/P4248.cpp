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
const int N = 1000010;
string ch;
int n;
int sa[N], rk[N];
int tmp[N];
int hg[N];
void get_sa(){
    for(int i = 1; i <= n; i++){
        sa[i] = i;
        rk[i] = ch[i];
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
        if(now) now--;
        while(i + now <= n && j + now <= n && ch[i + now] == ch[j + now]){
            now ++;
        }
        hg[rk[i]] = now;
    }
}
vector<int>e[N];
int sum = 0;
int fa[N];
int siz[N];
int las = 0;
int get(int x){
    return (fa[x] == x) ? (x) : (fa[x] = get(fa[x]));
}
void merge(int x, int y){
    int fx = get(x), fy = get(y);
    if(fx == fy) return ;
    fa[fx] = fy;
    sum += siz[fx] * siz[fy];
    // cerr << siz[fx] * siz[fy] << '\n';
    siz[fy] += siz[fx];
}

signed main() {
#ifndef Air
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> ch;
    n = ch.size();
    ch = ' ' + ch;
    get_sa();
    get_hg();
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans += i * (n - 1);
        // cerr << sa[i] <<  ' ' << rk[i] << '\n';
        fa[i] = i;
        siz[i] = 1;
    }
    // ans *= 2;
    for(int i = 2; i <= n; i++){
        // cerr << hg[i] << '\n';
        e[hg[i]].push_back(i);
    }
    // cerr << '\n';
    for(int i = n; i >= 1; i--){
        las = sum;
        for(auto y: e[i]){
            merge(y, y - 1);
        }
        // cerr << sum - las << ' ' << '\n';
        ans -= (sum - las) * i * 2;
    }
    cout << ans << '\n';

    return 0;
}
