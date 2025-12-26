// adapted from implicit_treap.h

#include <bits/stdc++.h>
using namespace std;

using ll=long long;
template <typename T> using vec=vector<T>;

constexpr char nl='\n';
#define pb push_back
#define sz(c) (int)(c).size()
#define all(c) c.begin(),c.end()
#define rep(a, b) for(decltype(b) a=0; a<b; ++a)

#ifdef LOCAL
#define DEBUG 1
#else
#define DEBUG 0
#endif
#define ifbug if constexpr(DEBUG)
#define bug(...) ifbug{cerr<<"["#__VA_ARGS__"]: ";bug__(__VA_ARGS__);cerr<<'\n';}
template <typename...A> void bug__(A&&...a){((cerr<<a<<' '),...);}

constexpr int LIM=2e5+6;

uint32_t rng() {
    static uint32_t x=2463534242u;
    x^=x<<13;
    x^=x>>17;
    x^=x<<5;
    return x;
}

// Implicit Treap
struct ImpTreap {
    using ptr=ImpTreap*;

    char val; uint32_t pri; 
    int cnt=1;
    ptr l=nullptr; ptr r=nullptr;
    ImpTreap() {}
    ImpTreap(char v) : val(v), pri(rng()) {}
    
    static inline int size(ptr t) { return ((t) ?t->cnt :0); }

    static inline void upd_size(ptr t) {
        if(!t) { return; }
        t->cnt=1+size(t->l)+size(t->r);
    }

    static void merge(ptr &t, ptr l, ptr r) {
        if(!l || !r) {
            t=((l) ?l :r);
        } else if(l->pri > r->pri) {
            merge(l->r, l->r, r);
            t=l;
        } else {
            merge(r->l, l, r->l);
            t=r;
        }
        upd_size(t);
    }

    static void split(ptr t, ptr &l, ptr &r, int k) {
        if(!t) {
            l=nullptr; r=nullptr;
            return;
        }
        if(size(t->l) < k) {
            split(t->r, t->r, r, k-size(t->l)-1); 
            l=t;
        } else {
            split(t->l, l, t->l, k);
            r=t;
        }
        upd_size(t);
    }

    static void print(ptr t, char endl='\n') {
        if(t->l) { print(t->l, '\0'); }
        std::cout<<(t->val);
        if(t->r) { print(t->r, '\0'); } 
        if(endl) { std::cout<<endl; }
    }
};

ImpTreap::ptr new_ImpTreap(char v) {
    static ImpTreap pool[LIM];
    // === A
    static ImpTreap::ptr pool_ptr=pool;
    *pool_ptr=ImpTreap(v);
    return pool_ptr++;
    // === B
    // static int pool_ptr=0;
    // ImpTreap::ptr t=&pool[pool_ptr++];
    // t->val=v;
    // t->pri=rng();
    // t->cnt=1;
    // t->l=nullptr; t->r=nullptr;
    // return t;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    using S=ImpTreap;
    S::ptr t=nullptr;
    int n,q;
    cin>>n>>q;
    rep(_, n) {
        char chr;
        cin>>chr;
        S::merge(t, t, new_ImpTreap(chr));
    }
    rep(_, q) {
        int l,r;
        cin>>l>>r;
        S::ptr a,b,c,d;
        S::split(t, a, b, l-1);
        S::split(b, c, d, r-l+1);
        S::merge(t, a, d);
        S::merge(t, t, c);
    }
    S::print(t);
}
