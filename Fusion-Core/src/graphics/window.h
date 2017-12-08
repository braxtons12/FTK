
#ifndef _WINDOW
#define _WINDOW

#include "../src/input/input.h"
#include "../src/signals/windowupdatesignal.h"


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace fusion { namespace core { namespace graphics { namespace window {

    class Window {

        private:

            friend struct GLFWwindow;
            const char *m_name;
            int m_width, m_height;
            GLFWwindow *m_Window;
            bool m_closed;
			
			static WindowUpdateSignal* m_Signal;

            bool init();

        public:
            Window(const char *name, int width, int height);
            ~Window();
            void clear() const;
            void update();
            bool closed() const;

			static void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
				
				input::Keyboard::GetInstance().SetKeyState(key, action != GLFW_RELEASE);
				
			}
			
			static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
				
				input::Mouse::GetInstance().SetButtonState(button, action != GLFW_RELEASE);
			}
			
			static void mousePositionCallback(GLFWwindow *window, double x, double y) {
				
				input::Mouse& mouse = input::Mouse::GetInstance();
				
				mouse.SetX(x);
				mouse.SetY(y);
			}
			
			static void WindowResizeCallBack(GLFWwindow *window, int width, int height) {
				
				m_Signal->sendSignal();
				glViewport(0, 0, width, height);
			}
			
            inline int getWidth() const { return m_width; }
            inline int getHeight() const { return m_height; }
            inline const WindowUpdateSignal* const getSignalServer() const { return m_Signal; }
            inline void makeContextCurrent() { glfwMakeContextCurrent(m_Window); }
    };
}}}}

#endif
