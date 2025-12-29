/*
Date: 2025-12-29
Source: folklore
Status: OK (https://cses.fi/problemset/task/3314)
*/

#include "template.h"

///
/// @brief Union-Find data structure
/// @param n Nodes count
///
struct UF {
    vec<int> par;
    vec<int> rnk;
    int n;
    UF(int _n) {
        n=_n;
        par.resize(n);
        rnk.resize(n);
        for(int i=0; i<n; ++i) {
            par[i]=i;
            rnk[i]=1;
        }
    }
    int find(int x) {
        if(par[x]==x) { return x; }
        return par[x]=find(par[x]);
    }
    void merge(int x, int y) {
        x=find(x); y=find(y);
        if(x==y) { return; }
        if(rnk[x]<rnk[y]) { swap(x, y); }
        rnk[x]+=rnk[y];
        par[y]=x;
    }
};
