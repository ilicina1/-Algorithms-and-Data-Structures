#include <iostream>

using namespace std;

int fib2_0(int n) {
    if(n <= 1) return n;

    int f1=fib2_0(n-1);

    int f2=fib2_0(n-2);

    return f1+f2;
}

int nzd(int x, int y) {
    if (y==0) return x;
    
    x = x % y; 
    
    return nzd(y,x);
}

int main() {
    std::cout << fib2_0(9);
    return 0;
}
