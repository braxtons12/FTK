/**
 * UI ToggleButton class
 * Enhances the base button class by adding toggle functionality
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _FTK_TOGGLE_BUTTON
#define _FTK_TOGGLE_BUTTON

#include "graphics/color.h"
#include "graphics/texture.h"
#include "graphics/renderables/renderable2D.h"
#include "graphics/ui/ftkbutton.h"




namespace ftk { namespace core { namespace graphics { namespace ui { 

    //define the on state
    #define BUTTON_STATE_ON 3

    class FtkToggleButton : public FtkButton {

        protected:
            Color m_ColorOn;
            bool m_On;

            void SetColor() override;
        
        public:
            /**
             * Constructor
             * 
             * Takes in a position, size, colors for each state, the initial state, and a parent Window
             * 
             **/
            FtkToggleButton(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover,
                               Color colorOn, int state, NativeWindow* parentWindow)
                : FtkButton(position, size, colorOff, colorNormal, colorHover, state, parentWindow), m_ColorOn(colorOn)
            {   
                m_State = state;
                if(m_State == BUTTON_STATE_ON) m_On = true;
                else m_On = false;
                SetColor();
            }

            /**
             * Destructor
             * 
             **/
            ~FtkToggleButton() { }

            /**
             * Checks if the button is clicked
             * 
             **/
            bool clicked() override;

            /**
             * Checks if the mouse is hovering over the button
             * Updates the state accordingly
             * 
             **/
            bool checkHover() override;

            //get and set the state
            inline int getState() const { return m_State; }
            inline void setState(int state) override { if(state == BUTTON_STATE_ON) m_On = true; m_State = state; SetColor(); }

            //get the current color
            inline math::vec4 getColor() { return m_Color; }
        
    };
}}}}

#endif
