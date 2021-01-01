#include <iostream>
#include "../../Klase/stek.h"


template <typename Tip>
int presjek(Stek<Tip> s1, Stek<Tip> s2) {
    static int brojac = 0;
    if(s1.brojElemenata() == 0 || s2.brojElemenata() == 0) {
        return brojac;
    }

    if(s2.vrh() > s1.vrh()) {
        s2.skini();
        return presjek(s1, s2);
    } else if(s1.vrh() > s2.vrh()) {
        s1.skini();
        return presjek(s1,s2);
    } else if(s1.vrh() == s2.vrh()) {
        brojac++;
        s1.skini();
        s2.skini();
        return presjek(s1, s2);
    }
}

int main() {
    Stek<char> s1;
    Stek<char> s2;
    s1.stavi('A');
    s1.stavi('C');
    s1.stavi('D');
    s1.stavi('F');

    s2.stavi('B');
    s2.stavi('C');
    s2.stavi('D');
    s2.stavi('E');
    s2.stavi('F');
    s2.stavi('G');

    std::cout << presjek(s1, s2);
}
