# include "randfiller.h"
# include "timecounter.h"
# include <algorithm>
# include <vector>
# include <iostream>
# include <stdlib.h>
# include "sorts.h"

void testTime() {

    randfiller randf; // randfiller è una classe, così eseguo il costruttore
    timecounter timer; // timecounter è una classe, così eseguo il costruttore

    for (size_t i = 4; i <= 8192; i *= 2) {
        std::vector<int> vec(i);
        randf.fill(vec, -1000, 1000);
        std::vector<int> copiaInsertion = vec;
        std::vector<int> copiaSelection = vec;
        std::vector<int> copiaNativo = vec;
        timer.tic();
        bubbleSort(vec);
        double tempoImpiegatoBubble = timer.toc();
    
        timer.tic();
        insertionSort(copiaInsertion);
        double tempoImpiegatoInsertion = timer.toc();
        
        timer.tic();
        selectionSort(copiaSelection);
        double tempoImpiegatoSelection = timer.toc();
        
        timer.tic();
        std::sort(copiaNativo.begin(), copiaNativo.end() );
        double tempoImpiegatoNativo = timer.toc();

        std::cout << "Dimensione del vettore: " << i << "\n" 
        << "Tempo impiegato BubbleSort: " << tempoImpiegatoBubble << "\n" 
        << "Tempo impiegato InsertionSort: " << tempoImpiegatoInsertion << "\n" 
        << "Tempo impiegato SelectionSort: " << tempoImpiegatoSelection << "\n" 
        << "Tempo impiegato Nativo: " << tempoImpiegatoNativo << "\n" << "\n";
    }
}

int main() {
    testTime();
    return EXIT_SUCCESS;
}