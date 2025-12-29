/*
Date: 2025-12-29
Status: not tested
Notes:
- query is r-inclusive
- f must be associative
- f can be made non-static
*/

#include "template.h"

template <typename T>
struct Tree {
    static constexpr T unit=numeric_limits<T>::min();
    static T f(T a, T b) { return max(a, b); }
    vector<T> t; int baza=1;
    Tree(int n) { 
        baza=1; 
        while(baza < n) { baza*=2; } 
        t.assign(2*baza, unit);
    }
    void upd(int pos, T val) {
        pos+=baza;
        t[pos]=val;
        pos/=2;
        while(pos>0) {
            int l=2*pos; int r=2*pos+1;
            t[pos]=f(t[l], t[r]);
            pos/=2;
        }
    }
    T qry(int l, int r) {
        T wl=unit; T wr=unit;
        l+=baza; r+=baza;
        while(l<=r) {
            if(l&1) { wl=f(wl, t[l]); ++l; }
            if(!(r&1)) { wr=f(t[r], wr); --r; }
            l/=2; r/=2;
        }
        return f(wl, wr);
    }
};