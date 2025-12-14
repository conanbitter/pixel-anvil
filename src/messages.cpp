#include "messages.hpp"
#include <GLFW/glfw3.h>
#include <format>

#ifndef DEBUG

#include "tinyfiledialogs.h"

#else

#include <chrono>
#include <iostream>

#endif

void pixanv::msg::error(const std::string& message) {
#ifndef DEBUG
    tinyfd_messageBox("Error", message.c_str(), "ok", "error", 1);
#else
    const auto now = std::chrono::system_clock::now();
    std::cout << "[" << std::format("{:%d-%m-%Y %H:%M:%OS}", now) << "] Error: " << message << std::endl;
#endif
}

void pixanv::msg::info(const std::string& message) {
#ifdef DEBUG
    const auto now = std::chrono::system_clock::now();
    std::cout << "[" << std::format("{:%d-%m-%Y %H:%M:%OS}", now) << "] Info: " << message << std::endl;
#endif
}

void pixanv::msg::throwGLFWError() {
    const char* description;
    int code = glfwGetError(&description);

    if (code != GLFW_NO_ERROR) {
        if (description) {
            throw std::runtime_error(std::format("{} (GLFW error code {})", description, code));
        } else {
            throw std::runtime_error(std::format("GLFW error code {}", code));
        }
    } else {
        throw std::runtime_error("Unknown GLFW error");
    }
}

void pixanv::msg::checkGLFWError() {
    const char* description;
    int code = glfwGetError(&description);

    if (code != GLFW_NO_ERROR) {
        if (description) {
            throw std::runtime_error(std::format("{} (GLFW error code {})", description, code));
        } else {
            throw std::runtime_error(std::format("GLFW error code {}", code));
        }
    }
}