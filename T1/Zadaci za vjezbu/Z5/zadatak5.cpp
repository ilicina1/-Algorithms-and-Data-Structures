#include <iostream>
#include <vector>

void funkcija(std::vector<std::vector<int>> matrica, int& prvaRef, int& drugaRef) {
    for(int i = 0; i < matrica.size(); i++) {
        for(int j = 0; j < matrica.at(i).size(); j++) {
            if(i != 0 && j != 0 && i != matrica.size() - 1 && j != matrica.at(i).size() - 1) {
                if(matrica.at(i).at(j) <= matrica.at(i+1).at(j) && matrica.at(i).at(j) <= matrica.at(i).at(j+1) && matrica.at(i).at(j) <= matrica.at(i-1).at(j) && matrica.at(i).at(j) <= matrica.at(i).at(j-1) ) {
                    prvaRef = i;
                    drugaRef = j;
                    return;
                }
            }
        }
    }
}

int main() {
    
}
