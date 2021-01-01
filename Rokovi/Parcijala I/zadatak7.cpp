#include <iostream>
#include "../../Klase/red.h"
#include <vector>

/*
    Pronaci zbir maksimalnog i minimalnog elementa svih vektora u redu.
*/

int funkcijaAV(Red<std::vector<int>>& r) {
    static int brojac = 0, maks = 0, min = 0;
    if(brojac == r.brojElemenata()) {
        return maks + min;
    }

    std::vector<int> pomVector = r.skini();

    // Ovo treba ispraviti da bude pretraga O(logn);
    for(int i = 0; i < pomVector.size(); i++) {
        if(pomVector.at(i) > maks) maks = pomVector.at(i);
        if(pomVector.at(i) < min) min = pomVector.at(i);
    }

    r.stavi(pomVector);
    brojac++;

    return funkcijaAV(r);
}

int main() {
    Red<std::vector<int>> red;

    std::vector<int> v1 { 1, 3, 8, 9, 11, 8, 4, 1 };
    std::vector<int> v2 { 2, 4, 6, 8, 4, 3, 2 };
    std::vector<int> v3 { 500, 88, 150, 400 };
    std::vector<int> v4 { -8, -9, -3, -2, -1 };

    red.stavi(v1);
    red.stavi(v2);
    red.stavi(v3);
    red.stavi(v4);

    std::cout << funkcijaAV(red);

}
