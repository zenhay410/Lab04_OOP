#include <gtest/gtest.h>
#include "../include/point.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/octagon.h"
#include "../include/array.h"

// 1. Базовый тест точки
TEST(PointTest, BasicCreation) {
    Point<int> p1;
    EXPECT_EQ(p1.x(), 0);
    EXPECT_EQ(p1.y(), 0);
    
    Point<double> p2(1.5, 2.5);
    EXPECT_DOUBLE_EQ(p2.x(), 1.5);
    EXPECT_DOUBLE_EQ(p2.y(), 2.5);
}

// 2. Тест копирования точки
TEST(PointTest, CopyOperations) {
    Point<int> p1(10, 20);
    Point<int> p2 = p1;
    EXPECT_EQ(p2.x(), 10);
    EXPECT_EQ(p2.y(), 20);
    
    Point<int> p3;
    p3 = p1;
    EXPECT_EQ(p3.x(), 10);
    EXPECT_EQ(p3.y(), 20);
}

// 3. Тест перемещения точки
TEST(PointTest, MoveOperations) {
    Point<int> p1(5, 15);
    Point<int> p2 = std::move(p1);
    EXPECT_EQ(p2.x(), 5);
    EXPECT_EQ(p2.y(), 15);
}

// 4. Тест сравнения точек
TEST(PointTest, Comparison) {
    Point<int> p1(5, 10);
    Point<int> p2(5, 10);
    Point<int> p3(10, 5);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
}

// 5. Тест создания пятиугольника
TEST(PentagonTest, CreationAndArea) {
    Pentagon<double> p(0, 0, 1.0);
    EXPECT_GT(p.area(), 0.0);
    EXPECT_LT(p.area(), 3.0);
}

// 6. Тест центра пятиугольника
TEST(PentagonTest, CenterCalculation) {
    Pentagon<double> p(5.0, 5.0, 2.0);
    auto c = p.center();
    EXPECT_NEAR(c.x(), 5.0, 0.01);
    EXPECT_NEAR(c.y(), 5.0, 0.01);
}

// 7. Тест создания шестиугольника
TEST(HexagonTest, CreationAndArea) {
    Hexagon<double> h(0, 0, 1.0);
    EXPECT_GT(h.area(), 0.0);
    EXPECT_LT(h.area(), 3.0);
}

// 8. Тест центра шестиугольника
TEST(HexagonTest, CenterCalculation) {
    Hexagon<double> h(3.0, 4.0, 2.0);
    auto c = h.center();
    EXPECT_NEAR(c.x(), 3.0, 0.01);
    EXPECT_NEAR(c.y(), 4.0, 0.01);
}

// 9. Тест создания восьмиугольника
TEST(OctagonTest, CreationAndArea) {
    Octagon<double> o(0, 0, 1.0);
    EXPECT_GT(o.area(), 0.0);
    EXPECT_LT(o.area(), 5.0);
}

// 10. Тест центра восьмиугольника
TEST(OctagonTest, CenterCalculation) {
    Octagon<double> o(2.0, 3.0, 1.5);
    auto c = o.center();
    EXPECT_NEAR(c.x(), 2.0, 0.01);
    EXPECT_NEAR(c.y(), 3.0, 0.01);
}

// 11. Базовый тест массива
TEST(ArrayTest, BasicOperations) {
    Array<int> arr;
    arr.add(1);
    arr.add(2);
    arr.add(3);
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

// 12. Тест удаления из массива
TEST(ArrayTest, RemoveOperations) {
    Array<int> arr;
    arr.add(10);
    arr.add(20);
    arr.add(30);
    arr.add(40);
    
    arr.remove(1);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
    EXPECT_EQ(arr[2], 40);
    
    arr.remove(0);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 30);
}

// 13. Тест копирования массива
TEST(ArrayTest, CopyOperations) {
    Array<int> arr1;
    arr1.add(42);
    arr1.add(123);
    
    Array<int> arr2 = arr1;
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 42);
    EXPECT_EQ(arr2[1], 123);
}

// 14. Тест ошибок массива
TEST(ArrayTest, ErrorHandling) {
    Array<int> arr;
    EXPECT_TRUE(arr.empty());
    
    EXPECT_THROW(arr[0], std::out_of_range);
    EXPECT_THROW(arr.remove(0), std::out_of_range);
    
    arr.add(5);
    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr.remove(5), std::out_of_range);
}

// 15. Тест хранения фигур в массиве
TEST(FigureArrayTest, Storage) {
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

// 16. Тест имен фигур
TEST(FigureArrayTest, TypeNames) {
    Array<FigurePtr<double>> figures;
    
    figures.add(std::make_shared<Pentagon<double>>(0, 0, 1.0));
    figures.add(std::make_shared<Hexagon<double>>(0, 0, 1.0));
    figures.add(std::make_shared<Octagon<double>>(0, 0, 1.0));
    
    EXPECT_EQ(figures[0]->type(), "Pentagon");
    EXPECT_EQ(figures[1]->type(), "Hexagon");
    EXPECT_EQ(figures[2]->type(), "Octagon");
}

// 17. Тест удаления фигур из массива
TEST(FigureArrayTest, RemoveFigures) {
    Array<FigurePtr<double>> figures;
    
    figures.add(std::make_shared<Pentagon<double>>(0, 0, 1.0));
    figures.add(std::make_shared<Hexagon<double>>(0, 0, 1.0));
    figures.add(std::make_shared<Octagon<double>>(0, 0, 1.0));
    
    figures.remove(1);
    EXPECT_EQ(figures.size(), 2);
    EXPECT_EQ(figures[0]->type(), "Pentagon");
    EXPECT_EQ(figures[1]->type(), "Octagon");
}

// 18. Тест сравнения фигур (только одного типа)
TEST(FigureComparisonTest, AreaComparison) {
    Pentagon<double> small(0, 0, 1.0);
    Pentagon<double> large(0, 0, 2.0);
    
    EXPECT_TRUE(small < large);
    EXPECT_FALSE(small == large);
    EXPECT_TRUE(small != large);
}

// 19. Тест приведения к double
TEST(FigureConversionTest, DoubleConversion) {
    Pentagon<double> pentagon(0, 0, 1.0);
    double area = static_cast<double>(pentagon);
    
    EXPECT_GT(area, 0.0);
    EXPECT_EQ(area, pentagon.area());
}

// 20. Тест разных типов данных
TEST(DataTypeTest, DifferentTypes) {
    Pentagon<int> pentagon_int(0, 0, 5);
    Pentagon<float> pentagon_float(0.0f, 0.0f, 5.0f);
    Pentagon<double> pentagon_double(0.0, 0.0, 5.0);
    
    EXPECT_GT(pentagon_int.area(), 0);
    EXPECT_GT(pentagon_float.area(), 0.0f);
    EXPECT_GT(pentagon_double.area(), 0.0);
}

// 21. Интеграционный тест
TEST(IntegrationTest, CompleteWorkflow) {
    Array<FigurePtr<double>> figures;
    
    // Добавляем фигуры
    auto pentagon = std::make_shared<Pentagon<double>>(0, 0, 3.0);
    auto hexagon = std::make_shared<Hexagon<double>>(2.0, 1.0, 2.5);
    auto octagon = std::make_shared<Octagon<double>>(-1.0, -2.0, 4.0);
    
    figures.add(pentagon);
    figures.add(hexagon);
    figures.add(octagon);
    
    // Проверяем добавление
    EXPECT_EQ(figures.size(), 3);
    
    // Проверяем площади
    for (size_t i = 0; i < figures.size(); ++i) {
        EXPECT_GT(figures[i]->area(), 0.0);
    }
    
    // Проверяем имена
    EXPECT_EQ(figures[0]->type(), "Pentagon");
    EXPECT_EQ(figures[1]->type(), "Hexagon");
    EXPECT_EQ(figures[2]->type(), "Octagon");
    
    // Удаляем и проверяем
    figures.remove(1);
    EXPECT_EQ(figures.size(), 2);
    EXPECT_EQ(figures[0]->type(), "Pentagon");
    EXPECT_EQ(figures[1]->type(), "Octagon");
    
    // Проверяем общую площадь
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