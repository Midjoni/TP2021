//TP 2018/2019: Zadaća 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>

enum class Kriterij {Veca, Manja, Jednaka};

bool mozeProc (std::vector<int> v, int n)
{
    for(auto i : v) if (i == n) return false;
    return true;
}

int umnozakCifara (long a)
{
    a = fabs(a);
    int i=1;
    while(a>0) {
        i *= a%10;
        a/=10;
    }
    if(i<10)return 0;
    return i;
}

int otpornost (int n)
{
    if(fabs(n)<10)return 0;
    int i=1;
    while (n!=0) {
        n = umnozakCifara(static_cast<long>(n));
        if(n!=0)i++;
        else break;
    }
    return i;
}

std::vector<int> IBSZMU(std::vector<int> v, int n, Kriterij k)
{
    std::vector<int> rez;
    for (int i = 0; i < v.size(); i++) {
        if ( ( otpornost(v.at(i)) < n && k == Kriterij::Manja ) || ( otpornost(v.at(i)) > n && k == Kriterij::Veca ) || ( otpornost(v.at(i)) == n && k == Kriterij::Jednaka ) )
            if ( mozeProc(rez,v.at(i)) )rez.push_back(v.at(i));
    }
    return rez;
}

int main ()
{
    std::vector<int> v;
    std::cout << "Unesite slijed brojeva (0 za kraj): ";
    int n;
    while (std::cin>>n, n!=0)v.push_back(n);
    std::cout<<"Unesite zeljeni prag za multiplikativnu otpornost: ";
    std::cin>>n;
    
    std::cout << "\nBrojevi cija je multiplikativna otpornost manja od zadane: ";
    auto temp = IBSZMU(v,n,Kriterij::Manja);
    if(temp.empty()) std::cout << "Nema takvih brojeva";
    else for (auto i : temp) std::cout << i <<" ";
    
    std::cout << "\nBrojevi cija je multiplikativna otpornost veca od zadane: ";
    temp = IBSZMU(v,n,Kriterij::Veca);
    if(temp.empty()) std::cout << "Nema takvih brojeva";
    else for (auto i : temp) std::cout << i <<" ";
    
    std::cout << "\nBrojevi cija je multiplikativna otpornost jednaka zadanoj: ";
    temp = IBSZMU(v,n,Kriterij::Jednaka);
    if(temp.empty()) std::cout << "Nema takvih brojeva";
    else for (auto i : temp) std::cout << i <<" ";
    
    return 0;
}
