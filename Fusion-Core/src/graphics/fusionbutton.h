#ifndef _FUSION_BUTTON
#define _FUSION_BUTTON

#include "../../src/input/input.h"
#include "../../src/graphics/window.h"
#include "../../src/graphics/renderable2D.h"

#define BUTTON_STATE_OFF   0
#define BUTTON_STATE_HOVER 1

namespace fusion { namespace core { namespace graphics { 

    class FusionButton : public Renderable2D {

        protected:
            input::Mouse m_Mouse;
            window::Window* m_ParentWindow;
            int m_State;
            Texture* m_TextureOff;
            Texture* m_TextureHover;

            inline void init() {

                m_Mouse = input::Mouse::GetInstance();
                m_State = BUTTON_STATE_OFF;
            }

            inline void SetState(int state) {

                m_State = state;
                SetTexture();
            }

            inline virtual void SetTexture() {

                if (m_State == BUTTON_STATE_OFF) m_Texture = m_TextureOff;
                else if(m_State == BUTTON_STATE_HOVER) m_Texture = m_TextureHover;
            }

        public:
            FusionButton(math::vec3 position, math::vec2 size, math::vec4 color, Texture* textureOff, Texture* textureHover, window::Window* parentWindow)
                : Renderable2D(position, size, color), m_TextureOff(textureOff), m_TextureHover(textureHover), m_ParentWindow(parentWindow) 
            {
                m_Texture = textureOff;
                init();
            }
            
            ~FusionButton() { }

            virtual bool clicked() {

                double x,y = 0.0f;
                m_Mouse.getMousePosition(x,y);
                if (m_Mouse.Pressed(0) && (float)(x * 32.0f / m_ParentWindow->getWidth() - 16.0f) == m_Position.m_x &&
                   (float)(9.0f - y * 18.0f / m_ParentWindow->getHeight())== m_Position.m_y) 
                   return true;
                else return false;
            }

            virtual void checkHover() {

                double x, y = 0.0f;
                m_Mouse.getMousePosition(x, y);
                x = (x * 32.0f / m_ParentWindow->getWidth() - 16.0f);
                y = (9.0f - y * 18.0f / m_ParentWindow->getHeight());

                if(x <= m_Size.m_x && x >= m_Position.m_x) {

                    if(y <= m_Size.m_y && y >= m_Position.m_y) {

                        SetState(BUTTON_STATE_HOVER);
                    }
                    else {

                        SetState(BUTTON_STATE_OFF);
                    }
                }
                else {

                    SetState(BUTTON_STATE_OFF);
                }
            }

            inline bool getState() const { return m_State; }
            inline void setState(int state) { m_State = state; }
            inline void submit(Renderer2D* renderer) const override { renderer->submit(this); }
    };
}}}

#endif