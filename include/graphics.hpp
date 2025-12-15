#pragma once

#include <glad/gl.h>

namespace pixanv {
    class GraphicsContext {
    public:
        void init(int width, int height);
        void resize(int outer_width, int outer_height, int inner_width, int inner_height);
        void free();
        void present();
    private:
        GLuint m_program;
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_frame_texture;
        GLint m_scale_uniform;
    };
}