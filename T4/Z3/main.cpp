#include <iostream>
#include "../../Klase/lista.h"
#include "../../Klase/red.h"


//Nije tacan zadatak!!!!!
template <typename nekiTip>
void obrniRed(Red<nekiTip>& red) {
    if(red.brojElemenata() == 0) {
        return;
    }

    nekiTip temp = red.skini();

    obrniRed(red);

    red.stavi(temp);
}

template <typename nekiTip>
void funkcija(Red<nekiTip>& red, JednostrukaLista<nekiTip>& lista, int n) {
    static int brElem = red.brojElemenata() + lista.brojElemenata(), brojacLista = 0;
    static int brojac = 0, brojElemReda = red.brojElemenata(), brojacRed = 0;
    static bool check = false;

    if(red.brojElemenata() == 0) {
        return;
    }

    nekiTip temp = red.skini();

    funkcija(red, lista, n);

    //Kad je broj elemenata u redu i listi isti ili kad je broj elemanta u redu veci od broja elemenata u listi
    if(brojacRed < brojElemReda && brojacLista <= lista.brojElemenata()) {
        if(brojac < n) {
            red.stavi(temp);
            brojac++;
            brojacRed++;
        }
        if(brojac == n) {
            bool pom = true;
            while(brojac != 0) {
                red.stavi(lista.trenutni());
                brojacLista++;
                pom = lista.prethodni();
                if(!pom) break;
                brojac--;
            }
        }
    }

    if(brojacRed + brojacLista == brElem && !check) {
        check = true;
        obrniRed(red);
    }
}

int main() {
    Red<int> red;
    red.stavi(1);
    red.stavi(2);
    red.stavi(3);
    red.stavi(4);
    red.stavi(5);
    red.stavi(6);
    red.stavi(7);

    JednostrukaLista<int> lista;
    for(int i = 1; i <= 4; i++) {
        lista.dodajIza(i);
        lista.sljedeci();
    }
    lista.kraj();

    funkcija(red, lista, 2);

    red.Prikazi();
}

// 1 2 3 4 5 6 7
// 1 2 3 4
//
// 6 5 4 3 4 3 2 1 2 1
