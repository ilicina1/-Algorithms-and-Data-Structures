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
class NizLista : public Lista<nekiTip> {
private:
    nekiTip niz[10000];
    int velicinaNiza;
    int trenutniEl = 0;
public:
    friend class Iterator<nekiTip>;

    //Konstruktor bez parametara => postavlja trenutni element na prvo mjesto;
    NizLista() : velicinaNiza(0) {}
    //Broj elemenata => vraca broj elemenata u listi;
    int brojElemenata() const {
        return velicinaNiza;
    }
    //Trenutni => vraca trenutni element u listi;
    nekiTip &trenutni() {
        return niz[trenutniEl];
    }
    const nekiTip &trenutni() const {
        return niz[trenutniEl];
    }
    //Prethodni => vraca trenutni element za jedno mjesto unazad;
    bool prethodni() {
        if(velicinaNiza == 0) throw ("Prazna lista!");
        if(trenutniEl == 0) return false;
        trenutniEl--;
        return true;
    }
    //Sljedeci => postavlja trenutni element za jedno mjesto naprijed;
    bool sljedeci() {
        if(velicinaNiza == 0) throw ("Prazna lista!");
        if(trenutniEl == velicinaNiza - 1) return false;
        trenutniEl++;
        return true;
    }
    //Pocetak => trenutni element postaje prvi element u listi;
    void pocetak() {
        if(velicinaNiza == 0) throw ("Prazna lista!");
        trenutniEl = 0;
    }
    //Kraj => trenutni element postaje zadnji element u listi;
    void kraj() {
        if(velicinaNiza == 0) throw ("Prazna lista!");
        trenutniEl = velicinaNiza - 1;
    }
    //Obrisi => brise trenutni element u listi;
    void obrisi() {
        if(trenutniEl == velicinaNiza - 1) {
            velicinaNiza--;
            if(velicinaNiza == 0) return;
            trenutniEl--;
        } else {
            for(int i = trenutniEl; i < velicinaNiza; i++) {
                niz[i] = niz[i+1];
            }
            velicinaNiza--;
        }
    }
    //Dodaj ispred => dodaje element ispred trenutnog elementa ili ako je prazan vektor dodaje na pocetku i on postaje trenutni;
    void dodajIspred(const nekiTip& el) {
        if(velicinaNiza == 0) {
            niz[0] = el;
            velicinaNiza++;
            return;
        }
        for(int i = velicinaNiza; i > trenutniEl; i--) niz[i] = niz[i-1];
        niz[trenutniEl] = el;
        trenutniEl++;
        velicinaNiza++;
    }
    //Dodaj iza => dodaje element iza trenutnog elementa ili ako je prazan vektor dodaje na pocetku i on postaje trenutni;
    void dodajIza(const nekiTip& el) {
        if(velicinaNiza == 0) {
            niz[0] = el;
            velicinaNiza++;
            return;
        }
        int mjestoUbacaja = trenutniEl + 1;
        for(int i = velicinaNiza; i > mjestoUbacaja; i--) niz[i] = niz[i-1];
        niz[mjestoUbacaja] = el;
        velicinaNiza++;
    }
    //Preklopljeni operator "[]" omogucuje direktan pristup i-tom elementu;
    nekiTip &operator [](const int clan) {
        if(clan < 0 || clan >= velicinaNiza) throw ("Parametar nije uredu!");
        return niz[clan];
    }
    const nekiTip &operator [](const int clan) const {
        if(clan < 0 || clan >= velicinaNiza) throw ("Parametar nije uredu!");
        return niz[clan];
    }
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
};

template <typename Tip>
class Iterator {
    const NizLista<Tip> *niz;
    const JednostrukaLista<Tip> *lista;
    int trenutniNiz;
    Cvor<Tip> *trenutniLista;
public:
    Iterator(const NizLista<Tip> &l) {
        niz = &l;
        lista = nullptr;
        trenutniNiz = l.trenutniEl;
        trenutniLista = nullptr;
    }

    Iterator(const JednostrukaLista<Tip> &l) {
        lista = &l;
        niz = nullptr;
        trenutniNiz = 0;
        trenutniLista = l.trenutniEl;
    }

    Tip trenutni() const {
        // niz je pa u tom slučaju obavlja operacije za niz:
        if (niz!=0) {
            if(niz->brojElemenata() == 0) throw std::domain_error("Prazna lista");
            return niz->niz[trenutniNiz];
        }

        //U suprotnom slučaju obavlja operacije za listu:
        if(lista->brojElemenata() == 0) throw std::domain_error("Prazna lista");
        return trenutniLista->element;
    }

    bool sljedeci() {
        // niz je pa u tom slučaju obavlja operacije za niz:
        if (niz!=0) {
            if(niz->brojElemenata() == 0) throw std::domain_error("Prazna lista");
            if(niz->velicinaNiza == trenutniNiz - 1) return false;
            trenutniNiz++;
            return true;
        }

        //U suprotnom slučaju obavlja operacije za listu:
        if(lista->brojElemenata() == 0) throw std::domain_error("Prazna lista");
        if(trenutniLista->sljedeci == nullptr) return false;
        trenutniLista = trenutniLista->sljedeci;

        return true;
    }
    
    bool prethodni() {
        // niz je pa u tom slučaju obavlja operacije za niz:
        if (niz!=0) {
            if(niz->brojElemenata() == 0) throw std::domain_error("Prazna lista");
            if(trenutniNiz == 0) return false;
            trenutniNiz--;
            return true;
        }

        //U suprotnom slučaju obavlja operacije za listu:
        if(lista->brojElemenata() == 0) throw std::domain_error("Prazna lista");
        if(trenutniLista == lista->prvi) return false;
        Cvor<Tip> *pom = lista->prvi;
        while(pom->sljedeci != lista->trenutniEl) pom = pom->sljedeci;
        trenutniLista = pom;
        delete pom;
        return true;
    }
    
    void pocetak() {
        // niz je pa u tom slučaju obavlja operacije za niz:
        if (niz!=0) {
            if(niz->brojElemenata() == 0) throw std::domain_error("Prazna lista");
            trenutniNiz = 0;
            return;
        }

        if(lista->brojElemenata() == 0) throw std::domain_error("Prazna lista");
        trenutniLista = lista->prvi;
    }
};



template<typename nekiTip>
nekiTip dajMaksimum(const NizLista<nekiTip>& n) {
    Iterator<nekiTip> it(n);
    
    it.pocetak();
    
    nekiTip max_el = it.trenutni();
    
    for(int i(0); i < n.brojElemenata(); i++){
        if(it.trenutni() > max_el) max_el = it.trenutni();
        it.sljedeci();
    }
    
    return max_el;
}

template<typename nekiTip>
nekiTip dajMaksimum(const JednostrukaLista<nekiTip>& n) {
    Iterator<nekiTip> it(n);
    
    it.pocetak();
    
    nekiTip max_el = it.trenutni();
    
    for(int i(0); i < n.brojElemenata(); i++){
        if(it.trenutni() > max_el) max_el = it.trenutni();
        it.sljedeci();
    }
    
    return max_el;
}

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

    std::cout << dajMaksimum(l);
}
