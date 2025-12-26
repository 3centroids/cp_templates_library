#pragma once
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
template <typename T> using vec=vector<T>;

constexpr char nl='\n';
#define pb push_back
#define sz(c) (int)(c).size()
#define all(c) c.begin(),c.end()
#define rep(a, b) for(decltype(b) a=0; a<b; ++a)

#ifdef LOCAL
#define DEBUG 1
#else
#define DEBUG 0
#endif
#define ifbug if constexpr(DEBUG)
#define bug(...) ifbug{cerr<<"["#__VA_ARGS__"]: ";bug__(__VA_ARGS__);cerr<<'\n';}
template <typename...A> void bug__(A&&...a){((cerr<<a<<' '),...);}
