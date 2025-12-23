#pragma once

#include <string>
#include <unordered_set>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "graphics.hpp"
#include "canvas.hpp"
#include "keys.hpp"

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

        bool isKeyDown(Key key) const { return m_keys_down.contains(key); }
        bool isKeyPressed(Key key) const { return m_keys_pressed.contains(key); }
        bool isKeyReleased(Key key) const { return m_keys_released.contains(key); }

        Color getPixel(int x, int y) const { m_canvas.getPixel(x, y); }
        void putPixel(int x, int y, Color color) { m_canvas.putPixel(x, y, color); };
        void blit(const Image& src, int x, int y, Color color = Color::WHITE) { m_canvas.blit(src, x, y, color); }
        void blit(const Image& src, int x, int y, const Rect& src_rect, Color color = Color::WHITE) { m_canvas.blit(src, x, y, src_rect, color); }
        void fill(Color color) { m_canvas.fill(color); }

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
        Canvas m_canvas;

        std::unordered_set<Key> m_keys_down;
        std::unordered_set<Key> m_keys_pressed;
        std::unordered_set<Key> m_keys_released;

        void resize(int new_width, int new_height);
        void keyAction(Key key, bool down);
        void keyClear();

        friend void resizeCallback(GLFWwindow* window, int width, int height);
        friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    };

}