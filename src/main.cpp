#ifndef DEBUG
#include <windows.h>
#endif

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <format>
#include "messages.hpp"

const int frameWidth = 640;
const int frameHeight = 480;

void run() {
    GLFWwindow* window;

    if (!glfwInit()) {
        pixanv::msg::throwGLFWError();
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) {
        glfwTerminate();
        pixanv::msg::throwGLFWError();
    }

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) {
        glfwTerminate();
        pixanv::msg::throwGLFWError();
    }

    glfwWindowHint(GLFW_POSITION_X, (mode->width - frameWidth) / 2);
    glfwWindowHint(GLFW_POSITION_Y, (mode->height - frameHeight) / 2);

    window = glfwCreateWindow(frameWidth, frameHeight, "Pixel Anvil", NULL, NULL);
    if (!window) {
        glfwTerminate();
        pixanv::msg::throwGLFWError();
    }
    glfwSetWindowSizeLimits(window, frameWidth, frameHeight, GLFW_DONT_CARE, GLFW_DONT_CARE); pixanv::msg::checkGLFWError();

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        throw std::runtime_error("Failed to initialize OpenGL context");
    }

#ifdef DEBUG
    pixanv::msg::info(std::format("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version)));
#endif

    glClearColor(0.09, 0.14, 0.16, 1.0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window); pixanv::msg::checkGLFWError();

        glfwPollEvents(); pixanv::msg::checkGLFWError();
    }

    glfwTerminate();
}

#ifndef DEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main(void) {
#endif
    try {
        run();
    }
    catch (const std::exception& e) {
        pixanv::msg::error(e.what());
    }
    catch (...) {
        pixanv::msg::error("Unknown error");
    }
    return 0;
}