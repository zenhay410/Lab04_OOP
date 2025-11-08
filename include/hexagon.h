#ifndef HEXAGON_H
#define HEXAGON_H

#include "figure.h"
#include <cmath>

template<typename T>
class Hexagon : public Figure<T> {
public:
    Hexagon(T x, T y, T r) {
        for (int i = 0; i < 6; i++) {
            double a = 2 * 3.14159 * i / 6;
            T px = x + r * std::cos(a);
            T py = y + r * std::sin(a);
            this->points.push_back(std::make_unique<Point<T>>(px, py));
        }
    }
    
    Point<T> center() const override {
        T sx = 0, sy = 0;
        for (auto& p : this->points) {
            sx += p->x();
            sy += p->y();
        }
        return Point<T>(sx/6, sy/6);
    }
    
    double area() const override {
        if (this->points.size() != 6) return 0;
        T s = dist(*this->points[0], *this->points[1]);
        return (3.0 * std::sqrt(3.0) * s * s) / 2.0;
    }
    
    void print() const override {
        std::cout << "Hexagon points: ";
        for (auto& p : this->points) {
            std::cout << *p << " ";
        }
        std::cout << std::endl;
    }
    
    std::string type() const override {
        return "Hexagon";
    }

private:
    T dist(const Point<T>& a, const Point<T>& b) const {
        T dx = a.x() - b.x();
        T dy = a.y() - b.y();
        return std::sqrt(dx*dx + dy*dy);
    }
};

#endif