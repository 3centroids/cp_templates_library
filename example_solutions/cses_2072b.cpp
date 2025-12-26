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
constexpr int NIL=0;

uint32_t rng() {
    static uint32_t x=2463534242U;
    x^=x<<13;
    x^=x>>17;
    x^=x<<5;
    return x;
}

// Implicit Treap
struct ImpTreap {
    struct Node {
        char val; uint32_t pri; 
        int cnt=1; int l=NIL; int r=NIL;
        Node(char v) : val(v), pri(rng()) {}
    };
    
    vector<Node> t;
    int root=NIL;
    ImpTreap() {
        t.reserve(LIM+1);
        t.emplace_back(0);
        t[0].val='\0'; t[0].cnt=0;
        t[0].l=0; t[0].r=0;
    }

    inline int size(int v) const { return t[v].cnt; }
    inline void pull(int v) { t[v].cnt=1+size(t[v].l)+size(t[v].r); }
    void merge(int &v, int l, int r) {
        if(l==NIL || r==NIL) {
            v=((r==NIL) ?l :r);
        } else if(t[l].pri > t[r].pri) {
            merge(t[l].r, t[l].r, r);
            v=l;
        } else {
            merge(t[r].l, l, t[r].l);
            v=r;
        }
        pull(v);
    }
    void split(int v, int &l, int &r, int k) {
        if(v==NIL) {
            l=NIL; r=NIL;
            return;
        }
        if(size(t[v].l) < k) {
            split(t[v].r, t[v].r, r, k-size(t[v].l)-1); 
            l=v;
        } else {
            split(t[v].l, l, t[v].l, k);
            r=v;
        }
        pull(v);
    }
    int new_node(char val) {
        t.emplace_back(val);
        return (int)t.size()-1;
    }
    void print(int v=0, char endl='\n') {
        if(t[v].l!=NIL) { print(t[v].l, '\0'); }
        std::cout<<(t[v].val);
        if(t[v].r!=NIL) { print(t[v].r, '\0'); } 
        if(endl) { std::cout<<endl; }
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    auto t=ImpTreap();
    int n,q;
    cin>>n>>q;
    rep(_, n) {
        char chr;
        cin>>chr;
        t.merge(t.root, t.root, t.new_node(chr));
    }
    rep(_, q) {
        int l,r;
        cin>>l>>r;
        int a,b,c,d;
        t.split(t.root, a, b, l-1);
        t.split(b, c, d, r-l+1);
        t.merge(t.root, a, d);
        t.merge(t.root, t.root, c);
    }
    t.print();
}
