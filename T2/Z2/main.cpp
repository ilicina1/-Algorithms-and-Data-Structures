#include <iostream>

using namespace std;

template <typename Tip>
class Iterator; // Predefinisana klasa iterator template <typename Tip>

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
struct Cvor {
    nekiTip element;
    Cvor *sljedeci;
};

template <typename nekiTip>
class JednostrukaLista : public Lista<nekiTip> {
private:
    Cvor<nekiTip> *prvi, *trenutniEl;
    int velicinaListe;
public:
    friend class Iterator<nekiTip>;

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

    void promijeniTrenutni(Cvor<nekiTip> *c) {
        trenutniEl = c;
    }

    //Prethodni => vraca trenutni element za jedno mjesto unazad;
    bool prethodni() {
        if(velicinaListe == 0) throw ("Prazna lista!");
        if(trenutniEl == prvi) return false;
        Cvor<nekiTip> *i;
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
            Cvor<nekiTip> *i;
            for(i = prvi; i->sljedeci != trenutniEl; i=i->sljedeci) {}
            if(i->sljedeci == trenutniEl) {
                trenutniEl = i;
            }
            return;
        } else {
            Cvor<nekiTip> *i;
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

    //Dodaj ispred => dodaje element ispred trenutnog elementa ili ako je prazan vektor dodaje na pocetku i on postaje trenutni;
    void dodajIspred(const nekiTip& el) {
        Cvor<nekiTip> *novi = new Cvor<nekiTip> {el, nullptr}; // Kreiranje novog čvora
        if(!prvi) {
            prvi = novi;
            trenutniEl = prvi;
            velicinaListe++;
            return;
        } else {
            Cvor<nekiTip> *i;
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
        Cvor<nekiTip> *novi = new Cvor<nekiTip> {el, nullptr}; // Kreiranje novog čvora
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
        Cvor<nekiTip> *pom = prvi;
        while(i != clan) {
            pom = pom->sljedeci;
            i++;
        }
        return pom->element;
    }

    const nekiTip &operator [](const int clan) const {
        if(clan < 0 || clan >= velicinaListe) throw ("Parametar nije uredu!");
        int i = 0;
        Cvor<nekiTip> *pom = prvi;
        while(i != clan) {
            pom = pom->sljedeci;
            i++;
        }
        return pom->element;
    }

    void izbaciSvakiNTi(int n) {
        if(velicinaListe == 0)  throw std::domain_error("Nema se sta izbaciti!");
        int brElem = this->brojElemenata();
        if(n == 1) {
            for (int i(1); i<=brElem; i++)
                this->obrisi();
            return;
        }
        Cvor<nekiTip> *pom = prvi;
        int brojac = 1;
        for(int i = 0; i < brElem; i++) {
            if(brojac == n) {
                if(pom->sljedeci == nullptr && prvi == pom) {
                    delete prvi;
                    prvi = nullptr;
                    velicinaListe--;
                    brojac = 1;
                    continue;
                    return;
                }
                if(pom == trenutniEl && pom->sljedeci != nullptr) {
                    velicinaListe--;
                    Cvor<nekiTip> *i;
                    for(i = prvi; i->sljedeci != pom; i=i->sljedeci) {}
                    trenutniEl = i;
                    i->sljedeci = pom->sljedeci;
                    i = i->sljedeci;
                    pom = pom->sljedeci;
                    delete i;
                    brojac = 1;
                    continue;
                } else if(pom->sljedeci == nullptr) { //23 111 222 33 1141 251 33 1 2
                    velicinaListe--;
                    Cvor<nekiTip> *i;
                    for(i = prvi; i->sljedeci != pom; i=i->sljedeci) {}
                    if(i->sljedeci == pom) {
                        pom = i;
                        i = i->sljedeci;
                        delete i;
                    }
                    brojac = 1;
                    continue;
                } else {
                    Cvor<nekiTip> *i;
                    for(i = prvi; i->sljedeci != pom; i=i->sljedeci) {}
                    if(i->sljedeci == pom) {
                        i->sljedeci = pom->sljedeci;
                        i = pom;
                        pom = pom->sljedeci;
                        i->sljedeci = nullptr;
                        delete i;
                    }
                    velicinaListe--;
                    brojac = 1;
                    continue;
                }
            }

            pom = pom->sljedeci;
            brojac++;
        }
        delete pom;
    }

    void ispisi() {
        Cvor<nekiTip> *pom = prvi;
        for(int i = 0; i < this->brojElemenata(); i++) {
            std::cout << pom->element << std::endl;
            pom = pom->sljedeci;
        }
    }
};

int main() {
    JednostrukaLista<int> l;
    l.dodajIspred(2);
    l.dodajIspred(23);
    l.dodajIspred(111);
    l.dodajIspred(222);
    l.dodajIspred(33);
    l.dodajIspred(1141);
    l.dodajIspred(251);
    l.dodajIspred(33);
    l.dodajIspred(1);

    l.izbaciSvakiNTi(2);    //23 111 222 33 1141 251 33 1 2

    l.ispisi();

    //  std::cout << l.brojElemenata();
}
