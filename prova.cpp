#pragma once

#define STACK_SIZE 8

template<typename T>
struct stack {
    T   data[STACK_SIZE];
    int top;

            stack();
            stack(const stack& other);
    void    push(int value);
    int     pop();
    bool    empty();
    bool    full();
};