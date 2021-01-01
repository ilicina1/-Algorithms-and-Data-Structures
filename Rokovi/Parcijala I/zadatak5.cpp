#include <iostream>
#include <vector>
#include "../../Klase/stek.h"

/*
    U vektoru su  stekovi sortirani od najmanjeg ka najvecem po sumi elemenata.
    Funkcija treba binarnom pretragom pronaci stek cija je suma elemenata jednaka n.
*/

int sumaSteka(Stek<int> s) {
    static int suma = 0;
    if(s.brojElemenata() == 0) {
        int pom = suma;
        suma = 0;
        return pom;
    }

    int temp = s.skini();
    suma += temp;

    return sumaSteka(s);
}

int pretraga(std::vector<Stek<int>> v, int n) {
    static int vrh = v.size() - 1;
    static int dno = 0;

    if(vrh - dno > 1) {
        // Racunamo sredinu;
        int middleIndex = dno + (vrh - dno) / 2;

        // Provjeravamo da li smo pronasli element i ako jesmo vracamo ga;
        if(sumaSteka(v.at(middleIndex)) == n) return middleIndex;

        // Ako je element na sredini manji od onog kojeg trazimo nastavljamo gledati desnu polovinu;
        if(sumaSteka(v.at(middleIndex)) < n) {
            dno = middleIndex;
            return pretraga(v, n);
        }

        // Ako je element na sredini veci od onog kojeg trazimo nastavljamo gledati lijevu polovinu;
        if(sumaSteka(v.at(middleIndex)) > n) {
            vrh = middleIndex;
            return pretraga(v, n);
        }
    }

    if(sumaSteka(v.at(dno)) == n) return dno;
    if(sumaSteka(v.at(vrh)) == n) return vrh;

    return -1;
}

int main() {
    Stek<int> s1;
    s1.stavi(1);
    s1.stavi(2);
    s1.stavi(3);
    s1.stavi(4);

    Stek<int> s2;
    s2.stavi(1);
    s2.stavi(2);
    s2.stavi(3);
    s2.stavi(4);
    s2.stavi(5);

    Stek<int> s3;
    s3.stavi(1);
    s3.stavi(2);
    s3.stavi(3);
    s3.stavi(4);

    Stek<int> s4;
    s4.stavi(1);
    s4.stavi(2);
    s4.stavi(5);
    s4.stavi(4);

    std::vector<Stek<int>> v;
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);
    v.push_back(s4);

    int indeks = pretraga(v, 15);

}
