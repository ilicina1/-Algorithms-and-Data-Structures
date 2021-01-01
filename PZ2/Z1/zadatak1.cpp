#include <iostream>

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


void testMetodaZaObjeKlase()  {
    NizLista<int> nekaLista;
    //Primjer rada sa klasom NizLista;
    //---------------------------------
    std::cout << "Primjer rada sa klasom NizLista" << std::endl << "---------------------------------" << std::endl;
    //Ubacujemo elemente u liste;
    //Nakon prvog ubacivanja niz treba izgledati ovako {1};
    nekaLista.dodajIspred(1);
    //Nakon drugog ubacivanja niz treba izgledati ovako {2, 1};
    nekaLista.dodajIspred(2);
    //Nakon treceg ubacivanja niz treba izgledati ovako {2, 1, 4};
    nekaLista.dodajIza(4);
    //Nakon cetvrtog ubacivanja niz treba izgledati ovako {2, 1, 5, 4};
    nekaLista.dodajIza(5);
    //Nakon petog ubacivanja niz treba izgledati ovako {2, 1, 6, 5, 4};
    nekaLista.dodajIza(6);

    //Nakon ubacivanja lista izgleda ovako: {2, 1, 6, 5, 4};
    nekaLista.pocetak();
    std::cout << "Elementi liste glase: {";
    for(int i = 0; i < nekaLista.brojElemenata(); i++) {
        if(i == nekaLista.brojElemenata() - 1) std::cout << nekaLista.trenutni() << "}" << std::endl;
        else
            std::cout << nekaLista.trenutni() << ", ";
        nekaLista.sljedeci();
    }
    //Vracamo trenutni element na broj 1;
    nekaLista.prethodni();
    nekaLista.prethodni();
    nekaLista.prethodni();
    //pocinjemo testiranje metoda;
    nekaLista.sljedeci();
    //Nakon metode "sljedeci()" trenutni element treba biti 6;
    std::cout << "Trenutni element nakon metode 'sljedeci()' je: " << nekaLista.trenutni() << std::endl;
    nekaLista.prethodni();
    //Nakon metode "prethodni()" trenutni element treba biti 1;
    std::cout << "Trenutni element nakon metode 'prethodni()' je: " << nekaLista.trenutni() << std::endl;
    nekaLista.pocetak();
    //Nakon metode "pocetak()" trenutni element treba biti 2;
    std::cout << "Trenutni element nakon metode 'pocetak' je: " << nekaLista.trenutni() << std::endl;
    nekaLista.kraj();
    //Nakon metode "kraj()" trenutni element treba biti 4;
    std::cout << "Trenutni element nakon metode 'kraj' je: " << nekaLista.trenutni() << std::endl;
    //Broj elemenata treba biti 5 s obzirom da su elementi u listi: {2, 1, 6, 5, 4};
    std::cout << "Broj elemenata u listi je: " << nekaLista.brojElemenata() << std::endl;
    //Brisemo trenutni element => trenutni element je posljednji element u listi i nakon brisanja trenutni bi trebao biti broj 5;
    nekaLista.obrisi();
    std::cout << "Broj elemenata u listi nakon brisanja je: " << nekaLista.brojElemenata() << std::endl;
    std::cout << "Trenutni element nakon brisanja trenutnog elementa je: " << nekaLista.trenutni() << std::endl;
    //Citamo element indeksiranjem => treci element treba biti broj 6;
    std::cout << "Treci element u listi je: " << nekaLista[2] << std::endl;
    //Izmjena ideksiranog elementa => mijenjamo treci element sa broja 6 na broj 9;
    nekaLista[2] = 9;
    std::cout << "Treci element u listi nakon izmjene je: " << nekaLista[2] << std::endl;

    JednostrukaLista<int> jednostrukaLista;
    //Primjer rada sa klasom NizLista;
    //---------------------------------
    std::cout << std::endl << "Primjer rada sa klasom JednostrukaLista" << std::endl << "-----------------------------------------" << std::endl;
    //Ubacujemo elemente u liste;
    //Nakon prvog ubacivanja niz treba izgledati ovako {1};
    jednostrukaLista.dodajIspred(1);
    //Nakon drugog ubacivanja niz treba izgledati ovako {2, 1};
    jednostrukaLista.dodajIspred(2);
    //Nakon treceg ubacivanja niz treba izgledati ovako {2, 1, 4};
    jednostrukaLista.dodajIza(4);
    //Nakon cetvrtog ubacivanja niz treba izgledati ovako {2, 1, 5, 4};
    jednostrukaLista.dodajIza(5);
    //Nakon petog ubacivanja niz treba izgledati ovako {2, 1, 6, 5, 4};
    jednostrukaLista.dodajIza(6);

    //Nakon ubacivanja lista izgleda ovako: {2, 1, 6, 5, 4};
    jednostrukaLista.pocetak();
    std::cout << "Elementi liste glase: {";
    for(int i = 0; i < jednostrukaLista.brojElemenata(); i++) {
        if(i == jednostrukaLista.brojElemenata() - 1) std::cout << jednostrukaLista.trenutni() << "}" << std::endl;
        else
            std::cout << jednostrukaLista.trenutni() << ", ";
        jednostrukaLista.sljedeci();
    }
    //Vracamo trenutni element na broj 1;
    jednostrukaLista.prethodni();
    jednostrukaLista.prethodni();
    jednostrukaLista.prethodni();
    //pocinjemo testiranje metoda;
    jednostrukaLista.sljedeci();
    //Nakon metode "sljedeci()" trenutni element treba biti 6;
    std::cout << "Trenutni element nakon metode 'sljedeci()' je: " << jednostrukaLista.trenutni() << std::endl;
    jednostrukaLista.prethodni();
    //Nakon metode "prethodni()" trenutni element treba biti 1;
    std::cout << "Trenutni element nakon metode 'prethodni()' je: " << jednostrukaLista.trenutni() << std::endl;
    jednostrukaLista.pocetak();
    //Nakon metode "pocetak()" trenutni element treba biti 2;
    std::cout << "Trenutni element nakon metode 'pocetak' je: " << jednostrukaLista.trenutni() << std::endl;
    jednostrukaLista.kraj();
    //Nakon metode "kraj()" trenutni element treba biti 4;
    std::cout << "Trenutni element nakon metode 'kraj' je: " << jednostrukaLista.trenutni() << std::endl;
    //Broj elemenata treba biti 5 s obzirom da su elementi u listi: {2, 1, 6, 5, 4};
    std::cout << "Broj elemenata u listi je: " << jednostrukaLista.brojElemenata() << std::endl;
    //Brisemo trenutni element => trenutni element je posljednji element u listi i nakon brisanja trenutni bi trebao biti broj 5;
    jednostrukaLista.obrisi();
    std::cout << "Broj elemenata u listi nakon brisanja je: " << jednostrukaLista.brojElemenata() << std::endl;
    std::cout << "Trenutni element nakon brisanja trenutnog elementa je: " << jednostrukaLista.trenutni() << std::endl;
    //Citamo element indeksiranjem => treci element treba biti broj 6;
    std::cout << "Treci element u listi je: " << jednostrukaLista[2] << std::endl;
    //Izmjena ideksiranog elementa => mijenjamo treci element sa broja 6 na broj 9;
    jednostrukaLista[2] = 9;
    std::cout << "Treci element u listi nakon izmjene je: " << jednostrukaLista[2] << std::endl;
}

int main() {
    testMetodaZaObjeKlase();    testMetodaZaObjeKlase();
}
