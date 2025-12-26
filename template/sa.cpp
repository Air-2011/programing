//これも運命じゃないか
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
const int N = 2e6 + 10;
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
    for(int i = 2; i <= n; i++){
        int j = sa[rk[i] - 1];
        if(now) now --;
        while(j + now <= n && i + now <= n && ch[j + now] == ch[i + now]){
            now++;
        }
        hg[rk[i]] = now;
    }
}
signed main() {
#ifndef Air
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    // n = read();
    fin >> (ch + 1);
    n = strlen(ch + 1);
    // for(int i = 1; i <= n; i++){
        // a[i] = read();
    // }
    get_sa();
    for(int i = 1; i <= n; i++){
        cout << sa[i] << ' ';
    }
    get_hg();

    return 0;
}
