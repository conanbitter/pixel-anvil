#ifndef DEBUG
#include <windows.h>
#endif

#include "app.hpp"
#include "messages.hpp"
#include "image.hpp"
#include "utils.hpp"

class MyApp :public pixanv::App
{
public:
    MyApp() {}

    void load() override {
        sprite = pixanv::Image::load("../../assets/other/transp1.img");
        gfx.fill(pixanv::Color(15, 20, 15));
        gfx.putPixel(1, 1, pixanv::Color::WHITE);
        for (int i = 0;i < 360;i++) {
            gfx.putPixel(i, 360 - i - 1, pixanv::Color(10, 5, 5));
        }
    }
private:
    pixanv::Image sprite;
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