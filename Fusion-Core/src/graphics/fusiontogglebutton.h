#ifndef _FUSION_TOGGLE_BUTTON
#define _FUSION_TOGGLE_BUTTON

#include "../../src/graphics/fusionbutton.h"

namespace fusion { namespace core { namespace graphics {

    class FusionToggleButton : FusionButton {

        private:
            Texture* m_OffTexture;
            Texture* m_OnTexture;
            bool m_State;
            bool m_MenuState;

            void SetTexture() {

                if(m_State || m_MenuState) m_Texture = m_OnTexture;
                else m_Texture = m_OffTexture;
            }
        
        public:
            FusionToggleButton(math::vec3 position, math::vec2 size, math::vec4 color, Texture* offTexture, Texture* onTexture,
                               bool state, Window* parentWindow)
                : Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color), m_State(state), 
                m_OffTexture(offTexture), m_OnTexture(onTexture), m_ParentWindow(parentWindow), m_MenuState(false)
            {
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

                    m_State = !m_State;
                    SetTexture();
                    return true;
                }
                else return false;
            }

            void setMenuClicked() {

                m_MenuState = true;
                SetTexture();
            }

            void setMenuNotClicked() {

                m_MenuState = false;
                SetTexture();
            }

            inline bool getState() const { return m_State; }
            inline void setState(bool state) { m_State = state; }
        
    };
}}}

#endif