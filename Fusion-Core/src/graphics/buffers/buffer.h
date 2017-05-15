#ifndef _BUFFER
#define _BUFFER

#include <GL/glew.h>

namespace fusion { namespace core { namespace graphics {

    class Buffer {

        private:
            GLuint m_BufferID;
            GLuint m_ComponentCount;

        public:
            Buffer(GLfloat* data, GLsizei count, GLuint componentCount);

            ~Buffer();

            inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_BufferID); }
            inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

            inline GLuint getComponentCount() const { return m_ComponentCount; }

    };
}}}

#endif