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

            void SetColor() override;
        
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

            bool clicked() override;
            void checkHover() override;

            //functions used to get and set the clicked state
            inline int getState() const { return m_State; }
            inline void setState(int state) override { if(state == BUTTON_STATE_ON) m_On = true; m_State = state; SetColor(); }
            inline math::vec4 getColor() { return m_Color; }
        
    };
}}}}

#endif
