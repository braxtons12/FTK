#ifndef _FUSION_TOGGLE_BUTTON
#define _FUSION_TOGGLE_BUTTON

#include "../../src/graphics/fusionbutton.h"
#include "../../src/graphics/texture.h"
#include "../../src/graphics/renderable2D.h"

#define BUTTON_STATE_ON 2

namespace fusion { namespace core { namespace graphics {

    class FusionToggleButton : public FusionButton {

        protected:
            Texture* m_TextureOn;
            bool m_On;

            void SetTexture() override {

                if(m_State == BUTTON_STATE_OFF) m_Texture = m_TextureOff;
                else if (m_State == BUTTON_STATE_HOVER && !m_On) m_Texture = m_TextureHover;
                else if (m_State == BUTTON_STATE_ON || m_On) m_Texture = m_TextureOn;
            }
        
        public:
            FusionToggleButton(math::vec3 position, math::vec2 size, math::vec4 color, Texture* textureOff, Texture* textureOn,
                               Texture* textureHover, int state, window::Window* parentWindow)
                : FusionButton(position, size, color, textureOff, textureHover, parentWindow), m_TextureOn(textureOn)
            {
                if(state < 2) m_On = state;
                else m_On = false;
                m_State = state;
                if(m_On) m_Texture = textureOn;
                else m_Texture = textureOff;
                m_TextureOff = textureOff;
                m_TextureHover = textureHover;
                m_ParentWindow = parentWindow;
                init();
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

                        SetState(BUTTON_STATE_HOVER);
                    }
                    else {

                        SetState(m_On);
                    }
                }
                else {

                    SetState(m_On);
                }
            }

            //functions used to get and set the clicked state
            inline int getState() const { return m_State; }
            inline void setState(int state) { if(state < 2) m_On = state; m_State = state; }
        
    };
}}}

#endif
