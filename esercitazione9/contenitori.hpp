#include <queue>
#include <stack>
#pragma once // aiuto da Gemini, serve per non leggere due volte lo stesso .hpp

template <typename T>
class fifo {
    private:
        std::queue<T> q;
    public:
        fifo() = default; // costruttore di default

        void put(T val) {
            q.push(val);
        }
        T get() {
            T val = q.front();
            q.pop();
            return val;
        }
        bool empty() const {
            return q.empty();
        }
};

template <typename T>
class lifo {
    private:
        std::stack<T> s;
    public:
        lifo() = default; // costruttore di default, meglio delle parentesi vuote

        void put(T val) {
            s.push(val);
        }
        int get() {
            int val = s.top();
            s.pop();
            return val;
        }
        bool empty() const {
            return s.empty();
        }
};