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
    }

    void load() override {
        sprite = pixanv::Image::load("../../assets/other/transp1.img");
        opaq = pixanv::Image::load("../../assets/pic1.img");
    }

    void draw() override {
        gfx.fill(pixanv::Color(15, 20, 15));
        gfx.putPixel(1, 1, pixanv::Color::WHITE);
        for (int i = 0;i < 360;i++) {
            gfx.putPixel(i, 360 - i - 1, pixanv::Color(10, 5, 5));
        }
        gfx.blit(opaq, 10, 10, pixanv::Color(28, 31, 28));
        gfx.blit(sprite, x, y, pixanv::Color(20, 20, 20));
    }
private:
    pixanv::Image sprite;
    pixanv::Image opaq;
    int x = 300;
    int y = 100;
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