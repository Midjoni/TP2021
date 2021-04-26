#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include <cctype>

enum class KodoviGresaka { PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar };

enum class Komande { PomjeriJednoMjesto, PomjeriDalje, Blokiraj, Deblokiraj, PrikaziOkolinu, ZavrsiIgru, KreirajIgru };

enum class Polje { Prazno, Posjeceno, Mina, BlokiranoPrazno, BlokiranoPosjeceno, BlokiranoMina };

enum class Status { NijeKraj, KrajPoraz, KrajPobjeda };

enum class Smjerovi { GoreLijevo, Gore, GoreDesno, Desno, DoljeDesno, Dolje, DoljeLijevo, Lijevo };

typedef std::vector<std::vector<Polje>> Tabla;

using IntegerMatrica = std::vector<std::vector<int>>;

static const std::vector<std::string> DozvoljeneKomande{ "P1", "P>", "B", "D", "PO", "Z", "K" };

static const std::vector<std::string> DozvoljenaKretanja{ "GL", "G", "GD", "D", "DoD", "Do", "DoL", "L" };

bool jeBroj(const std::string& s) { return std::all_of(s.begin(), s.end(), isdigit); }

std::vector<int> UnesiMine(const std::string& s)
{
    std::vector<int> rez(2);
    auto it = s.begin();
    while (it != s.end())if (isspace(*it))it++;
    else break;
    if (it == s.end() || *it != '(') throw std::domain_error("(");
    else it++;
    while (it != s.end())if (isspace(*it))it++;
    else break;
    if (!isdigit(*it)) throw std::domain_error("nijebroj");
    auto itt = it;
    while (itt != s.end())if (isdigit(*itt))itt++;
    else break;
    rez.at(0) = std::stoi(std::string(it, itt));
    it = itt;
    while (it != s.end())if (isspace(*it))it++;
    else break;
    if (it == s.end() || *it != ',') throw std::domain_error(",");
    else it++;
    while (it != s.end())if (isspace(*it))it++;
    else break;
    if (!isdigit(*it)) throw std::domain_error("nijebroj");
    itt = it;
    while (itt != s.end())if (isdigit(*itt))itt++;
    else break;
    rez.at(1) = std::stoi(std::string(it, itt));
    it = itt;
    while (it != s.end())if (isspace(*it))it++;
    else break;
    if (it == s.end() || *it != ')') throw std::domain_error(")");
    it++;
    while (it != s.end())if (isspace(*it))it++;
    else throw std::domain_error("nakonzagrade");
    return rez;
}

std::vector<std::string> IzdvojiRijeci(const std::string& s)
{
    std::vector<std::string> rez;
    auto it1 = s.begin(), it2 = s.begin();
    while (1) {
        it1 = std::find_if_not(it2, s.end(), isspace);
        if (it1 == s.end()) break;
        it2 = std::find_if(it1, s.end(), isspace);
        rez.push_back(std::string(it1, it2));
    }
    return rez;
}

void OcistiTok()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void ZavrsiIgru(Tabla& t)
{
    std::for_each(t.begin(), t.end(), [](std::vector<Polje>& v) {for (auto& i : v)i = Polje::Prazno; });
    throw std::runtime_error("Igra zavrsena");
}

void BlokirajPolje(Tabla& polja, int x, int y)
{
    if (x >= polja.size() || y >= polja.size())throw std::domain_error(std::string("Polje (") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(") ne postoji"));
    switch (polja.at(x).at(y)) {
    case Polje::Mina:
        polja.at(x).at(y) = Polje::BlokiranoMina;
        break;
    case Polje::Posjeceno:
        polja.at(x).at(y) = Polje::BlokiranoPosjeceno;
        break;
    case Polje::Prazno:
        polja.at(x).at(y) = Polje::BlokiranoPrazno;
        break;
    default:
        break;
    }
}

void DeblokirajPolje(Tabla& polja, int x, int y)
{
    if (x >= polja.size() || y >= polja.size())throw std::domain_error(std::string("Polje (") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(") ne postoji"));
    switch (polja.at(x).at(y)) {
    case Polje::BlokiranoMina:
        polja.at(x).at(y) = Polje::Mina;
        break;
    case Polje::BlokiranoPosjeceno:
        polja.at(x).at(y) = Polje::Posjeceno;
        break;
    case Polje::BlokiranoPrazno:
        polja.at(x).at(y) = Polje::Prazno;
        break;
    default:
        break;
    }
}

void PrijaviGresku(KodoviGresaka greska)
{
    switch (greska) {
    case KodoviGresaka::PogresnaKomanda:
        std::cout << "Nerazumljiva komanda!\n";
        break;
    case KodoviGresaka::NedostajeParametar:
        std::cout << "Komanda trazi parametar koji nije naveden!\n";
        break;
    case KodoviGresaka::NeispravanParametar:
        std::cout << "Parametar komande nije ispravan!\n";
        break;
    case KodoviGresaka::SuvisanParametar:
        std::cout << "Zadan je suvisan parametar nakon komande!\n";
        break;
    }
}

auto dajKomandu = [](const std::string& str) -> Komande
{
    if (str == "P1") return Komande::PomjeriJednoMjesto;
    else if (str == "P>") return Komande::PomjeriDalje;
    else if (str == "B") return Komande::Blokiraj;
    else if (str == "D") return Komande::Deblokiraj;
    else if (str == "PO") return Komande::PrikaziOkolinu;
    else if (str == "Z") return Komande::ZavrsiIgru;
    return Komande::KreirajIgru;
};

auto dajSmjer = [](const std::string& str) -> Smjerovi
{
    if (str == "GL") return Smjerovi::GoreLijevo;
    else if (str == "G") return Smjerovi::Gore;
    else if (str == "GD") return Smjerovi::GoreDesno;
    else if (str == "D") return Smjerovi::Desno;
    else if (str == "DoD") return Smjerovi::DoljeDesno;
    else if (str == "Do") return Smjerovi::Dolje;
    else if (str == "DoL") return Smjerovi::DoljeLijevo;
    return Smjerovi::Lijevo;
};

bool jeNaMini(const Tabla& tabla, const int& x, const int& y) { return tabla.at(x).at(y) == Polje::Mina; }

bool UnosKomande(Komande& komanda, Smjerovi& smjer, int& x, int& y, KodoviGresaka& greska)
{
    std::string temp, UnesenaKomanda;
    getline(std::cin >> std::skipws, temp);
    auto input = IzdvojiRijeci(temp);
    //provjeri jel prvi unos komanda
    if (!std::any_of(DozvoljeneKomande.begin(), DozvoljeneKomande.end(), [&](const std::string& s) {return s == input.at(0); })) {// ako nije brisi stream i baci gresku
        greska = KodoviGresaka::PogresnaKomanda;
        return false;
    }
    else { // ako je komanda unesena
        if (!std::any_of(DozvoljeneKomande.begin(), DozvoljeneKomande.begin() + 4, [&](const std::string& s) {return s == input.at(0); })) {// ako komanda ne zahtjeva paramatar provjeri jesu li proslijedjeni
            if (input.size() > 1) {
                greska = KodoviGresaka::SuvisanParametar;
                return false;
            }
            else {
                komanda = dajKomandu(input.at(0));
                return true;
            }
        }
        else { // ako treba parametar provjeri da li su dobri
            if (input.size() == 1) { // ako nema parametra prijavi nedostatak
                greska = KodoviGresaka::NedostajeParametar;
                return false;
            }
            else { //ako ima parametara
                UnesenaKomanda = input.at(0);
            }
        }
    }
    std::string Parametar1, Parametar2{};
    Parametar1 = input.at(1);
    //ako je komanda p1 samo je jedan validan oblik unosa
    if (UnesenaKomanda == "P1" && std::any_of(DozvoljenaKretanja.begin(), DozvoljenaKretanja.end(), [&](const std::string& s) {return s == Parametar1; }) && input.size() == 2) {
        komanda = Komande::PomjeriJednoMjesto;
        smjer = dajSmjer(Parametar1);
        return true;
    }
    else if (UnesenaKomanda == "P1" || !jeBroj(Parametar1) || input.size() != 3) { // ukoliko nije zadovoljen uslov za p1 a komanda je p1, baci gresku, sve druge komanda zahtjevaju brojeve i fixno dva parametra
        greska = KodoviGresaka::NeispravanParametar;
        return false;
    }
    Parametar2 = input.at(2);
    if (!jeBroj(Parametar2)) {
        greska = KodoviGresaka::NeispravanParametar;
        return false;
    }
    komanda = dajKomandu(UnesenaKomanda);
    x = std::stoi(Parametar1);
    y = std::stoi(Parametar2);
    return true;
}

Status status(Tabla& polja, const int& x, const int& y)
{
    if (jeNaMini(polja, x, y)) {
        std::for_each(polja.begin(), polja.end(), [](std::vector<Polje>& v) {for (auto& i : v)i = Polje::Prazno; });
        return Status::KrajPoraz;
    }
    unsigned brojSlobodnih = 0;
    for (int i = 0; i < polja.size(); i++) for (int j = 0; j < polja.size(); j++) if (polja.at(i).at(j) == Polje::Prazno) brojSlobodnih++;
    if (brojSlobodnih == 1 && polja.at(x).at(y) == Polje::Prazno)return Status::KrajPobjeda;
    return Status::NijeKraj;
}

Tabla EkspanzijaMatrice(const Tabla& tabla)  //radi lakse provjere da li se nalaze mine oko tacke
{
    auto rez = Tabla(tabla.size() + 4, std::vector<Polje>(tabla.size() + 4, Polje::Prazno));
    for (int i = 2; i < tabla.size() + 2; i++) for (int j = 2; j < tabla.size() + 2; j++) rez.at(i).at(j) = tabla.at(i - 2).at(j - 2);
    return rez;
}

unsigned BrojMinaUOkoliniTacke(const Tabla& tabla, const int& x, const int& y)  // sigurno za upotrebu sa ekspandovanom matricom
{
    unsigned broj = 0;
    for (int i = x - 1; i <= x + 1; i++) for (int j = y - 1; j <= y + 1; j++) if (tabla.at(i).at(j) == Polje::Mina) (i == x && j == y) ? broj : broj++;
    return broj;
}

Tabla KreirajIgru(int n, const std::vector<std::vector<int>>& mine)
{
    if (!std::all_of(mine.begin(), mine.end(), [](const std::vector<int>& v) {return v.size() == 2; }))throw std::domain_error("Ilegalan format zadavanja mina");
    if (std::any_of(mine.begin(), mine.end(), [&n](const std::vector<int>& v) {return ((v.at(0) >= n) || (v.at(1) >= n)); }))throw std::domain_error("Ilegalne pozicije mina");
    if (n <= 0)throw std::domain_error("Ilegalna velicina");
    Tabla tabla(n, std::vector<Polje>(n, Polje::Prazno));
    for (auto i : mine)tabla.at(i.at(0)).at(i.at(1)) = Polje::Mina;
    return tabla;
}

IntegerMatrica PrikaziOkolinu(const Tabla& polja, const int& x, const int& y)
{
    if (x >= polja.size() || y >= polja.size())throw std::domain_error(std::string("Polje (") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(") ne postoji"));
    IntegerMatrica m(3, std::vector<int>(3));
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) m.at(i).at(j) = BrojMinaUOkoliniTacke(EkspanzijaMatrice(polja), (x + 1 + i), (y + 1 + j));
    return m;
}

Status Idi(Tabla& polja, int& x, int& y, int novi_x, int novi_y)
{
    if (novi_x >= polja.size() || novi_y >= polja.size()) throw std::out_of_range("Izlazak van igrace table");
    try {
        if (polja.at(novi_x).at(novi_y) == Polje::BlokiranoPosjeceno || polja.at(novi_x).at(novi_y) == Polje::BlokiranoMina || polja.at(novi_x).at(novi_y) == Polje::BlokiranoPrazno)throw std::logic_error("Blokirano polje\n");
    }
    catch (...) {
        throw;
    }
    polja.at(x).at(y) = Polje::Posjeceno;
    x = novi_x;
    y = novi_y;
    return status(polja, x, y);
}

Status Idi(Tabla& polja, int& _x, int& _y, Smjerovi smjer)
{
    int x = _x, y = _y;
    switch (smjer) {
    case Smjerovi::GoreLijevo:
        x -= 1;
        y -= 1;
        break;
    case Smjerovi::Gore:
        x -= 1;
        break;
    case Smjerovi::GoreDesno:
        x -= 1;
        y += 1;
        break;
    case Smjerovi::Desno:
        y += 1;
        break;
    case Smjerovi::DoljeDesno:
        x += 1;
        y += 1;
        break;
    case Smjerovi::Dolje:
        x += 1;
        break;
    case Smjerovi::DoljeLijevo:
        x += 1;
        y -= 1;
        break;
    case Smjerovi::Lijevo:
        y -= 1;
        break;
    }
    try {
        return Idi(polja, _x, _y, x, y);
    }
    catch (...) {
        throw;
    }
}

void IzvrsiKomandu(Komande komanda, Tabla& polja, int& x, int& y, Smjerovi p_smjer = Smjerovi::Gore, int p_x = 0, int p_y = 0)
{
    switch (komanda) {
    case Komande::PomjeriJednoMjesto: {
        try {
            auto temp = Idi(polja, x, y, p_smjer);
            if (temp == Status::KrajPoraz) {
                std::cout << "Nagazili ste na minu\n";
                try {
                    ZavrsiIgru(polja);
                }
                catch (...) {
                    throw;
                }
            }
            else if (temp == Status::KrajPobjeda) {
                std::cout << "Bravo, obisli ste sva sigurna polja\n";
                try {
                    ZavrsiIgru(polja);
                }
                catch (...) {
                    throw;
                }
            }
            std::cout << "Tekuca pozicija igraca je (" << x << "," << y << ")\n";
            break;
        }
        catch (...) {
            throw;
        }

    case Komande::PomjeriDalje: {
        try {
            auto temp = Idi(polja, x, y, p_x, p_y);
            if (temp == Status::KrajPoraz) {
                std::cout << "Nagazili ste na minu\n";
                try {
                    ZavrsiIgru(polja);
                }
                catch (...) {
                    throw;
                }

            }
            else if (temp == Status::KrajPobjeda) {
                std::cout << "Bravo, obisli ste sva sigurna polja\n";
                try {
                    ZavrsiIgru(polja);
                }
                catch (...) {
                    throw;
                }
            }
        }
        catch (...) {
            throw;
        }
        std::cout << "Tekuca pozicija igraca je (" << x << "," << y << ")\n";
        break;
    }

    case Komande::Blokiraj: {
        try {
            BlokirajPolje(polja, p_x, p_y);
        }
        catch (...) {
            throw;
        }
        break;
    }

    case Komande::Deblokiraj: {
        try {
            DeblokirajPolje(polja, p_x, p_y);
        }
        catch (...) {
            throw;
        }
        break;
    }

    case Komande::PrikaziOkolinu: {
        for (auto& i : PrikaziOkolinu(polja, x, y)) {
            for (auto& j : i) std::cout << j << ' ';
            std::cout << "\n";
        }
        break;
    }

    case Komande::ZavrsiIgru: {
        try {
            ZavrsiIgru(polja);
        }
        catch (...) {
            throw;
        }
        break;
    }

    case Komande::KreirajIgru: {
        std::cout << "Unesite broj polja: ";
        int n;
        std::cin >> n;
        while (!std::cin || std::cin.peek() != '\n' || n <= 0) {
            std::cout << "Greska, unesite ponovo!\n";
            OcistiTok();
            std::cin >> n;
        }
        std::cout << "Unesite pozicije mina: ";
        std::vector<std::vector<int>> mine;
        std::string s;
        OcistiTok();
        getline(std::cin, s);
        while (s != ".") {
            try {
                auto temp = UnesiMine(s);
                if (temp.at(0) < n && temp.at(1) < n && temp.at(0) >= 0 && temp.at(1) >= 0)mine.push_back(temp);
                else std::cout << "Greska, unesite ponovo!\n";
                getline(std::cin, s);
            }
            catch (std::domain_error err) {
                std::cout << "Greska, unesite ponovo!\n";
                getline(std::cin, s);
            }
        }
        try {
            polja = KreirajIgru(n, mine);
        }
        catch (...) {
            throw;
        }
        x = 0;
        y = 0;
    }
    }
    }
}

int main()
{
    Komande komanda;
    Smjerovi smjer;
    Tabla polja;
    int x{ 0 }, y{ 0 }, x1{ 0 }, y1{ 0 };
    KodoviGresaka greska;
    while (1) {
        try {
            std::cout << "Unesite komandu: ";
            if (UnosKomande(komanda, smjer, x1, y1, greska)) IzvrsiKomandu(komanda, polja, x, y, smjer, x1, y1);
            else PrijaviGresku(greska);
        }
        catch (std::runtime_error) {
            std::cout << "Dovidjenja!";
            return 0;
        }
        catch (std::logic_error err) {
            std::cout << err.what();
        }
        catch (...) {
            std::cout << "Nesto drugo";
            return -1;
        }
    }
}
