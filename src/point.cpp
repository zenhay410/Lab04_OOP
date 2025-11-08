#include "../include/point.h"

template class Point<int>;
template class Point<float>;
template class Point<double>;

template<ScalarType T>
Point<T>::Point() noexcept : x_val(0), y_val(0) {}

template<ScalarType T>
Point<T>::Point(T x, T y) noexcept : x_val(x), y_val(y) {}

template<ScalarType T>
Point<T>::Point(const Point& other) noexcept : x_val(other.x_val), y_val(other.y_val) {}

template<ScalarType T>
Point<T>::Point(Point&& other) noexcept : x_val(std::move(other.x_val)), y_val(std::move(other.y_val)) {}

template<ScalarType T>
Point<T>::~Point() noexcept {}

template<ScalarType T>
Point<T>& Point<T>::operator=(const Point& other) noexcept {
    if (this != &other) {
        x_val = other.x_val;
        y_val = other.y_val;
    }
    return *this;
}

template<ScalarType T>
Point<T>& Point<T>::operator=(Point&& other) noexcept {
    if (this != &other) {
        x_val = std::move(other.x_val);
        y_val = std::move(other.y_val);
    }
    return *this;
}

template<ScalarType T>
bool Point<T>::operator==(const Point& other) const noexcept {
    return x_val == other.x_val && y_val == other.y_val;
}

template<ScalarType T>
bool Point<T>::operator!=(const Point& other) const noexcept {
    return !(*this == other);
}

template<ScalarType T>
std::ostream& operator<<(std::ostream& os, const Point<T>& pt) {
    os << "(" << pt.x_val << ", " << pt.y_val << ")";
    return os;
}