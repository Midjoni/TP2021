//TP 2018/2019: Zadaća 1, Zadatak 3
#include <iostream>
#include <deque>
#include <stdexcept>
#include <iomanip>

typedef std::deque<std::deque<double>> realnaMatrica;

//Tutorijal 3 , Zadatak 6

int brojCifara (int a)
{
    int broj = 0;
    if(a<0)++broj;
    while(a!=0) {
        ++broj;
        a/=10;
    }
    return broj;
}

int NajvecaSirina (realnaMatrica v)
{
    int max=0;
    for(int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.at(i).size(); j++) {
            if(brojCifara(v.at(i).at(j))>max) max = brojCifara(v.at(i).at(j));
        }
    }
    return max;
}

//Prekopirano iz zadatka dva
bool jeIspravnaMatrica (realnaMatrica v)
{
    if(v.size()==0)return false;
    size_t vel = v.at(0).size();
    for(int i = 0; i < v.size(); i++)if(v.at(i).size()!=vel)return false;
    return true;
}

realnaMatrica EkspanzijaMatrice (realnaMatrica mat, int p, int q)
{
    if( p<=0 || q<=0 )throw std::domain_error("Nelegalni parametri");
    if(!jeIspravnaMatrica(mat))throw std::domain_error("Nekorektna matrica");
    size_t m = mat.size(), n = mat.at(0).size();
    realnaMatrica rez( m*p, std::deque<double>(n*q) );
    for(size_t i = 0; i < m*p; i++) {
        for(size_t j = 0; j < n*q; j++) {
            rez.at(i).at(j) = mat.at(i/p).at(j/q);
        }
    }
    return rez;
}

int main ()
{
    try {
        int m,n;
        std::cout << "Unesite broj redova matrice A (m): ";
        std::cin >> m;
        std::cout << "Unesite broj kolona matrice A (n): ";
        std::cin >> n;
        realnaMatrica mat(m,std::deque<double>(n));
        for(size_t i = 0; i < m; i++) {
            std::cout << "Unesite "<<i+1<<". red matrice: ";
            for(size_t j = 0; j < n; j++) {
                std::cin >> mat.at(i).at(j);
            }
        }
        std::cout << "Unesite dimenziju ekspanzije p: ";
        int p,q;
        std::cin >> p;
        std::cout << "Unesite dimenziju ekspanzije q: ";
        std::cin >> q;
        std::cout << "Ekspanzija matrice A glasi:\n";
        mat = EkspanzijaMatrice(mat,p,q);
        size_t sirina = NajvecaSirina(mat)+1;
        for(size_t i = 0; i < m*p; i++) {
            for(size_t j = 0; j<n*q; j++) {
                if(j==0)std::cout << std::fixed <<  std::setprecision(2) <<std::skipws << mat.at(i).at(j);
                else std::cout << std::fixed <<  std::setprecision(2) <<std::setw(sirina+3) << mat.at(i).at(j);
            }
            std::cout << '\n';
        }
    } catch (std::domain_error err) {std::cout << err.what();}
    return 0;
}
