#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.h"
#include <cmath>

template<typename T>
class Pentagon : public Figure<T> {
public:
    Pentagon(T x, T y, T r) {
        for (int i = 0; i < 5; i++) {
            double a = 2 * 3.14159 * i / 5;
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
        return Point<T>(sx/5, sy/5);
    }
    
    double area() const override {
        if (this->p.size() != 5) return 0;
        T s = dist(*this->p[0], *this->p[1]);
        return (5.0 * s * s) / (4.0 * std::tan(3.14159 / 5.0));
    }
    
    void print() const override {
        std::cout << "Pentagon: ";
        for (auto& pt : this->p) {
            std::cout << *pt << " ";
        }
        std::cout << std::endl;
    }
    
    std::string type() const override {
        return "Pentagon";
    }

private:
    T dist(const Point<T>& a, const Point<T>& b) const {
        T dx = a.x() - b.x();
        T dy = a.y() - b.y();
        return std::sqrt(dx*dx + dy*dy);
    }
};

#endif