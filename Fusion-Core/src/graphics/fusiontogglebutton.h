#ifndef _FUSION_TOGGLE_BUTTON
#define _FUSION_TOGGLE_BUTTON

#include "../../src/graphics/fusionbutton.h"

#define BUTTON_STATE_ON 2

namespace fusion { namespace core { namespace graphics {

    class FusionToggleButton : FusionButton {

        private:
            Texture* m_TextureOn;
            int m_State;
            bool m_On;

            void SetTexture() override {

                if(m_State == BUTTON_STATE_OFF) m_Texture = m_TextureOff;
                else if (m_State == BUTTON_STATE_HOVER && !m_On) m_Texture = m_TextureHover;
                else if (m_Sate == BUTTON_STATE_ON || m_On) m_Texture = m_TextureOn;
            }
        
        public:
            FusionToggleButton(math::vec3 position, math::vec2 size, math::vec4 color, Texture* textureOff, Texture* textureOn,
                               Texture* textureHover, int state, Window* parentWindow)
                : Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color), m_State(state), m_Texture(textureOff)
                m_TextureOff(textureOff), m_TextureOn(textureOn), m_TextureHover(textureHover), m_ParentWindow(parentWindow)
            {
                if(state < 2) m_On = state;
                else m_On = false;
                init();
                SetTexture();
            }

            ~FusionToggleButton() { }

            bool clicked() override {
                
                double x,y = 0.0f;
                m_Mouse.getMousePosition(x,y);
                if (m_Mouse.Pressed(0) && (float)(x * 32.0f / m_ParentWindow.getWidth() - 16.0f) == position.m_x &&
                   (float)(9.0f - y * 18.0f / m_ParentWindow.getHeight()) == position.m_y) 
                {

                    m_State = BUTTON_STATE_ON;
                    SetTexture();
                    return m_On = true;
                }
                else return m_On = false;
            }

            virtual void checkHover() override {

                double x, y = 0.0f;
                m_Mouse.getMousePosition(x, y);
                x = (x * 32.0f / m_ParentWindow.getWidth() - 16.0f);
                y = (9.0f - y * 18.0f / m_ParentWindow.getHeight());

                if(x <= m_Size.m_x && x >= m_Position.m_x) {

                    if(y <= m_Size.m_y && y >= m_Position.m_y) {

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
            inline bool getState() const { return m_State; }
            inline void setState(int state) { if(state < 2) m_On = state; m_State = state; }
        
    };
}}}

#endif