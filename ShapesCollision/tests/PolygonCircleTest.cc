#include "Circle.h"
#include "Polygon.h"
#include "Reuleaux.h"
#include <gtest/gtest.h>
#include <cmath>

// Uncomment when you're ready

TEST(PolygonCircle, Contained){
    std::vector<Point> vert = {{0, 6}, {2, 8}, {4, 6}, {3, 3}, {0, 0}, {-3, 3}, {-4, 6}, {-2, 8}};
    Circle outer = Circle(Point(0, 3), 6);
    Polygon inner = Polygon(vert);
    ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, inner_outer_intersect){
    std::vector<Point> vert = {{-2, 6}, {-2, 10}, {2, 10}, {2, 8}};
    Circle outer = Circle(Point(0, 3), 6);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, inner_is_outside){
    std::vector<Point> vert = {{-14, 6}, {-14, 10}, {-10, 10}, {-10, 6}};
    Circle outer = Circle(Point(0, 3), 6);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, inner_surround_outer){
    std::vector<Point> vert = {{-8, -4}, {-8, 12}, {8, 12}, {8, -4}};
    Circle outer = Circle(Point(0, 3), 6);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, inner_coincident_outer){
    std::vector<Point> vert = {{-5.2, 0}, {-5.2, 6}, {5.2, 6}, {5.2, 0}};
    Circle outer = Circle(Point(0, 3), 6);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, inner_is_touching_inside){
    std::vector<Point> vert = {{-5.2, 6}, {-5, 6}, {-5, 5.8}, {-5.2, 5.8}};
    Circle outer = Circle(Point(0, 3), 6);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, inner_is_touching_outside){
    std::vector<Point> vert = {{-5.2, 6}, {-5.4, 6}, {-5.4, 6.2}, {-5.2, 6.2}};
    Circle outer = Circle(Point(0, 3), 6);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}
/* 
   You'll need to extend this by adding additional tests for:
    1. Inner and Outer intersect (not contained)
    2. Inner is entirely outside Outer (not contained)
    3. Inner surrounds Outer (not contained)
    3. Inner coincident with Outer (not contained)
    4. Inner perimeter touches Outer perimeter, Inner is inside Outer (not contained)
    5. Inner perimeter touches Outer perimeter, Inner is outside Outer (not contained)

    Note that 4. and 5. should be taken care of by 1. but you need the tests to make sure
*/