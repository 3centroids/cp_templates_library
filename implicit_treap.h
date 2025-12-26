/*
Date: 2025-12-26
Source: cp-algorithms, kactl, usaco.guide, cses
Status: OK (https://cses.fi/problemset/task/2072)
*/

// for printing
#include <iostream>

constexpr int LIM=2e5+6;

uint32_t rng() {
    static uint32_t x=2463534242u;
    x^=x<<13;
    x^=x>>17;
    x^=x<<5;
    return x;
}

// Implicit Treap
struct ImpTreap {
    using ptr=ImpTreap*;

    int val; uint32_t pri; 
    int cnt=1;
    ptr l=nullptr; ptr r=nullptr;
    ImpTreap() {}
    ImpTreap(int v) : val(v), pri(rng()) {}
    
    static inline int size(ptr t) { return ((t) ?t->cnt :0); }
    static inline void upd_size(ptr t) {
        if(!t) { return; }
        t->cnt=1+size(t->l)+size(t->r);
    }
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
        upd_size(t);
    }
    static void split(ptr t, ptr &l, ptr &r, int k) {
        if(!t) {
            l=nullptr; r=nullptr;
            return;
        }
        if(size(t->l) < k) {
            split(t->r, t->r, r, k-size(t->l)-1); 
            l=t;
        } else {
            split(t->l, l, t->l, k);
            r=t;
        }
        upd_size(t);
    }
    static void print(ptr t, char endl='\n') {
        if(t->l) { print(t->l, '\0'); }
        std::cout<<(t->val);
        if(t->r) { print(t->r, '\0'); } 
        if(endl) { std::cout<<endl; }
    }
};

ImpTreap::ptr new_ImpTreap(int v) {
    static ImpTreap pool[LIM];
    static ImpTreap::ptr pool_ptr=pool;
    *pool_ptr=ImpTreap(v);
    return pool_ptr++;
}
