#include <iostream>
#include "point.h"
#include "line.h"

int main() {
    Line l;
    Point p;

    while (std::cin >> l.a >> l.b >> l.c >> p.x >> p.y) {
        
        double gradValue = gradient(&l, &p);
        
        std::cout << CheckPointPosition(gradValue) << "\n";
    }

    return 0;
}