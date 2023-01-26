#include "Circle.h"
#include "Polygon.h"
#include "Reuleaux.h"
#include <gtest/gtest.h>
#include <cmath>
#include "helper.h"



TEST(ReuleauxCircle, Contained){
    Point c = vertex({3, 0},{0, 0});
    const Point vertices[3] = {{0, 0}, c, {3, 0}};
    Circle outer = Circle(Point(1.5, 1), 2);
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, inner_outer_intersect){
    Point c = vertex({3, 0},{0, 0});
    const Point vertices[3] = {{0, 0}, c, {3, 0}};
    //Circle outer = Circle(Point(3.77, 2.15), 5);  
    //Circle outer = Circle(Point(0, 0), 3);  //same as bottom left circle
    Circle outer = Circle(Point(1.2654,10.40293), dist({1.2654,10.40293}, {2.3, -0.3}));     //all vertices inside circle but special case
    //Circle outer = Circle(Point(2.6, 1.16), 2.5);
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, inner_outer_intersect_case2){
    Point c = vertex({3, 0},{0, 0});
    const Point vertices[3] = {{0, 0}, c, {3, 0}};
    //Circle outer = Circle(Point(3.77, 2.15), 5);  
    //Circle outer = Circle(Point(0, 0), 3);  //same as bottom left circle
    Circle outer = Circle(Point(-5.04967,-3.82772), dist({-5.04967,-3.82772}, {1.8, 2.4}));     //all vertices inside circle but special case
    //Circle outer = Circle(Point(2.6, 1.16), 2.5);
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, inner_outer_intersect_case3){
    Point c = vertex({3, 0},{0, 0});
    const Point vertices[3] = {{0, 0}, c, {3, 0}};
    //Circle outer = Circle(Point(3.77, 2.15), 5);  
    //Circle outer = Circle(Point(0, 0), 3);  //same as bottom left circle
    Circle outer = Circle(Point(12,-8), dist({12,-8}, {1.1, 2.3}));     //all vertices inside circle but special case
    //Circle outer = Circle(Point(2.6, 1.16), 2.5);
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, inner_is_outside){
    Point c = vertex({3, 0},{0, 0});
    const Point vertices[3] = {{0, 0}, c, {3, 0}};
    Circle outer = Circle(Point(-8, 10), 5);
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, inner_surround_outer){
    Point c = vertex({3, 0},{0, 0});
    const Point vertices[3] = {{0, 0}, c, {3, 0}};
    Circle outer = Circle(Point(1.52, 0.88), 0.58);
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, inner_coincident_outer){
    Point c = vertex({3, 0},{0, 0});
    const Point vertices[3] = {{0, 0}, c, {3, 0}};
    Circle outer = Circle(centroid({0, 0}, c, {3, 0}), dist(centroid({0, 0}, c, {3, 0}), {3,0}));
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, inner_is_touching_outside){
    Point c = vertex({3, 0},{0, 0});
    const Point vertices[3] = {{0, 0}, c, {3, 0}};
    Circle outer = Circle(Point(-5.04, -4.58), dist({-5.04, -4.58}, {0,0}));    //dist({-4,-4}, {0,0}
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, inner_is_touching_inside){
    Point c = vertex({3, 0},{0, 0});
    const Point vertices[3] = {{0, 0}, c, {3, 0}};
    Circle outer = Circle(Point(0, -6), dist({0, 6}, c));    //dist({-4,-4}, {0,0}
    ReuleauxTriangle inner = ReuleauxTriangle(vertices);
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