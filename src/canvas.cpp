#include "canvas.hpp"

using namespace pixanv;

void pixanv::Canvas::putPixel(int x, int y, Color color) {
    if (x<0 || x>m_width - 1 || y<0 || y>m_height - 1) return;
    m_data[x + y * m_width] = color;
}

Color pixanv::Canvas::getPixel(int x, int y) const {
    x %= m_width;
    if (x < 0) x += m_width;
    y %= m_height;
    if (y < 0)y += m_height;
    return m_data[x + y * m_width];
}

void Canvas::putPixelRaw(int x, int y, Color color) {
    m_data[x + y * m_width] = color;
}

Color Canvas::getPixelRaw(int x, int y) const {
    return m_data[x + y * m_width];
}

void Canvas::fill(Color color) {
    std::fill(m_data.begin(), m_data.end(), color);
}

void Canvas::resize(int width, int height) {
    m_width = width;
    m_height = height;
    m_data.resize(width * height);
}
