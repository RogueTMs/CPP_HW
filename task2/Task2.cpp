#include <iostream>
#include <cmath>

// Struct for Point
struct Point {
    double x;
    double y;

    // Default constructor
    Point() : x(0.0), y(0.0) {}
    
    Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}
};

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
        double x1 = start.x, y1 = start.y;
        double x2 = end.x, y2 = end.y;
        double x3 = otherLine.start.x, y3 = otherLine.start.y;
        double x4 = otherLine.end.x, y4 = otherLine.end.y;
        
        double det = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        
        if (det == 0) {
            std::cerr << "Lines are parallel, no intersection point!" << std::endl;
            return Point(0, 0);
        }
        
        double intersectionX = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / det;
        double intersectionY = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / det;
        
        return Point(intersectionX, intersectionY);
    }
    
    // Function to find the perpendicular line at a given point
    Line findPerpendicularLine(Point p) {
        double a = start.y - end.y;
        double b = end.x - start.x;
        double c = -a * p.x - b * p.y;
        
        return Line(a, b, c);
    }
};

int main() {
    Point p1(1.0, 2.0);
    Point p2(3.0, 4.0);
    
    Line line1(p1, p2);
    
    Line line2(2.0, -1.0, 3.0);
    
    Point intersection = line1.findIntersection(line2);
    std::cout << "Intersection point: (" << intersection.x << ", " << intersection.y << ")" << std::endl;
    
    Point pointForPerpendicular(5.0, 6.0);
    Line perpendicularLine = line1.findPerpendicularLine(pointForPerpendicular);
    std::cout << "Perpendicular line start: (" << perpendicularLine.start.x << ", " << perpendicularLine.start.y << ")" << std::endl;
    std::cout << "Perpendicular line end: (" << perpendicularLine.end.x << ", " << perpendicularLine.end.y << ")" << std::endl;
    
    return 0;
}