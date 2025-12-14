cmake_minimum_required(VERSION 3.16)

project(pixanv VERSION 0.1 LANGUAGES C CXX)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

add_executable(pixanv 
    src/main.cpp
    external/glad/src/gl.c
)

target_include_directories(pixanv
    PRIVATE
        external/glfw/include
        external/glad/include
)

target_link_directories(pixanv
    PRIVATE
        external/glfw/lib
)

target_link_libraries(pixanv
    glfw3
)