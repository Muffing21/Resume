#include "Circle.h"
#include "Polygon.h"
#include "Reuleaux.h"
#include <gtest/gtest.h>
#include <cmath>
#include "helper.h"



TEST(ReuleauxReuleaux, Contained){
    Point X = vertex({3, 0},{0, 0});
    Point x = vertex({2, 1}, {1, 1});
    const Point vertices[3] = {{1, 1}, x, {2, 1}};
    const Point VERTICES[3] = {{0, 0}, X, {3, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ReuleauxTriangle outer = ReuleauxTriangle(VERTICES);
    ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, inner_outer_intersect){
    Point X = vertex({3, 0},{0, 0});
    Point x = vertex({1, 0}, {0, 0});
    const Point vertices[3] = {{1, 0}, x, {0, 0}};
    const Point VERTICES[3] = {{0, 0}, X, {3, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ReuleauxTriangle outer = ReuleauxTriangle(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, inner_is_outside){
    Point X = vertex({3, 0},{0, 0});
    Point x = vertex({1, 0}, {0, 0});
    const Point vertices[3] = {{1, 0}, x, {0, 0}};
    const Point VERTICES[3] = {{0, 0}, X, {3, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ReuleauxTriangle outer = ReuleauxTriangle(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, inner_surround_outer){
    Point X = vertex({3, 0},{0, 0});
    Point x = vertex({2, 1}, {1, 1});
    const Point vertices[3] = {{0, 0}, X, {3, 0}}; 
    const Point VERTICES[3] = {{1, 1}, x, {2, 1}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ReuleauxTriangle outer = ReuleauxTriangle(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, inner_coincident_outer){
    Point X = vertex({3, 0},{0, 0});
    Point x = vertex({3, 0}, {0, 0});
    const Point vertices[3] = {{0, 0}, x, {3, 0}};
    const Point VERTICES[3] = {{0, 0}, X, {3, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ReuleauxTriangle outer = ReuleauxTriangle(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, inner_is_touching_inside){
    Point X = vertex({3, 0},{0, 0});
    Point x = vertex({3, 0}, {2, 0});
    const Point vertices[3] = {{2, 0}, x, {3, 0}};
    const Point VERTICES[3] = {{0, 0}, X, {3, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ReuleauxTriangle outer = ReuleauxTriangle(VERTICES);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, inner_is_touching_outside){
    Point X = vertex({3, 0},{0, 0});
    Point x = vertex({4, 0}, {3, 0});
    const Point vertices[3] = {{3, 0}, x, {4, 0}};
    const Point VERTICES[3] = {{0, 0}, X, {3, 0}};
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ReuleauxTriangle outer = ReuleauxTriangle(VERTICES);
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