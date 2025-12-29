#include "../headers/template.h"

mt19937 gen;

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(gen);
}
