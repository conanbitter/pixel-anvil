#pragma once

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "graphics.hpp"

namespace pixanv {
    enum class CursorMode {
        Visible,
        Hidden,
        Fixed
    };

    class App {
    public:
        static App& getInstance();
        ~App();
        void init(const std::string& title, int width, int height, int initial_scale = 1, bool use_integer_scaling = true);
        void run();

        void requestExit();

        void setIntegerScaling(bool use_integer_scaling);
        bool getIntegerScaling() const { return m_integer_scaling; }
        void setScale(int scale);

        void setCursorMode(CursorMode mode);
        CursorMode getCursorMode() const { return m_cursor_mode; };
    private:
        App() : m_init_complete{ false }, m_running{ false }, m_frame_width{ 0 }, m_frame_height{ 0 }, m_window{ nullptr } {};
        App(const App&) = delete;
        App& operator=(const App&) = delete;

        bool m_running;
        bool m_init_complete;
        int m_frame_width;
        int m_frame_height;
        int m_window_width;
        int m_window_height;
        bool m_integer_scaling;
        CursorMode m_cursor_mode;

        GLFWwindow* m_window;
        GraphicsContext m_context;

        void resize(int new_width, int new_height);

        friend void resizeCallback(GLFWwindow* window, int width, int height);
    };

}