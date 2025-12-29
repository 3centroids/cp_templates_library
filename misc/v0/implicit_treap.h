/*
Date: 2025-12-26
Source: cp-algorithms, kactl, usaco.guide
Status: none
Notes: 
- treap handles duplicates (multiset)
- for better performance use a faster random generator
like static uint32_t x with bit shifts
- use bump allocator to speed up memory allocation
*/

#include <random>
#include <iostream>
std::mt19937 gen_rand(0);

namespace Implicit_Treap {
struct Node;
using ptr=Node*;

struct Node {
    int val, pri; 
    int cnt=1;
    ptr l=nullptr; ptr r=nullptr;
    Node(int v) : val(v), pri(gen_rand()) {}
};

int size(ptr t) { return ((t) ?t->cnt :0); }

void upd_size(ptr t) {
    if(!t) { return; }
    t->cnt=1+size(t->l)+size(t->r);
}

void split(ptr t, ptr &l, ptr &r, int val, int add=0) {
    if(!t) {
        l=nullptr;
        r=nullptr;
        return;
    }
    int cur_size=add+size(t->l);
    if(cur_size < val) {
        split(t->r, t->r, r, val, add+1+size(t->l)); 
        l=t;
    } else {
        split(t->l, l, t->l, val, add);
        r=t;
    }
    upd_size(t);
}

void merge(ptr &t, ptr l, ptr r) {
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

void print(ptr t, char endl='\n') {
    if(t->l) { print(t->l, '\0'); }
    std::cerr<<(t->val)<<' ';
    if(t->r) { print(t->r, '\0'); } 
    if(endl) { std::cerr<<endl; }
}
} // namespace Implicit_Treap
