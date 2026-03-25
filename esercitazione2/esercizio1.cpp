# include <iostream>

int main()
{
    double ad[4] = {0.0, 1.1, 2.2, 3.3};
    float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    int ai[3] = {0, 1, 2};

    int x = 1;
    float y = 1.1; // ha dimensione 4

    std::cout << &x << "\n"; // indirizzo di x
    std::cout << &y << "\n"; // indirizzo di y
    // noto che y viene memorizzata prima di x e la differenza tra i due indirizzi è 4, che è la dimensione
    // del float y 

    (&y)[1] = 0; // all'indirizzo di y mi sposto avanti una volta di 4 (dimensione di un float)

    std::cout << x << "\n";

    for (int i=0; i<4; i++) {
        std::cout << &ad[i] << "\n";
    }

    for (int i=0; i<8; i++) {
        std::cout << &af[i] << "\n";
    }

    for (int i=0; i<3; i++) {
        std::cout << &ai[i] << "\n";
    }

    return 0;
}