#include "helper.h"
#include "Containable.h"
#include "Point.h"
#include "Circle.h"

double dist(Point Point1, Point Point2){
    return sqrt(pow(Point1.x - Point2.x, 2) + (pow(Point1.y - Point2.y, 2)));
}

bool point_in_circle(Point point, Point center, double radius){
    return ((point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y)) < (radius * radius);
}

//for the purpose of accurate testing on rt....
//https://stackoverflow.com/questions/2861904/how-to-find-coordinates-of-a-2d-equilateral-triangle-in-c
Point vertex(Point p1, Point p2){
  double s60 = sin(60 * M_PI / 180.0);    
  double c60 = cos(60 * M_PI / 180.0);

  Point v = {
    c60 * (p1.x - p2.x) - s60 * (p1.y - p2.y) + p2.x,
    s60 * (p1.x - p2.x) + c60 * (p1.y - p2.y) + p2.y
  };

  return v;
}

Point sub(Point p1, Point p2) {
    return Point(p1.x - p2.x, p1.y - p2.y);
}
Point add(Point p1, Point p2) {
    return Point(p1.x + p2.x, p1.y + p2.y);
}

// Point normal(Point p1) {
//     float length = sqrt(p1.x*p1.x + p1.y*p1.y);
//     return Point(p1.x/length, p1.y/length);
// }
Point scale(Point p1, double s) {
    return Point(p1.x*s, p1.y*s);
}

//https://stackoverflow.com/questions/3349125/circle-circle-intersection-points
std::pair<Point, Point> intersections(Circle c1, Circle c2){
    Point p1 = c1.getCenter();
    Point p2 = c2.getCenter();
    double d, a, h;
    d = dist(p1, p2);
    a = (c1.getRadius()*c1.getRadius() - c2.getRadius()*c2.getRadius() + d*d) / (2*d);
    h = sqrt(c1.getRadius() * c1.getRadius() - a*a);
    Point p3 = add(scale(sub(p2, p1), a/d), p1);
    double x3, y3, x4, y4;
    x3 = p3.x + h*(p2.y - p1.y) / d;
    y3 = p3.y - h*(p2.x - p1.x) / d;
    x4 = p3.x - h*(p2.y - p1.y) / d;
    y4 = p3.y + h*(p2.x - p1.x) / d;
    
    return std::pair<Point, Point>(Point(x3, y3), Point(x4, y4));
}

//https://www.geeksforgeeks.org/program-to-find-the-centroid-of-the-triangle/
Point centroid(Point p1, Point p2, Point p3){
    Point temp = {(p1.x + p2.x + p3.x) /3, (p1.y + p2.y + p3.y)/3};
    return temp;
}


int sgn(int dx){
    return dx < 0 ? -1:1; 
}

//https://mathworld.wolfram.com/Circle-LineIntersection.html#:~:text=In%20geometry%2C%20a%20line%20meeting,429).
std::pair<Point, Point> circle_line_intersect(Point p1, Point p2, Point center, double radius){
    double translate_x = p1.x;
    double translate_y = p1.y;
    double translate_x2 = p2.x;
    double translate_y2 = p2.y;
    
    if(center.x != 0 && center.y != 0){
        translate_x = p1.x - center.x;
        translate_y = p1.y - center.y;
        translate_x2 = p2.x - center.x;
        translate_y2 = p2.y - center.y;
    }
    
    double dx = translate_x2 - translate_x;
    double dy = translate_y2 - translate_y;
    double dr = sqrt(pow(dx, 2) + pow(dy, 2));
    double D = (translate_x*translate_y2) - (translate_x2*translate_y);

    double x = (D*dy + sgn(dy)*dx*sqrt(pow(radius,2)*pow(dr, 2)-pow(D, 2))) / pow(dr, 2); 
    double x2 = (D*dy - sgn(dy)*dx*sqrt(pow(radius,2)*pow(dr, 2)-pow(D, 2))) / pow(dr, 2);
    double y = (-D*dx + abs(dy)*sqrt(pow(radius,2) * pow(dr, 2) - pow(D, 2))) / pow(dr, 2);
    double y2 = (-D*dx - abs(dy)*sqrt(pow(radius,2) * pow(dr, 2) - pow(D, 2))) / pow(dr, 2);

    return std::pair<Point, Point> (Point(x, y), Point(x2, y2));
}