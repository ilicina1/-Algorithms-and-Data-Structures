#include <iostream>
#include "../../Klase/red.h"
#include "../../Klase/stek.h"
#include "../../Klase/lista.h"

int f10(Red<int> red,int k, Red<int> &red2){
 	if(red.brojElemenata()==0) return 0;
	red.skini();
	k = f10(red,k,red2);
	red2.stavi(k);
	k = f10(red,k,red2);
	red2.stavi(k);
	return k;
}


int f9(Stek<int> &s,int &sum){
	if(s.brojElemenata()==1) return s.skini();
	sum += s.skini();
	return  f9(s,sum);
}

int main() {
    Stek<int> s1;
    s1.stavi(6);
    s1.stavi(5);
    s1.stavi(4);
    s1.stavi(3);
    s1.stavi(2);
    s1.stavi(1);
    int sum=0;
    std::cout << f9(s1, sum);
}
