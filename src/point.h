#pragma once
#include <iostream>
#include <iterator>
#include <cmath>
#include <type_traits>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
    friend std::ostream& operator<<(std::ostream& os, const Point& point){
        os << "(" << point.point_x << ", " << point.point_y << ")";
        return os;
    };

    friend std::istream& operator>>(std::istream& is, Point& point){
        char delim;
        T x, y;
        if (is >> delim >> x >> delim >> y >> delim) {
            point.point_x = x;
            point.point_y = y;
        } else {
            is.setstate(std::ios::failbit);
        }
        return is;
    };

    friend double distance(const Point& p1, const Point& p2){
        double dx = p2.get_x() - p1.get_x();
        double dy = p2.get_y() - p1.get_y();
        return std::sqrt(dx * dx + dy * dy);
    };

public:
    Point() = default;
    Point(T p_x, T p_y) : point_x(p_x), point_y(p_y) {}

    T get_x() const { return point_x; }
    T get_y() const { return point_y; }

    void move(T new_x, T new_y){
        point_x = new_x;
        point_y = new_y;
    }

private:
    T point_x{0};
    T point_y{0};
};
