/*
Date: 2025-12-26
Source: cp-algorithms, kactl, usaco.guide, cses
Status: OK (https://cses.fi/problemset/task/2072)
*/

#include "template.h"

constexpr int LIM=2e5+6;

uint32_t rng() {
    static uint32_t x=2463534242U;
    x^=x<<13;
    x^=x>>17;
    x^=x<<5;
    return x;
}

// Implicit Treap
struct ImpTreap {
    struct Node {
        int val; uint32_t pri; 
        int cnt=1; int l=0; int r=0;
        Node(int v) : val(v), pri(rng()) {}
    };
    
    vector<Node> t;
    int root=0;
    ImpTreap() {
        t.reserve(LIM+1);
        t.emplace_back(0);
        t[0].cnt=0;
        t[0].l=0; t[0].r=0;
    }

    inline int size(int v) const { return t[v].cnt; }
    inline void pull(int v) { t[v].cnt=1+size(t[v].l)+size(t[v].r); }
    void merge(int &v, int l, int r) {
        if(l==0 || r==0) {
            v=((r==0) ?l :r);
        } else if(t[l].pri > t[r].pri) {
            merge(t[l].r, t[l].r, r);
            v=l;
        } else {
            merge(t[r].l, l, t[r].l);
            v=r;
        }
        pull(v);
    }
    void split(int v, int &l, int &r, int k) {
        if(v==0) {
            l=0; r=0;
            return;
        }
        if(size(t[v].l) < k) {
            split(t[v].r, t[v].r, r, k-size(t[v].l)-1); 
            l=v;
        } else {
            split(t[v].l, l, t[v].l, k);
            r=v;
        }
        pull(v);
    }
    int new_node(char val) {
        t.emplace_back(val);
        return (int)t.size()-1;
    }
    void print(int v=0, char endl='\n') {
        if(t[v].l!=0) { print(t[v].l, '\0'); }
        if(v>0) { std::cout<<(t[v].val); }
        if(t[v].r!=0) { print(t[v].r, '\0'); } 
        if(endl) { std::cout<<endl; }
    }
};
