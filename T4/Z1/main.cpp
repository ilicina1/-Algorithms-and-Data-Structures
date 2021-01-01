#include <iostream>
#include "../../Klase/red.h"

double rekurzijaProsjek(Red<int> red) {
    static int suma = 0, brojac = red.brojElemenata();
    static double prosjek = 0;

    if(brojac == 0) {
        prosjek = double(suma) / red.brojElemenata();
        return prosjek;
    }

    int pom = red.skini();
    suma += pom;
    red.stavi(pom);
    brojac--;
    return rekurzijaProsjek(red);
}

void funkcija(Red<int>& red) {    
    double prosjek = rekurzijaProsjek(red);
    int brojac = 0, brojElem = red.brojElemenata();
    while(brojac < brojElem) {
        int pom = red.skini();
        if(pom <= prosjek) {
            red.stavi(pom);
        }
        brojac++;
    }
}

int main() {
    Red<int> r1;
    r1.stavi(8);
    r1.stavi(9);
    r1.stavi(5);
    r1.stavi(4);
    r1.stavi(10);
    r1.stavi(1);
    r1.stavi(3);
    r1.stavi(6);
    r1.stavi(7);
    r1.stavi(2);
    
    funkcija(r1);

   // r1.Prikazi();
}
