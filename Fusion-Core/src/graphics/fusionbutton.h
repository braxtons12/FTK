#ifndef _FUSION_BUTTON
#define _FUSION_BUTTON

#include "../../src/input/input.h"
#include "../../src/graphics/window.h"

namespace fusion { namespace core { namespace graphics { 

    class FusionButton : Renderable2D {

        private:
            Input::Mouse m_Mouse;
            Window* m_ParentWindow;

        protected:
            inline void init() {

                m_Mouse = Input::Mouse::GetInstace();
            }

        public:
            FusionButton(math::vec3 position, math::vec2 size, math::vec4 color, Texture* texture, Window* parentWindow)
                : Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color), m_Texture(texture), m_ParentWindow(parentWindow) 
            {
                init();
            }
            
            ~FusionButton() { }

            virtual bool clicked() {

                double x,y = 0.0f;
                m_Mouse.getMousePosition(x,y);
                if (m_Mouse.Pressed(0) && (float)(x * 32.0f / m_ParentWindow.getWidth() - 16.0f) == position.m_x &&
                   (float)(9.0f - y * 18.0f / m_ParentWindow.getHeight())== position.m_y) 
                   return true;
                else return false;
            }
    };
}}}

#endif