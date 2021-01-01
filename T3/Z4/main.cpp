#include <iostream>
#include <algorithm>
#include "../../Klase/stek.h"


void ubaciSortirano(Stek<int>& s, int x) {
    if (s.JeLiPrazan() || x < s.vrh()) {
        s.stavi(x);
        return;
    }


    int temp = s.skini();
    ubaciSortirano(s, x);

    s.stavi(temp);
}

void sortiraj(Stek<int>& s) {
    if (!s.JeLiPrazan()) {
        int x = s.skini();

        sortiraj(s);
        
        ubaciSortirano(s, x);
    }
}

void spoji(Stek<int> s1, Stek<int> s2, Stek<int>& s3) {
    while(s1.brojElemenata() != 0) {
        s3.stavi(s1.vrh());
        s3.stavi(s2.vrh());
        s1.skini();
        s2.skini();
    }
    sortiraj(s3);
}

int main() {
    Stek<int> s1;
    Stek<int> s2;
    Stek<int> s3;

    s1.stavi(1);
    s1.stavi(3);
    s1.stavi(5);
    s1.stavi(8);

    s2.stavi(9);
    s2.stavi(6);
    s2.stavi(4);
    s2.stavi(2);

    spoji(s1, s2, s3);

    s3.Prikazi();
}
