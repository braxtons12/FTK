/**
 * Mouse and Keyboard classes used to get, manage, and save input states
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "input.h"

namespace fusion { namespace core { namespace input {

    /**
     * Constructor
     * 
     **/
    Mouse::Mouse() {
        for (int i = 0; i < MAX_BUTTONS; ++i) {
            m_MouseButtons[i] = false;
        }
    }

    //create the mouse
    Mouse Mouse::m_instance;

    /**
     * Return the instance of the mouse
     * 
     **/
    Mouse& Mouse::GetInstance() { return Mouse::m_instance; }

    /**
     * Constructor
     * 
     **/
    Keyboard::Keyboard() {
        for (int i = 0; i < MAX_KEYS; ++i) {
            m_Keys[i] = false;
        }
    }

    //create the keyboard
    Keyboard Keyboard::m_instance;

    /**
     * Return the instance of the keyboard
     * 
     **/
    Keyboard& Keyboard::GetInstance() { return Keyboard::m_instance; }


}}}