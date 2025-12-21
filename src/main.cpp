#ifndef DEBUG
#include <windows.h>
#endif

#include "app.hpp"
#include "messages.hpp"
#include "image.hpp"

class MyApp :public pixanv::App
{
public:
    void load() override {
        gfx = pixanv::Image::load("../../assets/bkg1.img");
    }
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