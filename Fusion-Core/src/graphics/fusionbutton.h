#ifndef _FUSION_BUTTON
#define _FUSION_BUTTON

#include "../../src/input/input.h"
#include "../../src/graphics/window.h"
#include "../../src/graphics/renderable2D.h"
#include "../../src/graphics/color.h"

#define BUTTON_STATE_OFF    0
#define BUTTON_STATE_NORMAL 1
#define BUTTON_STATE_HOVER  2

namespace fusion { namespace core { namespace graphics { 

    class FusionButton : public Renderable2D {

        protected:
            input::Mouse& m_Mouse = input::Mouse::GetInstance();
            window::Window* m_ParentWindow;
            int m_State;
            Color m_ColorOff;
            Color m_ColorNormal;
            Color m_ColorHover;

            inline virtual void SetColor() {

                if (m_State == BUTTON_STATE_OFF) m_Color = m_ColorOff.getColor();
                else if(m_State == BUTTON_STATE_NORMAL) m_Color = m_ColorNormal.getColor();
                else if(m_State == BUTTON_STATE_HOVER) m_Color = m_ColorHover.getColor();
            }

        public:
            FusionButton(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover,
                         int state, window::Window* parentWindow)
                : Renderable2D(position, size, colorOff.getColor()), m_ColorOff(colorOff), m_ColorNormal(colorNormal),
                m_ColorHover(colorHover), m_ParentWindow(parentWindow) 
            {
                m_Texture = nullptr;
                SetColor();
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

                if(x <= (m_Position.m_x + m_Size.m_x) && x >= m_Position.m_x) {

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
            inline virtual void setState(int state) { m_State = state; SetColor(); }
            inline void submit(Renderer2D* renderer) const override { renderer->submit(this); }
            inline math::vec4 getColor() { return m_Color; }
    };
}}}

#endif