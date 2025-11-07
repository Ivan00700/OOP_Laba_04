#pragma once

#include "figure.h"
#include <cstddef>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <utility>

template<typename FigureType>
class Array_Of_Figures {
public:
    Array_Of_Figures() = default;

    Array_Of_Figures(size_t cap) {
        size = 0;
        capacity = (cap == 0) ? 1 : (cap * 2);
        figures = std::make_shared<FigureType[]>(capacity);
        std::fill_n(figures.get(), capacity, FigureType{});
    }

    Array_Of_Figures(std::initializer_list<FigureType> list) {
        size = list.size();
        capacity = (size == 0) ? 1 : (size * 2);
        figures = std::make_shared<FigureType[]>(capacity);
        std::fill_n(figures.get(), capacity, FigureType{});
        size_t i = 0;
        for (const auto& fig : list) {
            figures[i++] = fig;
        }
    }

    Array_Of_Figures(Array_Of_Figures&& other) noexcept
        : figures(std::move(other.figures)), size(other.size), capacity(other.capacity) {
        other.figures = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Array_Of_Figures(const Array_Of_Figures& other) {
        size = other.size;
        capacity = other.capacity;
        figures = std::make_shared<FigureType[]>(capacity);
        std::fill_n(figures.get(), capacity, FigureType{});
        for (size_t i = 0; i < size; ++i) {
            figures[i] = other.figures[i];
        }
    }

    Array_Of_Figures& operator=(const Array_Of_Figures& other) {
        if (this == &other) return *this;
        Array_Of_Figures temp(other);
        swap(temp);
        return *this;
    }

    Array_Of_Figures& operator=(Array_Of_Figures&& other) noexcept {
        if (this == &other) return *this;
        figures = std::move(other.figures);
        size = other.size;
        capacity = other.capacity;
        other.figures = nullptr;
        other.size = 0;
        other.capacity = 0;
        return *this;
    }

    ~Array_Of_Figures() = default;

    void add_figure(FigureType figure) {
        if (size >= capacity) {
            resize();
        }
        figures[size++] = figure;
    }

    FigureType& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return figures[index];
    }

    const FigureType& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return figures[index];
    }

    void remove_figure(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; ++i) {
            figures[i] = figures[i + 1];
        }
        --size;
        figures[size] = FigureType{};
    }

    size_t get_size() const { return size; }
    size_t get_capacity() const { return capacity; }

    void print_figures(std::ostream& os) const {
        for (size_t i = 0; i < size; ++i) {
            if (figures[i]) {
                os << *figures[i] << std::endl;
            }
        }
    }

    double total_square() const {
        double total = 0.0;
        for (size_t i = 0; i < size; ++i) {
            if (figures[i]) {
                total += figures[i]->square();
            }
        }
        return total;
    }

private:
    std::shared_ptr<FigureType[]> figures{nullptr};
    size_t size{0};
    size_t capacity{0};

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        std::shared_ptr<FigureType[]> new_figures = std::make_shared<FigureType[]>(capacity);
        std::fill_n(new_figures.get(), capacity, FigureType{});
        for (size_t i = 0; i < size; ++i) {
            new_figures[i] = figures[i];
        }
        figures = new_figures;
    }

    void swap(Array_Of_Figures& other) noexcept {
        std::swap(figures, other.figures);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }
};