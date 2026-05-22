#include <iostream>
#include <vector>
#include "operatori.hpp"

std::vector<double> gradiente_coniugato(const std::vector<std::vector<double>>& A, const std::vector<double>& b, std::vector<double> x0, double tolleranza) {
    std::vector<double> x = x0; // inizializzo x_0
    std::vector<double> Ax = vec_prodotto_matrice(A, x);
    std::vector<double> r = vec_sottrazione(b, Ax);
    std::vector<double> p = r;
    
    while (norma_vettore(r) > tolleranza) {

        std::vector<double> Ap = vec_prodotto_matrice(A, p);
        double p_scalare_Ap = vec_prodotto_scalare(p, Ap);
        double alpha = vec_prodotto_scalare(p, r) / p_scalare_Ap;
        x = vec_somma(x, vec_moltiplicazione_scalare(alpha, p));
        std::vector<double> Ax_nuovo = vec_prodotto_matrice(A, x);
        std::vector<double> r_nuovo = vec_sottrazione(b, Ax_nuovo);
        double beta = vec_prodotto_scalare(Ap, r_nuovo) / p_scalare_Ap; // è la stessa coda di quello dello pseudocodice perché A è simmetrica
        p = vec_sottrazione(r_nuovo, vec_moltiplicazione_scalare(beta, p));
        r = r_nuovo;
    }
    return x;
}

int main() {
    std::vector<std::vector<double>> A = {
        {4.0, 1.0},
        {1.0, 3.0}
    };
    std::vector<double> b = {1.0, 2.0};
    std::vector<double> x0 = {0.0, 0.0}; // parto da 0
    double tol = 1e-8; // arbitraria, è ragionevole
    std::vector<double> soluzione = gradiente_coniugato(A, b, x0, tol);
    std::cout << "Soluzione trovata = [";
    for (double valore : soluzione) {
        std::cout  << valore << " ";
    }
    std::cout << "]\n";
    std::cout << "Soluzione attesa  = [0.0909 0.6364]\n"; // calcolata a mano, siccome in questo caso i calcoli erano veloci
    return 0;
}