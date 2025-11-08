#ifndef OCTAGON_H
#define OCTAGON_H

#include "figure.h"
#include <cmath>

template<typename T>
class Octagon : public Figure<T> {
public:
    Octagon(T x, T y, T r) {
        for (int i = 0; i < 8; i++) {
            double a = 2 * 3.14159 * i / 8;
            T px = x + r * std::cos(a);
            T py = y + r * std::sin(a);
            this->p.push_back(std::make_unique<Point<T>>(px, py));
        }
    }
    
    Point<T> center() const override {
        T sx = 0, sy = 0;
        for (auto& pt : this->p) {
            sx += pt->x();
            sy += pt->y();
        }
        return Point<T>(sx/8, sy/8);
    }
    
    double area() const override {
        if (this->p.size() != 8) return 0;
        T s = dist(*this->p[0], *this->p[1]);
        return 2.0 * (1.0 + std::sqrt(2.0)) * s * s;
    }
    
    void print() const override {
        std::cout << "Octagon: ";
        for (auto& pt : this->p) {
            std::cout << *pt << " ";
        }
        std::cout << std::endl;
    }
    
    std::string type() const override {
        return "Octagon";
    }

private:
    T dist(const Point<T>& a, const Point<T>& b) const {
        T dx = a.x() - b.x();
        T dy = a.y() - b.y();
        return std::sqrt(dx*dx + dy*dy);
    }
};

#endif