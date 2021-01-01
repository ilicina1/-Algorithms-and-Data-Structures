#include <iostream>

// pow je kljucna rijec za funkciju koja vec postoji te zbog toga koristimo drugi naziv;
double ntiStepen(double a, unsigned int n) {
    if(n == 1){
        return a;
    }
    
    return a * ntiStepen(a, n-1);
}

int main() {
    std::cout << ntiStepen(3, 5);
}
