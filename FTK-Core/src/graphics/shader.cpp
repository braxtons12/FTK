/**
 * Datatype encapsulating an OpenGL Shader
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "shader.h"

namespace ftk { namespace core { namespace graphics {

    /**
     * Constructor
     * 
     **/
    Shader::Shader(const char* vertPath, const char* fragPath)
       : m_VertPath(vertPath), m_FragPath(fragPath)
    {
        m_ShaderID = load();
    }

    /**
     * Destructor
     * 
     **/
    Shader::~Shader() {

        glDeleteProgram(m_ShaderID);
    }

    /**
     * Load the Shader from a file
     * 
     **/
    GLuint Shader::load() {

        //create the Shader program and the individual shaders in OpenGL
        GLuint program = glCreateProgram();
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

        //read in the shader files
        std::string vertSourceString = utils::FileUtils::read_file(m_VertPath);
        std::string fragSourceString = utils::FileUtils::read_file(m_FragPath);

        const char* vertSource = vertSourceString.c_str();
        const char* fragSource = fragSourceString.c_str();

        //have OpenGL compile the vertex shader
        glShaderSource(vertex, 1, &vertSource, NULL);
        glCompileShader(vertex);

        //if there is an error compiling the shader, tell us
        GLint result;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {

            GLint length;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(vertex, length, &length, &error[0]);
            std::cout << "Failed to complile vertex shader!" << &error[0] << std::endl;
            glDeleteShader(vertex);
            return 0;
        }

        //have OpenGL compile the fragment shader
        glShaderSource(fragment, 1, &fragSource, NULL);
        glCompileShader(fragment);

        //if there is an error compiling the shader, tell us
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {

            GLint length;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(fragment, length, &length, &error[0]);
            std::cout << "Failed to complile fragment shader!" << &error[0] << std::endl;
            glDeleteShader(fragment);
            return 0;
        }

        //attach the shaders to the shader program
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);

        //link and validate the program in OpenGL
        glLinkProgram(program);

        glValidateProgram(program);

        //delete the now unnecessary shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        //return the program ID
        return program;
    }

}}}
