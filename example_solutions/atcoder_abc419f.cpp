#include <bits/stdc++.h>
using namespace std;

constexpr char nl='\n';
#define pb push_back
#define sz(c) (int)(c.size())
#define all(c) c.begin(),c.end()
#define rep(a, b) for(int a=0; a<b; ++a)

using ll=long long;

struct AhoCorasick {
    static const int ALPHA=26;
    struct Node {
        vector<int> next;
        int link;
        int mask; // maska konczacych sie tutaj
        Node() {
            next.assign(ALPHA, -1);
            link=0;
            mask=0;
        };
    };
    vector<Node> trie;
    AhoCorasick() {
        trie.emplace_back(); // root
    }
    void add(const string &s, int id) {
        int v=0;
        for(char ch:s) {
            int c=ch-'a';
            if(trie[v].next[c]==-1) {
                trie[v].next[c]=sz(trie);
                trie.emplace_back();
            }
            v=trie[v].next[c];
        }
        trie[v].mask|=(1<<id);
    }
    void build() {
        queue<int> q;
        for(int c=0; c<ALPHA; ++c) { // przejscia z roota
            int v=trie[0].next[c];
            if(v!=-1) {
                trie[v].link=0;
                q.push(v);
            } else {
                trie[0].next[c]=0;
            }
        }
        while(!q.empty()) { // pozostale przejscia
            int v=q.front(); q.pop();
            int link=trie[v].link;
            trie[v].mask|=trie[link].mask;
            for(int c=0; c<ALPHA; ++c) {
                int u=trie[v].next[c];
                if(u!=-1) {
                    trie[u].link=trie[link].next[c];
                    q.push(u);
                } else {
                    trie[v].next[c]=trie[link].next[c];
                }
            }
        }
    }
};

constexpr int MOD=998244353;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,l;
    cin>>n>>l;
    auto AC=AhoCorasick();
    for(int i=0; i<n; ++i) {
        string s;
        cin>>s;
        AC.add(s, i);
    }
    AC.build();
    int m=sz(AC.trie);
    vector<vector<ll>> dp(1<<n, vector<ll>(m, 0));
    vector<vector<ll>> ndp(1<<n, vector<ll>(m, 0));
    dp[0][0]=1;
    for(int i=0; i<l; ++i) {
        for(int bm=0; bm<(1<<n); ++bm) { // clear ndp
            fill(all(ndp[bm]), 0);
        }
        for(int bm=0; bm<(1<<n); ++bm) {
            for(int v=0; v<m; ++v) {
                for(int c=0; c<26; ++c) {
                    int to=AC.trie[v].next[c];
                    int nbm=bm|AC.trie[to].mask;
                    ndp[nbm][to]=(dp[bm][v]+ndp[nbm][to])%MOD;
                }
            }
        }
        swap(dp, ndp); // set dp to ndp
    }
    ll ans=0;
    for(int v=0; v<m; ++v) {
        ans=(ans+dp[(1<<n)-1][v])%MOD;
    }
    cout<<ans<<nl;
}
