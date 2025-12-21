#pragma once

#include <glad/gl.h>
#include "image.hpp"
#include "utils.hpp"

namespace pixanv {
    class GraphicsContext {
    public:
        void init(int width, int height);
        void resize(const Size& window_size, const FRect& scale_data);
        void free();
        void present(const Image& source);
    private:
        GLuint m_program;
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_frame_texture;
        GLint m_scale_uniform;
    };
}