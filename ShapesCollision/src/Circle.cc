#include "Circle.h"
#include <cmath>
#include "Reuleaux.h"
#include "helper.h"
#include "Polygon.h"

Circle::Circle(const Point &center, double radius){
    center_.x = center.x;
    center_.y = center.y;
    radius_ = radius;
}


bool Circle::ContainedBy(Circle &circle){
    double distance = sqrt(pow((circle.getX_circle() - getX_circle()), 2) + pow((circle.getY_circle() - getY_circle()), 2));
    return distance < circle.getRadius() - getRadius();
}


//https://stackoverflow.com/questions/68188474/how-to-check-if-a-circle-is-outside-of-a-polygon
// bool Circle::ContainedBy(Polygon &polygon){
//     return polygon.ray_casting_circle(getCenter(), polygon.getVector());
// }

bool Circle::ContainedBy(Polygon &polygon){
    return polygon.casting_check_inside(getCenter(), getRadius(), polygon.getVector());
}

bool Circle::ContainedBy(ReuleauxTriangle &rt){

    Circle Circle1 = Circle(rt.getCenter1(), rt.getRadius1());
    Circle Circle2 = Circle(rt.getCenter2(), rt.getRadius2());
    Circle Circle3 = Circle(rt.getCenter3(), rt.getRadius3());

    return ContainedBy(Circle1) && ContainedBy(Circle2) && ContainedBy(Circle3);
}

//Accessor
double Circle::getRadius(){
    return radius_;
}

double Circle::getX_circle(){
    return center_.x;
}

double Circle::getY_circle(){
    return center_.y;
}

Point Circle::getCenter(){
    return center_;
}




