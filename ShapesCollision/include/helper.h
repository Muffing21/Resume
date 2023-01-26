#include "Containable.h"
#include "Point.h"
#include <cmath>


double dist(Point Point1, Point Point2);

bool point_in_circle(Point point, Point center, double radius);

Point vertex(Point p1, Point p2);

Point sub(Point p1, Point p2);
          
Point add(Point p1, Point p2);

//Point normal();

Point scale(Point p1, double s);

Point centroid(Point p1, Point p2, Point p3);

std::pair<Point, Point> intersections(Circle c1, Circle c2);

std::pair<Point, Point> circle_line_intersect(Point p1, Point p2, Point center, double radius);