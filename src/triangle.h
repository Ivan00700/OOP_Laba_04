#pragma once
#include <cmath>
#include <compare>
#include <string>
#include <memory>
#include "point.h"
#include "figure.h"

template<Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() : Figure<T>("triangle") {
        for (int i = 0; i < 3; ++i)
            points[i] = std::make_unique<Point<T>>();
    }

    Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3,
             std::string desc = "triangle")
        : Figure<T>(desc)
    {
        points[0] = std::make_unique<Point<T>>(p1);
        points[1] = std::make_unique<Point<T>>(p2);
        points[2] = std::make_unique<Point<T>>(p3);
    }

    // --- Копирование ---
    Triangle(const Triangle& other) : Figure<T>("triangle") {
        for (int i = 0; i < 3; ++i)
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }

    Triangle& operator=(const Triangle& other) {
        if (this != &other) {
            for (int i = 0; i < 3; ++i)
                points[i] = std::make_unique<Point<T>>(*other.points[i]);
        }
        return *this;
    }

    // --- Перемещение ---
    Triangle(Triangle&& other) noexcept {
        for (int i = 0; i < 3; ++i)
            points[i] = std::move(other.points[i]);
    }

    Triangle& operator=(Triangle&& other) noexcept {
        if (this != &other) {
            for (int i = 0; i < 3; ++i)
                points[i] = std::move(other.points[i]);
        }
        return *this;
    }

    // --- Сравнение ---
    bool operator==(const Triangle& other) const {
        return std::fabs(this->square() - other.square()) <= 1e-9;
    }

    std::partial_ordering operator<=>(const Triangle& other) const {
        return this->square() <=> other.square();
    }

    // --- Геометрический центр ---
    std::unique_ptr<Point<T>> geometric_center() const override {
        double cx = 0, cy = 0;
        for (int i = 0; i < 3; ++i) {
            cx += points[i]->get_x();
            cy += points[i]->get_y();
        }
        return std::make_unique<Point<T>>(cx / 3.0, cy / 3.0);
    }

    // --- Площадь ---
    double square() const override {
        double x1 = points[0]->get_x(), y1 = points[0]->get_y();
        double x2 = points[1]->get_x(), y2 = points[1]->get_y();
        double x3 = points[2]->get_x(), y3 = points[2]->get_y();

        return std::abs(
            x1 * (y2 - y3) +
            x2 * (y3 - y1) +
            x3 * (y1 - y2)
        ) * 0.5;
    }

    // --- Периметр ---
    double perimeter() const override {
        return distance(*points[0], *points[1]) +
               distance(*points[1], *points[2]) +
               distance(*points[2], *points[0]);
    }

    operator double() const override {
        return square();
    }

    // --- Вывод ---
    void print(std::ostream& os) const override {
        for (int i = 0; i < 3; ++i)
            os << *points[i] << std::endl;
    }

    // --- Ввод ---
    void read(std::istream& is) override {
        for (int i = 0; i < 3; ++i)
            is >> *points[i];
    }

    // --- Клонирование ---
    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Triangle<T>>(
            *points[0], *points[1], *points[2]
        );
    }

private:
    std::unique_ptr<Point<T>> points[3];
};
