#include <iostream>

/*
    dodati meetodu u listi koja premjesta elemente iz intervala od n do m na poziciju k:
*/

template <typename nekiTip>
class Lista {
public:
    //Konstruktor bez parametara => postavlja trenutni element na prvo mjesto;
    Lista() {}
    //Destruktor;
    virtual ~Lista() {}
    //Broj elemenata => vraca broj elemenata u listi;
    virtual int brojElemenata() const = 0;
    //Trenutni => vraca trenutni element u listi;
    virtual const nekiTip &trenutni() const = 0;
    //Prethodni => vraca trenutni element za jedno mjesto unazad;
    virtual bool prethodni() = 0;
    //Sljedeci => postavlja trenutni element za jedno mjesto naprijed;
    virtual bool sljedeci() = 0;
    //Pocetak => trenutni element postaje prvi element u listi;
    virtual void pocetak() = 0;
    //Kraj => trenutni element postaje zadnji element u listi;
    virtual void kraj() = 0;
    //Obrisi => brise trenutni element u listi;
    virtual void obrisi() = 0;
    //Dodaj ispred => dodaje element ispred trenutnog elementa ili ako je prazan vektor dodaje na pocetku i on postaje trenutni;
    virtual void dodajIspred(const nekiTip& el) = 0;
    //Dodaj iza => dodaje element iza trenutnog elementa ili ako je prazan vektor dodaje na pocetku i on postaje trenutni;
    virtual void dodajIza(const nekiTip& el) = 0;
    //Preklopljeni operator "[]" omogucuje direktan pristup i-tom elementu;
    virtual nekiTip &operator [](const int clan) = 0;
};

template <typename nekiTip>
class JednostrukaLista : public Lista<nekiTip> {
private:
    struct Cvor {
        nekiTip element;
        Cvor *sljedeci;
    };
    Cvor *prvi, *trenutniEl;
    int velicinaListe;
public:
    //Konstruktor bez parametara => postavlja trenutni element na prvo mjesto;
    JednostrukaLista() : prvi(0), trenutniEl(0), velicinaListe(0) {}
    ~JednostrukaLista() {
        while(prvi != nullptr) {
            trenutniEl = prvi;
            prvi = prvi->sljedeci;
            delete trenutniEl;
        }
        prvi = nullptr;
        trenutniEl = nullptr;
    }

    //Broj elemenata => vraca broj elemenata u listi;
    int brojElemenata() const {
        return velicinaListe;
    }

    //Trenutni => vraca trenutni element u listi;
    nekiTip &trenutni() {
        return trenutniEl->element;
    }
    const nekiTip &trenutni() const {
        return trenutniEl->element;
    }

    void promijeniTrenutni(Cvor *c) {
        trenutniEl = c;
    }

    //Prethodni => vraca trenutni element za jedno mjesto unazad;
    bool prethodni() {
        if(velicinaListe == 0) throw ("Prazna lista!");
        if(trenutniEl == prvi) return false;
        Cvor *i;
        for(i = prvi; i->sljedeci != trenutniEl; i=i->sljedeci) {}
        if(i->sljedeci == trenutniEl) {
            trenutniEl = i;
        }
        return true;
    }

    //Sljedeci => postavlja trenutni element za jedno mjesto naprijed;
    bool sljedeci() {
        if(velicinaListe == 0) throw ("Prazna lista!");
        if(trenutniEl->sljedeci == nullptr) return false;
        trenutniEl = trenutniEl->sljedeci;
        return true;
    }

    //Pocetak => trenutni element postaje prvi element u listi;
    void pocetak() {
        if(velicinaListe == 0) throw ("Prazna lista!");
        trenutniEl = prvi;
    }


    //Kraj => trenutni element postaje zadnji element u listi;
    void kraj() {
        if(velicinaListe == 0) throw ("Prazna lista!");
        for(trenutniEl = trenutniEl; trenutniEl->sljedeci != nullptr; trenutniEl=trenutniEl->sljedeci) {}
    }

    //Obrisi => brise trenutni element u listi;
    void obrisi() {
        if(velicinaListe == 0)  throw ("Nema se sta izbaciti!");
        if(prvi->sljedeci == nullptr) {
            delete prvi;
            prvi = nullptr;
            velicinaListe--;
            return;
        }
        if(trenutniEl->sljedeci == nullptr) {
            velicinaListe--;
            Cvor *i;
            for(i = prvi; i->sljedeci != trenutniEl; i=i->sljedeci) {}
            if(i->sljedeci == trenutniEl) {
                trenutniEl = i;
            }
            return;
        } else {
            Cvor *i;
            if(prvi != trenutniEl) {
                for(i = prvi; i->sljedeci != trenutniEl; i=i->sljedeci) {}
                if(i->sljedeci == trenutniEl) {
                    trenutniEl = trenutniEl->sljedeci;
                    delete i->sljedeci;
                    i->sljedeci = trenutniEl;
                }
            }
            velicinaListe--;
        }
    }

    // obrisi elemente koji se nalaze izmedju elemenata A i B;
    // pretpostavljamo da se elementi a i b nalaze samo jednom u listi;
    void obrisiOdAdoB(nekiTip a, nekiTip b) {
        if(velicinaListe == 0) throw ("Prazna lista!");
        Cvor *pom;
        pom = prvi;

        while(pom->sljedeci != nullptr) {
            if(pom->element == a || pom->element == b) break;

            pom = pom->sljedeci;
        }


        if(pom->element == a) {
            Cvor *elA;
            elA = pom;
            pom = pom->sljedeci;

            while(pom->element != b) {
                Cvor *i = pom;
                for(i = prvi; i->sljedeci != pom; i=i->sljedeci) {}

                if(pom == trenutniEl) {
                    trenutniEl = elA;
                    i->sljedeci = pom->sljedeci;
                    delete pom;
                    pom = i;
                } else {
                    i->sljedeci = pom->sljedeci;
                    delete pom;
                    pom = i;
                }

                pom = pom->sljedeci;
                velicinaListe--;
            }
        } else if(pom->element == b) {
            Cvor *elB;
            elB = pom;
            pom = pom->sljedeci;

            while(pom->element != a) {
                Cvor *i;
                i = pom;
                for(i = prvi; i->sljedeci != pom; i=i->sljedeci) {}

                if(pom == trenutniEl) {
                    trenutniEl = elB;
                    i->sljedeci = pom->sljedeci;
                    delete pom;
                    pom = i;
                } else {
                    i->sljedeci = pom->sljedeci;
                    delete pom;
                    pom = i;
                }

                pom = pom->sljedeci;
                velicinaListe--;
            }
        } else
            throw ("Elementi ne postoje!");
    }

    //Dodaj ispred => dodaje element ispred trenutnog elementa ili ako je prazan vektor dodaje na pocetku i on postaje trenutni;
    void dodajIspred(const nekiTip& el) {
        Cvor *novi = new Cvor {el, nullptr}; // Kreiranje novog čvora
        if(!prvi) {
            prvi = novi;
            trenutniEl = prvi;
            velicinaListe++;
            return;
        } else {
            Cvor *i;
            if(prvi == trenutniEl) {
                prvi = novi;
                prvi->sljedeci = trenutniEl;
                velicinaListe++;
            } else {
                velicinaListe++;
                for(i = prvi; i->sljedeci != trenutniEl; i=i->sljedeci) {}
                if(i->sljedeci == trenutniEl) {
                    i->sljedeci = novi;
                    novi->sljedeci = trenutniEl;
                }
            }
        }
    }

    //Dodaj iza => dodaje element iza trenutnog elementa ili ako je prazan vektor dodaje na pocetku i on postaje trenutni;
    void dodajIza(const nekiTip& el) {
        Cvor *novi = new Cvor {el, nullptr}; // Kreiranje novog čvora
        if(!prvi) {
            prvi = novi;
            trenutniEl = prvi;
            velicinaListe++;
            return;
        } else {
            velicinaListe++;
            novi->sljedeci = trenutniEl->sljedeci;
            trenutniEl->sljedeci = novi;
        }
    }


    //Preklopljeni operator "[]" omogucuje direktan pristup i-tom elementu;
    nekiTip &operator [](const int clan) {
        if(clan < 0 || clan >= velicinaListe) throw ("Parametar nije uredu!");
        int i = 0;
        Cvor *pom = prvi;
        while(i != clan) {
            pom = pom->sljedeci;
            i++;
        }
        return pom->element;
    }

    const nekiTip &operator [](const int clan) const {
        if(clan < 0 || clan >= velicinaListe) throw ("Parametar nije uredu!");
        int i = 0;
        Cvor *pom = prvi;
        while(i != clan) {
            pom = pom->sljedeci;
            i++;
        }
        return pom->element;
    }

    void PremjestiSaMax(int n, int m, int k) {
        Cvor *pom;
        pom = prvi;
        int brojacIndeksa = 0, brojacPomIndeksa = 0, brojacIzbacenih = 0;

        while(pom != nullptr) {
            Cvor *pomPovratak;
            pomPovratak = pom;
            if(brojacIndeksa == n) {
                brojacPomIndeksa = brojacIndeksa;


                while(brojacPomIndeksa != k) {
                    Cvor *i;
                    for(i = prvi; i->sljedeci != pom; i = i->sljedeci) {}

                    i->sljedeci = pom->sljedeci;
                    i = pom->sljedeci;

                    pom->sljedeci = i->sljedeci;
                    i->sljedeci = pom;

                    brojacPomIndeksa++;
                }
            }

            brojacIndeksa++;
            pom = pom->sljedeci;
        }

        if(n != m) PremjestiSaMax(n, m-1, k);
    }
};


int main() {
    JednostrukaLista<int> l;

    for(int i = 1; i < 10; i++) {
        l.dodajIza(i);
        l.sljedeci();
    }

    l.pocetak();

    l.PremjestiSaMax(2, 4, 6);

    for(int i = 0; i < l.brojElemenata(); i++) {
        std::cout << l.trenutni() << " ";
        l.sljedeci();
    }
}
