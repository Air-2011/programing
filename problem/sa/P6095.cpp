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
int n, m;
const int N = 8e5 + 10;
char ch[N];
int sa[N], rk[N];
int tmp[N];
int t;
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
bool check(int mid){
    for(int i = 1; i <= t; i++){
        int now = i;
        int sum = 0;
        for(int j = 1; j <= m; j++){
            if(rk[now] <= mid){
                sum += t;
            }
            else{
                sum += t - 1;
            }
            now = (i + sum - 1) % (n / 2) + 1;
        }
        // cerr << sum << ' ' << now << '\n';
        if(sum >= n / 2) return 1; 
    }
    return 0;
}
signed main() {
#ifndef Air
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    n = read();
    m = read();
    t = (n - 1) / m + 1;
    fin >> (ch + 1);
    for(int i = 1; i <= n; i++){
        ch[i + n] = ch[i];
    }
    n *= 2;
    get_sa();
    int l = 1, r = n;
    // for(int i = l; i <= r; i++){
    //     cerr << sa[i] << '\n';
    // }
    while(l + 1 < r){
        int mid = (l + r) >> 1;
        if(check(mid)){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    for(int i = l; i <= r; i++){
        if(check(i)){
            for(int j = 1; j <= t; j++){
                cout << ch[sa[i] + j - 1];
            }
            return 0;
        }
    }
    return 0;
}
