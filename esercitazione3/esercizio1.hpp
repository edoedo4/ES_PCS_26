#include <concepts> 
#include <iostream>
#include <numeric>

template <typename I> requires std::integral<I> // la classe funziona solo con interi
class rational {
    I num_;
    I den_;
    void simplify() {
        if (den_ == 0) return;
        I gcd = std::gcd(num_,den_); // lo salvo come variabile per evitare di calcolarlo due volte
        num_ = num_ / gcd;
        den_ = den_ / gcd;
        if (den_ < 0) { // non voglio un denominatore negativo
            num_ = -num_;
            den_ = -den_;
        }
    }

public:
    /* Costruttore di default */
    rational()
        : num_(0), den_(1) // inizializzo la frazione 0/1
    {}
    /* Costruttore user-defined */
    rational(const I& px, const I& py)
        : num_(px), den_(py) {
        if (den_ != 0)
            simplify();
        }
    /* Restituiscono i valori di x e y */
    I num() const { return num_; }
    I den() const { return den_; }

    /* Implementazione canonica dell'incremento */
    rational& operator+=(const rational& other) {
    num_ = num_*other.den_+den_*other.num_;
    den_ = den_*other.den();
    simplify();
    return *this;
    }

    /* Implementazione canonica della somma */
    rational operator+(const rational& other) const {
    rational ret = *this;
    ret += other;
    return ret;
    }

    /* Implementazione canonica del decremento */
    rational& operator-=(const rational& other) {
    num_ = num_*other.den()- den_*other.num();
    den_ = den_*other.den();
    simplify();
    return *this;
    }

    /* Implementazione canonica della differenza */
    rational operator-(const rational& other) const {
    rational ret = *this;
    ret -= other;
    return ret;
    }

    /* Implementazione canonica del prodotto *= */
    rational& operator*=(const rational& other) {
    num_ = num_*other.num();
    den_ = den_*other.den();
    simplify();
    return *this;
    }

    /* Implementazione canonica del prodotto * */
    rational operator*(const rational& other) const {
    rational ret = *this;
    ret *= other;
    return ret;
    }

    /* Implementazione canonica della divisione /= */
    rational& operator/=(const rational& other) {
    num_ = num_*other.den();
    den_ = den_*other.num();
    simplify();
    return *this;
    }

    /* Implementazione canonica della divisione / */
    rational operator/(const rational& other) const {
    rational ret = *this;
    ret /= other;
    return ret;
    }
};

template <typename I>
std::ostream& operator<<(std::ostream& os, const rational<I>& r) { // Casi Inf e NaN
    if (r.den() == 0) {
        if (r.num() == 0)
        os << "NaN";
        else 
        os << "Inf";
    }
    else {
        os << r.num() << "/" << r.den();
    }
    return os;
    }