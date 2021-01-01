#include <iostream>
#include <ctime>

using namespace std;

void ispisiProsteBrojeve(int n) {
    bool jelProst = true;
    
    for(int i = 2; i < n; i++) {
        for(int j = 2; j < i / 2; j++) {
            if (i % j == 0) {
                jelProst = false;
                break;
            }
        }
        if(jelProst && i != 4) std::cout << i << " ";
        jelProst = true;
    }
    
    std::cout << std::endl;
}

int main() {
    clock_t vrijeme1 = clock();
    ispisiProsteBrojeve(50);
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << endl;
    return 0;
}
