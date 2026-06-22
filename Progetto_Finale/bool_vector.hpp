#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>

class bool_vector
{
private:
    // internamente è solo un vettore di interi, dove ogni elemento è 0 o 1
    std::vector<int> data_;

public:
    // costruttore vuoto, serve per dichiarare un bool_vector senza inizializzarlo
    // esempio: bool_vector v;
    bool_vector() = default;

    // costruttore che crea un vettore di n zeri
    // esempio: bool_vector v(5) crea [0, 0, 0, 0, 0]
    explicit bool_vector(int n) : data_(n, 0) {}

    // restituisce quanti elementi ha il vettore
    int size() const
    {
        return data_.size();
    }

    // legge l'elemento in posizione i (senza poterlo modificare)
    // esempio: int x = v[2];
    int operator[](int i) const
    {
        return data_[i];
    }

    // legge e modifica l'elemento in posizione i
    // esempio: v[2] = 1;
    int& operator[](int i)
    {
        return data_[i];
    }

    // imposta l'elemento in posizione i al valore x (solo 0 o 1)
    // esempio: v.set(3, 1) mette 1 in posizione 3
    void set(int i, int x)
    {
        if (x != 0 && x != 1)
            std::cerr << "Errore: bool_vector accetta solo 0 o 1\n";
        data_[i] = x;
    }

    // prodotto scalare modulo 2 tra due vettori
    // moltiplica elemento per elemento e somma tutto, poi prende il resto della divisione per 2
    // esempio: [1,0,1] * [1,1,1] = 1*1 + 0*1 + 1*1 = 2, mod 2 = 0
    int prod_scal_mod2(const bool_vector& other) const
    {
        if (size() != other.size())
            std::cerr << "Errore: I vettori hanno dimensioni diverse\n";

        int risultato = 0;
        for (int i = 0; i < size(); i++)
            risultato += data_[i] * other.data_[i];

        return risultato % 2;
    }

    // XOR elemento per elemento: this = this XOR other
    // lo XOR è come la somma modulo 2: 0^0=0, 0^1=1, 1^0=1, 1^1=0
    // esempio: [1,0,1].xor_with([1,1,0]) -> [0,1,1]
    void xor_with(const bool_vector& other)
    {
        if (size() != other.size())
            std::cerr << "Errore: I vettori hanno dimensioni diverse\n";

        for (int i = 0; i < size(); i++)
            data_[i] = data_[i] ^ other.data_[i];
    }


    bool operator==(const bool_vector& other) const
    {
        if (size() != other.size()) return false;
        for (int i = 0; i < size(); i++)
            if (data_[i] != other.data_[i]) return false;
        return true;
    }

    
    // controlla se il vettore è tutto zeri
    // esempio: [0,0,0].is_zero() -> true, [0,1,0].is_zero() -> false
    bool empty() const
    {
        for (int i = 0; i < size(); i++)
            if (data_[i] != 0)
                return false;
        return true;
    }

    // stampa il vettore, utile per il debug
    // esempio: cout << v stampa (1, 0, 1)
    friend std::ostream& operator<<(std::ostream& os, const bool_vector& v)
    {
        os << "(";
        for (int i = 0; i < v.size(); i++)
        {
            os << v[i];
            if (i + 1 < v.size())
                os << ", ";
        }
        os << ")";
        return os;
    }
};