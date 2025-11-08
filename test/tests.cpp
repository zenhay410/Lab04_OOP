#include <gtest/gtest.h>
#include "../include/point.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/octagon.h"
#include "../include/array.h"

TEST(PointTest, Create) {
    Point<int> p1;
    EXPECT_EQ(p1.x(), 0);
    EXPECT_EQ(p1.y(), 0);
    
    Point<double> p2(1.5, 2.5);
    EXPECT_DOUBLE_EQ(p2.x(), 1.5);
    EXPECT_DOUBLE_EQ(p2.y(), 2.5);
}

TEST(PointTest, Copy) {
    Point<int> p1(10, 20);
    Point<int> p2 = p1;
    EXPECT_EQ(p2.x(), 10);
    EXPECT_EQ(p2.y(), 20);
}

TEST(PointTest, Compare) {
    Point<int> p1(5, 10);
    Point<int> p2(5, 10);
    Point<int> p3(10, 5);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PentagonTest, Create) {
    Pentagon<double> p(0, 0, 1.0);
    EXPECT_GT(p.area(), 0.0);
}

TEST(PentagonTest, Center) {
    Pentagon<double> p(5.0, 5.0, 2.0);
    auto c = p.center();
    EXPECT_NEAR(c.x(), 5.0, 0.01);
    EXPECT_NEAR(c.y(), 5.0, 0.01);
}

TEST(HexagonTest, Create) {
    Hexagon<double> h(0, 0, 1.0);
    EXPECT_GT(h.area(), 0.0);
}

TEST(HexagonTest, Center) {
    Hexagon<double> h(3.0, 4.0, 2.0);
    auto c = h.center();
    EXPECT_NEAR(c.x(), 3.0, 0.01);
    EXPECT_NEAR(c.y(), 4.0, 0.01);
}

TEST(OctagonTest, Create) {
    Octagon<double> o(0, 0, 1.0);
    EXPECT_GT(o.area(), 0.0);
}

TEST(OctagonTest, Center) {
    Octagon<double> o(2.0, 3.0, 1.5);
    auto c = o.center();
    EXPECT_NEAR(c.x(), 2.0, 0.01);
    EXPECT_NEAR(c.y(), 3.0, 0.01);
}

TEST(ArrayTest, Add) {
    Array<int> a;
    a.add(1);
    a.add(2);
    a.add(3);
    
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
}

TEST(ArrayTest, Remove) {
    Array<int> a;
    a.add(10);
    a.add(20);
    a.add(30);
    
    a.remove(1);
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a[0], 10);
    EXPECT_EQ(a[1], 30);
}

TEST(ArrayTest, Copy) {
    Array<int> a1;
    a1.add(42);
    a1.add(123);
    
    Array<int> a2 = a1;
    EXPECT_EQ(a2.size(), 2);
    EXPECT_EQ(a2[0], 42);
    EXPECT_EQ(a2[1], 123);
}

TEST(ArrayTest, Error) {
    Array<int> a;
    a.add(5);
    
    EXPECT_THROW(a[1], std::out_of_range);
    EXPECT_THROW(a.remove(5), std::out_of_range);
}

TEST(FigureTest, Types) {
    auto p = std::make_shared<Pentagon<double>>(0, 0, 1.0);
    auto h = std::make_shared<Hexagon<double>>(0, 0, 1.0);
    auto o = std::make_shared<Octagon<double>>(0, 0, 1.0);
    
    EXPECT_EQ(p->type(), "Pentagon");
    EXPECT_EQ(h->type(), "Hexagon");
    EXPECT_EQ(o->type(), "Octagon");
}

TEST(FigureTest, Compare) {
    Pentagon<double> p1(0, 0, 1.0);
    Pentagon<double> p2(0, 0, 2.0);
    
    EXPECT_TRUE(p1 < p2);
    EXPECT_FALSE(p1 == p2);
}

TEST(FigureTest, Convert) {
    Pentagon<double> p(0, 0, 1.0);
    double a = static_cast<double>(p);
    EXPECT_GT(a, 0.0);
}

TEST(IntegrationTest, Workflow) {
    Array<FigurePtr<double>> f;
    
    auto p = std::make_shared<Pentagon<double>>(0, 0, 3.0);
    auto h = std::make_shared<Hexagon<double>>(2.0, 1.0, 2.5);
    auto o = std::make_shared<Octagon<double>>(-1.0, -2.0, 4.0);
    
    f.add(p);
    f.add(h);
    f.add(o);
    
    EXPECT_EQ(f.size(), 3);
    
    for (size_t i = 0; i < f.size(); ++i) {
        EXPECT_GT(f[i]->area(), 0.0);
    }
    
    EXPECT_EQ(f[0]->type(), "Pentagon");
    EXPECT_EQ(f[1]->type(), "Hexagon");
    EXPECT_EQ(f[2]->type(), "Octagon");
    
    f.remove(1);
    EXPECT_EQ(f.size(), 2);
    EXPECT_EQ(f[0]->type(), "Pentagon");
    EXPECT_EQ(f[1]->type(), "Octagon");
    
    double total = 0.0;
    for (size_t i = 0; i < f.size(); ++i) {
        total += f[i]->area();
    }
    EXPECT_GT(total, 0.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}