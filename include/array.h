#ifndef ARRAY_H
#define ARRAY_H

#include "figure.h"
#include <memory>
#include <stdexcept>
#include <iostream>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t current_size;
    size_t current_capacity;

    void resize_with_move(size_t new_capacity) {
        auto new_data = std::shared_ptr<T[]>(new T[new_capacity]);
        for (size_t i = 0; i < current_size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = std::move(new_data);
        current_capacity = new_capacity;
    }

public:
    Array() : current_size(0), current_capacity(10) {
        data = std::shared_ptr<T[]>(new T[current_capacity]);
    }
    
    Array(size_t capacity) : current_size(0), current_capacity(capacity) {
        data = std::shared_ptr<T[]>(new T[current_capacity]);
    }
    
    Array(const Array& other) : current_size(other.current_size), current_capacity(other.current_capacity) {
        data = std::shared_ptr<T[]>(new T[current_capacity]);
        for (size_t i = 0; i < current_size; ++i) {
            data[i] = other.data[i];
        }
    }
    
    Array(Array&& other) noexcept 
        : data(std::move(other.data)), 
          current_size(other.current_size), 
          current_capacity(other.current_capacity) {
        other.current_size = 0;
        other.current_capacity = 0;
    }
    
    ~Array() = default;
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            current_size = other.current_size;
            current_capacity = other.current_capacity;
            data = std::shared_ptr<T[]>(new T[current_capacity]);
            for (size_t i = 0; i < current_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            current_size = other.current_size;
            current_capacity = other.current_capacity;
            other.current_size = 0;
            other.current_capacity = 0;
        }
        return *this;
    }
    
    void add(const T& item) {
        if (current_size >= current_capacity) {
            resize_with_move(current_capacity * 2);
        }
        data[current_size] = item;
        current_size++;
    }
    
    void add(T&& item) {
        if (current_size >= current_capacity) {
            resize_with_move(current_capacity * 2);
        }
        data[current_size] = std::move(item);
        current_size++;
    }
    
    void remove_at(size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range in array remove");
        }
        for (size_t i = index; i < current_size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        current_size--;
    }
    
    T& operator[](size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range in array access");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range in array const access");
        }
        return data[index];
    }
    
    size_t size() const { return current_size; }
    size_t capacity() const { return current_capacity; }
    bool empty() const { return current_size == 0; }
    void clear() { current_size = 0; }
};

#endif