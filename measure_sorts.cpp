# include "randfiller.h"
# include "timecounter.h"
# include <algorithm>
# include <vector>
# include <iostream>
# include <stdlib.h>
# include "sorts.hpp"

template <typename T>
void testTime() {

    randfiller randf; // randfiller è una classe, così eseguo il costruttore
    timecounter timer; // timecounter è una classe, così eseguo il costruttore

    const int nVettori = 100;

    for (int i = 4; i <= 8192; i *= 2) {
        std::vector<std::vector<T>> setVettori(nVettori, std::vector<T>(i));
        for (int j = 0; j < nVettori; j++) {
            randf.fill(setVettori[j], -1000, 1000);
        }
        std::vector<std::vector<T>> copiaInsertion = setVettori;
        std::vector<std::vector<T>> copiaSelection = setVettori;
        std::vector<std::vector<T>> copiaNativo = setVettori;
        std::vector<std::vector<T>> copiaMerge = setVettori;
        std::vector<std::vector<T>> copiaQuick = setVettori;
        std::vector<std::vector<T>> copiaQuickPotenziato = setVettori;
        
        timer.tic();
        for (int j=0; j < nVettori; j++) {
            bubbleSort(setVettori[j]);
        }
        double tempoMedioBubble = timer.toc()/nVettori;

        timer.tic();
        for (int j=0; j < nVettori; j++) {
            insertionSort(copiaInsertion[j]);
        }
        double tempoMedioInsertion = timer.toc()/nVettori;

        timer.tic();
        for (int j=0; j < nVettori; j++) {
            selectionSort(copiaSelection[j]);
        }
        double tempoMedioSelection = timer.toc()/nVettori;
        
        timer.tic();
        for (int j=0; j < nVettori; j++) {
            mergeSort(copiaMerge[j], 0, copiaMerge[j].size()-1);
        }
        double tempoMedioMerge = timer.toc()/nVettori;

        timer.tic();
        for (int j=0; j < nVettori; j++) {
            quickSort(copiaQuick[j], 0, copiaQuick[j].size()-1);
        }
        double tempoMedioQuick = timer.toc()/nVettori;

        timer.tic();
        for (int j=0; j < nVettori; j++) {
            std::sort(copiaNativo[j].begin(), copiaNativo[j].end());
        }
        double tempoMedioNativo = timer.toc()/nVettori;

        timer.tic();
        for (int j=0; j < nVettori; j++) {
            quickSortPotenziato(copiaQuickPotenziato[j], 0, copiaQuickPotenziato[j].size()-1);
        }
        double tempoMedioQuickPotenziato = timer.toc()/nVettori;

        std::cout << "Dimensione del vettore: " << i << "\n" 
        << "Tempo impiegato BubbleSort: " << tempoMedioBubble << "\n" 
        << "Tempo impiegato InsertionSort: " << tempoMedioInsertion << "\n" 
        << "Tempo impiegato SelectionSort: " << tempoMedioSelection << "\n" 
        << "Tempo impiegato Nativo: " << tempoMedioNativo << "\n"
        << "Tempo impiegato Merge: " << tempoMedioMerge << "\n"
        << "Tempo impiegato Quick: " << tempoMedioQuick << "\n"
        << "Tempo impiegato QuickPotenziato: " << tempoMedioQuickPotenziato << "\n\n";
    }
}

int main() {
    testTime<int>();
    return EXIT_SUCCESS;
}