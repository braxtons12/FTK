/**
 * Datatype encapsulating an OpenGL Shader
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _SHADER
#define _SHADER

#include "utils/fileutils.h"
#include "mathLibs/mathLib.h"

#include <GL/glew.h>
#include <vector>
#include <iostream>


namespace ftk { namespace core { namespace graphics {

    class Shader {

        private:
            GLuint m_ShaderID;
            const char *m_VertPath, *m_FragPath;

            /**
             * Get the memory location of the requested uniform
             * 
             **/
            inline GLint getUniformLocation(const GLchar* name) { return glGetUniformLocation(m_ShaderID, name);}

        public:
            /**
             * Constructor
             * 
             **/
            Shader(const char* vertPath, const char* fragPath);

            /**
             * Destructor
             * 
             **/
            ~Shader();

            //setters for various uniforms of types float or int, and vectors (c-arrays) of floats or ints
            inline void setUniform1f(const GLchar* name, float value)
                { glUniform1f(getUniformLocation(name), value); }

            inline void setUniform1fv(const GLchar* name, float* value, int count)
                { glUniform1fv(getUniformLocation(name), count, value); }

            inline void setUniform1i(const GLchar* name, int value)
                { glUniform1i(getUniformLocation(name), value); }

            inline void setUniform1iv(const GLchar* name, int* value, int count)
                { glUniform1iv(getUniformLocation(name), count, value); }

            inline void setUniform2f(const GLchar* name, const math::vec2& vector)
                { glUniform2f(getUniformLocation(name), vector.m_x, vector.m_y); }

            inline void setUniform3f(const GLchar* name, const math::vec3& vector)
                { glUniform3f(getUniformLocation(name), vector.m_x, vector.m_y, vector.m_z); }

            inline void setUniform4f(const GLchar* name, const math::vec4& vector)
                { glUniform4f(getUniformLocation(name), vector.m_x, vector.m_y, vector.m_z, vector.m_w); }

            inline void setUniformMat4(const GLchar* name, const math::mat4& matrix)
                { glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements); }

            /**
             * Enable the Shader
             * 
             **/
            inline void enable() const { glUseProgram(m_ShaderID); }

            /**
             * Disable the Shader
             * 
             **/
            inline void disable() const { glUseProgram(0); }

            /**
             * Load the Shader from a file
             * 
             **/
            GLuint load();
    };



}}}

#endif
