#ifndef PENTAGON_H
#define PENTAGON_H

#include "figure.h"
#include <cmath>
#include <numbers>

template<ScalarType T>
class Pentagon : public Figure<T> {
public:
    Pentagon() { create_regular(0, 0, 1); }
    Pentagon(T center_x, T center_y, T radius) { create_regular(center_x, center_y, radius); }
    Pentagon(const Pentagon& other) {
        for (const auto& vertex : other.vertices) {
            this->vertices.push_back(std::make_unique<Point<T>>(vertex->x(), vertex->y()));
        }
    }
    Pentagon(Pentagon&& other) noexcept { this->vertices = std::move(other.vertices); }
    ~Pentagon() override = default;
    
    Pentagon& operator=(const Pentagon& other) {
        if (this != &other) {
            this->vertices.clear();
            for (const auto& vertex : other.vertices) {
                this->vertices.push_back(std::make_unique<Point<T>>(vertex->x(), vertex->y()));
            }
        }
        return *this;
    }
    
    Pentagon& operator=(Pentagon&& other) noexcept {
        if (this != &other) {
            this->vertices = std::move(other.vertices);
        }
        return *this;
    }
    
    Point<T> geometric_center() const override {
        if (this->vertices.empty()) return Point<T>(0, 0);
        T sum_x = 0, sum_y = 0;
        for (const auto& vertex : this->vertices) {
            sum_x += vertex->x();
            sum_y += vertex->y();
        }
        return Point<T>(sum_x / 5, sum_y / 5);
    }
    
    double area() const override {
        if (this->vertices.size() != 5) return 0.0;
        T side = distance_between(*this->vertices[0], *this->vertices[1]);
        return (5.0 * side * side) / (4.0 * std::tan(std::numbers::pi / 5.0));
    }
    
    void print_vertices() const override {
        std::cout << "  Vertices: ";
        for (size_t i = 0; i < this->vertices.size(); ++i) {
            std::cout << *this->vertices[i];
            if (i < this->vertices.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    std::string name() const override { return "Pentagon"; }

private:
    void create_regular(T center_x, T center_y, T radius) {
        this->vertices.clear();
        for (int i = 0; i < 5; ++i) {
            double angle = 2 * std::numbers::pi * i / 5;
            T x = center_x + radius * static_cast<T>(std::cos(angle));
            T y = center_y + radius * static_cast<T>(std::sin(angle));
            this->vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
    }
    
    T distance_between(const Point<T>& p1, const Point<T>& p2) const {
        T dx = p1.x() - p2.x();
        T dy = p1.y() - p2.y();
        return std::sqrt(dx * dx + dy * dy);
    }
};

#endif