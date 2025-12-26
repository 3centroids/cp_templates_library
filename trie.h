/*
Date: 2025-12-26
Source: cp-algorithms, atcoder
Status: OK (https://atcoder.jp/contests/abc419/tasks/abc419_f)
*/

#include "template.h"

struct AhoCorasick {
    static const int ALPHA=26;
    struct Node {
        vector<int> next;
        int link;
        int mask; // maska konczacych sie tutaj
        Node() {
            next.assign(ALPHA, -1);
            link=0;
            mask=0;
        };
    };
    vector<Node> trie;
    AhoCorasick() {
        trie.emplace_back(); // root
    }
    void add(const string &s, int id) {
        int v=0;
        for(char ch:s) {
            int c=ch-'a';
            if(trie[v].next[c]==-1) {
                trie[v].next[c]=sz(trie);
                trie.emplace_back();
            }
            v=trie[v].next[c];
        }
        trie[v].mask|=(1<<id);
    }
    void build() {
        queue<int> q;
        for(int c=0; c<ALPHA; ++c) { // przejscia z roota
            int v=trie[0].next[c];
            if(v!=-1) {
                trie[v].link=0;
                q.push(v);
            } else {
                trie[0].next[c]=0;
            }
        }
        while(!q.empty()) { // pozostale przejscia
            int v=q.front(); q.pop();
            int link=trie[v].link;
            trie[v].mask|=trie[link].mask;
            for(int c=0; c<ALPHA; ++c) {
                int u=trie[v].next[c];
                if(u!=-1) {
                    trie[u].link=trie[link].next[c];
                    q.push(u);
                } else {
                    trie[v].next[c]=trie[link].next[c];
                }
            }
        }
    }
};
