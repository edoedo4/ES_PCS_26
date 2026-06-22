#include <iostream>
#include <stack>
#pragma once

template<typename T>
class lifo {

    std::stack<T> s;

public:
    /*Costruttore di default*/
    lifo() = default;
    
    /*Implementazione put(), inserisce l'elemento*/
    void put(const T& x) {
        s.push(x);
    }

    /*Implementazione get(), estrae l'elemento*/
    T get() {
        T x = s.top();
        s.pop();
        return x;
    }
    /*Implementazione empty(), controlla se è vuoto*/
    bool empty() const {
        return s.empty();
    }
};