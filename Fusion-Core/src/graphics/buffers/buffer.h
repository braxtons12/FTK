/**
 * Basic Generic Buffer class.
 * Used to Encapsulate openGL buffers into a local datatype
 * Header
 * 
 * Version: 0.0.1
 * 0 2017 Braxton Salyer and Logan Tibbetts
 * 
 **/

#ifndef _BUFFER
#define _BUFFER

#include <GL/glew.h>

namespace fusion { namespace core { namespace graphics {

    class Buffer {

        private:
            GLuint m_BufferID;
            GLuint m_ComponentCount;

        public:
            
            /*
             * Constructor
            */ 
            Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
            
            /*
             * Destructor
             */
            ~Buffer();
            
            /*
             *  Binds the buffer in openGL
             */ 
            inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_BufferID); }
            
            /*
             * Unbinds the buffer
             */
            inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
            
            /*
             * Returns the total number of components contained in the buffer
             */ 
            inline GLuint getComponentCount() const { return m_ComponentCount; }

    };
}}}

#endif
