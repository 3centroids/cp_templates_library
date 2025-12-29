#include "../headers/template.h"
#include "../headers/segment_tree.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n,q;
    cin>>n>>q;
    vec<int> a(n);
    for(int i=0; i<n; ++i) { cin>>a[i]; }

    Tree<int> tr(n);
    for(int i=0; i<n; ++i) {
        tr.upd(i, a[i]);
    }

    rep(_, q) {
        int l,r; // 0-indexed
        cin>>l>>r;
        int w=tr.qry(l, r);
        cout<<w<<nl;
    }
}