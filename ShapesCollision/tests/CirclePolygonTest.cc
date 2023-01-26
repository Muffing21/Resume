#include "Circle.h"
#include <gtest/gtest.h>
#include "Polygon.h"

TEST(CirclePolygon, Contained){
    std::vector<Point> vert = {{0, 5}, {1, 4.5}, {2.5, 0}, {-2.5, 0}};
    Circle inner = Circle(Point(0, 2), 1);
    Polygon outer = Polygon(vert);
    ASSERT_TRUE(inner.ContainedBy(outer));
}

//failing this test
TEST(CirclePolygon, Intersect){
    std::vector<Point> vert = {{0, 5}, {1, 4.5}, {2.5, 0}, {-2.5, 0}};
    //Circle inner = Circle(Point(-1, 2), 1);
    Circle inner = Circle(Point(0, 1), 1);
    Polygon outer = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CirclePolygon, inner_is_outside){
    std::vector<Point> vert = {{0, 5}, {1, 4.5}, {2.5, 0}, {-2.5, 0}};
    //Circle inner = Circle(Point(0, 7), 1);
    //Circle inner = Circle(Point(-4, 2), 1);
    Circle inner = Circle(Point(4, 2), 1);
    //Circle inner = Circle(Point(0, -2), 1);
    Polygon outer = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

//fail
TEST(CirclePolygon, inner_surround_outside){
    std::vector<Point> vert = {{0, 6}, {0, 2}, {6.27, -0.08}, {-6, 0}};
    Circle inner = Circle(Point(0, 2), 8);
    Polygon outer = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

//how? change later
TEST(CirclePolygon, inner_coincident_outer){
    std::vector<Point> vert = {{0, 5}, {1, 4.5}, {2.5, 0}, {-2.5, 0}};
    Circle inner = Circle(Point(0, 2), 3);
    Polygon outer = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CirclePolygon, inner_is_touching_outside){
    std::vector<Point> vert = {{0, 5}, {1, 4.5}, {2.5, 0}, {-2.5, 0}};
    //Circle inner = Circle(Point(0, 6), 1);
    Circle inner = Circle(Point(3.5, 0), 1);
    Polygon outer = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

//fail
TEST(CirclePolygon, inner_is_touching_inside){
    std::vector<Point> vert = {{0, 6},{0, 2}, {6.27, -0.08}, {-6, 0}};
    Circle inner = Circle(Point(-0.8, 1.4), 1);
    Polygon outer = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}


/* 
   You'll need to extend this by adding additional tests for:
    1. Inner and Outer intersect (not contained) /
    2. Inner is entirely outside Outer (not contained) /
    3. Inner surrounds Outer (not contained) /
    3. Inner coincident with Outer (not contained) /
    4. Inner perimeter touches Outer perimeter, Inner is inside Outer (not contained)/
    5. Inner perimeter touches Outer perimeter, Inner is outside Outer (not contained)/

    Note that 4. and 5. should be taken care of by 1. but you need the tests to make sure
*/