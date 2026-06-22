#include <concepts> 
#include <iostream>
#pragma once 

template<typename I> 
class unidirected_edge
{
    I a;
    I b;

public:
    unidirected_edge(I x, I y) {
        if (x <= y) {
        a = x;
        b = y;
        } else {
        a = y;
        b = x;
        }
    }
    I from() const { return a; }
    I to() const { return b; }

    bool operator<(const unidirected_edge& other) const {
        if (from() < other.from()) return true;
        if (from() > other.from()) return false;
        return to() < other.to();
    }

    bool operator==(const unidirected_edge& other) const {
        return from() == other.from() && to() == other.to();
    }
    
};

template<typename I>
std::ostream& operator<<(std::ostream& os, const unidirected_edge<I>& e) {
    return os << "(" << e.from() << "," << e.to() << ")";
};