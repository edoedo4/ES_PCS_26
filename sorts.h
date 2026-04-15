#include <vector>
#include <algorithm>
#include <iostream>

// Bubble sort 

template <typename I>
void bubbleSort(std::vector<I>& A) {
        bool cambio = 1;
        while (cambio==1) {
            cambio = 0;
            for (int i = 0; i < A.size()-1; i++) {
                if (A[i] > A[i+1]) {
                    I var = A[i+1];
                    A[i+1] = A[i];
                    A[i] = var;
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
        I c = A[i];
        A[i] = A[min];
        A[min] = c;
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