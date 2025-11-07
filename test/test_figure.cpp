#include <gtest/gtest.h>

#include "point.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"
#include "figures_array.h"
#include "figure.h"

// ======================
//   Triangle Tests
// ======================

TEST(TriangleTest, AreaCorrect) {
    Triangle<double> t({0,0}, {4,0}, {0,3});
    EXPECT_DOUBLE_EQ(t.square(), 6.0);
}

TEST(TriangleTest, PerimeterCorrect) {
    Triangle<double> t({0,0}, {3,0}, {0,4});
    EXPECT_NEAR(t.perimeter(), 12.0, 1e-9);
}

TEST(TriangleTest, CenterCorrect) {
    Triangle<double> t({0,0}, {3,0}, {0,3});
    auto c = t.geometric_center();
    EXPECT_DOUBLE_EQ(c->get_x(), 1.0);
    EXPECT_DOUBLE_EQ(c->get_y(), 1.0);
}

// ======================
//   Hexagon Tests
// ======================

TEST(HexagonTest, AreaCorrect) {
    Hexagon<double> h(
        {0,0}, {2,0}, {3,1},
        {2,2}, {0,2}, {-1,1}
    );
    EXPECT_NEAR(h.square(), 6.0, 1e-9);
}

TEST(HexagonTest, CloneWorks) {
    Hexagon<double> h(
        {0,0}, {1,0}, {1,1},
        {0,1}, {-1,1}, {-1,0}
    );

    auto cloned = h.clone();
    EXPECT_DOUBLE_EQ(cloned->square(), h.square());
}

// ======================
//   Octagon Tests
// ======================

TEST(OctagonTest, PerimeterCorrect) {
    Octagon<double> o(
        {0,0},{1,0},{2,1},{2,2},
        {1,3},{0,3},{-1,2},{-1,1}
    );

    double p = o.perimeter();
    EXPECT_GT(p, 0.0);
}

TEST(OctagonTest, ComparisonWorks) {
    Octagon<double> o1(
        {0,0},{2,0},{3,1},{3,2},
        {2,3},{0,3},{-1,2},{-1,1}
    );

    Octagon<double> o2 = o1;  // equal

    EXPECT_TRUE(o1 == o2);
    EXPECT_EQ(o1 <=> o2, std::partial_ordering::equivalent);
}

// ===========================
//   Array_Of_Figures tests
// ===========================

TEST(ArrayTest, AddAndAccess) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr(2);

    arr.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(0,1)));

    EXPECT_EQ(arr.get_size(), 1);
    EXPECT_NE(arr[0], nullptr);
}

TEST(ArrayTest, TotalArea) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr(2);

    arr.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(4,0), Point<double>(0,3))); // area = 6
    arr.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(2,0), Point<double>(0,2))); // area = 2

    EXPECT_DOUBLE_EQ(arr.total_square(), 8.0);
}

TEST(ArrayTest, RemoveWorks) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr(2);

    arr.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(2,0), Point<double>(0,2)));
    arr.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(4,0), Point<double>(0,3)));

    arr.remove_figure(0);

    EXPECT_EQ(arr.get_size(), 1);
}

// ===========================
//   Дополнительные тесты
// ===========================

// ======================
//   Triangle Additional
// ======================

TEST(TriangleTest, CloneWorks) {
    Triangle<double> t({0,0},{3,0},{0,4});
    auto clone = t.clone();
    EXPECT_DOUBLE_EQ(clone->square(), t.square());
}

TEST(TriangleTest, ComparisonWorks) {
    Triangle<double> t1({0,0},{3,0},{0,4});
    Triangle<double> t2({0,0},{3,0},{0,4});
    EXPECT_TRUE(t1 == t2);
}

TEST(TriangleTest, InequalityWorks) {
    Triangle<double> t1({0,0},{3,0},{0,4});
    Triangle<double> t2({0,0},{2,0},{0,2});
    EXPECT_FALSE(t1 == t2);
}

TEST(TriangleTest, PerimeterPositive) {
    Triangle<double> t({0,0},{1,1},{0,2});
    EXPECT_GT(t.perimeter(), 0.0);
}

// ======================
//   Hexagon Additional
// ======================

TEST(HexagonTest, GeometricCenter) {
    Hexagon<double> h({0,0},{2,0},{3,1},{2,2},{0,2},{-1,1});
    auto c = h.geometric_center();
    EXPECT_NEAR(c->get_x(), 1.0, 1e-9);
    EXPECT_NEAR(c->get_y(), 1.0, 1e-9);
}

TEST(HexagonTest, PerimeterPositive) {
    Hexagon<double> h({0,0},{1,0},{1,1},{0,1},{-1,1},{-1,0});
    EXPECT_GT(h.perimeter(), 0.0);
}

TEST(HexagonTest, AssignmentWorks) {
    Hexagon<double> h1({0,0},{1,0},{1,1},{0,1},{-1,1},{-1,0});
    Hexagon<double> h2 = h1;
    EXPECT_TRUE(h1 == h2);
}

// ======================
//   Octagon Additional
// ======================

TEST(OctagonTest, CloneWorks) {
    Octagon<double> o({0,0},{1,0},{2,1},{2,2},{1,3},{0,3},{-1,2},{-1,1});
    auto clone = o.clone();
    EXPECT_DOUBLE_EQ(clone->square(), o.square());
}

TEST(OctagonTest, GeometricCenter) {
    Octagon<double> o({0,0},{1,0},{2,1},{2,2},{1,3},{0,3},{-1,2},{-1,1});
    auto c = o.geometric_center();
    EXPECT_NEAR(c->get_x(), 0.5, 1e-9); // примерное значение
    EXPECT_NEAR(c->get_y(), 1.5, 1e-9);
}

TEST(OctagonTest, PerimeterComparison) {
    Octagon<double> o1({0,0},{1,0},{2,1},{2,2},{1,3},{0,3},{-1,2},{-1,1});
    Octagon<double> o2({0,0},{2,0},{3,1},{3,2},{2,3},{0,3},{-1,2},{-1,1});
    EXPECT_LT(o1.perimeter(), o2.perimeter());
}

// ===========================
//   Array_Of_Figures Additional
// ===========================

TEST(ArrayTest, AddMultipleFigures) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr(5);
    arr.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(0,1)));
    arr.add_figure(std::make_shared<Hexagon<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(1,1), Point<double>(0,1), Point<double>(-1,1), Point<double>(-1,0)));
    arr.add_figure(std::make_shared<Octagon<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(2,1), Point<double>(2,2), Point<double>(1,3), Point<double>(0,3), Point<double>(-1,2), Point<double>(-1,1)));
    EXPECT_EQ(arr.get_size(), 3);
}

TEST(ArrayTest, AccessOutOfBounds) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr(2);
    arr.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(0,1)));
    EXPECT_THROW(arr[5], std::out_of_range);
}

TEST(ArrayTest, RemoveAll) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr(2);
    arr.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(0,1)));
    arr.add_figure(std::make_shared<Hexagon<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(1,1), Point<double>(0,1), Point<double>(-1,1), Point<double>(-1,0)));
    arr.remove_figure(0);
    arr.remove_figure(0);
    EXPECT_EQ(arr.get_size(), 0);
}

TEST(ArrayTest, ReplaceFigure) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr(2);
    arr.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(0,1)));
    arr.add_figure(std::make_shared<Hexagon<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(1,1), Point<double>(0,1), Point<double>(-1,1), Point<double>(-1,0)));
    arr[0] = std::make_shared<Octagon<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(2,1), Point<double>(2,2), Point<double>(1,3), Point<double>(0,3), Point<double>(-1,2), Point<double>(-1,1));
    EXPECT_TRUE(dynamic_cast<Octagon<double>*>(arr[0].get()) != nullptr);
}

TEST(ArrayTest, CopyArrayWorks) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr1(2);
    arr1.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(0,1)));
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr2 = arr1;
    EXPECT_EQ(arr2.get_size(), 1);
    EXPECT_TRUE(dynamic_cast<Triangle<double>*>(arr2[0].get()) != nullptr);
}

TEST(ArrayTest, MoveArrayWorks) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr1(2);
    arr1.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(0,1)));
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr2 = std::move(arr1);
    EXPECT_EQ(arr2.get_size(), 1);
    EXPECT_EQ(arr1.get_size(), 0);
}

TEST(ArrayTest, EmptyArrayTotalAreaZero) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr(3);
    EXPECT_DOUBLE_EQ(arr.total_square(), 0.0);
}

TEST(ArrayTest, AddBeyondCapacity) {
    Array_Of_Figures<std::shared_ptr<Figure<double>>> arr(1);
    arr.add_figure(std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(0,1)));
    arr.add_figure(std::make_shared<Hexagon<double>>(Point<double>(0,0), Point<double>(1,0), Point<double>(1,1), Point<double>(0,1), Point<double>(-1,1), Point<double>(-1,0)));
    EXPECT_EQ(arr.get_size(), 2); // Проверка, что массив увеличился
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ===========================
//        END OF TESTS
// ===========================
