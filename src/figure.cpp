#include "../include/figure.h"

template class Figure<int>;
template class Figure<float>;
template class Figure<double>;

template<ScalarType T>
Figure<T>::~Figure() {}

template<ScalarType T>
Figure<T>::operator double() const {
    return area();
}

template<ScalarType T>
bool Figure<T>::operator==(const Figure& other) const {
    return area() == other.area();
}

template<ScalarType T>
bool Figure<T>::operator!=(const Figure& other) const {
    return !(*this == other);
}

template<ScalarType T>
bool Figure<T>::operator<(const Figure& other) const {
    return area() < other.area();
}

template<ScalarType T>
bool Figure<T>::operator>(const Figure& other) const {
    return area() > other.area();
}

template<ScalarType T>
void Figure<T>::print_info() const {
    std::cout << name() << " info:" << std::endl;
    std::cout << "  Geometric center: " << geometric_center() << std::endl;
    std::cout << "  Area: " << area() << std::endl;
    print_vertices();
}