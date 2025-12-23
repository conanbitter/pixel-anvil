#ifndef DEBUG
#include <windows.h>
#endif

#include "app.hpp"
#include "messages.hpp"
#include "image.hpp"
#include "color.hpp"
#include "keys.hpp"

class MyApp :public pixanv::App
{
public:
    MyApp() {}

    void load() override {
        sprite = pixanv::Image::load("../../assets/other/transp1.img");
        opaq = pixanv::Image::load("../../assets/pic1.img");
    }

    void update() override {
        if (isKeyDown(pixanv::Key::Right)) {
            x++;
        }
        if (isKeyDown(pixanv::Key::Left)) {
            x--;
        }
        if (isKeyDown(pixanv::Key::Down)) {
            y++;
        }
        if (isKeyDown(pixanv::Key::Up)) {
            y--;
        }

        col_mul += col_mul_d;
        if (col_mul <= 0.0 || col_mul >= 33.0) {
            col_mul_d = -col_mul_d;
        }
    }

    void draw() override {
        fill(pixanv::Color(15, 20, 15));
        putPixel(1, 1, pixanv::Color::WHITE);
        for (int i = 0;i < 360;i++) {
            putPixel(i, 360 - i - 1, pixanv::Color(10, 5, 5));
        }
        blit(opaq, 10, 10, pixanv::Color(28, 31, 28));
        blit(sprite, x, y, pixanv::Color(col_mul, col_mul, col_mul));
    }
private:
    pixanv::Image sprite;
    pixanv::Image opaq;
    int x = 300;
    int y = 100;
    float col_mul = 31.0;
    float col_mul_d = -0.2;
};


#ifndef DEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main(void) {
#endif
    try {
        MyApp app;
        app.init("Pixel Anvil", 640, 360, 1, true);
        app.run();
    }
    catch (const std::exception& e) {
        pixanv::msg::error(e.what());
    }
    catch (...) {
        pixanv::msg::error("Unknown error");
    }
    return 0;
}