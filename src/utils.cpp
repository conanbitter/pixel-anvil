#include "utils.hpp"
#include <cmath>
#include <algorithm>

using namespace pixanv;

bool Rect::contains(const Point& point)
{
    return
        point.x >= x &&
        point.y >= y &&
        point.x < x + width &&
        point.y < y + height;
}

#pragma region Color

Color::Color(int r, int g, int b, int a = 1)
{
    a = std::clamp(a, 0, 1);
    r = std::clamp(r, 0, 0b11111);
    g = std::clamp(g, 0, 0b11111);
    b = std::clamp(b, 0, 0b11111);
    value = a << 15 | r << 10 | g << 5 | b;
}

int Color::r() const
{
    return (value >> 10) & 0b11111;
}

int Color::g() const
{
    return (value >> 5) & 0b11111;
}

int Color::b() const
{
    return value & 0b11111;
}

int Color::a() const
{
    return value >> 15;
}

Color pixanv::Color::operator*(const Color& rhs) const
{
    return Color(
        (r() * rhs.r()) / 31,
        (g() * rhs.g()) / 31,
        (b() * rhs.b()) / 31,
        (a() * rhs.a())
    );
}

Color pixanv::Color::operator*(float rhs) const
{
    return Color(
        std::round(r() * rhs),
        std::round(g() * rhs),
        std::round(b() * rhs),
        a()
    );
}

const Color Color::BLACK = Color(0, 0, 0);
const Color Color::WHITE = Color(31, 31, 31);
const Color Color::RED = Color(31, 0, 0);
const Color Color::GREEN = Color(0, 31, 0);
const Color Color::BLUE = Color(0, 0, 31);
const Color Color::CYAN = Color(0, 31, 31);
const Color Color::MAGENTA = Color(31, 0, 31);
const Color Color::YELLOW = Color(31, 31, 0);
const Color Color::TRANSPARENT = Color(0);

#pragma endregion Color