#include <bits/stdc++.h>
#include "../../treap.h"
using namespace std;
using namespace chrono;

int main() {
    vector<int> Ns = {1000, 10000, 100000, 200000, 500000}; // sizes to test
    int K = 5; // repeats per N

    mt19937 rng(12345); // fixed seed

    cout << "N,Treap(ms),multiset(ms)\n"; // CSV header

    for (int N : Ns) {
        long long treap_total = 0, ms_total = 0;

        for (int rep = 0; rep < K; ++rep) {
            vector<int> ops(N);
            for (int &x : ops) x = rng() % (N*2); // allow duplicates

            // --- Treap ---
            Treap::ptr t = nullptr;
            auto start = high_resolution_clock::now();
            for (int x : ops) Treap::insert(t, x);
            for (int x : ops) Treap::extract(t, x);
            auto end = high_resolution_clock::now();
            treap_total += duration_cast<milliseconds>(end - start).count();

            // --- multiset ---
            multiset<int> s;
            start = high_resolution_clock::now();
            for (int x : ops) s.insert(x);
            for (int x : ops) {
                auto it = s.find(x);
                if (it != s.end()) s.extract(it);
            }
            end = high_resolution_clock::now();
            ms_total += duration_cast<milliseconds>(end - start).count();
        }

        cout << N << "," 
             << treap_total / K << "," 
             << ms_total / K << "\n"; // average over K runs
    }
}
