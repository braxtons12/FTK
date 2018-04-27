/**
 * Base Window class
 * Maintains an OpenGL context through GLFW and glew
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 **/

#include "nativewindow.h"

namespace ftk { namespace core { namespace graphics {
	
	Signal<NativeWindow, ui::FtkWindow, std::array<int, 2>, void, std::array<int, 2>>* NativeWindow::m_Signal = 
	new Signal<NativeWindow, ui::FtkWindow, std::array<int, 2>, void, std::array<int, 2>>();
	
    /**
     * Initialize the Window
     * 
     **/
    bool NativeWindow::init() {
		
        m_XScaleFactor = 1.0;
        m_YScaleFactor = 1.0;

        //start glfw and make sure glfw started properly
        if(!glfwInit()) {
            std::cout << "Failed to initialize GLFW!" << std::endl;
            return false;
        }

        //create the window
        m_Window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);

        //make sure glfw created our window
        if (!m_Window) {
            std::cout << "Failed to create GLFW window!" << std::endl;
            return false;
        }

        //make this the current OpenGL context and set our callbacks
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetWindowSizeCallback(m_Window, WindowResizeCallBack);
        glfwSetKeyCallback(m_Window, keyCallback);
        glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
        glfwSetCursorPosCallback(m_Window, mousePositionCallback);
		glfwSwapInterval(1.0f);

		glewExperimental = GL_TRUE;

        //start glew and make sure glew started properly
        if(glewInit() != GLEW_OK) {
            std::cout << "Could not initialize GLEW!" << std::endl;
            return false;
        }

        //if everything went well, return true
        return true;
    }

    /**
     * Constructor
     * 
     **/
    NativeWindow::NativeWindow(const char *name, int width, int height) {

        m_name = name;
        m_width = width;
        m_height = height;
        if (!init()) glfwTerminate();

    }

    /**
     * Destructor
     * 
     **/
    NativeWindow::~NativeWindow() {

    }

    /**
     * Update the Window State
     * 
     **/
    void NativeWindow::update() {

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL Error: " << error << std::endl;
        }
        glfwPollEvents();
        glfwSwapBuffers(m_Window);

    }

    /**
     * Convert mouse coordinates to framebuffer coordinates
     * 
     **/
    void NativeWindow::convertCoords(double& x, double& y) {

        x /= m_XScaleFactor;
        y /= m_YScaleFactor;
    }

}}}
