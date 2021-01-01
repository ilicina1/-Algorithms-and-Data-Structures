#include <iostream>
#include <ctime>

bool daLiJeProst(long long int n) {
    int m = n / 2;
    for(int i = 2; i < m; i++)
        if(n % i == 0) return false;
    return true;
}

void Goldbach ( int n, int& p, int& q) {
    if(n % 2 != 0 && !(n > 2)) throw std::domain_error("Broj koji ste unijeli nije paran ili nije veci od broja 2!");
    int i = 1;
    for(int j = n - i; j > 2; j--) {
        if(daLiJeProst(i) && daLiJeProst(j)) {
            p = i;
            q = j;
            return;
        }
        i++;
    }
    throw std::domain_error("Goldbachova hipoteza nije tacna za ovaj broj");
}

int main() {
    std::cout << "Unesite broj koji se testira: ";
     int n = 0;
    std::cin >> n;
    int p = 0, q = 0;
    clock_t vrijeme1 = clock();
    Goldbach(n,p,q);
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
}
