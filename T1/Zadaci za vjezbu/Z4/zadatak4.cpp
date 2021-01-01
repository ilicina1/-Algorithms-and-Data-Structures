#include <iostream>
#include <vector>

bool obrnuta(std::vector<std::vector<std::vector<int>>>& vm) {
    bool postoji = false;
    //Pocinje prolaz kroz vektor matrica;
    //Svaki clan vektora tj. svaka matrica se poredi sa ostalim matricama do vm.size();
    for(int i = 0; i < vm.size(); i++) {
        //Prolazim kroz vektor sa i+1 (porede se matrice);
        for(int j = i + 1; j < vm.size(); j++) {
            //Prolaz kroz prvu matricu;
            for(int k = 0; k < vm.at(i).size(); k++) {
                for(int l = 0; l < vm.at(i).at(k).size(); l++) {
                    //Prolaz kroz drugu matricu;
                    for(int m = 0; m < vm.at(j).size(); m++) {
                        for(int n = 0; n < vm.at(j).at(m).size(); n++) {
                            //Poredimo da li postoji isti element ako postoji dodijelimo varijabli "postoji" vrijednost "true";
                            if(vm.at(i).at(k).at(l) == vm.at(j).at(m).at(n)) {
                                postoji = true;
                                break;
                            }
                        }
                        if(postoji == true) {
                            postoji = false;
                            break;
                        }
                        if(postoji == false && m == vm.at(j).size() - 1) return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    std::cout << "Unesite broj matrica koji zelite unijeti: ";
    int velicinaVektora = 0;
    std::cin >> velicinaVektora;
    std::cout << "Unesite sirinu za sve matrice: ";
    int brojRedova = 0;
    std::cin >> brojRedova;
    std::cout << "Unesite visinu za sve matrice: ";
    int brojKolona;
    std::cin >> brojKolona;
    std::vector<std::vector<std::vector<int>>> vektorMatrica;
    //Prolaz kroz vektor;
    for(int i = 0; i < velicinaVektora; i++) {
        std::vector<std::vector<int>> pomocniVektor(brojRedova, std::vector<int>(brojKolona));
        //Prolaz kroz matricu;
        std::cout << "Unos " << i + 1 << ". matrice!" << std::endl << "-------------------------------" << std::endl;
        for(int j = 0; j < brojRedova; j++) {
            for(int k = 0; k < brojKolona; k++) {
                std::cout << "Unesite " << k + 1 << ". element u " << j + 1 << " redu: ";
                std::cin >> pomocniVektor.at(j).at(k);
            }
        }
        vektorMatrica.push_back(pomocniVektor);
    }
    if(obrnuta(vektorMatrica)) std::cout << "Postoje dvije matrice u vektoru sastavljene od istih cifara";
    else
        std::cout << "Ne postoje dvije matrice u vektoru sastavljene od istih cifara";
        
    return 0;
}
