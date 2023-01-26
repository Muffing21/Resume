/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>

#include "Containable.h"
#include "Point.h"

class Polygon : public Containable {
  private:
    std::vector<Point> vertices_;
  public:
    // do not modify or remove this constructor
    Polygon(std::vector<Point> vertices /* clockwise */);

    // do not modify or remove these functions
    bool ContainedBy(Circle &circle);
    bool ContainedBy(Polygon &polygon);
    bool ContainedBy(ReuleauxTriangle &rt);
    bool ray_casting_circle(Point point, std::vector<Point> polygon);
    void setVertices(Point point);
    Point getVertices(double index);
    unsigned long int getSize();
    std::vector<Point> getVector();
    
    bool casting_check_inside(Point center, double radius, std::vector<Point> polygon);
    bool pointInPolygon(Point point, std::vector<Point> polygon);
    bool lineIntersectCircle(double ax, double by, double c, Point center, double radius);
    bool pointInCircle(Point point, Point center, double radius);
    bool polygonIntersectPolygon(std::vector<Point> out, std::vector<Point> in);
};

#endif
