#pragma once
#include <concepts>
#include <iostream>
#include <string_view>
#include <string>
#include <ostream>
#include <memory>
#include "point.h"

template<Scalar T>
class Figure {
    friend std::ostream& operator<<(std::ostream& os, const Figure& figure){
        os << figure.description << ":\n";
        figure.print(os);
        return os;
    };

    friend std::istream& operator>>(std::istream& is, Figure& figure){
        figure.read(is);
        return is;
    };

protected:
    Figure() = default;
    Figure(std::string_view description) : description(description) {}

public:
    virtual ~Figure() = default;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    virtual std::unique_ptr<Point<T>> geometric_center() const = 0;
    virtual double square() const = 0;
    virtual double perimeter() const = 0;

    virtual std::shared_ptr<Figure<T>> clone() const = 0;

    virtual operator double() const = 0;

private:
    std::string description = "Figure";
};
