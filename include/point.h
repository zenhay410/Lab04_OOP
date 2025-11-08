#ifndef POINT_H
#define POINT_H

#include <concepts>
#include <memory>
#include <iostream>
#include <type_traits>

template<typename T>
concept ScalarType = std::is_scalar_v<T>;

template<ScalarType T>
class Point {
private:
    T x_val, y_val;

public:
    Point() noexcept : x_val(0), y_val(0) {}
    Point(T x, T y) noexcept : x_val(x), y_val(y) {}
    Point(const Point& other) noexcept : x_val(other.x_val), y_val(other.y_val) {}
    Point(Point&& other) noexcept : x_val(std::move(other.x_val)), y_val(std::move(other.y_val)) {}
    ~Point() noexcept = default;
    
    Point& operator=(const Point& other) noexcept {
        if (this != &other) {
            x_val = other.x_val;
            y_val = other.y_val;
        }
        return *this;
    }
    
    Point& operator=(Point&& other) noexcept {
        if (this != &other) {
            x_val = std::move(other.x_val);
            y_val = std::move(other.y_val);
        }
        return *this;
    }
    
    T x() const noexcept { return x_val; }
    T y() const noexcept { return y_val; }
    void set_x(T x) noexcept { x_val = x; }
    void set_y(T y) noexcept { y_val = y; }
    
    bool operator==(const Point& other) const noexcept {
        return x_val == other.x_val && y_val == other.y_val;
    }
    
    bool operator!=(const Point& other) const noexcept {
        return !(*this == other);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& pt) {
        os << "(" << pt.x_val << ", " << pt.y_val << ")";
        return os;
    }
};

template<ScalarType T>
using PointPtr = std::unique_ptr<Point<T>>;

#endif