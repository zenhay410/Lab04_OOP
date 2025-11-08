#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>

template<typename T>
class Array {
    std::shared_ptr<T[]> data_;
    size_t size_;
    size_t cap_;

    void resize() {
        size_t new_cap = cap_ * 2;
        auto new_data = std::shared_ptr<T[]>(new T[new_cap]);
        for (size_t i = 0; i < size_; i++) {
            new_data[i] = std::move(data_[i]);
        }
        data_ = std::move(new_data);
        cap_ = new_cap;
    }

public:
    Array() : size_(0), cap_(10) {
        data_ = std::shared_ptr<T[]>(new T[cap_]);
    }
    
    void add(const T& item) {
        if (size_ >= cap_) {
            resize();
        }
        data_[size_] = item;
        size_++;
    }
    
    void remove(size_t idx) {
        if (idx >= size_) {
            throw std::out_of_range("bad index");
        }
        for (size_t i = idx; i < size_-1; i++) {
            data_[i] = std::move(data_[i+1]);
        }
        size_--;
    }
    
    T& get(size_t idx) {
        if (idx >= size_) {
            throw std::out_of_range("bad index");
        }
        return data_[idx];
    }
    
    T& operator[](size_t idx) {
        return get(idx);
    }
    
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
};

#endif