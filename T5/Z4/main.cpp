#include <iostream>
#include "../../Klase/stek.h"

template <typename nekiTip>
bool daLiJeDupli(Stek<nekiTip> s, nekiTip element) {
    if(s.JeLiPrazan()) {
        return false;
    }

    nekiTip temp = s.skini();
    
    if(temp == element) {
        return true;
    }

    if(temp != element && s.brojElemenata() == 0) {
        return false;
    }

    return daLiJeDupli(s, element);
}

template <typename nekiTip>
void ubaciSortirano(Stek<nekiTip>& s, nekiTip x) {
    if (s.JeLiPrazan() || x < s.vrh()) {
        s.stavi(x);
        return;
    }

    nekiTip temp = s.skini();
    ubaciSortirano(s, x);

    s.stavi(temp);
}

template <typename nekiTip>
Stek<nekiTip> spojiSortirano(Stek<nekiTip> s1, Stek<nekiTip> s2) {
    static Stek<nekiTip> s3;
    if(s1.brojElemenata() == 0 && s2.brojElemenata() == 0) {
        return s3;
    }

    nekiTip temp1 = s1.skini();
    nekiTip temp2 = s2.skini();

    if(daLiJeDupli(s3, temp1) == false) {
        ubaciSortirano(s3,temp1);
    }

    if(daLiJeDupli(s3, temp2) == false) {
        ubaciSortirano(s3,temp2);
    }

    return spojiSortirano(s1, s2);
}

int main() {
    Stek<int> s1;
    Stek<int> s2;
    Stek<int> s3;

    s1.stavi(30);
    s1.stavi(25);
    s1.stavi(24);
    s1.stavi(1);

    s2.stavi(31);
    s2.stavi(26);
    s2.stavi(24);
    s2.stavi(10);

    s3 = spojiSortirano(s1, s2);

    s3.Prikazi();

    // std::cout << daLiJeDupli(s1, 5);
}


// 8 5 3 1
// 2 4 6 9

// 2 8 4 5 3 6 1 9
