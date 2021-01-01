#include <iostream>

template <typename nekiTip>
int binarna_pretraga(nekiTip* niz, int n, nekiTip element) {
    static int vrh = n - 1;
    static int dno = 0;

    if(vrh - dno > 1) {
        // Racunamo sredinu;
        int middleIndex = dno + (vrh - dno) / 2;

        // Provjeravamo da li smo pronasli element i ako jesmo vracamo ga;
        if(niz[middleIndex] == element) return middleIndex;

        // Ako je element na sredini manji od onog kojeg trazimo nastavljamo gledati desnu polovinu;
        if(niz[middleIndex] < element) {
            dno = middleIndex;
            return binarna_pretraga(niz, n, element);
        }

        // Ako je element na sredini veci od onog kojeg trazimo nastavljamo gledati lijevu polovinu;
        if(niz[middleIndex] > element) {
            vrh = middleIndex;
            return binarna_pretraga(niz, n, element);
        }
    }

    if(niz[dno] == element) return dno;
    if(niz[vrh] == element) return vrh;

    return -1;
}

int main() {
    int foo [16] = { 5, 19, 22, 25, 31, 44, 90, 93, 99, 102, 110, 150, 155, 159, 200, 202 };
    int result = binarna_pretraga(foo, 16, 202);

    std::cout << result;
}
