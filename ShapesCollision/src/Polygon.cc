#include "Polygon.h"
#include "Circle.h"
#include "Reuleaux.h"
#include <cmath>
#include <iostream>
#include "helper.h"


Polygon::Polygon(std::vector<Point> vertices /* clockwise */){
    for(long unsigned int i = 0; i != vertices.size(); i++){
        setVertices(vertices[i]);
    }
}

// do not modify or remove these functions

bool Polygon::ContainedBy(Circle &circle){
    for(unsigned long int i = 0; i < getSize(); i++){
        auto distance = std::abs(dist(circle.getCenter(), getVertices(i)));
        if(circle.getRadius() < distance){
            return false;
        }
    }
    return true;
}

bool Polygon::ContainedBy(Polygon &polygon){
    if(polygonIntersectPolygon(polygon.getVector(), getVector())){
        return false;
    }
    for(unsigned long int i = 0; i < getSize(); i++){
        if(!pointInPolygon(getVertices(i), polygon.getVector())){
            return false;
        }
    }
    return true;
}

bool Polygon::ContainedBy(ReuleauxTriangle &rt){
    Circle circle1 = Circle(rt.getCenter1(), rt.getRadius1());
    Circle circle2 = Circle(rt.getCenter2(), rt.getRadius2());
    Circle circle3 = Circle(rt.getCenter3(), rt.getRadius3());
    return ContainedBy(circle1) && ContainedBy(circle2) && ContainedBy(circle3); 
}

//https://stackoverflow.com/questions/68188474/how-to-check-if-a-circle-is-outside-of-a-polygon
bool Polygon::casting_check_inside(Point center, double radius, std::vector<Point> polygon){
    unsigned long int edges = getSize();
    //center of circle is not within polygon
    if(!pointInPolygon(center, polygon)){
        //std::cout << "center of circle is not within polygon" << std::endl;
        return false;
    }

    for(unsigned long int i = 0; i < edges; i++){
        if(pointInCircle(polygon[i], center, radius)){
            //std::cout << "i am in pointinCircle loop" << std::endl;
            return false;
        }

        Point a = polygon[i];
        Point b;
        if(i+1 >= edges){
            b = polygon[0];
        }
        else{
            b = polygon[i+1];
        }

        double x1 = a.x, x2 = b.x, y1 = a.y, y2 = b.y;

        double A = y1 - y2, B = x2 - x1, C = (x1 * y2) - (x2 * y1);

        if(lineIntersectCircle(A, B, C, center, radius)){
            //std::cout << "im in lineIntersectCircle" << std::endl;
            return false;
        }        
    }
    return true;
}

//https://www.youtube.com/watch?v=01E0RGb2Wzo
// bool Polygon::ray_casting(Point point, std::vector<Point> polygon){
//     unsigned long int num_edge = getSize();
//     int intersect = 0; //if count is 1, it is inside. If more than one, it is outside. if 0 it is also outside
//     double center_x = point.x;
//     double center_y = point.y;

//     for(unsigned long int i = 0; i < num_edge; i++){
//         //declare each side of the polygon, A and B
//         auto a = polygon[i];
//         Point b;
//         if(i+1 >= num_edge){
//             b = polygon[0];
//         }
//         else{
//             b = polygon[i+1];
//         }
        
        
//         double x1 = a.x, x2 = b.x, y1 = a.y, y2 = b.y;
        

//         //if inside the verticle axis of point a and b
//         if((center_y < y1) != (center_y < y2) && center_x < (x2-x1) * (center_y - y1) / (y2 -y1) + x1){
//             intersect += 1;
//         }
//     }
    
//     if(intersect % 2 == 0){
//         return false;
//     }
//     return true;
// }

void Polygon::setVertices(Point point){
    vertices_.push_back(point);
}

Point Polygon::getVertices(double index){
    return vertices_[index];
}

unsigned long int Polygon::getSize(){
    return vertices_.size();
}

std::vector<Point> Polygon::getVector(){
    return vertices_;
}

//https://stackoverflow.com/questions/68188474/how-to-check-if-a-circle-is-outside-of-a-polygon
// bool Polygon::pointInPolygon(Point point, std::vector<Point> polygon){
//     bool temp = false;
//     //unsigned long int size = polygon.size() - 1;
//     std::size_t size = polygon.size();
//     for (unsigned long int i = 0; i < polygon.size(); i++){
//         if (((polygon[i].y <= point.y && point.y < polygon[size-1].y) || (polygon[size-1].y <= point.y && point.y < polygon[i].y))) {
//             if(point.x < ((polygon[size-1].x - polygon[i].x) * (point.y - polygon[i].y) / (polygon[size-1].y - polygon[i].y) + polygon[i].x)){
//                 temp = !temp;
//             }
//         }
//         size = i;
//     }
//     return temp;
// }

bool Polygon::pointInPolygon(Point point, std::vector<Point> polygon){
    bool c = false;
    long unsigned int i, j;
    for(i = 0, j = polygon.size()-1; i < polygon.size(); j = i++){
        if(((polygon[i].y > point.y) != (polygon[j].y > point.y)) &&
        (point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)){
            c = !c;
        }    
    }
    return c;
}

//https://stackoverflow.com/questions/68188474/how-to-check-if-a-circle-is-outside-of-a-polygon
bool Polygon::lineIntersectCircle(double ax, double by, double c, Point center, double radius){
    double distance = (std::abs(ax * center.x + by * center.y + c) / sqrt(ax * ax + by * by));
    return distance <= radius;
}

//https://stackoverflow.com/questions/68188474/how-to-check-if-a-circle-is-outside-of-a-polygon
bool Polygon::pointInCircle(Point point, Point center, double radius){
    return ((point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y)) < (radius * radius);
}

bool Polygon::polygonIntersectPolygon(std::vector<Point> out, std::vector<Point> in){
    for(unsigned long int i = 0; i < out.size(); i++){
        for(unsigned long int j = 0; j < in.size(); j++){
            Point A = out[i];
            Point B;
            if(i+1 == out.size()){
                B = out[0]; //outer
            }
            else{
                B = out[i+1];
            }
            
            Point a = in[j];       //inner
            Point b;
            if(j+1 == in.size()){
                b = in[0];
            }
            else{
                b = in[j+1];
            }

            //line intersection formula https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
            double t = ((A.x - a.x)*(a.y - b.y) - (A.y - a.y)*(a.x - b.x)) / ((A.x - B.x)*(a.y - b.y) - (A.y - B.y)*(a.x - b.x));
            double u = ((A.x - a.x)*(A.y - B.y) - (A.y - a.y)*(A.x - B.x)) / ((A.x - B.x)*(a.y - b.y) - (A.y - B.y)*(a.x - b.x));

            // std::cout << "t: " << t << std::endl;
            // std::cout << "u: " << u << std::endl;
            if((0 <= t && t <= 1) && (0 <= u && u <= 1)){
                return true;
            }
        }
    }
    return false;
}