#include <iostream>

using namespace std;

template <typename nekiTip>
struct Cvor {
    nekiTip element;
    Cvor *sljedeci;
    Cvor (const nekiTip &element, Cvor *sljedeci) : element(element), sljedeci(sljedeci) {}
};

template <typename nekiTip>
class Stek {
private:
    Cvor<nekiTip> *vrhu;
    int velicinaSteka;
    void Kopiraj(const Stek &s) {
        Cvor<nekiTip> *q, *p(s.vrhu);
        vrhu = 0;
        velicinaSteka = s.velicinaSteka;
        while(p != nullptr) {
            Cvor<nekiTip> *n(new Cvor<nekiTip>(p->element,nullptr));
            if (vrhu == 0)
                vrhu = n;
            else
                q->sljedeci = n;
            p = p->sljedeci;
            q = n;
        }
    }
public:
    //Konstruktor
    Stek() : vrhu(nullptr), velicinaSteka(0) {}

    //Konstruktor kopije
    Stek(const Stek &s) {
        Kopiraj(s);
    }

    //Destruktor
    ~Stek() {
        brisi();
    }

    //Preklopljeni operator dodjele
    Stek &operator =(const Stek &s) {
        if (&s == this) return *this;
        brisi();
        Kopiraj(s);
        return *this;
    }

    //Stavlja element na vrh steka
    void stavi(const nekiTip &element) {
        vrhu = new Cvor<nekiTip> {element, vrhu};
        velicinaSteka++;
    }

    //Skida element sa vrha steka
    nekiTip skini() {
        if (vrhu == nullptr)
            throw "\nStek je prazan!\n";
        nekiTip element(vrhu->element);
        Cvor<nekiTip> *p = vrhu->sljedeci;
        delete vrhu;
        vrhu = p;
        velicinaSteka--;
        return element;
    }

    //Vraca element na vrhu steka
    const nekiTip& vrh() const {
        if (vrhu == 0)
            throw "Stek je prazan!\n";
        return vrhu->element;
    }

    nekiTip& vrh()  {
        if (vrhu == 0)
            throw "Stek je prazan!\n";
        return vrhu->element;
    }

    //Brise sve elemente
    void brisi() {
        while(!JeLiPrazan())
            skini();
    }

    // Provjerava da li je stek prazan;
    bool JeLiPrazan() const {
        return vrhu == 0;
    }

    // Vraca broj elemenata steka
    int brojElemenata() const {
        return velicinaSteka;
    }

    // Prikazi elemente
    void Prikazi() const {
        Cvor<nekiTip> *p(vrhu);
        while (p != 0) {
            std::cout << p->element << " ";
            p = p->sljedeci;
        }
        std::cout << std::endl;
    }
};

void testMetoda() {
    Stek<int> s1;
    for(int i = 1; i <= 10; i++)
        s1.stavi(i);

    std::cout << "Sadrzaj prvog steka: " << std::endl;
    s1.Prikazi();
    std::cout << std::endl;

    Stek<int> s2(s1);
    std::cout << "Sadrzaj kopirajuceg steka: " << std::endl;
    s2.Prikazi();
    std::cout << std::endl;

    Stek<int> s3(s1);
    std::cout << "Sadrzaj steka dobijenim pomocu operatora dodjele: " << std::endl;
    s3.Prikazi();
    std::cout << std::endl;


    s1.skini();
    std::cout << "Sadrzaj nakon skidanja elementa iz prvog steka ne bi trebao sadrzavati broj 10 koji je bio na vrhu: " << std::endl;
    s1.Prikazi();
    std::cout << std::endl;

    std::cout << "Novi vrh nakon skidanja elementa je: " << std::endl << s1.vrh() << std::endl;
    std::cout << std::endl;

    std::cout << "Broj elemenata ovog steka je: " << std::endl << s1.brojElemenata() << std::endl;
    std::cout << std::endl;

    s1.brisi();
    std::cout << "Bro elemenata nakon brisanja svih elemenata je: " << std::endl << s1.brojElemenata();
}

int main() {
    testMetoda();
    return 0;
}