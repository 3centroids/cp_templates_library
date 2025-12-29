#include "../headers/template.h"
#include "../headers/implicit_treap.h"

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    ImpTreap<char> trp;
    int n,q;
    cin>>n>>q;
    rep(_, n) {
        char chr;
        cin>>chr;
        trp.merge(trp.root, trp.root, trp.new_node(chr));
    }
    rep(_, q) {
        int l,r;
        cin>>l>>r;
        int a,b,c,d;
        trp.split(trp.root, a, b, l-1);
        trp.split(b, c, d, r-l+1);
        trp.merge(trp.root, a, d);
        trp.merge(trp.root, trp.root, c);
    }
    trp.print(trp.root);
}
