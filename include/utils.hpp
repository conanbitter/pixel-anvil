#pragma once

namespace pixanv {
    struct Vec2D
    {
        int x;
        int y;

        Vec2D(int x, int y) :x{ x }, y{ y } {}
        Vec2D() :x{ 0 }, y{ 0 } {}
    };

    typedef Vec2D Point;

    struct FVec2D
    {
        float x;
        float y;

        FVec2D(float x, float y) :x{ x }, y{ y } {}
        FVec2D() :x{ 0.0f }, y{ 0.0f } {}
    };

    typedef FVec2D FPoint;

    struct Size
    {
        int width;
        int height;

        Size(int width, int height) :width{ width }, height{ height } {}
        Size() :width{ 0 }, height{ 0 } {}
    };

    struct FSize
    {
        float width;
        float height;

        FSize(float width, float height) :width{ width }, height{ height } {}
        FSize() :width{ 0.0f }, height{ 0.0f } {}
    };


    struct Rect
    {
        int x;
        int y;
        int width;
        int height;

        Rect(int x, int y, int width, int height) :x{ x }, y{ y }, width{ width }, height{ height } {}
        Rect(const Point& pos, const Size& size) :x{ pos.x }, y{ pos.y }, width{ size.width }, height{ size.height } {}
        Rect() :x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 } {}

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
        FRect() :x{ 0.0f }, y{ 0.0f }, width{ 0.0f }, height{ 0.0f } {}

        FPoint pos() const { return FPoint(x, y); }
        FSize size() const { return FSize(width, height); }
    };

#pragma pack(push, 1) 
    class Color {
    public:
        Color() :value(0) {}
        Color(uint16_t raw) :value(raw) {}
        Color(int r, int g, int b, int a);
        int r() const;
        int g() const;
        int b() const;
        int a() const;

        static const Color BLACK;
        static const Color WHITE;
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
        static const Color CYAN;
        static const Color MAGENTA;
        static const Color YELLOW;

        bool operator==(const Color& rhs)const { return value == rhs.value; }
        Color operator*(const Color& rhs)const;
        Color operator*(float rhs)const;
    private:
        uint16_t value;
    };
#pragma pack(pop)

}