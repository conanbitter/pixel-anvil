#include "canvas.hpp"

using namespace pixanv;

void pixanv::Canvas::putPixel(int x, int y, Color color) {
    if (x<0 || x>m_width - 1 || y<0 || y>m_height - 1) return;
    m_data[x + y * m_width] = color;
}

void Canvas::putPixelRaw(int x, int y, Color color) {
    m_data[x + y * m_width] = color;
}

void Canvas::fill(Color color) {
    std::fill(m_data.begin(), m_data.end(), color);
}

void Canvas::resize(int width, int height) {
    m_width = width;
    m_height = height;
    m_data.resize(width * height);
}

void Canvas::blit(const Image& src, int x, int y, Color color) {
    blitGeneral(src, Point(x, y), Point(0, 0), Size(src.m_width, src.m_height), color);
}

void Canvas::blit(const Image& src, int x, int y, const Rect& src_rect, Color color) {
    blitGeneral(src, Point(x, y), src_rect.pos(), src_rect.size(), color);
}

void Canvas::blitGeneral(const Image& src, Point dst_pos, Point src_pos, Size size, Color color) {
    // Remove overflow
    int left_overflow = -dst_pos.x;
    if (left_overflow > 0) {
        src_pos.x += left_overflow;
        size.width -= left_overflow;
        dst_pos.x = 0;
    }

    int right_overflow = (dst_pos.x + size.width) - m_width;
    if (right_overflow > 0) {
        size.width -= right_overflow;
    }

    if (size.width <= 0) return;

    int top_overflow = -dst_pos.y;
    if (top_overflow > 0) {
        src_pos.y += top_overflow;
        size.height -= top_overflow;
        dst_pos.y = 0;
    }

    int bottom_overflow = (dst_pos.y + size.height) - m_height;
    if (bottom_overflow > 0) {
        size.height -= bottom_overflow;
    }

    if (size.height <= 0) return;

    if (src.m_has_transparency) {
        if (color == Color::WHITE) {
            for (int y = 0; y < size.height; y++) {
                for (int x = 0;x < size.width;x++) {
                    Color src_color = src.getPixelRaw(src_pos.x + x, src_pos.y + y);
                    if (src_color != Color::TRANSPARENT) {
                        putPixelRaw(dst_pos.x + x, dst_pos.y + y, src_color);
                    }
                }
            }
        } else {
            for (int y = 0; y < size.height; y++) {
                for (int x = 0;x < size.width;x++) {
                    Color src_color = src.getPixelRaw(src_pos.x + x, src_pos.y + y);
                    if (src_color != Color::TRANSPARENT) {
                        putPixelRaw(dst_pos.x + x, dst_pos.y + y, src_color * color);
                    }
                }
            }
        }
    } else {
        if (color == Color::WHITE) {
            for (int y = 0; y < size.height; y++) {
                auto src_start = src.m_data.begin() + src_pos.x + (src_pos.y + y) * src.m_width;
                auto src_end = src_start + size.width;
                auto dst_start = m_data.begin() + dst_pos.x + (dst_pos.y + y) * m_width;
                std::copy(src_start, src_end, dst_start);
            }
        } else {
            for (int y = 0; y < size.height; y++) {
                for (int x = 0;x < size.width;x++) {
                    putPixelRaw(
                        dst_pos.x + x,
                        dst_pos.y + y,
                        src.getPixelRaw(
                            src_pos.x + x,
                            src_pos.y + y) * color);
                }
            }
        }
    }
}
