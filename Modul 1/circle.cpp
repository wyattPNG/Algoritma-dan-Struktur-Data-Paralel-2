#include "circle.h"
#include <cmath>

double distance(const Circle * c, const Point * p) {
    double dx = p->x - c->centre.x;
    double dy = p->y - c->centre.y;
    return std::sqrt((dx * dx) + (dy * dy));
}

std::string CheckPointInCircle(double diff) {
    if (diff > EPSILON) {
        return "Outside";
    } else if (diff < -EPSILON) {
        return "Inside";
    } else {
        return "On Circle";
    }
}