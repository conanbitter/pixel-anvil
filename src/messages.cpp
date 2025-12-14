#include "messages.hpp"

#ifndef DEBUG

#include "tinyfiledialogs.h"

#else

#include <chrono>
#include <format>
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