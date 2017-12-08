/**
 * Basic Index Buffer class.
 * Used to Encapsulate openGL IBOs into a local datatype
 * Implementation
 * 
 * Version: 0.0.1
 * 0 2017 Braxton Salyer and Logan Tibbetts
 * 
 **/

#include "indexbuffer.h"

namespace fusion { namespace core { namespace graphics {

    IndexBuffer::IndexBuffer(GLuint* data, GLsizei count) 
        : m_Count(count)
    {

        //create the buffer with given m_BufferID
        glGenBuffers(1, &m_BufferID);
        //bind the buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
        //give it data
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
        //unbind the buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
    }

    IndexBuffer::~IndexBuffer() {
        
        //delete the buffer
        glDeleteBuffers(1, &m_BufferID);
    }
    
}}}
