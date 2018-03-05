/**
 * Basic Index Buffer class.
 * Used to Encapsulate openGL IBOs into a local datatype
 * Header
 * 
 * Version: 0.0.1
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _INDEX_BUFFER
#define _INDEX_BUFFER

#include <GL/glew.h>

namespace fusion { namespace core { namespace graphics {

    class IndexBuffer {

        private:
            GLuint m_BufferID;
            GLuint m_Count;

        public:
            /*
             * Constructor
             */
            IndexBuffer(GLuint* data, GLsizei count);
            
            /*
             * Destructor
             */
            ~IndexBuffer();

            /*
             * Binds the buffer in openGL
             */ 
            inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID); }
            
            /*
             * Unbinds the buffer
             */
            inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
            
            /*
             * Returns the number of indices
             */
            inline GLuint getCount() const { return m_Count; }

    };
}}}

#endif
