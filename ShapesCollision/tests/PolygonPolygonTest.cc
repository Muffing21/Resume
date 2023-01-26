#include "Circle.h"
#include "Polygon.h"
#include "Reuleaux.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(PolygonPolygon, Contained){
    std::vector<Point> vert = {{0, 1}, {1, 1}, {1, 0}, {0,0}};
    std::vector<Point> vert2 = {{0.6, 0.2}, {0.6, 0.4}, {0.8, 0.4}, {0.8, 0.4}};
    Polygon outer = Polygon(vert);
    Polygon inner = Polygon(vert2);
    ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, inner_outer_intersect){
    std::vector<Point> vert = {{0, 1}, {1, 1}, {1, 0}, {0,0}};
    std::vector<Point> vert2 = {{0, 0}, {0, 0.2}, {0.2, 0.2}, {0.2, 0}};
    Polygon outer = Polygon(vert);
    Polygon inner = Polygon(vert2);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, inner_is_outside){
    std::vector<Point> vert = {{0, 1}, {1, 1}, {1, 0}, {0,0}};
    std::vector<Point> vert2 = {{-0.3, 0}, {-0.3, 0.2}, {-0.1, 0.2}, {-0.1, 0}};
    Polygon outer = Polygon(vert);
    Polygon inner = Polygon(vert2);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, inner_surround_outer){
    std::vector<Point> vert = {{0, 1}, {1, 1}, {1, 0}, {0,0}};
    std::vector<Point> vert2 = {{-0.2, -0.2}, {-0.2, 1.2}, {1.2, 1.2}, {1.2, -0.2}};
    Polygon outer = Polygon(vert);
    Polygon inner = Polygon(vert2);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, inner_coincident_outer){
    std::vector<Point> vert = {{0, 1}, {1, 1}, {1, 0}, {0,0}};
    std::vector<Point> vert2 = {{0, 1}, {1, 1}, {1, 0}, {0,0}};
    Polygon outer = Polygon(vert);
    Polygon inner = Polygon(vert2);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, inner_is_touching_outside){
    std::vector<Point> vert = {{0, 1}, {1, 1}, {1, 0}, {0,0}};
    std::vector<Point> vert2 = {{1, 1}, {1, 1.2}, {1.2, 1.2}, {1.2,1}};
    Polygon outer = Polygon(vert);
    Polygon inner = Polygon(vert2);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, inner_is_touching_inside){
    std::vector<Point> vert = {{-0.8, 0.2}, {-1, 0}, {-1, 0.6}, {-0.4, 0.6}, {-0.4, 0}};
    std::vector<Point> vert2 = {{-1, 1.46}, {2, 1.46}, {1, -0.54}, {0, -0.54}};
    Polygon outer = Polygon(vert);
    Polygon inner = Polygon(vert2);
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