#ifndef _FUSION_TOGGLE_BUTTON
#define _FUSION_TOGGLE_BUTTON

#include "../../src/graphics/fusionbutton.h"
#include "../../src/graphics/texture.h"
#include "../../src/graphics/renderable2D.h"

#define BUTTON_STATE_ON 3

namespace fusion { namespace core { namespace graphics {

    class FusionToggleButton : public FusionButton {

        protected:
            Texture* m_TextureOn;
            bool m_On;

            void SetTexture() override {

                if(m_State == BUTTON_STATE_OFF) m_Texture = m_TextureOff;
                else if (m_State == BUTTON_STATE_HOVER && !m_On) m_Texture = m_TextureHover;
                else if (m_State == BUTTON_STATE_ON || m_On) m_Texture = m_TextureOn;
                else if (m_State == BUTTON_STATE_NORMAL) m_Texture == m_TextureNormal;
            }
        
        public:
            FusionToggleButton(math::vec3 position, math::vec2 size, math::vec4 color, Texture* textureOff, Texture* textureOn,
                               Texture* textureHover, Texture* textureNormal, int state, window::Window* parentWindow)
                : FusionButton(position, size, color, textureOff, textureHover, textureNormal, parentWindow), m_TextureOn(textureOn)
            {   
                m_State = state;
                if(m_State == BUTTON_STATE_ON) m_On = true;
                else m_On = false;
                SetTexture();
            }

            ~FusionToggleButton() { }

            bool clicked() override {
                
                double x,y = 0.0f;
                m_Mouse.getMousePosition(x,y);
                if (m_Mouse.Pressed(0) && (float)(x * 32.0f / m_ParentWindow->getWidth() - 16.0f) == m_Position.m_x &&
                   (float)(9.0f - y * 18.0f / m_ParentWindow->getHeight()) == m_Position.m_y) 
                {

                    m_State = BUTTON_STATE_ON;
                    SetTexture();
                    return m_On = true;
                }
                else return m_On = false;
            }

            void checkHover() override {

                double x, y;
                m_Mouse.getMousePosition(x, y);
                x = (float)(x * 16.0f /((float) m_ParentWindow->getWidth()));
                y = (float)(9.0f - y * 9.0f / (float)(m_ParentWindow->getHeight()));

                if(x <= m_Size.m_x && x >= m_Position.m_x) {

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
            inline void setState(int state) override { if(state == BUTTON_STATE_ON) m_On = true; m_State = state; SetTexture(); }
        
    };
}}}

#endif
