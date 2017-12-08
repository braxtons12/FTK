#include "input.h"

namespace fusion { namespace core { namespace input {

    Mouse::Mouse() {
        for (int i = 0; i < MAX_BUTTONS; ++i) {
            m_MouseButtons[i] = false;
        }
    }

    Mouse Mouse::m_instance;

    Mouse& Mouse::GetInstance() { return Mouse::m_instance; }

    Keyboard::Keyboard() {
        for (int i = 0; i < MAX_KEYS; ++i) {
            m_Keys[i] = false;
        }
    }

    Keyboard Keyboard::m_instance;

    Keyboard& Keyboard::GetInstance() { return Keyboard::m_instance; }


}}}