#include "geometry.hpp"

using namespace pixanv;

bool Rect::contains(const Point& point)
{
    return
        point.x >= x &&
        point.y >= y &&
        point.x < x + width &&
        point.y < y + height;
}