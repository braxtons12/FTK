
#ifndef _WINDOW
#define _WINDOW

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"../src/input/input.h"


namespace fusion { namespace core { namespace window {

    class Window {

        private:

            friend struct GLFWwindow;
            const char *m_name;
            int m_width, m_height;
            GLFWwindow *m_Window;
            bool m_closed;

            bool init();

        public:
            Window(const char *name, int width, int height);
            ~Window();
            void clear() const;
            void update();
            bool closed() const;

            inline int getWidth() const { return m_width; }
            inline int getHeight() const { return m_height; }
    };
}}}

#endif