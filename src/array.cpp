#include "../include/array.h"

template class Array<int>;
template class Array<float>;
template class Array<double>;
template class Array<std::string>;
template class Array<FigurePtr<int>>;
template class Array<FigurePtr<float>>;
template class Array<FigurePtr<double>>;

template<typename T>
void Array<T>::resize_with_move(size_t new_capacity) {
    auto new_data = std::shared_ptr<T[]>(new T[new_capacity]);
    for (size_t i = 0; i < current_size; ++i) {
        new_data[i] = std::move(data[i]);
    }
    data = std::move(new_data);
    current_capacity = new_capacity;
}

template<typename T>
Array<T>::Array() : current_size(0), current_capacity(10) {
    data = std::shared_ptr<T[]>(new T[current_capacity]);
}

template<typename T>
Array<T>::Array(size_t capacity) : current_size(0), current_capacity(capacity) {
    data = std::shared_ptr<T[]>(new T[current_capacity]);
}

template<typename T>
Array<T>::Array(const Array& other) : current_size(other.current_size), current_capacity(other.current_capacity) {
    data = std::shared_ptr<T[]>(new T[current_capacity]);
    for (size_t i = 0; i < current_size; ++i) {
        data[i] = other.data[i];
    }
}

template<typename T>
Array<T>::Array(Array&& other) noexcept 
    : data(std::move(other.data)), 
      current_size(other.current_size), 
      current_capacity(other.current_capacity) {
    other.current_size = 0;
    other.current_capacity = 0;
}

template<typename T>
Array<T>::~Array() {}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
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

template<typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
        current_size = other.current_size;
        current_capacity = other.current_capacity;
        other.current_size = 0;
        other.current_capacity = 0;
    }
    return *this;
}

template<typename T>
void Array<T>::add(const T& item) {
    if (current_size >= current_capacity) {
        resize_with_move(current_capacity * 2);
    }
    data[current_size] = item;
    current_size++;
}

template<typename T>
void Array<T>::add(T&& item) {
    if (current_size >= current_capacity) {
        resize_with_move(current_capacity * 2);
    }
    data[current_size] = std::move(item);
    current_size++;
}

template<typename T>
void Array<T>::remove_at(size_t index) {
    if (index >= current_size) {
        throw std::out_of_range("Index out of range in array remove");
    }
    for (size_t i = index; i < current_size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    current_size--;
}

template<typename T>
T& Array<T>::operator[](size_t index) {
    if (index >= current_size) {
        throw std::out_of_range("Index out of range in array access");
    }
    return data[index];
}

template<typename T>
const T& Array<T>::operator[](size_t index) const {
    if (index >= current_size) {
        throw std::out_of_range("Index out of range in array const access");
    }
    return data[index];
}

template<typename T>
bool Array<T>::empty() const {
    return current_size == 0;
}

template<typename T>
void Array<T>::clear() {
    current_size = 0;
}