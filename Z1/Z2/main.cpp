//TP 2018/2019: Zadaća 1, Zadatak 2
#include <iostream>
#include <array>
#include <vector>
#include <stdexcept>
#include <cmath>
constexpr double errorMargin = 0.00001;

bool jeIspravnaMatrica (std::vector<std::vector<double>> v)
{
    if(v.size()==0)throw std::domain_error("Raspon nije definiran za nul-matricu ili praznu matricu");
    size_t vel = v.at(0).size();
    for(int i = 0; i < v.size(); i++)if(v.at(i).size()!=vel)return false;
    return true;
}

bool sveNule (std::vector<std::vector<double>> v)
{
    for(int i = 0; i< v.size(); i++) {
        for(int j = 0; j < v.at(i).size(); j++) if(fabs(v.at(i).at(j))>errorMargin)return false;
    }
    return true;
}

bool sveNuleRed(std::vector<double> v)
{
    for(auto i : v) if (fabs(i)>errorMargin) return false;
    return true;
}

bool sveNuleKolona(std::vector<std::vector<double>> v, int n)
{
    for(int i = 0; i < v.size(); i++)if(fabs(v.at(i).at(n))>errorMargin) return false;
    return true;
}

std::array<int,4> RasponMatrice (std::vector<std::vector<double>> v)
{
    if(!jeIspravnaMatrica(v))throw std::domain_error("Nekorektna matrica");
    if (v.size()==0 || sveNule(v))throw std::domain_error("Raspon nije definiran za nul-matricu ili praznu matricu");
    int iMin=0, iMax=0, jMin=0, jMax=0;
    while( iMin < v.size() && sveNuleRed(v.at(iMin)) ) iMin++;
    iMax = v.size()-1;
    while(  iMax < v.size() && sveNuleRed(v.at(iMax)) ) iMax--;
    while(  jMin < v.at(0).size() && sveNuleKolona(v, jMin) ) jMin++;
    jMax = v.at(0).size()-1;
    while( jMax < v.at(0).size() && sveNuleKolona(v, jMax))jMax--;
    return {{iMin+1,jMin+1,iMax+1,jMax+1}};
}

int main ()
{
    //for( auto i : RasponMatrice({{0, 0, 0, 0, 0, 0, 0},{0, 0, 6, 3, 5, 0, 0},{0, 6, 0, 0, 3, 0, 0},{0, 0, 0, 0, 0, 0, 0}}) )std::cout<<i<<' ';
    try {
        std::cout<<"Unesite dimenziju matrice u formatu m x n: ";
        int m, n;
        std::cin>>m;
        std::cin.ignore(3);
        std::cin>>n;
        std::vector<std::vector<double>> v(m);
        std::cout << "Unesite elemente matrice: \n";
        for(int i = 0; i < m; i++) {
            std::cout << "Elementi "<<i+1<<". reda: ";
            for(int j = 0; j < n; j++) {
                int temp;
                std::cin>>temp;
                v.at(i).push_back(temp);
            }
        }
        auto rez = RasponMatrice(v);
        std::cout << "\nRaspon matrice je od ("<<rez.at(0)<<","<<rez.at(1)<<") do ("<<rez.at(2)<<","<<rez.at(3)<<").";

    } catch(std::domain_error err) {
        std::cout << "IZUZETAK: " <<err.what()<<"!";
    }
    
    return 0;
}
