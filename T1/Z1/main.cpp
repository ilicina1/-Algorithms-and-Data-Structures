#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

bool permutacija(std::string s1, std::string s2) {
    std::string pom = "";
    std::vector<std::string> vektorStringova1;
    bool krajRijeci = false;
    for(int i = 0; i < s1.length(); i++) {
        if((!(s1.at(i) >= 'A' && s1.at(i) <= 'Z') && !(s1.at(i) >= 'a' && s1.at(i) <= 'z')) && pom.length() > 0) {
            krajRijeci = true;
            vektorStringova1.push_back(pom);
            pom = "";
        }
        if(!krajRijeci && ((s1.at(i) >= 'A' && s1.at(i) <= 'Z') || (s1.at(i) >= 'a' && s1.at(i) <= 'z'))) {
            pom.push_back(s1.at(i));
        }
        if(!krajRijeci && ((s1.at(i) >= 'A' && s1.at(i) <= 'Z') || (s1.at(i) >= 'a' && s1.at(i) <= 'z')) && i == s1.length() - 1) {
            vektorStringova1.push_back(pom);
        }
        if(krajRijeci) krajRijeci = false;
    }

    std::vector<std::string> vektorStringova2;
    pom = "";
    krajRijeci = false;

    for(int i = 0; i < s2.length(); i++) {
        if((!(s2.at(i) >= 'A' && s2.at(i) <= 'Z') && !(s2.at(i) >= 'a' && s2.at(i) <= 'z')) && pom.length() > 0) {
            krajRijeci = true;
            vektorStringova2.push_back(pom);
            pom = "";
        }
        if(!krajRijeci && ((s2.at(i) >= 'A' && s2.at(i) <= 'Z') || (s2.at(i) >= 'a' && s2.at(i) <= 'z'))) {
            pom.push_back(s2.at(i));
        }
        if(!krajRijeci && ((s2.at(i) >= 'A' && s2.at(i) <= 'Z') || (s2.at(i) >= 'a' && s2.at(i) <= 'z')) && i == s2.length() - 1) {
            vektorStringova2.push_back(pom);
        }
        if(krajRijeci) krajRijeci = false;
    }

    for(int i = 0; i < vektorStringova1.size(); i++) {
        std::transform(vektorStringova1.at(i).begin(), vektorStringova1.at(i).end(), vektorStringova1.at(i).begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });
        std::sort(vektorStringova1.at(i).begin(), vektorStringova1.at(i).end());

    }

    for(int i = 0; i < vektorStringova2.size(); i++) {
        std::transform(vektorStringova2.at(i).begin(), vektorStringova2.at(i).end(), vektorStringova2.at(i).begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });
        std::sort(vektorStringova2.at(i).begin(), vektorStringova2.at(i).end());
    }


    for(int i = 0; i < vektorStringova1.size(); i++) {
        for(int j =  0; j < vektorStringova2.size(); j++) {
            if(vektorStringova1.at(i).compare(vektorStringova2.at(j)) == 0) return true;
        }
    }


    return false;
}

int main() {
    clock_t vrijeme1 = clock();
    std::cout << permutacija("Ilhan je najjaci da","baba lihnA je tu") << std::endl;
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << endl;
    return 0;
}