//TP 2018/2019: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <ctime>
#include <stdexcept>
#include <cmath>

static constexpr bool jeSavrsenKvadrat (const int& n){return static_cast<int>(sqrt(n)) * static_cast<int>(sqrt(n)) == n;}

void SumaCetiriKvadrata(const int &n, int &a, int &b, int &c, int &d)
{
    if(n<0) throw std::domain_error("Broj koji se rastavlja mora biti nenegativan");
    for(unsigned i = 0 ; i <= sqrt(n) ; i++)
        for(unsigned j = i ; j <= sqrt(n-i*i) ; j++)
            for(unsigned k = j ; k <= sqrt(n-i*i) ; k++)
                if( (jeSavrsenKvadrat(n-i*i-j*j-k*k)) ) 
                    {
                        auto l = static_cast<int>(sqrt(n-i*i-j*j-k*k));
                        a = l;
                        b = k;
                        c = j;
                        d = i;
                        return;
                    }

}

int main ()
{
    std::cout << "Unesite broj: ";
    int n,a{0},b{0},c{0},d{0};
    std::cin>>n;
    try {
        SumaCetiriKvadrata(n,a,b,c,d);
        std::cout << "Broj "<<n<<" se moze zapisati kao zbir kvadrata brojeva: "<< a << ", " << b << ", " << c << ", " << d <<'.';
    } catch(std::domain_error err) {
        std::cout<<err.what();
    }
    return 0;
}
