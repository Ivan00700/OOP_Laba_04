#include <iostream>
#include <sstream>
#include <utility>
#include <memory>

#include "point.h"
#include "figure.h"
#include "figures_array.h"

#include "hexagon.h"
#include "octagon.h"
#include "triangle.h"

int main() {
    using std::cout;
    using std::endl;

    // --- Точки ---
    Point<double> p1(0.0, 0.0);
    Point<double> p2(4.0, 0.0);
    Point<double> p3(4.0, 4.0);
    Point<double> p4(0.0, 4.0);

    Point<double> p5(1.0, 1.0);
    Point<double> p6(5.0, 1.0);
    Point<double> p7(5.0, 3.0);
    Point<double> p8(3.0, 5.0);
    Point<double> p9(1.0, 3.0);

    cout << "Точки: "
         << p1 << " " << p2 << " " << p3 << " " << p4 << " "
         << p5 << " " << p6 << " " << p7 << " " << p8 << " " << p9 
         << endl;

    cout << "Расстояние между p1 и p2: " << distance(p1, p2) << endl;


    // тестик треугольника
    Triangle<double> tri1(p1, p2, p3);
    cout << "\nТреугольник tri1:" << endl << tri1 << endl;

    cout << "  центр: " << *tri1.geometric_center() << endl;
    cout << "  площадь: " << tri1.square()
         << " периметр: " << tri1.perimeter() << endl;
    cout << "  приведение к double (площадь): " << static_cast<double>(tri1) << endl;
    cout << "  tri1 == tri1: " << std::boolalpha << (tri1 == tri1) << endl;

    // Чтение из потока
    Triangle<double> tri2;
    std::istringstream tin("(0,0) (2,0) (1,3)");
    tin >> tri2;

    cout << "Треугольник tri2 (прочитан из строки):" << endl << tri2 << endl;
    cout << "  tri1 == tri2 (площади равны?): " << (tri1 == tri2) << endl;


    // тестик шестиугоьника
    Hexagon<double> hex1(p1, p2, p3, p4, p5, p9);
    cout << "Шестиугольник hex1:" << endl << hex1 << endl;

    cout << "  центр: " << *hex1.geometric_center() << endl;
    cout << "  площадь: " << hex1.square()
         << " периметр: " << hex1.perimeter() << endl;
    cout << "  hex1 == hex1: " << (hex1 == hex1) << endl;


    // тестик восьмиугольника
    Octagon<double> oct1(p1, p2, p3, p4, p7, p8, p9, p5);
    cout << "Восьмиугольник oct1:" << endl << oct1 << endl;

    cout << "  центр: " << *oct1.geometric_center() << endl;
    cout << "  площадь: " << oct1.square()
         << " периметр: " << oct1.perimeter() << endl;
    cout << "  oct1 == oct1: " << (oct1 == oct1) << endl;


    // тест клона
    auto tri_clone  = tri1.clone();
    auto hex_clone  = hex1.clone();
    auto oct_clone  = oct1.clone();

    cout << "Клонированные фигуры:" << endl;
    cout << *tri_clone << endl;
    cout << *hex_clone << endl;
    cout << *oct_clone << endl;


    // тестик
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr(2);

    arr.add_figure(tri1.clone());
    arr.add_figure(hex1.clone());
    arr.add_figure(oct1.clone());

    cout << "Массив после добавления (size="
         << arr.get_size() << ", cap=" << arr.get_capacity() << "):" << endl;
    arr.print_figures(cout);

    cout << "Общая площадь: " << arr.total_square() << endl;


    // копирование
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr_copy = arr;
    cout << "Скопированный массив:" << endl;
    arr_copy.print_figures(cout);


    // перемещение
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr_moved = std::move(arr);
    cout << "Перемещённый массив, новый size=" << arr_moved.get_size()
         << ", исходный arr.size=" << arr.get_size() << endl;

    arr_moved.print_figures(cout);


    // Copy assignment
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr_assign(1);
    arr_assign = arr_copy;
    cout << "После copy-assignment arr_assign size=" << arr_assign.get_size() << endl;


    // Move assignment
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr_move_assign(1);
    arr_move_assign = std::move(arr_copy);

    cout << "После move-assignment arr_move_assign size="
         << arr_move_assign.get_size()
         << ", arr_copy size=" << arr_copy.get_size() << endl;


    // оператор тест
    if (arr_moved.get_size() > 0) {
        auto f = arr_moved[0];
        cout << "Первый элемент arr_moved:" << endl;
        if (f) cout << *f << endl;
    }

    if (arr_moved.get_size() > 1) {
        cout << "Удаляем элемент с индексом 1" << endl;
        arr_moved.remove_figure(1);
        cout << "После удаления размер=" << arr_moved.get_size() << endl;
        arr_moved.print_figures(cout);
    }
    return 0;
}
