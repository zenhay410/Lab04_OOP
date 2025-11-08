#include <gtest/gtest.h>
#include "../include/point.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/octagon.h"
#include "../include/array.h"

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.x(), 0);
    EXPECT_EQ(p.y(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.14, 2.71);
    EXPECT_DOUBLE_EQ(p.x(), 3.14);
    EXPECT_DOUBLE_EQ(p.y(), 2.71);
}

TEST(PointTest, CopyConstructor) {
    Point<int> p1(10, 20);
    Point<int> p2 = p1;
    EXPECT_EQ(p2.x(), 10);
    EXPECT_EQ(p2.y(), 20);
}

TEST(PointTest, MoveConstructor) {
    Point<int> p1(5, 15);
    Point<int> p2 = std::move(p1);
    EXPECT_EQ(p2.x(), 5);
    EXPECT_EQ(p2.y(), 15);
}

TEST(PointTest, AssignmentOperators) {
    Point<int> p1(1, 2);
    Point<int> p2(3, 4);
    p1 = p2;
    EXPECT_EQ(p1.x(), 3);
    EXPECT_EQ(p1.y(), 4);
    
    Point<int> p3(5, 6);
    p1 = std::move(p3);
    EXPECT_EQ(p1.x(), 5);
    EXPECT_EQ(p1.y(), 6);
}

TEST(PointTest, ComparisonOperators) {
    Point<int> p1(5, 10);
    Point<int> p2(5, 10);
    Point<int> p3(10, 5);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
}

TEST(PentagonTest, ConstructorAndArea) {
    Pentagon<double> pentagon(0, 0, 1.0);
    EXPECT_GT(pentagon.area(), 0.0);
}

TEST(PentagonTest, GeometricCenter) {
    Pentagon<double> pentagon(5.0, 5.0, 2.0);
    auto center = pentagon.geometric_center();
    EXPECT_NEAR(center.x(), 5.0, 1e-9);
    EXPECT_NEAR(center.y(), 5.0, 1e-9);
}

TEST(PentagonTest, VertexCount) {
    Pentagon<double> pentagon(0, 0, 1.0);
    EXPECT_EQ(pentagon.get_vertices().size(), 5);
}

TEST(PentagonTest, CopyOperations) {
    Pentagon<double> p1(0, 0, 3.0);
    Pentagon<double> p2 = p1;
    EXPECT_NEAR(p1.area(), p2.area(), 1e-9);
}

TEST(PentagonTest, MoveOperations) {
    Pentagon<double> p1(0, 0, 2.0);
    double area = p1.area();
    Pentagon<double> p2 = std::move(p1);
    EXPECT_NEAR(p2.area(), area, 1e-9);
}

TEST(HexagonTest, BasicFunctionality) {
    Hexagon<float> hexagon(1.0f, 1.0f, 2.0f);
    auto center = hexagon.geometric_center();
    EXPECT_NEAR(center.x(), 1.0f, 1e-6);
    EXPECT_NEAR(center.y(), 1.0f, 1e-6);
    EXPECT_GT(hexagon.area(), 0.0f);
}

TEST(HexagonTest, VertexCount) {
    Hexagon<int> hexagon(0, 0, 5);
    EXPECT_EQ(hexagon.get_vertices().size(), 6);
}

TEST(HexagonTest, AreaCalculation) {
    Hexagon<double> hexagon(0, 0, 1.0);
    double area = hexagon.area();
    EXPECT_GT(area, 0.0);
    EXPECT_LT(area, 3.0);
}

TEST(OctagonTest, ConstructorAndArea) {
    Octagon<double> octagon(0, 0, 1.0);
    EXPECT_GT(octagon.area(), 0.0);
}

TEST(OctagonTest, GeometricCenter) {
    Octagon<double> octagon(3.0, 4.0, 2.0);
    auto center = octagon.geometric_center();
    EXPECT_NEAR(center.x(), 3.0, 1e-9);
    EXPECT_NEAR(center.y(), 4.0, 1e-9);
}

TEST(OctagonTest, VertexCount) {
    Octagon<double> octagon(0, 0, 1.0);
    EXPECT_EQ(octagon.get_vertices().size(), 8);
}

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_GT(arr.capacity(), 0);
}

TEST(ArrayTest, AddElements) {
    Array<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, RemoveElements) {
    Array<int> arr;
    arr.add(10);
    arr.add(20);
    arr.add(30);
    
    arr.remove_at(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr1;
    arr1.add(42);
    arr1.add(123);
    
    Array<int> arr2 = arr1;
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 42);
    EXPECT_EQ(arr2[1], 123);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr1;
    arr1.add(100);
    arr1.add(200);
    
    Array<int> arr2 = std::move(arr1);
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 100);
    EXPECT_EQ(arr2[1], 200);
    EXPECT_EQ(arr1.size(), 0);
}

TEST(ArrayTest, AssignmentOperators) {
    Array<int> arr1;
    arr1.add(1);
    arr1.add(2);
    
    Array<int> arr2;
    arr2 = arr1;
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    
    Array<int> arr3;
    arr3 = std::move(arr1);
    EXPECT_EQ(arr3.size(), 2);
    EXPECT_EQ(arr3[0], 1);
    EXPECT_EQ(arr3[1], 2);
}

TEST(ArrayTest, OutOfBoundsAccess) {
    Array<int> arr;
    arr.add(5);
    
    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr.remove_at(5), std::out_of_range);
}

TEST(ArrayTest, EmptyArrayOperations) {
    Array<int> arr;
    EXPECT_TRUE(arr.empty());
    EXPECT_THROW(arr[0], std::out_of_range);
    EXPECT_THROW(arr.remove_at(0), std::out_of_range);
}

TEST(ArrayTest, ResizeWithMove) {
    Array<std::string> arr(2);
    
    arr.add("first");
    arr.add("second");
    arr.add("third");
    
    EXPECT_GT(arr.capacity(), 2);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], "first");
    EXPECT_EQ(arr[1], "second");
    EXPECT_EQ(arr[2], "third");
}

TEST(FigureArrayTest, StoreFigures) {
    Array<FigurePtr<double>> figures;
    
    auto pentagon = std::make_shared<Pentagon<double>>(0, 0, 1.0);
    auto hexagon = std::make_shared<Hexagon<double>>(0, 0, 1.0);
    auto octagon = std::make_shared<Octagon<double>>(0, 0, 1.0);
    
    figures.add(pentagon);
    figures.add(hexagon);
    figures.add(octagon);
    
    EXPECT_EQ(figures.size(), 3);
    EXPECT_GT(static_cast<double>(*figures[0]), 0.0);
    EXPECT_GT(static_cast<double>(*figures[1]), 0.0);
    EXPECT_GT(static_cast<double>(*figures[2]), 0.0);
}

TEST(FigureArrayTest, FigureNames) {
    Array<FigurePtr<double>> figures;
    
    figures.add(std::make_shared<Pentagon<double>>(0, 0, 1.0));
    figures.add(std::make_shared<Hexagon<double>>(0, 0, 1.0));
    figures.add(std::make_shared<Octagon<double>>(0, 0, 1.0));
    
    EXPECT_EQ(figures[0]->name(), "Pentagon");
    EXPECT_EQ(figures[1]->name(), "Hexagon");
    EXPECT_EQ(figures[2]->name(), "Octagon");
}

TEST(FigureArrayTest, RemoveFigures) {
    Array<FigurePtr<double>> figures;
    
    figures.add(std::make_shared<Pentagon<double>>(0, 0, 1.0));
    figures.add(std::make_shared<Hexagon<double>>(0, 0, 1.0));
    figures.add(std::make_shared<Octagon<double>>(0, 0, 1.0));
    
    figures.remove_at(1);
    EXPECT_EQ(figures.size(), 2);
    EXPECT_EQ(figures[0]->name(), "Pentagon");
    EXPECT_EQ(figures[1]->name(), "Octagon");
}

TEST(FigureComparisonTest, EqualAreas) {
    Pentagon<double> p1(0, 0, 1.0);
    Pentagon<double> p2(0, 0, 1.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
}

TEST(FigureComparisonTest, DifferentAreas) {
    Pentagon<double> p1(0, 0, 1.0);
    Pentagon<double> p2(0, 0, 2.0);
    Hexagon<double> h1(0, 0, 1.0);
    
    EXPECT_TRUE(p1 < p2);
    EXPECT_TRUE(p2 > p1);
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 == p2);
}

TEST(FigureConversionTest, DoubleConversion) {
    Pentagon<double> pentagon(0, 0, 1.0);
    double area = static_cast<double>(pentagon);
    
    EXPECT_GT(area, 0.0);
    EXPECT_EQ(area, pentagon.area());
}

TEST(DataTypeTest, DifferentScalarTypes) {
    Pentagon<int> pentagon_int(0, 0, 5);
    Pentagon<float> pentagon_float(0.0f, 0.0f, 5.0f);
    Pentagon<double> pentagon_double(0.0, 0.0, 5.0);
    
    EXPECT_GT(pentagon_int.area(), 0);
    EXPECT_GT(pentagon_float.area(), 0.0f);
    EXPECT_GT(pentagon_double.area(), 0.0);
}

TEST(IntegrationTest, CompleteWorkflow) {
    Array<FigurePtr<double>> figures;
    
    auto pentagon = std::make_shared<Pentagon<double>>(0, 0, 3.0);
    auto hexagon = std::make_shared<Hexagon<double>>(2.0, 1.0, 2.5);
    auto octagon = std::make_shared<Octagon<double>>(-1.0, -2.0, 4.0);
    
    figures.add(pentagon);
    figures.add(hexagon);
    figures.add(octagon);
    
    EXPECT_EQ(figures.size(), 3);
    
    for (size_t i = 0; i < figures.size(); ++i) {
        EXPECT_GT(figures[i]->area(), 0.0);
        EXPECT_GT(static_cast<double>(*figures[i]), 0.0);
    }
    
    EXPECT_EQ(figures[0]->name(), "Pentagon");
    EXPECT_EQ(figures[1]->name(), "Hexagon");
    EXPECT_EQ(figures[2]->name(), "Octagon");
    
    figures.remove_at(1);
    EXPECT_EQ(figures.size(), 2);
    EXPECT_EQ(figures[0]->name(), "Pentagon");
    EXPECT_EQ(figures[1]->name(), "Octagon");
    
    double total_area = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += figures[i]->area();
    }
    EXPECT_GT(total_area, 0.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}