/**
 * Base Window class
 * Maintains an OpenGL context through GLFW and glew
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 **/

#ifndef _WINDOW
#define _WINDOW

#include "input/input.h"
#include "signals/windowupdatesignal.h"


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace fusion { namespace core { namespace graphics {

    class Window {

        private:

            friend struct GLFWwindow;
            const char *m_name;
            int m_width, m_height;
            GLFWwindow *m_Window;
            bool m_closed;

			static WindowUpdateSignal* m_Signal;

            /**
             * Initialize the Window
             * 
             **/
            bool init();

        public:
            double m_XScaleFactor;
		    double m_YScaleFactor;

            /**
             * Constructor
             * 
             **/
            Window(const char *name, int width, int height);

            /**
             * Destructor
             * 
             **/
            ~Window();

            /**
             * Clear the Window in OpenGL
             * 
             **/
            inline void clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

            /**
             * Update the Window State
             * 
             **/
            void update();

            /**
             * Check if the Window should close
             * 
             **/
            inline bool closed() const { return glfwWindowShouldClose(m_Window); }

            /**
             * GLFW key Callback
             * 
             **/
			static void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {

				input::Keyboard::GetInstance().SetKeyState(key, action != GLFW_RELEASE);

			}

            /**
             * GLFW mouse button Callback
             * 
             **/
			static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

				input::Mouse::GetInstance().SetButtonState(button, action != GLFW_RELEASE);
			}

            /**
             * GLFW mouse position Callback
             * 
             **/
			static void mousePositionCallback(GLFWwindow *window, double x, double y) {

				input::Mouse& mouse = input::Mouse::GetInstance();

				mouse.SetX(x);
				mouse.SetY(y);
			}

            /**
             * GLFW window resized Callback
             * 
             **/
			static void WindowResizeCallBack(GLFWwindow *window, int width, int height) {

				m_Signal->sendSignal(width, height);
				glViewport(0, 0, width, height);
			}

            //getters and setters
            inline int getWidth() const { return m_width; }
            inline void setWidth(int width) { m_width = width; }
            inline int getHeight() const { return m_height; }
            inline void setHeight(int height) { m_height = height; }
            inline const WindowUpdateSignal* const getSignalServer() const { return m_Signal; }

            /**
             * Make this the current OpenGL context
             * 
             **/
            inline void makeContextCurrent() { glfwMakeContextCurrent(m_Window); }

            /**
             * Convert mouse coordinates to framebuffer coordinates
             * 
             **/
            void convertCoords(double& x, double& y);
    };
}}}

#endif
