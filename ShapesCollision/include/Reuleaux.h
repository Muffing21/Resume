/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#ifndef _REULEAUX_H_
#define _REULEAUX_H_

#include "Containable.h"
#include "Point.h"
#include <vector>

class ReuleauxTriangle : public Containable {
  private:
    double radius1;
    double radius2;
    double radius3;
    Point center1;
    Point center2;
    Point center3;
    std::vector<Point> vec;
  public:
    // do not modify or remove this constructor
    ReuleauxTriangle(const Point vertices[3] /* clockwise */);

    // do not modify or remove these functions
    bool ContainedBy(Circle &circle);
    bool ContainedBy(Polygon &polygon);
    bool ContainedBy(ReuleauxTriangle &rt);
    double getRadius1();
    double getRadius2();
    double getRadius3();
    Point getCenter1();
    Point getCenter2();
    Point getCenter3();
    
};

#endif
