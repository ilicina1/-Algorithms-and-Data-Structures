#include <iostream>
#include "../../Klase/red.h"
#include "../../Klase/stek.h"

void queueToStack(Stek<int>& s, Red<int>& red) {
    if (s.JeLiPrazan()) {
        int brojac = 0, brojElem = red.brojElemenata();
        while(brojac < brojElem) {
            int pom = red.skini();
            s.stavi(pom);
            red.stavi(pom);
            brojac++;
        }
        return;
    }

    int temp = s.skini();
    queueToStack(s, red);

    s.stavi(temp);
}

int main() {
    Stek<int> s1;

    s1.stavi(5);
    s1.stavi(6);
    s1.stavi(7);
    s1.stavi(8);
    Red<int> r1;

    r1.stavi(1);
    r1.stavi(2);
    r1.stavi(3);
    r1.stavi(4);

    queueToStack(s1, r1);

    // 8 7 6 5 4 3 2 1 <==> gdje je 8 vrh steka
    s1.Prikazi();
}
