#include "Reuleaux.h"
#include <cmath>
#include "helper.h"
#include "Circle.h"
#include "Polygon.h"
#include <iostream>
#include <cfloat>



ReuleauxTriangle::ReuleauxTriangle(const Point vertices[3]){
    center1 = vertices[0];
    center2 = vertices[1];
    center3 = vertices[2];
    radius1 = dist(vertices[0], vertices[1]);
    radius2 = dist(vertices[1], vertices[2]);
    radius3 = dist(vertices[2], vertices[0]);
    for(int i = 0; i < 3; i++){
        vec.push_back(vertices[i]);
    }
}

//     // do not modify or remove these functions
// bool ReuleauxTriangle::ContainedBy(Circle &circle){
//     Circle circle1 = Circle(getCenter1(), getRadius1());
//     // Circle circle2 = Circle(getCenter2(), getRadius2());
//     // Circle circle3 = Circle(getCenter3(), getRadius3());
    

//     bool vert1 = point_in_circle(getCenter1(), circle.getCenter(), circle.getRadius());
//     bool vert2 = point_in_circle(getCenter2(), circle.getCenter(), circle.getRadius());
//     bool vert3 = point_in_circle(getCenter3(), circle.getCenter(), circle.getRadius());
//     std::cout << vert1 << std::endl;
//     std::cout <<  vert2  << std::endl;
//     std::cout << vert3 << std::endl;
//     if(vert1 == 1 && vert2 == 1 && vert3 == 1){
//         if(circle1.getRadius() < circle.getRadius()){
//             return false;
//         }
//         return true;
//     }
    
//     return false;
// }

bool ReuleauxTriangle::ContainedBy(Circle &circle){
    std::pair<Point, Point> intersected;
    Circle circle1 = Circle(getCenter1(), getRadius1());
    Circle circle2 = Circle(getCenter2(), getRadius2());
    Circle circle3 = Circle(getCenter3(), getRadius3());
    bool vert1 = point_in_circle(getCenter1(), circle.getCenter(), circle.getRadius());
    bool vert2 = point_in_circle(getCenter2(), circle.getCenter(), circle.getRadius());
    bool vert3 = point_in_circle(getCenter3(), circle.getCenter(), circle.getRadius());
    double temp = DBL_MAX;
    unsigned long int temp2 = 0;
    if(vert1 == 1 && vert2 == 1 && vert3 == 1){
        for(unsigned long int i = 0; i < 3; i++){
            if(dist(vec[i], circle.getCenter()) < temp){
                temp = dist(vec[i], circle.getCenter());
                temp2 = i;
            }
        }
        if(temp2 == 0){
            intersected = intersections(circle, circle1);       //the if state here checks if the 2 intersection points are in both circles that are further away from the container obj
            if((point_in_circle(intersected.first, getCenter2(), getRadius2()) && point_in_circle(intersected.second, getCenter2(), getRadius2()))
                 && (point_in_circle(intersected.first, getCenter3(), getRadius3()) && point_in_circle(intersected.second, getCenter3(), getRadius3()))){
                return false;
            }
        }
        else if(temp2 == 1){
            intersected = intersections(circle, circle2);
            if((point_in_circle(intersected.first, getCenter1(), getRadius1()) && point_in_circle(intersected.second, getCenter1(), getRadius1()))
                && (point_in_circle(intersected.first, getCenter3(), getRadius3()) && point_in_circle(intersected.second, getCenter3(), getRadius3()))){
                return false;
            }
        }
        else{
            intersected = intersections(circle, circle3);
            if((point_in_circle(intersected.first, getCenter1(), getRadius1()) && point_in_circle(intersected.second, getCenter1(), getRadius1()))
                && (point_in_circle(intersected.first, getCenter2(), getRadius2()) && point_in_circle(intersected.second, getCenter2(), getRadius2()))){
                return false;
            }
        }
        return true;            //if non of given intersection points exist in both of them simultaneously, then no intersection occured
    }
    return false;
}

bool ReuleauxTriangle::ContainedBy(Polygon &polygon){
    std::pair<Point, Point> judpobgun;
    Circle circle1 = Circle(getCenter1(), getRadius1());
    Circle circle2 = Circle(getCenter2(), getRadius2());
    Circle circle3 = Circle(getCenter3(), getRadius3());
    
    
    Polygon polygon1 = Polygon(vec);  
    bool poly1 = polygon1.ContainedBy(polygon);

    // bool poly1 = polygon.pointInPolygon(getCenter1(), polygon.getVector());
    // bool poly2 = polygon.pointInPolygon(getCenter2(), polygon.getVector());
    // bool poly3 = polygon.pointInPolygon(getCenter3(), polygon.getVector());
    
    if(poly1){
        for(unsigned long int z = 0; z < 3; z++){
            if(z == 0){
                judpobgun = circle_line_intersect(polygon.getVertices(1), polygon.getVertices(2), circle1.getCenter(), circle1.getRadius());
              
                if((point_in_circle(judpobgun.first, getCenter2(), getRadius2()) && point_in_circle(judpobgun.second, getCenter2(), getRadius2())) 
                && (point_in_circle(judpobgun.first, getCenter3(), getRadius3()) && point_in_circle(judpobgun.second, getCenter3(), getRadius3()))){
                    
                    return false;
                }
            }
            // else if(z == 1){
            //     judpobgun = circle_line_intersect(polygon.getVertices(0), polygon.getVertices(2), circle2.getCenter(), circle2.getRadius());
            //     std::cout << "in case 3" << std::endl;
            //     if((point_in_circle(judpobgun.first, getCenter1(), getRadius1()) && point_in_circle(judpobgun.second, getCenter1(), getRadius1()))
            //     && (point_in_circle(judpobgun.first, getCenter3(), getRadius3()) && point_in_circle(judpobgun.second, getCenter3(), getRadius3()))){
                
            //         return false;
            //     }
            // }
        
            else if(z == 2){
                judpobgun = circle_line_intersect(polygon.getVertices(0), polygon.getVertices(1), circle3.getCenter(), circle3.getRadius());
                if((point_in_circle(judpobgun.first, circle1.getCenter(), circle1.getRadius()) || point_in_circle(judpobgun.second, circle1.getCenter(), circle1.getRadius()))
                && (point_in_circle(judpobgun.first, circle2.getCenter(), circle2.getRadius()) || point_in_circle(judpobgun.second, circle2.getCenter(), circle2.getRadius()))){
                    return false;
                }
            }
        
        }
        return true;
    }
    return false;
}

bool ReuleauxTriangle::ContainedBy(ReuleauxTriangle &rt){
    Circle circle1 = Circle(rt.getCenter1(), rt.getRadius1());
    Circle circle2 = Circle(rt.getCenter2(), rt.getRadius2());
    Circle circle3 = Circle(rt.getCenter3(), rt.getRadius3());
    
    return ContainedBy(circle1) && ContainedBy(circle2) && ContainedBy(circle3); 
}



double ReuleauxTriangle::getRadius1(){
    return radius1;
}

double ReuleauxTriangle::getRadius2(){
    return radius2;
}

double ReuleauxTriangle::getRadius3(){
    return radius3;
}

Point ReuleauxTriangle::getCenter1(){
    return center1;
}

Point ReuleauxTriangle::getCenter2(){
    return center2;
}

Point ReuleauxTriangle::getCenter3(){
    return center3;
}

