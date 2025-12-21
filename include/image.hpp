#pragma once

#include "utils.hpp"
#include <vector>
#include <string>

using std::vector;

namespace pixanv {

    class Image
    {
    public:
        Image(int width, int height) :m_width(width), m_height(height), m_data(width* height), m_has_transparency(true) {}
        bool isEmpty() const { return m_width == 0 || m_height == 0; }

        void pixel(int x, int y, Color color);
        Color pixel(int x, int y) const;
        void fill(Color color);

        int width() const { return m_width; };
        int height() const { return m_height; };
    protected:
        Image() :m_width(0), m_height(0), m_data(0), m_has_transparency(false) {};
        int m_width;
        int m_height;
        vector<Color> m_data;
        bool m_has_transparency;

        void pixelRaw(int x, int y, Color color);
        Color pixelRaw(int x, int y) const;

        static Image load(const std::string& filename);
    };
}