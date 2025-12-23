#pragma once

#include "image.hpp"
#include "color.hpp"
#include "geometry.hpp"

namespace pixanv {

    class Canvas : public Image {
    public:

        void putPixel(int x, int y, Color color);
        void putPixelRaw(int x, int y, Color color);

        void blit(const Image& src, int x, int y, Color color = Color::WHITE);
        void blit(const Image& src, int x, int y, const Rect& src_rect, Color color = Color::WHITE);

        void fill(Color color);

    private:
        void resize(int width, int height);
        void blitGeneral(const Image& src, Point dst_pos, Point src_pos, Size size, Color color);

        friend class App;
    };

}