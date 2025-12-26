#include "template.h"
#include "implicit_treap.h"

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    ImpTreap<char> t;
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
    t.print(t.root);
}
