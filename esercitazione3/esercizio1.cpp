# include "esercizio1.hpp"
# include <iostream> 

int main() {

    rational<int> a(3,0);
    rational<int> b(0,0);

    rational<int> c = a - b;

    std::cout << "Prima frazione: " << a << "\n";
    std::cout << "Seconda frazione: " << b << "\n";
    std::cout << "Risultato: " << c << "\n";

    return 0;
}