/*
Date: 2025-12-25
Source: cp-algorithms, kactl
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

namespace Treap {
struct Node;
using ptr=Node*;

struct Node {
    int val, pri; 
    // int cnt=1;
    ptr l=nullptr; ptr r=nullptr;
    Node(int v) : val(v), pri(gen_rand()) {}
};

// int size(ptr t) { return ((t) ?t->cnt :0); }

// void upd_size(ptr t) {
//     if(!t) { return; }
//     t->cnt=1+size(t->l)+size(t->r);
// }

void split(ptr t, ptr &l, ptr &r, int k) {
    if(!t) {
        l=nullptr;
        r=nullptr;
        return;
    }
    if(t->val <= k) {
        split(t->r, t->r, r, k); 
        l=t;
    } else {
        split(t->l, l, t->l, k);
        r=t;
    }
    // upd_size(t);
}

void insert(ptr &t, ptr x) {
    if(!t) {
        t=x;
    } else if(x->pri > t->pri) {
        split(t, x->l, x->r, x->val);
        t=x;
    } else {
        insert(((t->val <= x->val) ?t->r :t->l), x);
    }
    // upd_size(t);
}

void insert(ptr &t, int val) {
    ptr x=new Node(val);
    insert(t, x);
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
    // upd_size(t);
}

void extract(ptr &t, int k) {
    if(!t) { return; }
    if(t->val == k) {
        ptr help=t;
        merge(t, t->l, t->r);
        delete help;
    } else {
        extract(((k < t->val) ?t->l :t->r), k);
    }
    // upd_size(t);
}

// void find
// void lower_bound
// void clear

void print(ptr t, char endl='\n') {
    if(t->l) { print(t->l, '\0'); }
    std::cerr<<(t->val)<<' ';
    if(t->r) { print(t->r, '\0'); } 
    if(endl) { std::cerr<<endl; }
}
} // namespace Treap
