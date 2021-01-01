#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

template <typename Tip>
void swap(Tip *a, Tip *b) {
    Tip t = *a;
    *a = *b;
    *b = t;
}

template <typename Tip>
void bubble_sort(Tip* niz, int vel) {
    for(int i = 0; i < vel - 1; i++) {
        for(int j = i + 1; j < vel; j++) {
            if(niz[i] > niz[j]) {
                swap(niz[i], niz[j]);
            }
        }
    }
}

template <typename Tip>
void selection_sort(Tip* niz, int vel) {

    for(int i = 0; i < vel - 1; i++) {
        int minIndex = i;
        for(int j = i + 1; j < vel; j++) {
            if(niz[j] < niz[minIndex]) {
                minIndex = j;
            }
        }
        swap(niz[minIndex], niz[i]);
    }
}

template <typename Tip>
int partition(Tip* niz, int prvi, int zadnji) {

    Tip pivot = niz[prvi];
    Tip temp1;

    int i = prvi+1;


    while(i <= zadnji && niz[i] < pivot) {
        i++;
    }

    for(int j(i+1) ; j<=zadnji ; j++) {
        if(niz[j] < pivot) {
            temp1 = niz[j];
            niz[j] = niz[i];
            niz[i] = temp1;
            i++;
        }
    }

    temp1 = niz[prvi];
    niz[prvi] = niz[i-1];
    niz[i-1] = temp1;

    return i-1;
}

template <typename Tip>
void helpFun(Tip *niz, int prvi, int zadnji) {
    if(prvi < zadnji) {
        int j = partition(niz, prvi, zadnji);
        helpFun(niz, prvi, j - 1);
        helpFun(niz, j + 1, zadnji);
    }

}


template <typename Tip>
void quick_sort(Tip* niz, int vel) {
    helpFun(niz, 0, vel - 1);
}

template <typename Tip>
void merge(Tip *arr, int low, int high, int mid) {
    int i, j, k;
    Tip c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {

        if (arr[i] < arr[j]) {
            c[k] = arr[i];
            k++;
            i++;
        } else  {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)  {
        arr[i] = c[i];
    }
}

template <typename Tip>
void pomocna(Tip *niz,int p,int l,int q,int u) {
    int i = 0;
    int j = q-l;
    int k = l;
    auto novi_niz = new Tip[u-l+1];


    for(int m(0) ; m<=u-l ; m++) {
        novi_niz[m] = niz[l+m];
    }

    while(i <= p-l && j <= u-l) {
        if(novi_niz[i] < novi_niz[j]) {
            niz[k] = novi_niz[i];
            i++;
        } else {
            niz[k] = novi_niz[j];
            j++;
        }
        k++;
    }

    while(i <= p-l) {
        niz[k] = novi_niz[i];
        i++;
        k++;
    }
    while(j<=u-l) {
        niz[k] = novi_niz[j];
        j++;
        k++;
    }

    delete []novi_niz;

}

template <typename Tip>
void merge(Tip* niz,int l,int u) {
    if(l < u) {
        int p = (l+u-1) / 2;
        int q = p+1;
        merge(niz,l,p);
        merge(niz,q,u);
        pomocna(niz,p,l,q,u);
    }
}

template <typename Tip>
void merge_sort(Tip *niz,int vel) {
    int l = 0;
    int u = vel-1;

    merge(niz,l,u);
}

void ucitaj(std::string filename, int*& niz, int &vel) {
    ifstream myReadFile;
    myReadFile.open(filename);
    int broj = 0;

    while(myReadFile >> broj) {
        vel++;
    }

    myReadFile.close();
    myReadFile.open(filename);

    niz = new int[vel];

    int i = 0;

    while(i < vel && myReadFile >> broj) {
        niz[i] = broj;
        i++;
    }

    myReadFile.close();
}

void funkcija(std::string filename) {
    int *niz;
    int vel = 0;

    ucitaj(filename, niz, vel);

    int opcija = 0;

    while(opcija < 1 || opcija > 4) {
        std::cout << "Da izaberes algoritam za sortiranje niza upisi broj koji se nalazi pored naziva algoritma kojeg zelis:\n";
        std::cout << "[1] Bubble sort \n[2] Selection sort \n[3] Quick sort \n[4] Merge sort" << std::endl;
        std::cin >> opcija;
    }

    std::cout << "Niz prije sortiranja: ";
    for(int i = 0; i < vel;  i++) std::cout << niz[i] << " ";
    std::cout << std::endl;

    clock_t vrijeme1 = clock();

    if(opcija == 1) bubble_sort(niz, vel);
    if(opcija == 2) selection_sort(niz, vel);
    if(opcija == 3) quick_sort(niz, vel);
    if(opcija == 4) merge_sort(niz, vel);


    std::cout << "Niz nakon sortiranja: ";
    for(int i = 0; i < vel;  i++) std::cout << niz[i] << " ";
    std::cout << std::endl;

    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;

    for(int i = 1; i < vel; i++) {
        if(niz[i] < niz[i-1]) {
            std::cout << "Nije sortiran kako treba";
            return;
        }
    }

    ofstream myfile ("pisi.txt");
    if (myfile.is_open()) {
        for(int i = 0; i < vel;  i++) {
            myfile << niz[i] << " ";
        }
        myfile.close();
    } else std::cout << "Nemoguce otvoriti file";
    
    delete[] niz;
}

void generisi(std::string filename, int vel) {
    ofstream myfile (filename);
    srand((unsigned)time(0));

    if (myfile.is_open()) {
        for(int i = 0; i < vel;  i++) {
            myfile << (rand()%100)+1 << " ";
        }
        myfile.close();
    } else std::cout << "Nemoguce otvoriti file";
}

int main() {
    funkcija("citaj.txt");
    return 0;
}
