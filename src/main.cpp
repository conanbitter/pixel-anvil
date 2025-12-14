#ifndef DEBUG
#include <windows.h>
#endif

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <format>
#include "messages.hpp"

#ifndef DEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main(void) {
#endif
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_POSITION_X, (mode->width - 640) / 2);
    glfwWindowHint(GLFW_POSITION_Y, (mode->height - 480) / 2);

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        pixanv::msg::error("Failed to load GLFW");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        pixanv::msg::error("Failed to initialize OpenGL context");
        return -1;
    }

#ifdef DEBUG
    pixanv::msg::info(std::format("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version)));
#endif

    glClearColor(0.09, 0.14, 0.16, 1.0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}