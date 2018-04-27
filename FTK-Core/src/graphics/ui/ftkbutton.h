/**
 * UI Button class
 * Forms the base functionality for any other button-type ui elements
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _FTK_BUTTON
#define _FTK_BUTTON

#include "input/input.h"
#include "graphics/color.h"
#include "graphics/nativewindow.h"
#include "graphics/renderables/renderable2D.h"

//temporary for testing purposes only
#include <iostream>

namespace ftk { namespace core { namespace graphics { namespace ui { 

    //define button states
    #define BUTTON_STATE_OFF    0
    #define BUTTON_STATE_NORMAL 1
    #define BUTTON_STATE_HOVER  2

    class FtkButton : public Renderable2D {

        protected:
            input::Mouse& m_Mouse = input::Mouse::GetInstance();
            NativeWindow* m_ParentWindow;
            int m_State;
            Color m_ColorOff;
            Color m_ColorNormal;
            Color m_ColorHover;

            /**
             * Set the button color based on the state of the button
             *
             **/
            virtual void SetColor() {

                if (m_State == BUTTON_STATE_OFF) m_Color = m_ColorOff.getColor();
                else if(m_State == BUTTON_STATE_NORMAL) m_Color = m_ColorNormal.getColor();
                else if(m_State == BUTTON_STATE_HOVER) m_Color = m_ColorHover.getColor();
            }

        public:
            /**
             * Constructor
             * 
             * Takes in a position, size, colors for each state, the initial state, and a parent Window
             * 
             **/
            FtkButton(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover,
                         int state, NativeWindow* parentWindow)
                : Renderable2D(math::vec3(position.m_x, parentWindow->getHeight() - position.m_y, position.m_z), size, 
                colorOff.getColor()), m_State(state), m_ColorOff(colorOff), m_ColorNormal(colorNormal),
                m_ColorHover(colorHover), m_ParentWindow(parentWindow) 
            {
                SetColor();
            }
            
            /**
             * Destructor
             * 
             **/
            ~FtkButton() { }

            /**
             * Checks if the button is clicked
             * 
             **/
            virtual bool clicked() {

                double x,y;
                m_Mouse.getMousePosition(x,y);
                y = m_ParentWindow->getHeight() - y;
                m_ParentWindow->convertCoords(x, y);

                if (m_Mouse.Pressed(0) && (x >= m_Position.m_x && x <= (m_Position.m_x + m_Size.m_x)) &&
                   (y >= m_Position.m_y && y <= (m_Position.m_y + m_Size.m_y)))
                   {
                       std::cout << "clicked" << std::endl;
                       return true;
                   }

                else return false;
            }

            /**
             * Checks if the mouse is hovering over the button
             * 
             **/
            virtual bool checkHover() {

                double x, y;
                m_Mouse.getMousePosition(x, y);
                y = m_ParentWindow->getHeight() - y;
                m_ParentWindow->convertCoords(x, y);

                if(x <= (m_Position.m_x + m_Size.m_x) && x >= m_Position.m_x) {

                    if(y <= (m_Position.m_y + m_Size.m_y) && y >= m_Position.m_y) {

                        setState(BUTTON_STATE_HOVER);
                        return true;
                    }
                    else {

                        setState(BUTTON_STATE_NORMAL);
						return false;
                    }
                }
                else {

                    setState(BUTTON_STATE_NORMAL);
					return false;
                }
            }

            //get and set the state
            inline bool getState() const { return m_State; }
            inline virtual void setState(int state) { m_State = state; SetColor(); }

            //get the current color
            inline math::vec4 getColor() { return m_Color; }
			inline NativeWindow* const getNativeWindow() const { return m_ParentWindow; }
			inline Color const getNormalColor() const { return m_ColorNormal; }
			inline Color const getHoverColor() const { return m_ColorHover; }
			inline Color const getOffColor() const { return m_ColorOff; }
            
            FtkButton& operator=(const FtkButton& button) {
				
				return *(new FtkButton(button.getPosition(), button.getSize(), button.getOffColor(),
										  button.getNormalColor(), button.getHoverColor(), 
										  button.getState(), button.getNativeWindow()));
			}
    };
}}}}

#endif
