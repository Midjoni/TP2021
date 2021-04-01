//Zadaca doradjena prilikom downtime servera (https://ibb.co/bKvMpV7), prijasni kod ostavljen kao referenca
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

static constexpr bool isspace(unsigned char& c) { return c == ' '; }

typedef std::vector<std::string> listaRijeci;

size_t dajIndex(const std::string& s, const listaRijeci& v)
{
	for (int i = 0; i < v.size(); i++)if (s == v.at(i))return i;
	throw std::domain_error("Nema rijeci");
}

bool seNalaziUnutar(const std::string& s, const listaRijeci& vs)
{
	for (size_t i = 0; i < vs.size(); i++)if (s == vs.at(i))return true;
	return false;
}

std::string ZamjenaRijeci(std::string s, const listaRijeci& v1, const listaRijeci& v2) {
	if (v1.size() != v2.size())throw std::domain_error("Nekorektni parametri");
	auto it1 = s.begin(), it2 = s.begin();
	while (it1 != s.end() && it2!=s.end()) {
		while (it1 != s.end() && isspace(*it1))it1++;
		if (it1 == s.end())break;
		it2 = it1;
		while (it2 != s.end() && !isspace(*it2))it2++;
		auto rijec = std::string(it1, it2);
		if (seNalaziUnutar(rijec, v1)) {
			auto index = dajIndex(rijec, v1);
			s.erase(it1, it2);
			s.insert(it1, v2.at(index).begin(), v2.at(index).end());
			while (it1 != s.end() && !isspace(*it1))it1++;
		}
		else it1 = it2;
	}
	return s;
}

int main() {
	std::cout << "Unesite koliko riječi sadrži rječnik.\n";
	int n;
	std::cin >> n;
	listaRijeci v1(n), v2(n);
	for (unsigned i = 0; i < n; i++) {
		std::cout << "Unesite " << i + 1 << ". original rječnika.\n";
		std::cin >> v1.at(i);
		std::cout << "Unesite " << i + 1 << ". zamjenu rječnika.\n";
		std::cin >> v2.at(i);
	}
	std::cin.ignore(10000, '\n');
	std::cin.clear();
	while (1) {
		std::cout << "Unesite rečenicu koju želite transformisati: \n";
		std::string s;
		getline(std::cin, s);
		if (s.size() == 0)break;
		std::cout << "Transformisana rečenica glasi:\n" << ZamjenaRijeci(s, v1, v2) << '\n';
	}
	return 0;
}

/*
//TP 2018/2019: Zadaća 1, Zadatak 4
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

typedef std::vector<std::string> listaRijeci;

size_t dajIndex(std::string s, listaRijeci v)
{
    for (int i = 0; i < v.size(); i++)if (s == v.at(i))return i;
    throw std::domain_error("Nema rijeci");
}
//Kopirano T4 Z3
bool seNalaziUnutar(std::string s, listaRijeci& vs)
{
    for (int i = 0; i < vs.size(); i++)if (s == vs.at(i))return true;
    return false;
}

std::string ZamjenaRijeci(std::string s, listaRijeci v1, listaRijeci v2)
{
    if (v1.size() != v2.size())throw std::domain_error("Nekorektni parametri");
    auto it1 = s.begin(), it2 = s.begin();
    //Kopiran dio iz TUT 3 ZAD 8 (prilagodjeno)
    while (it1 != s.end() && it2 != s.end()) {
        while (it1 != s.end()) {
            if(isspace(*it1))it1++;
            else break;
        }
        it2 = it1;
        while (it2 != s.end()) {
            if(!isspace(*it2))it2++;
            else break;
        }
        if (it2 != s.end()) {
            auto tmp = std::string(it1, it2);
            if (seNalaziUnutar(tmp, v1)) {
                size_t index = dajIndex(tmp,v1);
                auto pamtiPoziciju = it1;
                s.erase(it1, it2);
                s.insert(it1, v2.at(index).begin(), v2.at(index).end());
                it1 = pamtiPoziciju;
                while(it1 != s.end())if(!isspace(*it1))it1++;
            } else it1 = it2;

        } else if (it2 == s.end() && !isspace(*(it2 - 1))) {
            auto tmp = std::string(it1, it2);
            if (seNalaziUnutar(tmp, v1)) {
                s.erase(it1, it2);
                s.insert(it1, v2.at(dajIndex(tmp, v1)).begin(), v2.at(dajIndex(tmp, v1)).end());
                it1=s.end();
                it2=s.end();
            }
        } else break;

    }
    return s;
}




int main()
{
    std::cout << "Unesite koliko riječi sadrži rječnik.\n";
    int n;
    std::cin >> n;
    listaRijeci v1(n), v2(n);
    for (unsigned i = 0; i < n; i++) {
        std::cout << "Unesite " << i + 1 << ". original rječnika.\n";
        std::cin >> v1.at(i);
        std::cout << "Unesite " << i + 1 << ". zamjenu rječnika.\n";
        std::cin >> v2.at(i);
    }
    std::cin.ignore(10000, '\n');
    std::cin.clear();
    while (1) {
        //std::cin.ignore(10000,'\n');
        //std::cin.clear();
        std::cout << "Unesite rečenicu koju želite transformisati: \n";
        std::string s;
        //if(std::cin.peek() == '\n') break;
        getline(std::cin, s);
        if (s.size() == 0)break;
        std::cout << "Transformisana rečenica glasi:\n" << ZamjenaRijeci(s, v1, v2) << '\n';
    }
    return 0;
}
