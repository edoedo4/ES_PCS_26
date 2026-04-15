# include "randfiller.h"
# include <stdlib.h>
# include <string>
# include <vector>
# include <iostream>
# include "sorts.h"

int main() {
    randfiller randf; // randfiller è una classe, così eseguo il costruttore
    for (size_t i = 0; i < 100; i++) {
        int dim = rand() % 100 + 1; // calcolo il resto della divisione che varia da 0 e 99 e lo traslo a destra di un'unità
        std::vector<int> vec(dim);
        randf.fill(vec, -1000, 1000);
        bubbleSort(vec);
        if (isSorted(vec) == false) {
            std::cout << "Il vettore non è ordinato";
            return EXIT_FAILURE;
        }
    }

    std::vector<std::string> provaStringhe = {"Le", "famiglie", "felici", "si", "somigliano", "tutte", "le", "famiglie", "infelici", "lo", "sono", "ognuna", "a", "modo", "suo"};
    bubbleSort(provaStringhe);
        if (isSorted(provaStringhe) == false) {
            std::cout << "Il vettore non è ordinato";
            return EXIT_FAILURE;
        }

        std::cout << "Il vettore è ordinato";
        return EXIT_SUCCESS;
}