#include "image.hpp"
#include "resources.hpp"

using namespace pixanv;

void Image::pixel(int x, int y, Color color) {
    if (x<0 || x>m_width - 1 || y<0 || y>m_height - 1) return;
    m_data[x + y * m_width] = color;
}

Color Image::pixel(int x, int y) const {
    x %= m_width;
    if (x < 0) x += m_width;
    y %= m_height;
    if (y < 0) y += m_height;
    return m_data[x + y * m_width];
}

void Image::pixelRaw(int x, int y, Color color) {
    m_data[x + y * m_width] = color;
}

Color Image::pixelRaw(int x, int y) const {
    return m_data[x + y * m_width];
}

void Image::fill(Color color) {
    std::fill(m_data.begin(), m_data.end(), color);
}

Image pixanv::Image::load(const std::string& filename)
{
    ResHandle handle(filename);
    int width = handle.readU32();
    int height = handle.readU32();

    Image image(width, height);

    int length = width * height;
    int index = 0;

    while (index < length) {
        uint8_t data1 = handle.readU8();
        if (data1 < 128) {
            for (int i = 0;i <= data1;i++) {
                image.m_data[index] = Color::TRANSPARENT;
                index++;
            }
        } else {
            uint16_t data2 = ((uint16_t)data1) << 8 | handle.readU8();
            image.m_data[index] = Color(data2);
            index++;
        }
    }

    return image;
}
