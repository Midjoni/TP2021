//TP 2018/2019: Zadaća 2, Zadatak 3
#include <iostream>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <deque>

template <typename T1, typename T2, typename T3>
T3 ZajednickiElementiBlokova (T1 p1, T1 p2, T2 p3, T2 p4, T3 p5)
{
    using tipElementa = typename std::remove_reference<decltype(*p5)>::type;
    using vektor = std::vector<tipElementa>;
    auto pok1 = p1;
    auto pok2 = p3;
    auto dest = p5;
    vektor uneseniBrojevi;
    while (pok1 != p2) {
        while(pok2 != p4) {
            if (*pok1 == *pok2) {
                auto temp = *pok1;
                bool sePonavlja = false;
                for(int i = 0; i < uneseniBrojevi.size(); i++)
                    if(temp == uneseniBrojevi.at(i)) {
                        sePonavlja = true;
                        break;
                    }
                if(sePonavlja) break;
                uneseniBrojevi.push_back(*pok1);
                *dest++ = temp;
            }
            pok2++;
        }
        pok2 = p3;
        pok1++;
    }
    return dest;
}

int main ()
{
    std::cout << "Unesi broj elemenata niza (ne vise od 100): \n";
    int n;
    std::cin >> n;
    std::cout << "Unesi elemente niza: \n";
    int niz[100], rez[100];
    for(int i = 0; i < n; i++)std::cin >> niz[i];
    std::cout << "Unesi broj elemenata deka: \n";
    int nd;
    std::cin >> nd;
    std::deque<int> v(nd);
    std::cout << "Unesi elemente deka: \n";
    for(int i = 0; i < nd; i++)std::cin >> v.at(i);
    auto p = ZajednickiElementiBlokova(niz,niz+n,v.begin(),v.end(), rez);
    std::vector<int> ispis(std::distance(rez, p));
    for(int i = 0; i < ispis.size(); i++)ispis.at(i) = rez[i];
    std::cout << "Vektor zajednickih elemenata niza i deka ima "<<ispis.size()<<" elemenata\n";
    std::cout << "Zajednicki elementi glase: ";
    for(auto &i : ispis) std::cout << i << ' ';
    return 0;
}
