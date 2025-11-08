#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <vector>
#include <memory>
#include <iostream>

template<ScalarType T>
class Figure {
protected:
    std::vector<PointPtr<T>> vertices;

public:
    virtual ~Figure() = default;
    
    virtual Point<T> geometric_center() const = 0;
    virtual double area() const = 0;
    virtual void print_vertices() const = 0;
    virtual std::string name() const { return "Figure"; }
    
    explicit operator double() const { return area(); }
    
    bool operator==(const Figure& other) const {
        return area() == other.area();
    }
    
    bool operator!=(const Figure& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Figure& other) const {
        return area() < other.area();
    }
    
    bool operator>(const Figure& other) const {
        return area() > other.area();
    }
    
    const std::vector<PointPtr<T>>& get_vertices() const { return vertices; }
    
    virtual void print_info() const {
        std::cout << name() << " info:" << std::endl;
        std::cout << "  Geometric center: " << geometric_center() << std::endl;
        std::cout << "  Area: " << area() << std::endl;
        print_vertices();
    }
};

template<ScalarType T>
using FigurePtr = std::shared_ptr<Figure<T>>;

#endif