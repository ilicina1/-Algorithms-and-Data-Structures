#include <iostream>
#include "../../Klase/red.h"
#include "../../Klase/stek.h"

/*
    Izjednaciti broj elemenata svih stekova u redu sa prosjecnim brojem elemenata od svih stekova u redu.
    Elemente sa vrhova koji su viska treba prebaciti u stek koji se vraca u rastucem poretku tj. da vrh bude najveci element.
    Stekove koji imaju manje elemenata od prosjeka treba izbaciti iz reda.
*/

void ubaciSortirano(Stek<int>& s, int x) {
    if (s.JeLiPrazan() || x > s.vrh()) {
        s.stavi(x);
        return;
    }

    int temp = s.skini();
    ubaciSortirano(s, x);

    s.stavi(temp);
}

double prosjekStekova(Red<Stek<int>> r) {
    static int brojStekova = r.brojElemenata();
    static double prosjek = 0;

    if(r.brojElemenata() == 0) {
        prosjek /= brojStekova;
        return prosjek;
    }

    prosjek += r.celo().brojElemenata();
    Stek<int> pom = r.skini();

    return prosjekStekova(r);
}

Stek<int> IzravnajStekove(Red<Stek<int>>& r) {
    static Stek<int> stek;
    static double p = prosjekStekova(r);
    static int prosjek = int(p), brojac = 0;

    if(brojac == r.brojElemenata()) {
        return stek;
    }

    if(r.celo().brojElemenata() < prosjek) {
        r.skini();
        return IzravnajStekove(r);
    }

    while(r.celo().brojElemenata() > prosjek) {
        ubaciSortirano(stek, r.celo().skini());
    }

    Stek<int> pom = r.skini();
    r.stavi(pom);
    brojac++;

    return IzravnajStekove(r);
}

int main() {
    Red<Stek<int>> r;

    Stek<int> s1;
    Stek<int> s2;
    Stek<int> s3;
    Stek<int> konacni;

    s1.stavi(1);
    s1.stavi(2);
    s1.stavi(3);

    s2.stavi(1);

    s3.stavi(8);
    s3.stavi(5);
    s3.stavi(22);
    s3.stavi(3);
    s3.stavi(27);
    s3.stavi(11);

    r.stavi(s1);
    r.stavi(s2);
    r.stavi(s3);

    konacni = IzravnajStekove(r);

    // r.PrikaziStekove();
    konacni.Prikazi();
    return 0;
}
