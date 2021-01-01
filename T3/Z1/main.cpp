#include <iostream>
#include "../../Klase/stek.h"

bool daLiJePar(char otvorena, char zatvorena) {
    if(otvorena == '{' && zatvorena == '}') return true;
    if(otvorena == '[' && zatvorena == ']') return true;
    if(otvorena == '(' && zatvorena == ')') return true;
    return false;
}

bool provjeri_zagrade(std::string tekst) {
    Stek<char> s;

    for(int i = 0; i < tekst.length(); i++) {
        if(tekst.at(i) == '(' || tekst.at(i) == '{' || tekst.at(i) == '[')
            s.stavi(tekst.at(i));
        else if(tekst.at(i) == ')' || tekst.at(i) == '}' || tekst.at(i) == ']') {
            if(s.JeLiPrazan() || !daLiJePar(s.vrh(), tekst.at(i)))
                return false;
            else
                s.skini();
        }
    }

    return s.JeLiPrazan() ? true:false;
}

int main() {
    std::string str = "([()])";
    std::cout << provjeri_zagrade(str);
    
    return 0;
}
