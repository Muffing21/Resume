#include "Circle.h"
#include "Polygon.h"
#include "Reuleaux.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(PolygonReuleaux, Contained){
    const Point vertices[3] = {{-1, 1.5}, {3, 1.5}, {1, -2}};
    std::vector<Point> vert = {{0,0}, {0,1}, {1,1}, {1,0}};
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    Polygon inner = Polygon(vert);
    ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, inner_outer_intersect){
    const Point vertices[3] = {{-1, 1.5}, {3, 1.5}, {1, -2}};
    std::vector<Point> vert = {{0,1}, {0,2}, {1,2}, {1,1}};
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, inner_is_outside){
    const Point vertices[3] = {{-1, 1.5}, {3, 1.5}, {1, -2}};
    std::vector<Point> vert = {{0,3}, {0,4}, {1,4}, {1,3}};
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, inner_surround_outer){
    const Point vertices[3] = {{-1, 1.5}, {3, 1.5}, {1, -2}};
    std::vector<Point> vert = {{-2,-3}, {-2,3}, {4,3}, {4,-3}};
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, inner_coincident_outer){
    const Point vertices[3] = {{-1, 1.5}, {3, 1.5}, {1, -2}};
    std::vector<Point> vert = {{-1, 1.5}, {1,-2}, {3, 1.5}};
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, inner_is_touching_outside){
    const Point vertices[3] = {{-1, 1.5}, {3, 1.5}, {1, -2}};
    std::vector<Point> vert = {{0,-4}, {0,-2}, {2,-2}, {2,-4}};
    //std::vector<Point> vert = {{-2,-2}, {-1,-4}, {1,-2}, {0,-4}};
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    Polygon inner = Polygon(vert);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, inner_is_touching_inside){
    const Point vertices[3] = {{-1, 1.5}, {3, 1.5}, {1, -2}};
    //std::vector<Point> vert = {{0, 0}, {2.14, 0}, {1,-2}};
    std::vector<Point> vert = {{-1,1.5}, {0,4}, {1,4}, {1,3}};
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
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