#include "fusiontogglebutton.h"

namespace fusion { namespace core { namespace graphics { namespace ui {
   
    void FusionToggleButton::SetColor() {

        if(m_State == BUTTON_STATE_OFF) m_Color = m_ColorOff.getColor();
        else if (m_State == BUTTON_STATE_NORMAL) m_Color = m_ColorNormal.getColor();
        else if (m_State == BUTTON_STATE_HOVER && !m_On) m_Color = m_ColorHover.getColor();
        else if (m_State == BUTTON_STATE_ON || m_On) m_Color = m_ColorOn.getColor();
    }

    bool FusionToggleButton::clicked() {
                
        double x,y = 0.0f;
        m_Mouse.getMousePosition(x,y);
        y = m_ParentWindow->getHeight() - y;
        if (m_Mouse.Pressed(0) && (x >= m_Position.m_x && x <= (m_Position.m_x + m_Size.m_x)) &&
            (y >= m_Position.m_y && y<= (m_Position.m_y + m_Size.m_y))) 
        {

            m_State = BUTTON_STATE_ON;
            SetColor();
            return m_On = true;
        }
        else return m_On = false;
    }

    void FusionToggleButton::checkHover() {

        double x, y;
        m_Mouse.getMousePosition(x, y);
        y = m_ParentWindow->getHeight() - y;

        if(x <= (m_Position.m_x + m_Size.m_x) && x >= m_Position.m_x) {

            if(y <= (m_Position.m_y + m_Size.m_y) && y >= m_Position.m_y) {

                setState(BUTTON_STATE_HOVER);
            }
            else {
                if(m_On) setState(BUTTON_STATE_ON);
                else setState(BUTTON_STATE_NORMAL);
            }
        }
        else {

            if(m_On) setState(BUTTON_STATE_ON);
            else setState(BUTTON_STATE_NORMAL);
        }
    }
}}}}