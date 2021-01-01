#include <iostream>

bool daLiJePotencija(int broj, int baza) {
    static int bazaPom = baza;
    if(baza > broj) {
        return false;
    }

    baza *= bazaPom;

    if(baza == broj) return true;

    return daLiJePotencija(broj, baza);

    return false;
}

int main() {
    std::cout << daLiJePotencija(729, 9);
}
