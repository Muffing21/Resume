#include "Circle.h"
#include <gtest/gtest.h>
#include <cmath>

// Uncomment when you're ready

TEST(CircleCircle, Contained)
{
  Circle inner = Circle(Point(0.0,0.0), 2.0);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(CircleCircle, inner_outer_intersect){
  Circle inner = Circle(Point(0, 0), 2);
  Circle outer = Circle(Point(0, 1.5), 1);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, inner_is_outside){
  Circle inner = Circle(Point(0, 4), 1);
  Circle outer = Circle(Point(0.0, 0.0), 2);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, inner_surround_outside){
  Circle inner = Circle(Point(0, 0), 3);
  Circle outer = Circle(Point(0,1), 1);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, inner_coincident_outer){
  Circle inner = Circle(Point(0.0, 0.0), 2.0);
  Circle outer = Circle(Point(0.0, 0.0), 2.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, inner_outside_touch_outer){
  Circle inner = Circle(Point(0, 3), 1);
  Circle outer = Circle(Point(0, 0), 2);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, inner_inside_touch_outer){
  Circle inner = Circle(Point(0, 1), 1);
  Circle outer = Circle(Point(0,0), 2);
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
