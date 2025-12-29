// adapted from union_find.h

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
struct UF {
    int par[LIM];
    int rnk[LIM];
    int val[LIM];
    int n;
    UF(int _n) {
        n=_n;
        for(int i=0; i<n; ++i) {
            par[i]=i;
            rnk[i]=1;
            val[i]=0;
        }
    }
    int find(int x) {
        if(par[x]==x) { return x; }
        return par[x]=find(par[x]);
    }
    void merge(int x, int y) {
        x=find(x); y=find(y);
        if(x==y) { return; }
        if(rnk[x]<rnk[y]) { swap(x, y); }
        rnk[x]+=rnk[y];
        val[x]=max(val[x], val[y]);
        par[y]=x;
    }
};

constexpr int INF=1e9+6;
constexpr int N=2e5+6;
int a[N];
int pom[N];
bool akt[N];

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin>>n;
    for(int i=1; i<=n; ++i) { cin>>a[i]; }

    for(int i=0; i<n; ++i) { pom[i]=i+1; }
    sort(pom, pom+n, [](int x, int y) {
        return a[x]<a[y];
    });

    int wyn=0;
    UF uf(n+2); // [0, n+1]
    vec<pair<int, int>> prz;
    int j=0;
    for(int i=0; i<n; i=j+1) {
        int k=pom[i];
        j=i;
        while(j+1<n && a[pom[j+1]]==a[k]) {
            ++j;
        }

        vec<pair<int, int>> batch; // {pos, val}
        for(int x=i; x<=j; ++x) {
            int t=pom[x];
            int l=uf.find(t-1); int r=uf.find(t+1);
            int cur=1;
            if(akt[l]) { cur=max(cur, uf.val[l]+1); }
            if(akt[r]) { cur=max(cur, uf.val[r]+1); }
            wyn=max(wyn, cur);
            batch.pb({t, cur});
        }

        for(const auto&[t, cur]:batch) {
            akt[t]=1;
            int l=uf.find(t-1); int r=uf.find(t+1);
            if(akt[l]) { uf.merge(t, l); }
            if(akt[r]) { uf.merge(t, r); }
            int p=uf.find(t);
            uf.val[p]=max(uf.val[p], cur);
        }
    }
    cout<<wyn<<nl;
}
