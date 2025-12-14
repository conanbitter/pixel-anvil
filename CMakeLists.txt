cmake_minimum_required(VERSION 3.16)

project(pixanv VERSION 0.1 LANGUAGES C CXX)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

set(SRC_FILES
    src/main.cpp
    external/glad/src/gl.c
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    # No console
    add_executable(pixanv WIN32 ${SRC_FILES})
    # Static linking
    set_property(TARGET pixanv PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
else()
    # With console
    add_executable(pixanv ${SRC_FILES})
    # DEBUG definition
    target_compile_definitions(pixanv PRIVATE DEBUG)
endif()

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
    glfw3_mt
)