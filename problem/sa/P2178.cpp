//これも運命じゃないか
//跑出来sa之后
//问题就转变为一段连续区间每次分裂区间
//问区间两数乘积最大值
//可以反着做然后并查集之
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define double long double
#define Air
namespace io {
    class In {
        public:
            template<typename T>
            inline In &operator>>(T &x) {
                x=0; bool f=0; char c=getchar();
                while(c<'0'||c>'9') f|=(c=='-'),c=getchar();
                while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
                if(c=='.') {
                    c=getchar(); double dot=0.1;
                    while(c>='0'&&c<='9') x+=(c-'0')*dot,dot*=0.1,c=getchar();
                } return (f?x=-x:x),*this;
            }
            inline In &operator>>(char &x) {while(isspace(x=getchar())); return *this;}
            inline In &operator>>(char *x) {
                char c=getchar(); while(isspace(c)) c=getchar(); while(!isspace(c)&&~c) *(x++)=c,c=getchar();
                return *x=0,*this;
            }
            inline In &operator>>(string &x) {
                char c=getchar(); x.clear();
                while(isspace(c)) c=getchar(); while(!isspace(c)&&~c) x.push_back(c),c=getchar();
                return *this;
            }
            inline In &operator>>(In &in) { return in;}
    };
    class Out {
        private:
            char buf[35]; short dot=6,top=0;
        public:
            template<typename T>
            inline Out &operator<<(T x) {
                if(x<0) putchar('-'),x=-x;
                do { buf[++top]=x%10,x/=10;} while(x);
                while(top) putchar(buf[top--]|'0'); return *this;
            }
            inline Out &operator<<(char c) {return putchar(c),*this;}
            inline Out &operator<<(string x) {for(auto c:x) putchar(c); return *this;}
            inline Out &operator<<(char *x) {while(*x) putchar(*(x++)); return *this;}
            inline Out &operator<<(const char *x) {while(*x) putchar(*(x++)); return *this;}
            inline Out &operator<<(double x) {snprintf(buf,sizeof(buf),"%.*lf",dot,x); return (*this)<<buf;}
            inline Out &operator<<(Out &out) {return out;}
            inline Out &setdot(const int n) {return dot=n,*this;}
    };
    In fin;
    Out fout;
    inline Out &setdot(const int n,Out& out=fout) {return fout.setdot(n),out;}
    inline In &getline(char *x,In& in=fin) {
        char c=getchar();
        while(!(c==' '||!isspace(c))) c=getchar(); while(c==' '||!isspace(c)) (*x++)=c,c=getchar();
        return *x=0,in;
    }
    inline In &getline(string &x,In& in=fin) {
        char c=getchar(); x.clear();
        while(!(c==' '||!isspace(c))) c=getchar(); while(c==' '||!isspace(c)) x.push_back(c),c=getchar();
        return in;
    }
}
using namespace io;
inline int read(){
    int x; fin >> x; return x;
}
int n;
const int N = 2e6 + 10, INF = 1e9;
char ch[N];
int a[N];
int sa[N], rk[N];
int hg[N];
int tmp[N];
int cnt[N];
void get_sa(){
    for(int i = 1; i <= n; i++){
        sa[i] = i;
        rk[i] = ch[i];
        cnt[rk[i]] ++;
    }
    int m = 128;
    for(int i = 1; i <= m; i++){
        cnt[i] += cnt[i - 1];
    }
    for(int i = n; i >= 1; i--){
        sa[cnt[rk[i]]--] = i;
    }
    for(int len = 1;; len <<= 1){
        int now = 0;
        for(int i = n - len + 1; i <= n; i++){
            tmp[++now] = i;
        }
        for(int i = 1; i <= n; i++){
            if(sa[i] > len)
            tmp[++now] = sa[i] - len;
        }
        memset(cnt, 0, sizeof cnt);
        for(int i = 1; i <= n; i++) cnt[rk[i]] ++;
        for(int i = 1; i <= m; i++) cnt[i] += cnt[i - 1]; 
        for(int i = n; i >= 1; i--) sa[cnt[rk[tmp[i]]]--] = tmp[i];
        for(int i = 1; i <= n; i++) tmp[i] = rk[i];
        int tot = 0;
        for(int i = 1; i <= n; i++){
            if(tmp[sa[i]] != tmp[sa[i - 1]] || tmp[sa[i] + len] != tmp[sa[i - 1] + len]){
                tot ++;
            }
            rk[sa[i]] = tot;
        }
        if(tot == n) break;
        m = tot;
    }
}
void get_hg(){
    int now = 0;
    for(int i = 1; i <= n; i++){
        int j = sa[rk[i] - 1];
        if(now) now --;
        while(j + now <= n && i + now <= n ){
            if(ch[j + now] == ch[i + now]) now++;
            else break;
        }
        hg[rk[i]] = now;
    }
}
int fa[N];
int siz[N];
struct Data{
    int x1, x2, y1, y2;//最大次大最小次小 
    friend Data operator + (Data x, Data y){
        Data ans = x;
        if(y.x1 > ans.x1){
            ans.x2 = ans.x1;
            ans.x1 = y.x1;
        }
        else{
            if(y.x1 > ans.x2){
                ans.x2 = y.x1;
            }
        }
        if(y.x2 > ans.x2){
            ans.x2 = y.x2;
        }
        if(y.y1 < ans.y1){
            ans.y2 = ans.y1;
            ans.y1 = y.y1;
        }
        else{
            if(y.y1 < ans.y2){
                ans.y2 = y.y1;
            }
        }
        if(y.y2 < ans.y2){
            ans.y2 = y.y2;
        }
        return ans;
    }
}dat[N];
int get(int x){
    return (fa[x] == x) ? (x) : (fa[x] = get(fa[x]));
}
int ans[N];
int now = -1e18;
int res[N];
int ot = 0;

void merge(int x, int y){
    int fx = get(x), fy = get(y);
    if(fx == fy) return ;
    dat[fx] = dat[fx] + dat[fy];
    fa[fy] = fx;
    ot += siz[fx] * siz[fy];
    siz[fx] += siz[fy];
    now = max(now, dat[fx].x1 * dat[fx].x2);
    now = max(now, dat[fx].y1 * dat[fx].y2);
}
vector<int>e[N];
void get_ans(int p){
    for(auto y: e[p]){
        merge(y - 1, y);
    }
    ans[p] = now;
    res[p] = ot;
}
signed main() {
#ifndef Air
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    n = read();
    fin >> (ch + 1);
    n = strlen(ch + 1);
    for(int i = 1; i <= n; i++){
        a[i] = read();
    }
    get_sa();
    get_hg();
    for(int i = 1; i <= n; i++){
        fa[i] = i;
        siz[i] = 1;
        dat[i] = {a[sa[i]], -INF, a[sa[i]], INF};
    }
    for(int i = 2; i <= n; i++){
        // cerr << hg[i] << ' ';
        e[hg[i]].push_back(i);
    }
    // cerr << '\n';
    for(int i = n; i >= 0; i--){
        get_ans(i);
    }
    for(int i = 0; i <= n - 1; i++){
        if(ans[i] == -1e18) ans[i] = 0;
        cout << res[i] << ' ' << ans[i] << '\n';
    }
    return 0;
}
