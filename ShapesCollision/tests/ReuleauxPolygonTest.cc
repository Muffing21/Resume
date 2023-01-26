
#include "Circle.h"
#include "Polygon.h"
#include "Reuleaux.h"
#include <gtest/gtest.h>
#include <cmath>
#include "helper.h"

TEST(ReuleauxPolygon, Contained){
    Point x = vertex({2, 1}, {1, 1});
    const Point vertices[3] = {{1, 1}, x, {2, 1}};
    std::vector<Point> VERTICES = {{0,0}, {0, 10}, {10, 10}, {10,0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    Polygon outer = Polygon(VERTICES);
    ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, inner_outer_intersect){
    Point x = vertex({3, 0}, {0, 0});
    const Point vertices[3] = {{0, 0}, x, {3, 0}};
    // Point X = vertex({6.5, 0.5}, {1.5, 0.5});
    // std::vector<Point> VERTICES = {{1.5,0.5}, X, {6.5, 0.5}};
    Point X = vertex({5, 0}, {0, 0});
    std::vector<Point> VERTICES = {{0,0}, X, {5, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    Polygon outer = Polygon(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, inner_outer_intersect_case2){
    Point x = vertex({3, 0}, {0, 0});
    const Point vertices[3] = {{0, 0}, x, {3, 0}};
    Point X = vertex({3.48176,-0.42891}, {-0.95879,-0.3846});
    std::vector<Point> VERTICES = {{-0.95879,-0.3846}, X, {3.48176,-0.42891}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    Polygon outer = Polygon(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

// TEST(ReuleauxPolygon, inner_outer_intersect_case3){
//     Point x = vertex({3, 0}, {0, 0});
//     const Point vertices[3] = {{0, 0}, x, {3, 0}};
//     Point X = vertex({4.04708,-0.28974}, {-1.10772,-0.27289});
//     std::vector<Point> VERTICES = {{-1.10772,-0.27289}, X, {4.04708,-0.28974}};
//     ReuleauxTriangle inner = ReuleauxTriangle(vertices);
//     Polygon outer = Polygon(VERTICES);
//     ASSERT_FALSE(inner.ContainedBy(outer));
// }

TEST(ReuleauxPolygon, inner_outer_intersect_case4){
    Point x = vertex({3, 0}, {0, 0});
    const Point vertices[3] = {{0, 0}, x, {3, 0}};
    Point X = vertex({4.20672,-0.33461}, {-0.94808,-0.31777});
    std::vector<Point> VERTICES = {{-0.94808,-0.31777}, X, {4.20672,-0.33461}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    Polygon outer = Polygon(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, inner_is_outside){
    Point x = vertex({3, 0}, {0, 0});
    const Point vertices[3] = {{0, 0}, x, {3, 0}};
    Point X = vertex({8, 0}, {4, 0});
    std::vector<Point> VERTICES = {{4,0}, X, {8, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    Polygon outer = Polygon(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, inner_surround_outer){
    Point x = vertex({3, 0}, {0, 0});
    const Point vertices[3] = {{0, 0}, x, {3, 0}};
    Point X = vertex({2, 0}, {1, 0});
    std::vector<Point> VERTICES = {{1,0}, X, {2, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    Polygon outer = Polygon(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, inner_coincident_outer){
    Point x = vertex({3, 0}, {0, 0});
    const Point vertices[3] = {{0, 0}, x, {3, 0}};
    Point X = vertex({3, 0}, {0, 0});
    std::vector<Point> VERTICES = {{0,0}, X, {3, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    Polygon outer = Polygon(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, inner_is_touching_outside){
    Point x = vertex({3, 0}, {0, 0});
    const Point vertices[3] = {{0, 0}, x, {3, 0}};
    Point X = vertex({8, 0}, {3, 0});
    std::vector<Point> VERTICES = {{3,0}, X, {8, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    Polygon outer = Polygon(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, inner_is_touching_inside){
    Point x = vertex({3, 0}, {0, 0});
    const Point vertices[3] = {{0, 0}, x, {3, 0}};
    std::vector<Point> VERTICES = {{0,-2}, {0,4}, {6,4}, {6, -2}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    Polygon outer = Polygon(VERTICES);
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