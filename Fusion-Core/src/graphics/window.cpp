#include "window.h"

namespace fusion { namespace core { namespace graphics {
	

	WindowUpdateSignal* Window::m_Signal = new WindowUpdateSignal();
	
    bool Window::init() {
		
        
        if(!glfwInit()) {
            std::cout << "Failed to initialize GLFW!" << std::endl;
            return false;
        }
        m_Window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);
        if (!m_Window) {
            std::cout << "Failed to create GLFW window!" << std::endl;
            return false;
        }
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetWindowSizeCallback(m_Window, WindowResizeCallBack);
        glfwSetKeyCallback(m_Window, keyCallback);
        glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
        glfwSetCursorPosCallback(m_Window, mousePositionCallback);
		glfwSwapInterval(0.0f);

		glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK) {
            std::cout << "Could not initialize GLEW!" << std::endl;
            return false;
        }

        return true;
    }

    Window::Window(const char *name, int width, int height) {

        m_name = name;
        m_width = width;
        m_height = height;
        if (!init()) glfwTerminate();

    }

    Window::~Window() {

    }

    void Window::clear() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::update() {

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL Error: " << error << std::endl;
        }
        glfwPollEvents();
        glfwSwapBuffers(m_Window);

    }

    bool Window::closed() const {
        return glfwWindowShouldClose(m_Window);
    }

}}}
