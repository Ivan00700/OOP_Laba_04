#pragma once
#include "point.h"
#include "figure.h"
#include <cmath>
#include <compare>
#include <memory>


template<Scalar T>
class Hexagon : public Figure<T> {
public:
    Hexagon() : Figure<T>("hexagon") {
        for (int i = 0; i < 6; ++i)
            points[i] = std::make_unique<Point<T>>();
    }

    // 6 точек, вводятся по кругу
    Hexagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3,
            const Point<T>& p4, const Point<T>& p5, const Point<T>& p6,
            std::string desc = "hexagon")
        : Figure<T>(desc)
    {
        points[0] = std::make_unique<Point<T>>(p1);
        points[1] = std::make_unique<Point<T>>(p2);
        points[2] = std::make_unique<Point<T>>(p3);
        points[3] = std::make_unique<Point<T>>(p4);
        points[4] = std::make_unique<Point<T>>(p5);
        points[5] = std::make_unique<Point<T>>(p6);
    }

    Hexagon(const Hexagon& other) : Figure<T>("hexagon") {
        for (int i = 0; i < 6; ++i)
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }

    Hexagon& operator=(const Hexagon& other) {
        if (this != &other) {
            for (int i = 0; i < 6; ++i)
                points[i] = std::make_unique<Point<T>>(*other.points[i]);
        }
        return *this;
    }

    Hexagon(Hexagon&& other) noexcept {
        for (int i = 0; i < 6; ++i)
            points[i] = std::move(other.points[i]);
    }

    Hexagon& operator=(Hexagon&& other) noexcept {
        if (this != &other) {
            for (int i = 0; i < 6; ++i)
                points[i] = std::move(other.points[i]);
        }
        return *this;
    }

    bool operator==(const Hexagon& other) const {
        return std::fabs(this->square() - other.square()) <= 1e-9;
    }

    std::partial_ordering operator<=>(const Hexagon& other) const {
        return this->square() <=> other.square();
    }

    // Геометрический центр — среднее всех координат
    std::unique_ptr<Point<T>> geometric_center() const override {
        double cx = 0, cy = 0;
        for (int i = 0; i < 6; ++i) {
            cx += points[i]->get_x();
            cy += points[i]->get_y();
        }
        cx /= 6.0;
        cy /= 6.0;
        return std::make_unique<Point<T>>(cx, cy);
    }

    // Площадь — многоугольник через формулу Гаусса
    double square() const override {
        double s = 0.;
        for (int i = 0; i < 6; ++i) {
            int j = (i + 1) % 6;
            s += points[i]->get_x() * points[j]->get_y()
               - points[j]->get_x() * points[i]->get_y();
        }
        return std::abs(s) * 0.5;
    }

    double perimeter() const override {
        double p = 0.;
        for (int i = 0; i < 6; ++i)
            p += distance(*points[i], *points[(i + 1) % 6]);
        return p;
    }

    operator double() const override {
        return square();
    }

    void print(std::ostream& os) const override {
        for (int i = 0; i < 6; ++i)
            os << *points[i] << std::endl;
    }

    void read(std::istream& is) override {
        for (int i = 0; i < 6; ++i)
            is >> *points[i];
    }

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Hexagon<T>>(
            *points[0], *points[1], *points[2],
            *points[3], *points[4], *points[5]
        );
    }

private:
    std::unique_ptr<Point<T>> points[6];
};
