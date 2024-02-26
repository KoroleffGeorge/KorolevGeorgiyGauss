#include <iostream>
#include "Euclid.h"

using namespace std;

int Euclid::gcd(int a, int b) {
    if (a == 0)
        return 1;
    a = abs(a), b = abs(b);
    if (a < b) {
        swap(a, b);
    }
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}