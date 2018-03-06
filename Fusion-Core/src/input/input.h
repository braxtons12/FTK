/**
 * Mouse and Keyboard classes used to get, manage, and save input states
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _INPUT
#define _INPUT

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace fusion { namespace core { namespace input {

//define necessary macros
#define MAX_KEYS  1024
#define MAX_BUTTONS 32

    class Mouse {

        private:
            static Mouse m_instance;
            bool m_MouseButtons[MAX_BUTTONS];
            double m_MouseX;
            double m_MouseY;

        public:
			
            /**
             * Constructor
             * 
             **/
			Mouse();

            /**
             * Return the instance of the mouse
             * 
             **/
            static Mouse& GetInstance();

            //getter for position
            inline double GetX() const { return m_MouseX; }
            inline double GetY() const { return m_MouseY; }
            inline void getMousePosition(double &x, double &y) { x = m_MouseX; y = m_MouseY; }

            //setters for position
            inline void SetX(double x) { m_MouseX = x; }
            inline void SetY(double y) { m_MouseY = y; }

            /**
             * Set the state of the indicated button
             * 
             **/
            inline void SetButtonState(unsigned int button, bool state) { m_MouseButtons[button] = state; }

            /**
             * Check if the button has been pressed
             * 
             **/
            inline bool Pressed(unsigned int button) const { return m_MouseButtons[button]; }

    };

    class Keyboard {

        private:
            static Keyboard m_instance;
            bool m_Keys[MAX_KEYS];
        
        public:
			/**
             * Constructor
             * 
             **/
			Keyboard();

            /**
             * Return the instance of the keyboard
             * 
             **/
            static Keyboard& GetInstance();

            /**
             * Set the state of the indicated key
             * 
             **/
            inline void SetKeyState(unsigned int key, bool state) { m_Keys[key] = state; }

            /**
             * Check if the key has been pressed
             * 
             **/
            inline bool Pressed(unsigned int key) const { return m_Keys[key]; }


    };


}}}

#endif
