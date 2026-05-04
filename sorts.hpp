#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// Merge

template <typename I>
void mergeMio(std::vector<I>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<I> L(n1), R(n2); // creo i due vettori

    for (int i = 0; i < n1; i++) // copio i dati sul vettore L
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++) // copio i dati sul vettore R
        R[j] = A[q + 1 + j];

    int i = 0, j = 0;
    int k = p;

    while (i < n1 && j < n2) { // riunisco insieme i vettori temp
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) { // se ne rimangono, copio gli elementi rimanenti di L[]
        A[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) { // se ne rimangono, copio gli elementi rimanenti di L[]
        A[k] = R[j];
        j++;
        k++;
    }
}

// Mergesort 

template <typename I>
void mergeSort(std::vector<I>& A, int p, int r) {
    if (p<r) {
        int q = (p+r)/2;
        mergeSort(A, p, q);
        mergeSort(A, q+1, r);
        mergeMio(A,p,q,r);
    }
}

// Partition 

template <typename I>
int partitionMio(std::vector<I>& A, int p, int r) {
    I x = A[r]; // x rappresenta il pivot
    int i = p - 1;

for (int j = p; j <= r - 1; j++) {
    if (A[j] <= x) {
        i++;
        std::swap(A[i],A[j]);
    }
    }
std::swap(A[i+1],A[r]);
return i+1;    
}

// Quicksort 

template <typename I>
void quickSort(std::vector<I>& A, int p, int r) {
    if (p<r) {
        int q = partitionMio(A,p,r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

// Insertion sort modificato

template <typename I>
void insertionSortModificato(std::vector<I>& A, int p, int r) {
    for (int j = p + 1; j <= r; j++) {
        I key = A[j];
        int i = j-1;
        while (i >= p && A[i] > key) {
            A[i+1]=A[i];
            i = i-1;
        }
        A[i+1] = key;
    }
}

// Quicksort potenziato

template <typename I>
void quickSortPotenziato(std::vector<I>& A, int p, int r) {
    const int soglia = 64; // ricavato sperimentalmente tramite test
    if (p<r) {
        int dim = r - p + 1;
        if (dim <= soglia) {
            insertionSortModificato(A, p, r);
        }
        else {
        int q = partitionMio(A, p, r);
        quickSortPotenziato(A, p, q - 1);
        quickSortPotenziato(A, q + 1, r);
        }
    }
}

// Bubble sort 

template <typename I>
void bubbleSort(std::vector<I>& A) {
        bool cambio = 1;
        while (cambio==1) {
            cambio = 0;
            for (int i = 0; i < A.size()-1; i++) {
                if (A[i] > A[i+1]) {
                    std::swap(A[i],A[i+1]);
                    cambio = 1;
                }
            }
        }
    }

// Insertion sort

template <typename I>
void insertionSort(std::vector<I>& A) {
    for (int j = 1; j < A.size(); j++) {
        I key = A[j];
        int i = j-1;
        while (i >= 0 && A[i] > key) {
            A[i+1]=A[i];
            i = i-1;
        }
        A[i+1] = key;
    }
}

// Selection sort

template <typename I>
void selectionSort(std::vector<I>& A) {
    for (int i = 0; i < A.size() -1; i++) {
        int min = i;
        for (int j = i+1; j < A.size(); j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        std::swap(A[i],A[min]);
    }
}

// Funzione isSorted

template <typename T>
bool isSorted(const std::vector<T>& vector) {
    if (vector.size() == 0) {
    return true;
    }
    for (int i = 0; i < vector.size() -1; i++) {
        if (vector[i] > vector[i+1]) {
            return false;
        }
    }
    return true;
}