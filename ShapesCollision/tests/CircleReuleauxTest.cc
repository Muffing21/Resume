#include "Circle.h"
#include "Reuleaux.h"
#include <gtest/gtest.h>
#include <cmath>

// Uncomment when you're ready

TEST(CircleReuleaux, Contained){
    const Point vertices[3] = {{-1, 1.5}, {1, -2}, {3, 1.5}};
    Circle inner = Circle(Point(1, 0), 1);
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, inner_outer_intersect){
    const Point vertices[3] = {{-1, 1.5}, {1, -2}, {3, 1.5}};
    Circle inner = Circle(Point(0, 0), 1);
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, inner_is_outside){
    const Point vertices[3] = {{-1, 1.5}, {1, -2}, {3, 1.5}};
    Circle inner = Circle(Point(0, 3), 1);
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, inner_surround_outer){
    const Point vertices[3] = {{-1, 1.5}, {1, -2}, {3, 1.5}};
    Circle inner = Circle(Point(0, 0), 5);
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, inner_coincident_outer){
    const Point vertices[3] = {{-1, 1.5}, {1, -2}, {3, 1.5}};
    Circle inner = Circle(Point(0, 0), 2.5);
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, inner_inside_touch_outer){
    const Point vertices[3] = {{-1, 1.5}, {1, -2}, {3, 1.5}};
    Circle inner = Circle(Point(1, -1), 1);
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
    ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, inner_outside_touch_outer){
    const Point vertices[3] = {{-1, 1.5}, {1, -2}, {3, 1.5}};
    Circle inner = Circle(Point(1, -3), 1);
    ReuleauxTriangle outer = ReuleauxTriangle(vertices);
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
