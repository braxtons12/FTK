/**
 * UI ToggleButton class
 * Enhances the base button class by adding toggle functionality
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "fusiontogglebutton.h"

namespace fusion { namespace core { namespace graphics { namespace ui {
   
    /**
     * Set the color based on the current state
     * 
     **/
    void FusionToggleButton::SetColor() {

        if(m_State == BUTTON_STATE_OFF) m_Color = m_ColorOff.getColor();
        else if (m_State == BUTTON_STATE_NORMAL) m_Color = m_ColorNormal.getColor();
        else if (m_State == BUTTON_STATE_HOVER && !m_On) m_Color = m_ColorHover.getColor();
        else if (m_State == BUTTON_STATE_ON || m_On) m_Color = m_ColorOn.getColor();
    }

    /**
     * Checks if the button has been clicked.
     * Updates the state accordingly
     * 
     **/
    bool FusionToggleButton::clicked() {
                
        double x, y;
        m_Mouse.getMousePosition(x, y);
        y = m_ParentWindow->getHeight() - y;
        m_ParentWindow->convertCoords(x, y);

        if (m_Mouse.Pressed(0) && (x >= m_Position.m_x && x <= (m_Position.m_x + m_Size.m_x)) &&
            (y >= m_Position.m_y && y<= (m_Position.m_y + m_Size.m_y))) 
        {

            if(m_State == BUTTON_STATE_ON) m_State = BUTTON_STATE_OFF;
            else m_State = BUTTON_STATE_ON;
            m_On = !m_On;
            SetColor();
            return true;
        }
        else return false;
    }

    /**
     * Checks if the mouse if hovering over the button
     * Updates the state accordingly
     * 
     **/
    bool FusionToggleButton::checkHover() {

        double x, y;
        m_Mouse.getMousePosition(x, y);
        y = m_ParentWindow->getHeight() - y;
        m_ParentWindow->convertCoords(x, y);

        if(x <= (m_Position.m_x + m_Size.m_x) && x >= m_Position.m_x) {

            if(y <= (m_Position.m_y + m_Size.m_y) && y >= m_Position.m_y) {

                setState(BUTTON_STATE_HOVER);
                return true;
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