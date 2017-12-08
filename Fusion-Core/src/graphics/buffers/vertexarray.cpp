/**
 * Basic Vertex Array class.
 * Used to Encapsulate openGL VAOs into a local datatype
 * Implementation
 * 
 * Version: 0.0.1
 * 0 2017 Braxton Salyer and Logan Tibbetts
 * 
 **/

#include "vertexarray.h"

namespace fusion { namespace core { namespace graphics {

    VertexArray::VertexArray() {

        //create the vertex array with the given ID in openGL
        glGenVertexArrays(1, &m_ArrayID);
    }

    VertexArray::~VertexArray() {
        
        //delete every buffer in the array
        for (int i = 0; i < m_Buffers.size(); ++i) {
            delete m_Buffers[i];
        }

        //delete the vertex array
        glDeleteVertexArrays(1, &m_ArrayID);
    }

    void VertexArray::addBuffer(Buffer* buffer, GLuint index) {

        //bind the vertex array and buffer in openGL
        bind();
        buffer->bind();
        
        //enable the vertex array and add the buffer to it
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

        //unbind the buffer and vertex array
        buffer->unbind();
        unbind();
    }

}}}
