#pragma once

namespace pixanv {
    struct Vec2D
    {
        int x;
        int y;

        Vec2D(int x, int y) :x{ x }, y{ y } {}
    };

    typedef Vec2D Point;

    struct FVec2D
    {
        float x;
        float y;

        FVec2D(float x, float y) :x{ x }, y{ y } {}
    };

    typedef FVec2D FPoint;

    struct Size
    {
        int width;
        int height;

        Size(int width, int height) :width{ width }, height{ height } {}
    };

    struct FSize
    {
        float width;
        float height;

        FSize(float width, float height) :width{ width }, height{ height } {}
    };


    struct Rect
    {
        int x;
        int y;
        int width;
        int height;

        Rect(int x, int y, int width, int height) :x{ x }, y{ y }, width{ width }, height{ height } {}
        Rect(const Point& pos, const Size& size) :x{ pos.x }, y{ pos.y }, width{ size.width }, height{ size.height } {}

        Point pos() const { return Point(x, y); }
        Size size() const { return Size(width, height); }
        bool contains(const Point& point);
    };

    struct FRect
    {
        float x;
        float y;
        float width;
        float height;

        FRect(float x, float y, float width, float height) :x{ x }, y{ y }, width{ width }, height{ height } {}
        FRect(const FPoint& pos, const FSize& size) :x{ pos.x }, y{ pos.y }, width{ size.width }, height{ size.height } {}

        FPoint pos() const { return FPoint(x, y); }
        FSize size() const { return FSize(width, height); }
    };

}