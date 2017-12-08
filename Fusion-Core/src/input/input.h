#ifndef _INPUT
#define _INPUT

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace fusion { namespace core { namespace input {

#define MAX_KEYS  1024
#define MAX_BUTTONS 32

    class Mouse {

        private:
            static Mouse m_instance;
            bool m_MouseButtons[MAX_BUTTONS];
            double m_MouseX;
            double m_MouseY;

        public:
			
			Mouse();
            static Mouse& GetInstance();

            inline double GetX() const { return m_MouseX; }
            inline double GetY() const { return m_MouseY; }
            inline void getMousePosition(double &x, double &y) { x = m_MouseX; y = m_MouseY; }

            inline void SetX(double x) { m_MouseX = x; }
            inline void SetY(double y) { m_MouseY = y; }

            inline void SetButtonState(unsigned int button, bool state) { m_MouseButtons[button] = state; }

            inline bool Pressed(unsigned int button) const { return m_MouseButtons[button]; }

    };

    class Keyboard {

        private:
            static Keyboard m_instance;
            bool m_Keys[MAX_KEYS];
        
        public:
			
			Keyboard();
            static Keyboard& GetInstance();

            inline void SetKeyState(unsigned int key, bool state) { m_Keys[key] = state; }

            inline bool Pressed(unsigned int key) const { return m_Keys[key]; }


    };


}}}

#endif
