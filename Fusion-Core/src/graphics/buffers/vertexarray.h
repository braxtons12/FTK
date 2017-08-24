#ifndef _VERTEX_ARRAY
#define _VERTEX_ARRAY

#include "../src/graphics/buffers/buffer.h"

#include <vector>
#include <GL/glew.h>

namespace fusion { namespace core { namespace graphics {

    class VertexArray {

        private:
            GLuint m_ArrayID;
            std::vector<Buffer*> m_Buffers;
        public:
            VertexArray();
            ~VertexArray();
            void addBuffer(Buffer* buffer, GLuint index);

            inline void bind() const { glBindVertexArray(m_ArrayID); }
            inline void unbind() const { glBindVertexArray(0); }
    };

}}}

#endif
