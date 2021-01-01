#include <iostream>
#include <utility>
#include <string>

using namespace std;

template <typename tipKljuca, typename tipVrijednosti>
class Mapa {
public:
    Mapa() {}
    virtual ~Mapa() {}
    virtual tipVrijednosti &operator [](const tipKljuca &kljuc) = 0;
    virtual const tipVrijednosti &operator [](const tipKljuca &kljuc) const = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const tipKljuca& kljuc) = 0;
};

template <typename tipKljuca, typename tipVrijednosti>
class NizMapa : public Mapa<tipKljuca, tipVrijednosti> {
private:
    std::pair<tipKljuca, tipVrijednosti> *niz;
    int kapacitet;
    int brojElem;
    tipVrijednosti temp;

    void promijeniKapacitet() {
        kapacitet *= 2;
        std::pair<tipKljuca, tipVrijednosti> *tmp = new std::pair<tipKljuca, tipVrijednosti> [kapacitet];

        for(int i = 0; i < brojElem; i++) {
            tmp[i].first = niz[i].first;
            tmp[i].second = niz[i].second;
        }

        delete[] niz;
        niz = tmp;
    }

public:
    NizMapa() : kapacitet(1000), brojElem(0), temp(tipVrijednosti()) {
        niz = new std::pair<tipKljuca, tipVrijednosti>[kapacitet];
    }

    ~NizMapa() {
        delete[] niz;
    }

    tipVrijednosti &operator [](const tipKljuca &kljuc) {
        if(brojElem == kapacitet - 1) promijeniKapacitet();

        for(int i = 0; i < brojElem; i++) {
            if(niz[i].first == kljuc) return niz[i].second;
        }

        // for(int i = 0; i < brojElem; i++) {
        //     if(niz[i].second == "obrisan") {
        //         niz[i] = std::pair<tipKljuca, tipVrijednosti>(kljuc, temp);
        //         brojElem++;
        //         return niz[i].second;
        //     }
        // }
        niz[brojElem] = std::pair<tipKljuca, tipVrijednosti>(kljuc, temp);
        brojElem++;
        return niz[brojElem - 1].second;
    }

    const tipVrijednosti &operator [](const tipKljuca &kljuc) const {
        if(brojElem <= 0) throw ("Nema elemenata u mapi!");

        for(int i = 0; i < brojElem; i++) {
            if(niz[i].first == kljuc) return niz[i].second;
        }

        return temp;
    }

    int brojElemenata() const {
        return brojElem;
    }

    void obrisi() {

        brojElem = 0;
    }

    void obrisi(const tipKljuca& kljuc) {
        if(brojElem <= 0) throw ("Nema elemenata u mapi!");

        // for(int i = 0; i < brojElem; i++) {
        //     if(niz[i].first == kljuc) {
        //         std::pair<std::string, std::string> pom("obrisan", "obrisan");
        //         niz[i] = pom;
        //         brojElem--;
        //     }
        //     return;
        // }
        // throw ("Kljuc ne postoji!");
    }

};

int main() {
    // Osnovni test funkcionalnosti NizMape
NizMapa<std::string,std::string> m;
m["Sarajevo"] = "BiH";
m["Zagreb"] = "Hrvatska";
cout << m.brojElemenata() << " " << m["Zagreb"] << " '"; // 2 Hrvatska

// Test praznih elemenata
cout << m["Beograd"] <<"' '"; // ''
cout << m["zagreb"] << "' "; // ''
m.obrisi("Zagreb");

// Potpuno korektna NizMapa nece kreirati objekte "Beograd" i "zagreb"
// jer oni nemaju vrijednosti pa ce se ispod ispisati 1
// Ali to zahtijeva implementaciju "Pristupnika" pa cemo priznavati
// rjesenje koje ispise broj 3
cout << m.brojElemenata(); // 3 ili 1

// Test brisanja
cout << " '" << m["Zagreb"] << "' " ; // ''
m.obrisi();
cout << m.brojElemenata(); // 0
cout << " '" << m["Sarajevo"] << "' "; // ''
    return 0;
}
