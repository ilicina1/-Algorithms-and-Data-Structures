#include <iostream>

using namespace std;

template <typename nekiTip>
struct Cvor {
    nekiTip element;
    Cvor *sljedeci, *prethodni;
    Cvor (const nekiTip &element, Cvor *sljedeci, Cvor *prethodni) : element(element), sljedeci(sljedeci), prethodni(prethodni) {}
};

template <typename nekiTip>
class DvostraniRed {
private:
    Cvor<nekiTip> *pocetak;
    Cvor<nekiTip> *kraj;
    int velicina;
    void Unisti() {
        while(!JeLiPrazan ())
            skiniSaCela ();
    }
    void Kopiraj (const DvostraniRed &q) {
        Cvor<nekiTip> *p(q.pocetak);
        while(p != nullptr) {
            staviNaVrh(p->element);
            p = p->sljedeci;
        }
        velicina = q.velicina;
    }
public:
    DvostraniRed() : pocetak(nullptr), kraj(nullptr), velicina(0) {}
    DvostraniRed(const DvostraniRed &q) : pocetak(nullptr), kraj(nullptr), velicina(0) {
        Kopiraj(q);
    }
    ~DvostraniRed() {
        Unisti();
    }

    DvostraniRed &operator = (const DvostraniRed &q) {
        if (&q == this)
            return *this;
        Unisti();
        Kopiraj(q);
        return *this;
    }

    const nekiTip& celo() const {
        if (pocetak == nullptr)
            throw "Red je prazan!\n";
        return pocetak->element;
    }

    nekiTip& celo()  {
        if (pocetak == nullptr)
            throw "Red je prazan!\n";
        return pocetak->element;
    }

    const nekiTip& vrh() const {
        if (pocetak == nullptr)
            throw "Red je prazan!\n";
        return kraj->element;
    }

    nekiTip& vrh()  {
        if (pocetak == nullptr)
            throw "Red je prazan!\n";
        return kraj->element;
    }

    void brisi() {
        Unisti();
    }

    void staviNaVrh (const nekiTip &info) {
        Cvor<nekiTip> *n = new Cvor<nekiTip> {info, nullptr, nullptr};
        if (pocetak == nullptr) {
            pocetak = n;
            kraj = n;
        } else {
            kraj->sljedeci = n;
            n->prethodni = kraj;
            kraj = kraj->sljedeci;
        }
        velicina++;
    }

    nekiTip skiniSaCela() {
        if (pocetak == nullptr)
            throw "\nRed je prazan!\n";
        nekiTip info(pocetak->element);
        Cvor<nekiTip> *p = pocetak;
        if (pocetak == kraj)
            pocetak = kraj = nullptr;
        else
            pocetak = pocetak->sljedeci;
        p->sljedeci = nullptr;
        delete p;
        velicina--;
        return info;
    }

    void staviNaCelo (const nekiTip &info) {
        Cvor<nekiTip> *n = new Cvor<nekiTip> {info, nullptr, nullptr};
        if(pocetak == nullptr) {
            pocetak = n;
            kraj = n;
        } else {
            n->sljedeci = pocetak;
            pocetak->prethodni = n;
            pocetak = pocetak->prethodni;
        }
        velicina++;
    }

    nekiTip skiniSaVrha() {
        if (kraj == nullptr)
            throw "\nRed je prazan!\n";
        nekiTip info(kraj->element);
        Cvor<nekiTip> *p = kraj;
        if (pocetak == kraj)
            pocetak = kraj = nullptr;
        else
            kraj = kraj->prethodni;
        p->prethodni = nullptr;
        delete p;
        velicina--;
        return info;
    }


    bool JeLiPrazan() const {
        return pocetak == 0;
    }

    int brojElemenata() const {
        return velicina;
    }

    void Prikazi() const {
        Cvor<nekiTip> *p(pocetak);
        while (p != nullptr) {
            std::cout << p->element << " ";
            p = p->sljedeci;
        }
        std::cout << std::endl;
    }
};

void testMetoda() {
    DvostraniRed<int> r1;
    for(int i = 1; i <= 10; i++)
        r1.staviNaVrh(i);
    for(int i = 11; i <= 20; i++)
        r1.staviNaCelo(i);

    std::cout << "Sadrzaj prvog reda: " << std::endl;
    r1.Prikazi();
    std::cout << std::endl;

    DvostraniRed<int> r2(r1);
    std::cout << "Sadrzaj kopirajuceg reda: " << std::endl;
    r2.Prikazi();
    std::cout << std::endl;

    DvostraniRed<int> r3(r1);
    std::cout << "Sadrzaj reda dobijenim pomocu operatora dodjele: " << std::endl;
    r3.Prikazi();
    std::cout << std::endl;

    r1.skiniSaCela();
    r1.skiniSaVrha();
    // std::cout << "Sadrzaj nakon skidanja elementa iz prvog steka ne bi trebao sadrzavati broj 20 na celu i 10 na vrhu: " << std::endl;
    r1.Prikazi();
    std::cout << std::endl;

    std::cout << "Novo celo nakon skidanja elementa je: " << std::endl << r1.celo() << std::endl;
    std::cout << std::endl;
    std::cout << "Novi vrh nakon skidanja elementa je: " << std::endl << r1.vrh() << std::endl;
    std::cout << std::endl;

    std::cout << "Broj elemenata ovog reda je: " << std::endl << r1.brojElemenata() << std::endl;
    std::cout << std::endl;

    r1.brisi();
    std::cout << "Bro elemenata nakon brisanja svih elemenata je: " << std::endl << r1.brojElemenata();
}


int main() {
    testMetoda();
    return 0;
}
