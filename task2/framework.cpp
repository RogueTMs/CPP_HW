#include <iostream>
#include <cmath>

// Struct for Point
typedef std::pair<double, double> Point;

inline double get_x(const Point& p){
    return p.first;
}

inline double get_y(const Point& p){
    return p.second;
}

// Struct for Line
struct Line {
    Point start;
    Point end;
    
    // Constructor from 2 points
    Line(Point startPoint, Point endPoint) : start(startPoint), end(endPoint) {}
    
    // Constructor from coefficients (ax + by + c = 0)
    Line(double a, double b, double c) {
        if (a == 0 && b == 0) {
            std::cerr << "Invalid coefficients for a line!" << std::endl;
            return;
        }
        
        if (b == 0) {
            start = Point(-c / a, 0);
            end = Point(-c / a, 1);
        } else {
            start = Point(0, -c / b);
            end = Point(1, (-c - a) / b);
        }
    }
    
    // Function to find the intersection with another line
    Point findIntersection(Line otherLine) {
        double x1 = get_x(start), y1 = get_y(start);
        double x2 = get_x(end), y2 = get_y(end);
        double x3 = get_x(otherLine.start), y3 = get_y(otherLine.start);
        double x4 = get_x(otherLine.end), y4 = get_y(otherLine.end);
        
        double det = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        
        if (det == 0) {
            throw std::runtime_error("Lines are parallel, no intersection point!");
        }
        
        double intersectionX = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / det;
        double intersectionY = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / det;
        
        return Point(intersectionX, intersectionY);
    }
    
    // Function to find the perpendicular line at a given point
    Line findPerpendicularLine(Point p) {
        double a = get_y(end) - get_y(start);
        double b = get_x(end) - get_x(start);
        double c = -a * get_x(p) - b * get_y(p);
        
        return Line(a, b, c);
    }
};
