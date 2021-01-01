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
    Cvor *sljedeci, *prethodni;
};

template <typename nekiTip>
class DvostrukaLista : public Lista<nekiTip> {
private:
    Cvor<nekiTip> *prvi, *trenutniEl, *krajj;
    int velicinaListe;
public:
    //Konstruktor klase;
    DvostrukaLista() : prvi(0), trenutniEl(0), krajj(0), velicinaListe(0) {}
    DvostrukaLista &operator =(const DvostrukaLista &dvostruka) {
        if (&dvostruka==this) {
            return *this;
        }
        Cvor<nekiTip> *p(dvostruka.prvi);
        while(p != nullptr) {
            dodaj(p->element);
            p=p->sljedeci;
        }
        return *this;
    }
    friend class Iterator<nekiTip>;

    //Destruktor klase
    ~DvostrukaLista() {
        while(prvi!=nullptr) {
            trenutniEl = prvi;
            prvi = prvi->sljedeci;
            delete trenutniEl;
        }
        trenutniEl = nullptr;
        velicinaListe = 0;
        krajj = nullptr;
    }

    //Vraca broj elemenata u listi;
    int brojElemenata() const override {
        return velicinaListe;
    }

    //Vraca vrijednost trenutnog elementa;
    nekiTip &trenutni()  {
        return trenutniEl->element;
    }

    const nekiTip &trenutni() const  {
        return trenutniEl->element;
    }

    //Prethodni => vraca trenutni element za jedno mjesto unazad;
    bool prethodni() override {
        if(velicinaListe == 0) throw ("Prazna lista!");
        if(trenutniEl == prvi) return false;
        trenutniEl = trenutniEl->prethodni;
        return true;
    }

    //Sljedeci => postavlja trenutni element za jedno mjesto naprijed;
    bool sljedeci() override {
        if(velicinaListe == 0) throw ("Prazna lista!");
        if(trenutniEl->sljedeci == nullptr) return false;
        trenutniEl = trenutniEl->sljedeci;
        return true;
    }

    //Pocetak => trenutni element postaje prvi element u listi;
    void pocetak() override {
        if(velicinaListe == 0) throw ("Prazna lista!");
        trenutniEl = prvi;
    }

    //Kraj => trenutni element postaje zadnji element u listi;
    void kraj() override {
        if(velicinaListe == 0) throw ("Prazna lista!");
        trenutniEl = krajj;
        for(trenutniEl = trenutniEl; trenutniEl->sljedeci != nullptr; trenutniEl=trenutniEl->sljedeci) {}
    }

    //Dodaj ispred => dodaje element ispred trenutnog elementa ili ako je prazan vektor dodaje na pocetku i on postaje trenutni;
    void dodajIspred(const nekiTip& el) override {
        Cvor<nekiTip> *novi = new Cvor<nekiTip> {el, nullptr, nullptr}; // Kreiranje novog čvora
        if(!prvi) {
            prvi = novi;
            krajj = novi;
            trenutniEl = prvi;
            velicinaListe++;
        } else {
            if(prvi == trenutniEl) {
                novi->sljedeci = trenutniEl;
                prvi = novi;
                krajj = novi->sljedeci;
                trenutniEl->prethodni = novi;
                velicinaListe++;
            } else {
                if(trenutniEl->sljedeci == nullptr) krajj = trenutniEl;
                novi->sljedeci = trenutniEl;
                novi->prethodni = trenutniEl->prethodni;
                trenutniEl->prethodni->sljedeci = novi;
                trenutniEl->prethodni = novi;
                velicinaListe++;
            }
        }

    }
    //Dodaj iza => dodaje element iza trenutnog elementa ili ako je prazan vektor dodaje na pocetku i on postaje trenutni;
    void dodajIza(const nekiTip& el) override {
        Cvor<nekiTip> *novi = new Cvor<nekiTip> {el, nullptr, nullptr}; // Kreiranje novog čvora
        if(!prvi) {
            prvi = novi;
            krajj = novi;
            trenutniEl = prvi;
            velicinaListe++;
        } else {
            if(trenutniEl->sljedeci == nullptr) {
                novi->sljedeci = nullptr;
                novi->prethodni = trenutniEl;
                krajj = novi;
                trenutniEl->sljedeci = novi;
                velicinaListe++;
            } else {
                novi->sljedeci = trenutniEl->sljedeci;
                novi->prethodni = trenutniEl;
                trenutniEl->sljedeci = novi;
                novi->sljedeci->prethodni = novi;
                velicinaListe++;
            }
        }
    }
    //Brisanje tekuceg elementa:
    void obrisi() override {
        if(velicinaListe == 0) throw ("Nista za izbaciti!");
        Cvor<nekiTip> *pom = trenutniEl;
        if(prvi == trenutniEl) {
            if(prvi->sljedeci != nullptr) {
                prvi = prvi->sljedeci;
                trenutniEl = prvi;
                trenutniEl->prethodni = nullptr;
                delete pom;
            } else {
                prvi = nullptr;
                delete pom;
            }
        } else if(trenutniEl->sljedeci == nullptr) {
            trenutniEl = trenutniEl->prethodni;
            trenutniEl->sljedeci = nullptr;
            pom->prethodni = nullptr;
            delete pom;
        } else {
            trenutniEl = trenutniEl->sljedeci;
            pom->prethodni->sljedeci = trenutniEl;
            trenutniEl->prethodni = pom->prethodni->sljedeci;
            pom->sljedeci = nullptr;
            pom->prethodni = nullptr;
            delete pom;
        }
        velicinaListe--;
    }
    //Idi na poziciju n;
    nekiTip &operator [](const int clan) override {
        if ((clan < 0) || (clan >= velicinaListe)) throw ("Indeks izvan dozvoljenog raspona!\n");
        int i = 0;
        Cvor<nekiTip> *pom = prvi;
        while(i != clan) {
            pom = pom->sljedeci;
            i++;
        }
        return pom->element;
    }
    const nekiTip &operator [](const int clan) const {
        if ((clan < 0) || (clan >= velicinaListe)) throw ("Indeks izvan dozvoljenog raspona!\n");
        int i = 0;
        Cvor<nekiTip> *pom = prvi;
        while(i != clan) {
            pom = pom->sljedeci;
            i++;
        }
        return pom->element;
    }

    bool dodaj(const nekiTip &element) {
        Cvor<nekiTip> *p = new Cvor<nekiTip> {element,nullptr,nullptr};
        if (velicinaListe == 0) {
            prvi = p;
            krajj = p;
        } else
            krajj = krajj->sljedeci = p;
        velicinaListe++;
        return true;
    }
};

template <typename Tip>
class Iterator {
    const DvostrukaLista<Tip> *lista;
    Cvor<Tip> *trenutniLista;
public:
    Iterator(const Lista<Tip> &l) {
        lista = (const DvostrukaLista<Tip>*) &l;
        trenutniLista = lista->prvi;
    }
    Tip trenutni() const {
        if(lista->brojElemenata() == 0) throw ("Prazna lista!");
        return trenutniLista->element;
    }
    bool sljedeci() {
        if(lista->brojElemenata() == 0) throw ("Prazna lista!");
        if(trenutniLista->sljedeci == nullptr) return false;
        trenutniLista = trenutniLista->sljedeci;
        return true;
    }
    bool prethodni() {
        if(lista->brojElemenata() == 0) throw ("Prazna lista!");
        if(trenutniLista->prethodni == nullptr) return false;
        trenutniLista = trenutniLista->prethodni;
        return true;
    }
    void pocetak() {
        if(lista->brojElemenata() == 0) throw ("Prazna lista!");
        trenutniLista = lista->prvi;
    }
};

template<typename Tip>
Tip dajMaksimum(const Lista<Tip>& n) {
    Iterator<Tip> it(n);

    it.pocetak();

    int velicina = n.brojElemenata();

    Tip max_el = n.trenutni();

    for(int i(0) ; i<velicina ; i++) {
        if(it.trenutni() > max_el) {
            max_el = it.trenutni();
        }
        it.sljedeci();
    }

    return max_el;
}

void testMetoda() {

    DvostrukaLista<int> dvostruka;
    //Primjer rada sa klasom NizLista;
    //---------------------------------
    std::cout << std::endl << "Primjer rada sa klasom DvostrukaLista" << std::endl << "-----------------------------------------" << std::endl;
    //Ubacujemo elemente u liste;
    //Nakon prvog ubacivanja niz treba izgledati ovako {1};
    dvostruka.dodajIspred(1);
    //Nakon drugog ubacivanja niz treba izgledati ovako {2, 1};
    dvostruka.dodajIspred(2);
    //Nakon treceg ubacivanja niz treba izgledati ovako {2, 1, 4};
    dvostruka.dodajIza(4);
    //Nakon cetvrtog ubacivanja niz treba izgledati ovako {2, 1, 5, 4};
    dvostruka.dodajIza(5);
    //Nakon petog ubacivanja niz treba izgledati ovako {2, 1, 6, 5, 4};
    dvostruka.dodajIza(6);

    //Nakon ubacivanja lista izgleda ovako: {2, 1, 6, 5, 4};
    dvostruka.pocetak();
    std::cout << "Elementi liste glase: {";
    for(int i = 0; i < dvostruka.brojElemenata(); i++) {
        if(i == dvostruka.brojElemenata() - 1) std::cout << dvostruka.trenutni() << "}" << std::endl;
        else
            std::cout << dvostruka.trenutni() << ", ";
        dvostruka.sljedeci();
    }
    //Vracamo trenutni element na broj 1;
    dvostruka.prethodni();
    dvostruka.prethodni();
    dvostruka.prethodni();
    //pocinjemo testiranje metoda;
    dvostruka.sljedeci();
    //Nakon metode "sljedeci()" trenutni element treba biti 6;
    std::cout << "Trenutni element nakon metode 'sljedeci()' je: " << dvostruka.trenutni() << std::endl;
    dvostruka.prethodni();
    //Nakon metode "prethodni()" trenutni element treba biti 1;
    std::cout << "Trenutni element nakon metode 'prethodni()' je: " << dvostruka.trenutni() << std::endl;
    dvostruka.pocetak();
    //Nakon metode "pocetak()" trenutni element treba biti 2;
    std::cout << "Trenutni element nakon metode 'pocetak' je: " << dvostruka.trenutni() << std::endl;
    dvostruka.kraj();
    //Nakon metode "kraj()" trenutni element treba biti 4;
    std::cout << "Trenutni element nakon metode 'kraj' je: " << dvostruka.trenutni() << std::endl;
    //Broj elemenata treba biti 5 s obzirom da su elementi u listi: {2, 1, 6, 5, 4};
    std::cout << "Broj elemenata u listi je: " << dvostruka.brojElemenata() << std::endl;
    //Brisemo trenutni element => trenutni element je posljednji element u listi i nakon brisanja trenutni bi trebao biti broj 5;
    dvostruka.obrisi();
    std::cout << "Broj elemenata u listi nakon brisanja je: " << dvostruka.brojElemenata() << std::endl;
    std::cout << "Trenutni element nakon brisanja trenutnog elementa je: " << dvostruka.trenutni() << std::endl;
    //Citamo element indeksiranjem => treci element treba biti broj 6;
    std::cout << "Treci element u listi je: " << dvostruka[2] << std::endl;
    //Izmjena ideksiranog elementa => mijenjamo treci element sa broja 6 na broj 9;
    dvostruka[2] = 9;
    std::cout << "Treci element u listi nakon izmjene je: " << dvostruka[2] << std::endl;
}

int main() {
    testMetoda();
}