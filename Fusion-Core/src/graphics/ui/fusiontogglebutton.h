#ifndef _FUSION_TOGGLE_BUTTON
#define _FUSION_TOGGLE_BUTTON

#include "graphics/ui/fusionbutton.h"
#include "graphics/texture.h"
#include "graphics/renderables/renderable2D.h"
#include "graphics/color.h"

#define BUTTON_STATE_ON 3

namespace fusion { namespace core { namespace graphics { namespace ui { 

    class FusionToggleButton : public FusionButton {

        protected:
            Color m_ColorOn;
            bool m_On;

            void SetColor() override {

                if(m_State == BUTTON_STATE_OFF) m_Color = m_ColorOff.getColor();
                else if (m_State == BUTTON_STATE_NORMAL) m_Color = m_ColorNormal.getColor();
                else if (m_State == BUTTON_STATE_HOVER && !m_On) m_Color = m_ColorHover.getColor();
                else if (m_State == BUTTON_STATE_ON || m_On) m_Color = m_ColorOn.getColor();
            }
        
        public:
            FusionToggleButton(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover,
                               Color colorOn, int state, Window* parentWindow)
                : FusionButton(position, size, colorOff, colorNormal, colorHover, state, parentWindow), m_ColorOn(colorOn)
            {   
                m_State = state;
                if(m_State == BUTTON_STATE_ON) m_On = true;
                else m_On = false;
                m_Texture = nullptr;
                SetColor();
            }

            ~FusionToggleButton() { }

            bool clicked() override {
                
                double x,y = 0.0f;
                m_Mouse.getMousePosition(x,y);
                if (m_Mouse.Pressed(0) && (float)(x * 32.0f / m_ParentWindow->getWidth() - 16.0f) == m_Position.m_x &&
                   (float)(9.0f - y * 18.0f / m_ParentWindow->getHeight()) == m_Position.m_y) 
                {

                    m_State = BUTTON_STATE_ON;
                    SetColor();
                    return m_On = true;
                }
                else return m_On = false;
            }

            void checkHover() override {

                double x, y;
                m_Mouse.getMousePosition(x, y);
                x = (float)(x * 16.0f /((float) m_ParentWindow->getWidth()));
                y = (float)(9.0f - y * 9.0f / (float)(m_ParentWindow->getHeight()));

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

            //functions used to get and set the clicked state
            inline int getState() const { return m_State; }
            inline void setState(int state) override { if(state == BUTTON_STATE_ON) m_On = true; m_State = state; SetColor(); }
            inline math::vec4 getColor() { return m_Color; }
        
    };
}}}}

#endif
