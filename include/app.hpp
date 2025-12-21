#pragma once

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "graphics.hpp"
#include "utils.hpp"

namespace pixanv {
    enum class CursorMode {
        Visible,
        Hidden,
        Fixed
    };

    class App {
    public:
        App() : m_init_complete{ false }, m_running{ false }, m_window{ nullptr } {};
        ~App();
        void init(const std::string& title, int width, int height, int initial_scale = 1, bool use_integer_scaling = true);
        void run();

        void requestExit();

        void setIntegerScaling(bool use_integer_scaling);
        bool getIntegerScaling() const { return m_integer_scaling; }
        void setScale(int scale);

        void setCursorMode(CursorMode mode);
        CursorMode getCursorMode() const { return m_cursor_mode; };

        Image gfx;

        virtual void load() {}
        virtual void update() {}
        virtual void draw() {}
    private:
        App(const App&) = delete;
        App& operator=(const App&) = delete;

        bool m_running;
        bool m_init_complete;
        Size m_window_size;
        Size m_frame_size;
        Rect m_view;
        bool m_integer_scaling;
        CursorMode m_cursor_mode;

        GLFWwindow* m_window;
        GraphicsContext m_context;

        void resize(int new_width, int new_height);

        friend void resizeCallback(GLFWwindow* window, int width, int height);
    };

}