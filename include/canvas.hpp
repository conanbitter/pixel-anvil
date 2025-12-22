#pragma once

#include "image.hpp"

namespace pixanv {

    class Canvas : public Image {
    public:

        void putPixel(int x, int y, Color color);
        Color getPixel(int x, int y) const;
        void putPixelRaw(int x, int y, Color color);
        Color getPixelRaw(int x, int y) const;

        void fill(Color color);

    private:
        void resize(int width, int height);

        friend class App;
    };

}