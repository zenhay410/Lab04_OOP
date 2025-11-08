#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <vector>
#include <memory>

template<typename T>
class Figure {
protected:
    std::vector<PointPtr<T>> points;
public:
    virtual ~Figure() = default;
    
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print() const = 0;
    virtual std::string type() const = 0;
    
    explicit operator double() const { return area(); }
    
    bool operator==(const Figure& other) const {
        return area() == other.area();
    }
    
    bool operator<(const Figure& other) const {
        return area() < other.area();
    }
};

template<typename T>
using FigurePtr = std::shared_ptr<Figure<T>>;

#endif