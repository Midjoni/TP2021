//TP 2018/2019: Zadaća 2, Zadatak 5
#include <iostream>
#include <vector>
#include <string>

unsigned PotencijalniKrivci(char**& znak, std::vector<std::string> v)
{
    char** p = nullptr;
    int i = 0;
    try {
        p = new char* [v.size()];
        for (; i < v.size(); i++) {
            try {
                p[i] = new char[v.at(i).size() + 1];
                for (int j = 0; j < v.at(i).size(); j++)p[i][j] = v.at(i).at(j);
                p[i][v.at(i).size()] = '\0';
            } catch (...) {
                for (int j = 0; j < i; j++)delete[] p[j];
                delete[] p;
                throw;
            }
        }
    } catch (...) {
        throw;
    }
    znak = p;
    return i;
}

unsigned OdbaciOptuzbu(char**& znak, int n, std::string s)
{
    bool jePronadjen = false;
    for (int i = 0; i < n; i++) {
        if(znak[i]==nullptr) continue;
        std::string str = znak[i];
        if (str == s) {
            jePronadjen = true;
            delete[] znak[i];
            znak[i] = nullptr;
            break;
        }
    }
    if (!jePronadjen)throw std::domain_error(std::string("Osoba sa imenom ") + s + std::string(" nije bila optuzena!"));
    bool jeSmanjen = false;
    size_t brojObrisanih = 0;
    for (int i = 0; i < n; i++)if (znak[i] == nullptr)brojObrisanih++;
    if (brojObrisanih > 10) {
        char** p = nullptr;
        try {
            p = new char* [n - brojObrisanih];
            for (int i = 0, j = 0; i < n; i++) {
                if (znak[i] == nullptr)continue;
                std::string str = znak[i];
                try {
                    p[j] = new char[str.size() + 1];
                    for (int k = 0; k < str.size(); k++)p[j][k] = znak[i][k];
                    p[j][str.size()] = '\0';
                    j++;
                } catch (...) {
                    for (int k = 0; k < j; k++) delete[] p[k];
                    delete[] p;
                    break;
                }
            }
            jeSmanjen = true;
            for (int i = 0; i < n; i++)delete[] znak[i];
            delete[] znak;
            znak = p;
        } catch (...) {
            return n;
        }
    }
    return ((jeSmanjen) ? n - brojObrisanih : n);
}

unsigned DodajOptuzbu(char**& znak, int n, std::string s)
{
    bool imaPraznih = false;
    for (int i = 0; i < n; i++) {
        try {
            if (znak[i] == nullptr) {
                imaPraznih = true;
                znak[i] = new char[s.size() + 1];
                for (int j = 0; j < s.size(); j++) znak[i][j] = s.at(j);
                znak[i][s.size()] = '\0';
                return n;
            }
        } catch (...) {
            throw;
        }
    }
    if (!imaPraznih) {
        char** p = nullptr;
        try {
            p = new char* [n + 1];
            for (int i = 0; i < n; i++) {
                std::string str = znak[i];
                try {
                    p[i] = new char[str.size() + 1];
                    for (int j = 0; j <= str.size(); j++)
                        p[i][j] = znak[i][j];

                } catch (...) {
                    for (int j = 0; j < i; j++) delete[] p[i];
                    delete[] p;
                    throw;
                }
            }
            try {
                p[n] = new char[s.size() + 1];
                for (int i = 0; i < s.size(); i++) p[n][i] = s.at(i);
                p[n][s.size()] = '\0';
            } catch(...) {
                for (int j = 0; j < n; j++) delete[] p[j];
                delete[] p;
                throw;
            }
            for (int i = 0; i < n; i++)delete[] znak[i];
            delete[] znak;
            znak = p;
            return n + 1;
        } catch (...) {
            throw;
        }
    }
    return n;
}

void IzlistajOptuzbu(char** znak, int n)
{
    std::cout << "Spisak trenutno optuzenih:\n";
    for (int i = 0; i < n; i++) {
        if (znak[i] == nullptr)continue;
        std::cout << znak[i] << '\n';
    }
}

int main()
{
    std::cout << "Unesite broj ljudi koji su optuzeni za prepisivanje/prodavanje zadaca: ";
    int n;
    char** optuzeni = nullptr;
    std::cin >> n;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    auto broj = 0;
    try {
        std::vector<std::string> imena(n);
        for (int i = 0; i < n; i++) {
            std::string ime;
            std::cout << "Unesite ime optuzenog: ";
            getline(std::cin, ime);
            imena.at(i) = ime;
        }
        broj = PotencijalniKrivci(optuzeni,imena);
    } catch(std::bad_alloc) {
        std::cout<<"Nedovoljno memorije!";
        return 0;
    }
    std::cout << "Duzina spiska: " << broj << '\n';
    IzlistajOptuzbu(optuzeni, n);
    std::cout << "Unesite ime osobe oslobodjene optuzbi: ";
    std::string ime;
    getline(std::cin, ime);
    try {
        broj = OdbaciOptuzbu(optuzeni, broj, ime);
    } catch(std::domain_error err) {
        std::cout << err.what();
        for(int i = 0; i < broj; i++)delete[] optuzeni[i];
        delete[] optuzeni;
        return 0;
    }
    IzlistajOptuzbu(optuzeni, broj);
    std::cout << "Unesite ime novog optuzenog: ";
    getline(std::cin, ime);
    broj = DodajOptuzbu(optuzeni, broj, ime);
    IzlistajOptuzbu(optuzeni, broj);
    for(int i = 0; i < broj; i++) delete[] optuzeni[i];
    delete[] optuzeni;
    return 0;
}
