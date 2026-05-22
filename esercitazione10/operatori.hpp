#pragma once 
#include <vector>
#include <cmath>

// somma (u + v)
std::vector<double> vec_somma(const std::vector<double>& u, const std::vector<double>& v) {
    std::vector<double> risultato(u.size()); // gli fornisco la dimensione
    for (size_t i = 0; i < u.size(); i++) {
        risultato[i] = u[i] + v[i];
    }
    return risultato;
}

// sottrazione (u - v)
std::vector<double> vec_sottrazione(const std::vector<double>& u, const std::vector<double>& v) {
    std::vector<double> risultato(u.size());
    for (size_t i = 0; i < u.size(); i++) {
        risultato[i] = u[i] - v[i];
    }
    return risultato;
}

// moltiplicazione scalare-vettore (alpha * v)
std::vector<double> vec_moltiplicazione_scalare(double alpha, const std::vector<double>& v) {
    std::vector<double> risultato(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        risultato[i] = alpha * v[i];
    }
    return risultato;
}

// prodotto scalare tra due vettori (u * v)
double vec_prodotto_scalare(const std::vector<double>& u, const std::vector<double>& v) {
    double somma = 0.0;
    for (size_t i = 0; i < u.size(); i++) {
        somma += u[i] * v[i];
    }
    return somma;
}

// norma di un vettore ||v||
double norma_vettore(const std::vector<double>& v) {
    return std::sqrt(vec_prodotto_scalare(v, v));
}

// prodotto matrice-vettore (A * x)
std::vector<double> vec_prodotto_matrice(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    std::vector<double> risultato(A.size(), 0.0);
    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < x.size(); ++j) {
            risultato[i] += A[i][j] * x[j];
        }
    }
    return risultato;
}