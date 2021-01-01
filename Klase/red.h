#define RED_H
//#include "cvorOstali.h"

template <typename nekiTip>
class Red {
private:
    struct Cvor {
        nekiTip element;
        Cvor *sljedeci;
        Cvor (const nekiTip &element, Cvor *sljedeci) : element(element), sljedeci(sljedeci) {}
    };
    Cvor *pocetak;
    Cvor *kraj;
    int velicina;
    void Unisti() {
        while(!JeLiPrazan ())
            skini ();
    }
    void Kopiraj (const Red &q) {
        Cvor *p(q.pocetak);
        while(p != nullptr) {
            stavi(p->element);
            p = p->sljedeci;
        }
        velicina = q.velicina;
    }
public:
    Red() : pocetak(nullptr), kraj(nullptr), velicina(0) {}
    Red(const Red &q) : pocetak(nullptr), kraj(nullptr), velicina(0) {
        Kopiraj(q);
    }
    ~Red() {
        Unisti();
    }
    Red &operator = (const Red &q) {
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
    void brisi() {
        Unisti();
    }
    void stavi (const nekiTip &info) {
        Cvor *n = new Cvor {info, nullptr};
        if (pocetak == nullptr) {
            pocetak = n;
            kraj = n;
        } else {
            kraj->sljedeci = n;
            kraj = kraj->sljedeci;
        }
        velicina++;
    }
    nekiTip skini() {
        if (pocetak == nullptr)
            throw "\nRed je prazan!\n";
        nekiTip info(pocetak->element);
        Cvor *p = pocetak;
        if (pocetak == kraj)
            pocetak = kraj = nullptr;
        else
            pocetak = pocetak->sljedeci;
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
        Cvor *p(pocetak);
        while (p != nullptr) {
            std::cout << p->element << std::endl;
            p = p->sljedeci;
        }
    }
    
    void PrikaziStekove() const {
        Cvor *p(pocetak);
        while (p != nullptr) {
            p->element.Prikazi();
            p = p->sljedeci;
        }
    }
};
