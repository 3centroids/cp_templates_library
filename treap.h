/*
Date: 2025-12-26
Source: cp-algorithms, kactl, usaco.guide, cses
Status: 
Notes: 
- treap handles duplicates (multiset)
*/

// for printing
#include <iostream>

uint32_t rng() {
    static uint32_t x=2463534242u;
    x^=x<<13;
    x^=x>>17;
    x^=x<<5;
    return x;
}

constexpr int LIM=2e5+6;

struct Treap;
Treap* new_Treap(int v);

struct Treap {
    using ptr=Treap*;

    int val; uint32_t pri; 
    // int cnt=1;
    ptr l=nullptr; ptr r=nullptr;
    Treap() {}
    Treap(int v) : val(v), pri(rng()) {}
    
    // static inline int size(ptr t) { return ((t) ?t->cnt :0); }
    // static inline void upd_size(ptr t) {
    //     if(!t) { return; }
    //     t->cnt=1+size(t->l)+size(t->r);
    // }
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
        // upd_size(t);
    }
    static void split(ptr t, ptr &l, ptr &r, int k) {
        if(!t) {
            l=nullptr; r=nullptr;
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
    static void insert(ptr &t, ptr x) {
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
    static void insert(ptr &t, int val) {
        ptr x=new_Treap(val);
        insert(t, x);
    }
    static void extract(ptr &t, int val) {
        if(!t) { return; }
        if(t->val == val) {
            merge(t, t->l, t->r);
        } else {
            extract(((val < t->val) ?t->l :t->r), val);
        }
        // upd_size(t);
    }
    // void find
    // void lower_bound
    // void clear
    static void print(ptr t, char endl='\n') {
        if(t->l) { print(t->l, '\0'); }
        std::cerr<<(t->val)<<' ';
        if(t->r) { print(t->r, '\0'); } 
        if(endl) { std::cerr<<endl; }
    }
};

Treap::ptr new_Treap(int v) {
    static Treap pool[LIM];
    // static vector<Treap> pool;
    static Treap::ptr pool_ptr=pool;
    *pool_ptr=Treap(v);
    return pool_ptr++;
}
