#include "template.h"
#include "treap.h"

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    Treap::ptr t=nullptr;
    int q;
    cin>>q;
    rep(_, q) {
        char chr;
        cin>>chr;
        if(chr=='+') {
            // add
            int x;
            cin>>x;
            Treap::insert(t, x);
        } else if(chr=='-') {
            // remove
            int x;
            cin>>x;
            Treap::extract(t, x);
        }
        Treap::print(t);
    }
}
