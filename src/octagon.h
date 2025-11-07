#pragma once
#include "point.h"
#include "figure.h"
#include <cmath>
#include <compare>
#include <memory>


template<Scalar T>
class Octagon : public Figure<T> {
public:
    Octagon() : Figure<T>("octagon") {
        for (int i = 0; i < 8; ++i)
            points[i] = std::make_unique<Point<T>>();
    }

    Octagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4,
            const Point<T>& p5, const Point<T>& p6, const Point<T>& p7, const Point<T>& p8,
            std::string desc = "octagon")
        : Figure<T>(desc)
    {
        points[0] = std::make_unique<Point<T>>(p1);
        points[1] = std::make_unique<Point<T>>(p2);
        points[2] = std::make_unique<Point<T>>(p3);
        points[3] = std::make_unique<Point<T>>(p4);
        points[4] = std::make_unique<Point<T>>(p5);
        points[5] = std::make_unique<Point<T>>(p6);
        points[6] = std::make_unique<Point<T>>(p7);
        points[7] = std::make_unique<Point<T>>(p8);
    }

    Octagon(const Octagon& other) : Figure<T>("octagon") {
        for (int i = 0; i < 8; ++i)
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }

    Octagon& operator=(const Octagon& other) {
        if (this != &other) {
            for (int i = 0; i < 8; ++i)
                points[i] = std::make_unique<Point<T>>(*other.points[i]);
        }
        return *this;
    }

    Octagon(Octagon&& other) noexcept {
        for (int i = 0; i < 8; ++i)
            points[i] = std::move(other.points[i]);
    }

    Octagon& operator=(Octagon&& other) noexcept {
        if (this != &other) {
            for (int i = 0; i < 8; ++i)
                points[i] = std::move(other.points[i]);
        }
        return *this;
    }

    bool operator==(const Octagon& other) const {
        return std::fabs(this->square() - other.square()) <= 1e-9;
    }

    std::partial_ordering operator<=>(const Octagon& other) const {
        return this->square() <=> other.square();
    }

    std::unique_ptr<Point<T>> geometric_center() const override {
        double cx = 0, cy = 0;
        for (int i = 0; i < 8; ++i) {
            cx += points[i]->get_x();
            cy += points[i]->get_y();
        }
        return std::make_unique<Point<T>>(cx / 8.0, cy / 8.0);
    }

    double square() const override {
        double s = 0.;
        for (int i = 0; i < 8; ++i) {
            int j = (i + 1) % 8;
            s += points[i]->get_x() * points[j]->get_y()
               - points[j]->get_x() * points[i]->get_y();
        }
        return std::abs(s) * 0.5;
    }

    double perimeter() const override {
        double p = 0.;
        for (int i = 0; i < 8; ++i)
            p += distance(*points[i], *points[(i + 1) % 8]);
        return p;
    }

    operator double() const override {
        return square();
    }

    void print(std::ostream& os) const override {
        for (int i = 0; i < 8; ++i)
            os << *points[i] << std::endl;
    }

    void read(std::istream& is) override {
        for (int i = 0; i < 8; ++i)
            is >> *points[i];
    }

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Octagon<T>>(
            *points[0], *points[1], *points[2], *points[3],
            *points[4], *points[5], *points[6], *points[7]
        );
    }

private:
    std::unique_ptr<Point<T>> points[8];
};
