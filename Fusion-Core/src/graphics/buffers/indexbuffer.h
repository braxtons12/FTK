#ifndef _INDEX_BUFFER
#define _INDEX_BUFFER

#include <GL/glew.h>

namespace fusion { namespace core { namespace graphics {

    class IndexBuffer {

        private:
            GLuint m_BufferID;
            GLuint m_Count;

        public:
            IndexBuffer(GLushort* data, GLsizei count);

            inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID); }
            inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

            inline GLuint getCount() const { return m_Count; }

    };
}}}

#endif