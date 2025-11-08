#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>

template<typename T>
class Array {
    std::shared_ptr<T[]> d;
    size_t s;
    size_t c;

    void resize() {
        size_t nc = c * 2;
        auto nd = std::shared_ptr<T[]>(new T[nc]);
        for (size_t i = 0; i < s; i++) {
            nd[i] = std::move(d[i]);
        }
        d = std::move(nd);
        c = nc;
    }

public:
    Array() : s(0), c(10) {
        d = std::shared_ptr<T[]>(new T[c]);
    }
    
    void add(const T& item) {
        if (s >= c) {
            resize();
        }
        d[s] = item;
        s++;
    }
    
    void remove(size_t idx) {
        if (idx >= s) {
            throw std::out_of_range("bad idx");
        }
        for (size_t i = idx; i < s-1; i++) {
            d[i] = std::move(d[i+1]);
        }
        s--;
    }
    
    T& get(size_t idx) {
        if (idx >= s) {
            throw std::out_of_range("bad idx");
        }
        return d[idx];
    }
    
    T& operator[](size_t idx) {
        return get(idx);
    }
    
    size_t size() const { return s; }
    bool empty() const { return s == 0; }
};

#endif