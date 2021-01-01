#include <iostream>
#include <vector>

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

    Cvor<nekiTip> *dajVrh() {
        if (vrhu == 0)
            throw "Stek je prazan!\n";
        return vrhu;
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
};

void pretraga(Stek<std::vector<int> >& s, int trazeni) {
    if(s.brojElemenata() == 0) {
        std::cout << "Nema elementa";
        return;
    }
    static int x = 0;
    int middleIndex = int(s.vrh().size())/2;
    x += middleIndex;

    //Kada ce se smanjiti na iduci vektor;
    if(s.vrh().size() < 2) {
        if(s.vrh().size() == 0) {
            if(s.dajVrh()->sljedeci == nullptr) {
                std::cout << "Nema elementa";
                return;
            } else {
                Stek<std::vector<int>> pom(s);
                pom.skini();
                x=0;
                return pretraga(pom, trazeni);
            }
        }
        if(trazeni == s.vrh()[0]) {
            std::cout << x << " " << s.brojElemenata() - 1;
            return;
        }

        if(s.dajVrh()->sljedeci == nullptr) {
            std::cout << "Nema elementa";
            return;
        } else {
            Stek<std::vector<int>> pom(s);
            pom.skini();
            x=0;
            return pretraga(pom, trazeni);
        }
    }

    int middle = s.vrh()[middleIndex];

    if(trazeni == middle) {
        
        std::cout << x << " " << s.brojElemenata() - 1;
        return;
    } else if(trazeni < middle) {
        std::vector<int>::const_iterator begin = s.vrh().begin();
        std::vector<int>::const_iterator last = s.vrh().begin() + middleIndex;
        std::vector<int> firstHalf(begin, last);
        Stek<std::vector<int>> pom(s);
        pom.skini();
        pom.stavi(firstHalf);
        if(x != 0) x -= middleIndex;
        return pretraga(pom, trazeni);
    } else if(trazeni > middle) {
        std::vector<int>::const_iterator begin = s.vrh().begin() + middleIndex;
        std::vector<int>::const_iterator last = s.vrh().begin() + s.vrh().size();
        std::vector<int> secondHalf(begin, last);
        Stek<std::vector<int>> pom(s);
        pom.skini();
        pom.stavi(secondHalf);
        return pretraga(pom, trazeni);
    } else {
        std::cout << "Nema elementa";
    }
}

int main() {
    Stek<vector<int> > s;
    vector<int> a;
    for (int i(10); i<10000; i++)
        a.push_back(i);
    vector<int> b;
    b.push_back(10006);
    b.push_back(10008);
    vector<int> c;
    c.push_back(10009);
    c.push_back(10010);
    c.push_back(10130);
    vector<int> d;
    d.push_back(10157);
    d.push_back(10226);
    d.push_back(13424);
    s.stavi(a);
    s.stavi(b);
    s.stavi(c);
    s.stavi(d);
    pretraga(s,254);
}
