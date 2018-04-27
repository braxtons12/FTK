/**
 * Basic Generic Buffer class.
 * Used to Encapsulate openGL buffers into a local datatype
 * Implementation
 * 
 * Version: 0.0.1
 * C 2018 Braxton Salyer
 * 
 **/

 #include "buffer.h"

namespace ftk { namespace core { namespace graphics {

    Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount) 
        : m_ComponentCount(componentCount)
    {
        
        //generate a buffer with the given m_BufferID
        glGenBuffers(1, &m_BufferID);
        //bind the buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
        //give it data
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
        //unbind the buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
    }

    Buffer::~Buffer() {
        
        //delete the buffer
        glDeleteBuffers(1, &m_BufferID);
    }
    
}}}
