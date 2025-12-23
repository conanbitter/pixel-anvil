#include "app.hpp"
#include "messages.hpp"
#include <stdexcept>
#include <format>
//#include <algorithm>

using namespace pixanv;

static void pixanv::resizeCallback(GLFWwindow* window, int width, int height) {
    App* app = (App*)glfwGetWindowUserPointer(window);
    app->resize(width, height);
}

static void pixanv::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_RELEASE) {
        App* app = (App*)glfwGetWindowUserPointer(window);
        app->keyAction(static_cast<Key>(key), action == GLFW_PRESS);
    }
}

static Size getScreenSize() {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) msg::throwGLFWError();

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) msg::throwGLFWError();

    return Size(mode->width, mode->height);
}

static GLFWwindow* initWindow(const std::string& title, int width, int height, int scale) {
    if (!glfwInit()) {
        msg::throwGLFWError();
    }

    Size screen_size = getScreenSize();

    glfwWindowHint(GLFW_POSITION_X, (screen_size.width - width * scale) / 2);
    glfwWindowHint(GLFW_POSITION_Y, (screen_size.height - height * scale) / 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width * scale, height * scale, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        pixanv::msg::throwGLFWError();
    }
    glfwSetWindowSizeLimits(window, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE); pixanv::msg::checkGLFWError();

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        throw std::runtime_error("Failed to initialize OpenGL context");
    }

#ifdef DEBUG
    msg::info(std::format("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version)));
#endif

    glfwSwapInterval(1); msg::checkGLFWError();

    return window;
}

void App::init(const std::string& title, int width, int height, int initial_scale, bool use_integer_scaling) {
    if (m_init_complete) return;
    m_integer_scaling = use_integer_scaling;
    m_window = initWindow(title, width, height, initial_scale);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetWindowSizeCallback(m_window, resizeCallback);
    glfwSetKeyCallback(m_window, keyCallback);
    m_frame_size.width = width;
    m_frame_size.height = height;

    m_context.init(width, height);

    resize(width * initial_scale, height * initial_scale);

    m_canvas.resize(width, height);

    load();
    m_init_complete = true;
}

void App::resize(int new_width, int new_height) {
    m_window_size.width = new_width;
    m_window_size.height = new_height;

    FRect shader_scale_data;

    if (m_window_size.width % m_frame_size.width == 0 && m_window_size.height % m_frame_size.height == 0) {
        shader_scale_data.x = 0.0;
        shader_scale_data.y = 0.0;
        shader_scale_data.width = 1.0f;
        shader_scale_data.height = 1.0f;

        m_view.x = 0;
        m_view.y = 0;
        m_view.width = new_width;
        m_view.height = new_height;
    } else if (m_integer_scaling) {
        int iscale = std::min(new_width / m_frame_size.width, new_height / m_frame_size.height);

        m_view.width = m_frame_size.width * iscale;
        m_view.height = m_frame_size.height * iscale;
        m_view.x = (new_width - m_view.width) / 2;
        m_view.y = (new_height - m_view.height) / 2;

        bool x_offset = (new_width - m_view.width * iscale) % 2 != 0;
        bool y_offset = (new_height - m_view.height) % 2 != 0;
        shader_scale_data.x = x_offset ? -1.0f / (float)new_width : 0.0f;
        shader_scale_data.y = y_offset ? -1.0f / (float)new_height : 0.0f;
        shader_scale_data.width = (float)m_view.width / (float)new_width;
        shader_scale_data.height = (float)m_view.height / (float)new_height;
    } else {
        float window_ar = (float)new_width / (float)new_height;
        float frame_ar = (float)m_frame_size.width / (float)m_frame_size.height;
        if (frame_ar < window_ar) {
            shader_scale_data.x = 0.0;
            shader_scale_data.y = 0.0;
            shader_scale_data.width = frame_ar / window_ar;
            shader_scale_data.height = 1.0f;

            m_view.width = (float)new_width * frame_ar;
            m_view.height = new_height;
            m_view.x = (new_width - m_view.width) / 2;
            m_view.y = 0;
        } else {
            shader_scale_data.x = 0.0;
            shader_scale_data.y = 0.0;
            shader_scale_data.width = 1.0f;
            shader_scale_data.height = window_ar / frame_ar;
            m_view.width = new_height;
            m_view.height = (float)new_height / frame_ar;
            m_view.x = 0;
            m_view.y = (new_height - m_view.height) / 2;
        }
    }

    m_context.resize(m_window_size, shader_scale_data);
}

void App::run() {
    if (!m_init_complete) return;
    m_running = true;

    while (!glfwWindowShouldClose(m_window) && m_running) {
        update();
        keyClear();

        draw();

        glClear(GL_COLOR_BUFFER_BIT);
        m_context.present(m_canvas);

        glfwSwapBuffers(m_window); msg::checkGLFWError();

        glfwPollEvents(); msg::checkGLFWError();
    }
}

App::~App() {
    glfwTerminate();
}

void App::requestExit() {
    m_running = false;
}

void App::setIntegerScaling(bool use_integer_scaling) {
    m_integer_scaling = use_integer_scaling;
    if (m_init_complete) resize(m_window_size.width, m_window_size.height);
}

void App::setScale(int scale) {
    m_window_size.width = m_frame_size.width * scale;
    m_window_size.height = m_frame_size.height * scale;


    if (glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED)) {
        glfwRestoreWindow(m_window);
    }

    glfwSetWindowSize(m_window, m_window_size.width, m_window_size.height);

    Size screen_size = getScreenSize();
    glfwSetWindowPos(
        m_window,
        (screen_size.width - m_window_size.width) / 2,
        (screen_size.height - m_window_size.height) / 2
    );
}

void App::setCursorMode(CursorMode mode) {
    m_cursor_mode = mode;
    switch (mode)
    {
    case CursorMode::Visible:
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        break;

    case CursorMode::Hidden:
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        break;

    case CursorMode::Fixed:
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        break;
    }
}

void App::keyAction(Key key, bool down) {
    if (down) {
        if (!m_keys_down.contains(key)) {
            m_keys_pressed.insert(key);
            m_keys_down.insert(key);
        }
    } else {
        if (m_keys_down.contains(key)) {
            m_keys_released.insert(key);
            m_keys_down.erase(key);
        }
    }
}

void App::keyClear() {
    m_keys_pressed.clear();
    m_keys_released.clear();
}