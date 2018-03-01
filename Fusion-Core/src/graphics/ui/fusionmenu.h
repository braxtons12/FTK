#ifndef _FUSION_MENU
#define _FUSION_MENU

#define MENU_STATE_OFF    0
#define MENU_STATE_NORMAL 1
#define MENU_STATE_HOVER  2

#define MENU_TYPE_HORIZONTAL 0
#define MENU_TYPE_VERTICAL   1

#include "input/input.h"
#include "graphics/window.h"
#include "graphics/ui/fusionbutton.h"
#include "graphics/color.h"


namespace fusion { namespace core { namespace graphics {

    class FusionMenu : public Renderable2D {

        private:
            input::Mouse& m_Mouse = input::Mouse::GetInstance();
            window::Window* m_ParentWindow;
            Color m_ColorOff;
            Color m_ColorNormal;
            Color m_ColorHover;
            int m_State;
            int m_MenuType;
            std::vector<FusionMenu*> m_SubMenus;
            int m_NumMenus;
            int m_NumEntries;
            std::vector<FusionButton*> m_Buttons;
            bool m_AlwaysVisible;
            bool m_Visible;

            void SetColor() {

                if(m_State == MENU_STATE_OFF) { m_Color = m_ColorOff.getColor(); m_Visible = false; }
                else if (m_State == MENU_STATE_NORMAL) { m_Color = m_ColorNormal.getColor(); m_Visible = true; }
                else if (m_State == MENU_STATE_HOVER) { m_Visible = true; checkHover(); }
            }

            void CheckHoverInBounds() {

                m_State = MENU_STATE_HOVER;
                m_Color = m_ColorHover.getColor();
                m_Visible = true;
                for(int i = 0; i < m_NumMenus; ++i) {

                    m_SubMenus.at(i)->checkHover();
                }
                for(int i = 0; i < m_NumEntries; ++i) {

                    m_Buttons.at(i)->checkHover();
                }
            }

            void CheckHoverOutOfBounds() {

                bool temp = false;
                for(int i = 0; i < m_NumMenus; ++i) {

                    temp = m_SubMenus.at(i)->getVisible();
                }
                
                if(temp) { m_State = MENU_STATE_HOVER; m_Visible = true; }
                else if(m_AlwaysVisible) setState(MENU_STATE_NORMAL);
                else { setState(MENU_STATE_OFF);}

                for(int i = 0; i < m_NumMenus; ++i) {

                    if(m_State == MENU_STATE_HOVER) m_SubMenus.at(i)->checkHover();
                    else m_SubMenus.at(i)->setState(MENU_STATE_OFF);
                }
                for(int i = 0; i < m_NumEntries; ++i) {

                    if(m_State == MENU_STATE_HOVER) m_Buttons.at(i)->checkHover();
                    else if(m_AlwaysVisible) m_Buttons.at(i)->setState(BUTTON_STATE_NORMAL);
                    else m_Buttons.at(i)->setState(BUTTON_STATE_OFF);
                }
            }

            void CheckHoverVertical(double x, double y) {

                if(y <= (m_Position.m_y + m_Size.m_y) && y >= m_Position.m_y) {

                    if(x <= (m_Position.m_x + m_Size.m_x) && x >= m_Position.m_x) {

                        CheckHoverInBounds();
                    }
                    else {

                        CheckHoverOutOfBounds();
                    }
                }
                else {

                    CheckHoverOutOfBounds();
                }
            } 
            
            void CheckHoverHorizontal(double x, double y) {

                if(x <= (m_Position.m_x + m_Size.m_x) && x >= m_Position.m_x) {

                    if(y <= (m_Position.m_y + m_Size.m_y) && y >= m_Position.m_y) {

                        CheckHoverInBounds();
                    }
                    else {

                       CheckHoverOutOfBounds();
                    }
                }
                else {

                    CheckHoverOutOfBounds();
                }
            }

        public:
            FusionMenu(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover,
                       int state, int menuType,  int numMenus, int numEntries, bool alwaysVisible, window::Window* parentWindow)
                : Renderable2D(position, size, colorOff.getColor()),
                m_ColorOff(colorOff), m_ColorNormal(colorNormal), m_ColorHover(colorHover), m_State(state),
                m_MenuType(menuType), m_NumMenus(numMenus), m_NumEntries(numEntries), m_AlwaysVisible(alwaysVisible),
                m_ParentWindow(parentWindow)
            {
                m_Visible = m_AlwaysVisible;
                m_Texture = nullptr;
                SetColor();
            }

            ~FusionMenu() { }

            void addSubMenu(math::vec3 position, math::vec2 size, int numMenus, int numEntries, int menuType, bool alwaysVisible) {

                m_SubMenus.push_back(new FusionMenu(position, size, m_ColorOff, m_ColorNormal, m_ColorHover, MENU_STATE_OFF,
                                                menuType, numMenus, numEntries, alwaysVisible, m_ParentWindow));
            }

            void addSubMenu(FusionMenu* menu) {

                m_SubMenus.push_back(menu);
            }

            void addButton(math::vec3 position, math::vec2 size) {

                m_Buttons.push_back(new FusionButton(position, size, m_ColorOff, m_ColorNormal, m_ColorHover,
                                                     BUTTON_STATE_OFF, m_ParentWindow));
            }

            void checkHover() {

                double x, y;
                m_Mouse.getMousePosition(x, y);
                x = (float)(x * 16.0f /((float) m_ParentWindow->getWidth()));
                y = (float)(9.0f - y * 9.0f / (float)(m_ParentWindow->getHeight()));

                if(m_MenuType == MENU_TYPE_HORIZONTAL) CheckHoverHorizontal(x, y);
                else CheckHoverVertical(x, y);
                
            }

            void submit(Renderer2D* renderer) const override {

                for(int i = 0; i < m_NumMenus; ++i) {

                    if(!(m_SubMenus.at(i)->getColor().m_w <= 0))
                    m_SubMenus.at(i)->submit(renderer);
                }
                for(int i = 0; i < m_NumEntries; ++i) {

                    if(!(m_Buttons.at(i)->getColor().m_w <= 0))
                    m_Buttons.at(i)->submit(renderer);
                }

            }

            void setState(int state) { m_State = state; SetColor(); }
            inline void setVisible(bool visibile) { m_Visible = visibile; }
            inline bool getVisible() { return m_Visible; }
            inline math::vec4 getColor() { return m_Color; }


    };
}}}
#endif
