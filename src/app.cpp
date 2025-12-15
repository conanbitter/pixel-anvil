#include "app.hpp"
#include "messages.hpp"
#include <stdexcept>
#include <format>

using namespace pixanv;

static void pixanv::resizeCallback(GLFWwindow* window, int width, int height) {
    App* app = (App*)glfwGetWindowUserPointer(window);
    app->resize(width, height);
}

static void getScreenSize(int& width, int& height) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) msg::throwGLFWError();

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) msg::throwGLFWError();

    width = mode->width;
    height = mode->height;
}

static GLFWwindow* initWindow(const std::string& title, int width, int height, int scale) {
    if (!glfwInit()) {
        msg::throwGLFWError();
    }

    int screen_width;
    int screen_height;

    getScreenSize(screen_width, screen_height);

    glfwWindowHint(GLFW_POSITION_X, (screen_width - width * scale) / 2);
    glfwWindowHint(GLFW_POSITION_Y, (screen_height - height * scale) / 2);
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

App& App::getInstance() {
    static App theInstance;
    return theInstance;
}

void App::init(const std::string& title, int width, int height, int initial_scale, bool use_integer_scaling) {
    if (m_init_complete) return;
    m_integer_scaling = use_integer_scaling;
    m_window = initWindow(title, width, height, initial_scale);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetWindowSizeCallback(m_window, resizeCallback);
    m_frame_width = width;
    m_frame_height = height;

    m_context.init(width, height);

    resize(width * initial_scale, height * initial_scale);
    m_init_complete = true;
}

void App::resize(int new_width, int new_height) {
    m_window_width = new_width;
    m_window_height = new_height;
    m_context.resize(new_width, new_height, 0, 0);
}

void App::run() {
    if (!m_init_complete) return;
    m_running = true;

    while (!glfwWindowShouldClose(m_window) && m_running) {
        glClear(GL_COLOR_BUFFER_BIT);
        m_context.present();

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
    if (m_init_complete) resize(m_window_width, m_window_height);
}

void App::setScale(int scale) {
    m_window_width = m_frame_width * scale;
    m_window_height = m_frame_height * scale;


    if (glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED)) {
        glfwRestoreWindow(m_window);
    }

    glfwSetWindowSize(m_window, m_window_width, m_window_height);

    int screen_width, screen_height;
    getScreenSize(screen_width, screen_height);
    glfwSetWindowPos(
        m_window,
        (screen_width - m_window_width) / 2,
        (screen_height - m_window_height) / 2
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

