//TP 2018/2019: Zadaća 2, Zadatak 4
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

int BrojDjelilaca (const int& n)
{
    if(n == 0 || n == 1) return n;
    int rez = 2;
    for(int i = 2; i < sqrt(n); i++)if(n % i == 0 ) rez+=2;
    if(static_cast<int>(sqrt(n)) * static_cast<int>(sqrt(n)) == n)rez++;
    return rez;
}

bool KriterijSortiranja (const int &a, const int &b){return (BrojDjelilaca(a) == BrojDjelilaca(b)) ? a < b : BrojDjelilaca(a) > BrojDjelilaca(b);}

bool PretraziBinarno (int *niz, const int& vel, const int &trazen){return std::binary_search(niz,niz+vel,trazen,KriterijSortiranja);}

void SortirajPoBrojuDjelilaca (int *niz,const int &vel){std::sort(niz,niz+vel,KriterijSortiranja);}

int main ()
{
    std::cout<<"Unesite broj elemenata niza: \n";
    int n;
    std::cin >> n;
    try {
        int* niz = new int[n];
        std::cout << "Unesite elemente niza: \n";
        for(int i = 0; i < n; i++)std::cin>>niz[i];
        SortirajPoBrojuDjelilaca(niz,n);
        std::cout<<"Sortiran niz glasi: ";
        for(int i = 0; i < n; i++)std::cout<<niz[i]<<' ';
        std::cout<<"\nUnesite element koji treba binarno pretraziti: \n";
        int broj;
        std::cin>>broj;
        std::cout<<"Trazeni element se " << ((PretraziBinarno(niz,n,broj)) ? "" : "ne ") << "nalazi u nizu.";
        delete[] niz;
    } catch(...) {return -1;}
    return 0;
}
