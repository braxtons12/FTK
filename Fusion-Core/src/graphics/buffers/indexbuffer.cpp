#include "indexbuffer.h"

namespace fusion { namespace core { namespace graphics {

    IndexBuffer::IndexBuffer(GLushort* data, GLsizei count) 
        : m_Count(count)
    {

        glGenBuffers(1, &m_BufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
    }
    
}}}