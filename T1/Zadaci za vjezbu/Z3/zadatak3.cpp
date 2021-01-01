#include <iostream>
#include <vector>
#include <cstring>

struct Student {
    std::string ime, prezime;
    int brojIndexa;
};

bool istoImePrezime(std::vector<Student> studenti) {
    for(int i = 0; i < studenti.size() - 1; i++) {
        for(int j = i + 1; j < studenti.size(); j++) {
            if(studenti.at(i).ime == studenti.at(j).ime && studenti.at(i).prezime == studenti.at(j).prezime)
                return true;
        }
    }
    return false;
}

int main() {
    std::vector<Student> studenti;
    std::cout << "Unesite broj studenata koji zelite upisati: ";
    int brojStudenata = 0;
    std::cin >> brojStudenata;
    Student s;
    for(int i = 0; i < brojStudenata; i++) {
        std::cout << "Unesite ime " << i+1 << ". studenta: ";
        std::cin >> s.ime;
        std::cout << "Unesite prezime " << i+1 << ". studenta: ";
        std::cin >> s.prezime;
        std::cout << "Unesite broj indexa " << i+1 << ". studenta: ";
        std::cin >> s.brojIndexa;

        studenti.push_back(s);
    }
    if(istoImePrezime(studenti)) std::cout << "Postoje dva studenta sa istim imenom i prezimenom!";
    else
        std::cout << "Ne postoje dva studenta sa istim imenom i prezimenom!";
    return 0;
}
