#ifndef POINT_H
#define POINT_H

#include <iostream>

template<typename T>
class Point {
    T x_, y_;
public:
    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}
    Point(const Point& other) : x_(other.x_), y_(other.y_) {}
    Point(Point&& other) : x_(std::move(other.x_)), y_(std::move(other.y_)) {}
    ~Point() = default;
    
    Point& operator=(const Point& other) {
        if (this != &other) {
            x_ = other.x_;
            y_ = other.y_;
        }
        return *this;
    }
    
    T x() const { return x_; }
    T y() const { return y_; }
    void set_x(T x) { x_ = x; }
    void set_y(T y) { y_ = y; }
    
    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x_ << "," << p.y_ << ")";
        return os;
    }
};

template<typename T>
using PointPtr = std::unique_ptr<Point<T>>;

#endif