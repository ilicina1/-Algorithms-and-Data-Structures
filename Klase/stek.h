#define STEK_H

template <typename nekiTip>
class Stek {
private:
    struct Cvor {
        nekiTip element;
        Cvor *sljedeci;
        Cvor (const nekiTip &element, Cvor *sljedeci) : element(element), sljedeci(sljedeci) {}
    };
    Cvor *vrhu;
    int velicinaSteka;
    void Kopiraj(const Stek &s) {
        Cvor *q, *p(s.vrhu);
        vrhu = 0;
        velicinaSteka = s.velicinaSteka;
        while(p != nullptr) {
            Cvor *n(new Cvor(p->element,nullptr));
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
        vrhu = new Cvor {element, vrhu};
        velicinaSteka++;
    }

    //Skida element sa vrha steka
    nekiTip skini() {
        if (vrhu == nullptr)
            throw "\nStek je prazan!\n";
        nekiTip element(vrhu->element);
        Cvor *p = vrhu->sljedeci;
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
        Cvor *p(vrhu);
        while (p != 0) {
            std::cout << p->element << " ";
            p = p->sljedeci;
        }
        std::cout << std::endl;
    }
};
