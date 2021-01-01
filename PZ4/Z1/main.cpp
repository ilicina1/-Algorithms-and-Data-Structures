#include <iostream>

using namespace std;
    
template <typename nekiTip>
struct Cvor {
    nekiTip element;
    Cvor *sljedeci;
    Cvor (const nekiTip &element, Cvor *sljedeci) : element(element), sljedeci(sljedeci) {}
};

template <typename nekiTip>
class Red {
private:
    Cvor<nekiTip> *pocetak;
    Cvor<nekiTip> *kraj;
    int velicina;
    void Unisti() {
        while(!JeLiPrazan ())
            skini ();
    }
    void Kopiraj (const Red &q) {
        Cvor<nekiTip> *p(q.pocetak);
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
        Cvor<nekiTip> *n = new Cvor<nekiTip> {info, nullptr};
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
        Cvor<nekiTip> *p = pocetak;
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
        Cvor<nekiTip> *p(pocetak);
        while (p != nullptr) {
            std::cout << p->element << std::endl;
            p = p->sljedeci;
        }
    }
};

void testMetoda() {
    Red<int> r1;
    for(int i = 1; i <= 10; i++)
        r1.stavi(i);

    std::cout << "Sadrzaj prvog reda: " << std::endl;
    r1.Prikazi();
    std::cout << std::endl;

    Red<int> r2(r1);
    std::cout << "Sadrzaj kopirajuceg reda: " << std::endl;
    r2.Prikazi();
    std::cout << std::endl;

    Red<int> r3(r1);
    std::cout << "Sadrzaj reda dobijenim pomocu operatora dodjele: " << std::endl;
    r3.Prikazi();
    std::cout << std::endl;

    r1.skini();
    std::cout << "Sadrzaj nakon skidanja elementa iz prvog steka ne bi trebao sadrzavati broj 1 koji je bio na celu: " << std::endl;
    r1.Prikazi();
    std::cout << std::endl;

    std::cout << "Novo celo nakon skidanja elementa je: " << std::endl << r1.celo() << std::endl;
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
