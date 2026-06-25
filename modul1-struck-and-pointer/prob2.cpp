#include <iostream>
#include "point.h"
#include "circle.h"

int main() {
    Circle c;
    Point p;

    while (std::cin >> c.centre.x >> c.centre.y >> c.radius >> p.x >> p.y) {
        
        double dist = distance(&c, &p);
        
        double diff = dist - c.radius;
        
        std::cout << CheckPointInCircle(diff) << "\n";
    }

    return 0;
}