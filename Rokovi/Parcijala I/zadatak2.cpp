#include <iostream>
#include "../../Klase/red.h"
#include "../../Klase/stek.h"

// Opis reda: celo predstavlja prvi element u redu, skini() skida element sa cela, stavi() stavlja element na kraj reda;
// Opis steka: vrh predstavlja zadnji element koji se ubacio, skin() skida zadnji element koji se ubacio, stavi()
// stavlja element na kraj

// U zadatku treba sve parne brojeve iz reda staviti na dno steka uz ocuvanje redoslijeda elemenata steka
// U stek se parni brojevi iz reda ubacuju obrnuto tako da zadnji parni broj iz reda bude na samom dnu steka

void ubaciPrvoRed(Stek<int>& s, Red<int>& r) {
    if(r.brojElemenata() == 0) {
        return;
    }

    int tempRed = r.skini();

    ubaciPrvoRed(s, r);

    if(tempRed % 2 == 0)
        s.stavi(tempRed);
}

void funkcija(Stek<int>& s, Red<int>& r) {
    if(s.brojElemenata() == 0) {
        ubaciPrvoRed(s, r);
        return;
    }

    int tempStek = s.skini();

    funkcija(s, r);

    s.stavi(tempStek);
}

int main() {
    Stek<int> s;
    s.stavi(1);
    s.stavi(2);
    s.stavi(3);
    s.stavi(4);
    s.stavi(5);
    s.stavi(6);
    s.stavi(7);

    Red<int> r;
    r.stavi(8);
    r.stavi(9);
    r.stavi(10);
    r.stavi(11);
    r.stavi(12);
    r.stavi(13);
    r.stavi(14);

    funkcija(s, r);

    s.Prikazi();
}