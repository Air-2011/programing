//これも運命じゃないか
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define double long double
#define Air
namespace io{
    inline int read(){
        int x; cin >> x; return x;
    }
    inline void write(int x){
        if(x < 0){putchar('-'); x = -x;}
        if(x >= 10){write(x / 10);}
        putchar(x % 10 + '0');
    }
}
using namespace io;
string ch;
int n, m;
const int N = 2e5 + 10;
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
        if(now) now --;
        while(i + now <= n && j + now <= n && ch[i + now] == ch[j + now]){
            now ++;
        }
        hg[rk[i]] = now;
    }
}
int st[N][30];
int pre[N];
void prework(){
    for(int i = 2; i <= n; i++){
        pre[i] = pre[i / 2] + 1;
    }
}
int ask(int l, int r){
    if(l > r) return 0;
    int step = pre[r - l + 1];
    return min(st[l][step], st[r - (1ll << step) + 1][step]);
}
struct Data{
    int st, len;
    friend bool operator < (Data x, Data y){
        int l = min(rk[x.st], rk[y.st]);
        int r = max(rk[x.st], rk[y.st]);
        int lcp = ask(l + 1, r);
        if(x.st == y.st) lcp = 1e18;
        if(y.len > lcp){
            return rk[x.st] < rk[y.st];
        }
        else{
            return x.len < y.len;
        }
    }
};
struct Ques{
    int pos, st;
    friend bool operator < (Ques x, Ques y){
        return (x.pos != y.pos) ? (x.pos > y.pos) : (x.st > y.st);
    }
};
priority_queue<Ques>q;
bool check(int x, int pos){
    int now = 1;
    for(int i = 1; i <= m; i++){
        int ed = n + 1;
        Data tmp = {now, 0};
        while(q.size()) q.pop();
        for(int j = now; j <= n; j++){
            tmp.len ++;
            if(rk[j] > rk[tmp.st]){//我需要修改
                int l = min(rk[j], rk[tmp.st]);
                int r = max(rk[j], rk[tmp.st]);
                int lcp = ask(l + 1, r);
                q.push({j + lcp, j});
            }
            while(q.size() && q.top().pos == j){
                Data p = {q.top().st, j - q.top().st + 1};
                if(tmp < p){
                    tmp = p;
                }
                else{
                    if(rk[q.top().st] > rk[tmp.st]){
                        int l = min(rk[q.top().st], rk[tmp.st]);
                        int r = max(rk[q.top().st], rk[tmp.st]);
                        int lcp = ask(l + 1, r);
                        q.push({q.top().st + lcp, q.top().st});    
                    }
                }
                q.pop();
            }
            if((Data){x, pos} < tmp){
                ed = j;
                break;
            }
        }
        now = ed;
    }
    if(now > n) return 1;
    return 0;
}
signed main() {
#ifndef Air
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    m = read();
    cin >> ch;
    n = ch.size();
    ch = ' ' + ch;
    prework();
    get_sa();
    get_hg();
    for(int i = 1; i <= n; i++){
        st[i][0] = hg[i];
        // cerr << ch[i] << ' '  <<  rk[i] << '\n';
    }
    for(int j = 1; j <= 20; j++){
        for(int i = 1; i + (1ll << j) - 1 <= n; i++){
            st[i][j] = min(st[i][j - 1], st[i + (1ll << (j - 1))][j - 1]);
        }
    }
    int l = 1, r = n;//先看答案在那个后缀里
    // cerr << rk[50] << '\n';
    // cerr << "!! " << check(1, 1e18);
    // return 0;
    while(l + 1 < r){
        int mid = (l + r) >> 1;
        if(check(sa[mid], 1e18)){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    int tp1 = 0;
    for(int i = l; i <= r; i++){
        if(check(sa[i], 1e18)){
            tp1 = sa[i];
            break;
        }
    }
    l = 1, r = n;
    while(l + 1 < r){
        int mid = (l + r) >> 1;
        if(check(tp1, mid)){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    for(int i = l; i <= r; i++){
        if(check(tp1, i)){
            for(int j = 0; j < i; j++){
                cout << ch[tp1 + j];
            }
            return 0;
        }
    }
    return 0;
}
