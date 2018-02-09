#ifndef _FUSION_BUTTON
#define _FUSION_BUTTON

#include "../../src/input/input.h"
#include "../../src/graphics/window.h"
#include "../../src/graphics/renderable2D.h"

#define BUTTON_STATE_OFF    0
#define BUTTON_STATE_NORMAL 1
#define BUTTON_STATE_HOVER  2

namespace fusion { namespace core { namespace graphics { 

    class FusionButton : public Renderable2D {

        protected:
            input::Mouse& m_Mouse = input::Mouse::GetInstance();
            window::Window* m_ParentWindow;
            int m_State;
            Texture* m_TextureOff;
            Texture* m_TextureHover;
            Texture* m_TextureNormal;

            inline virtual void SetTexture() {

                if (m_State == BUTTON_STATE_OFF) m_Texture = m_TextureOff;
                else if(m_State == BUTTON_STATE_HOVER) m_Texture = m_TextureHover;
                else if(m_State == BUTTON_STATE_NORMAL) m_Texture = m_TextureNormal;
            }

        public:
            FusionButton(math::vec3 position, math::vec2 size, math::vec4 color, Texture* textureOff, Texture* textureHover, 
                         Texture* textureNormal, window::Window* parentWindow)
                : Renderable2D(position, size, color), m_TextureOff(textureOff), m_TextureHover(textureHover),
                  m_TextureNormal(textureNormal), m_ParentWindow(parentWindow) 
            {
                m_Texture = textureOff;
                SetTexture();
            }
            
            ~FusionButton() { }

            virtual bool clicked() {

                double x,y;
                m_Mouse.getMousePosition(x,y);
                x = (float)(x * 16.0f /((float) m_ParentWindow->getWidth()));
                y = (float)(9.0f - y * 9.0f / (float)(m_ParentWindow->getHeight()));
                if (m_Mouse.Pressed(0)) {

                    if( x <= m_Size.m_x && x >= m_Position.m_x) {

                        if( y <= (m_Position.m_y + m_Size.m_y) && y >= m_Position.m_y) return true;
                        else return false;
                    } else return false;

                } else return false;
            }

            virtual void checkHover() {

                double x, y = 0.0f;
                m_Mouse.getMousePosition(x, y);
                x = (float)(x * 16.0f /((float) m_ParentWindow->getWidth()));
                y = (float)(9.0f - y * 9.0f / (float)(m_ParentWindow->getHeight()));

                if(x <= m_Size.m_x && x >= m_Position.m_x) {

                    if(y <= (m_Position.m_y + m_Size.m_y) && y >= m_Position.m_y) {

                        setState(BUTTON_STATE_HOVER);
                    }
                    else {

                        setState(BUTTON_STATE_NORMAL);
                    }
                }
                else {

                    setState(BUTTON_STATE_NORMAL);
                }
            }

            inline bool getState() const { return m_State; }
            inline virtual void setState(int state) { m_State = state; SetTexture(); }
            inline void submit(Renderer2D* renderer) const override { renderer->submit(this); }
    };
}}}

#endif