#ifndef _FUSION_MENU
#define _FUSION_MENU

#define MENU_STATE_OFF    0
#define MENU_STATE_NORMAL 1
#define MENU_STATE_HOVER  2

#define MENU_TYPE_HORIZONTAL 0
#define MENU_TYPE_VERTICAL   1

#include "../../src/input/input.h"
#include "../../src/graphics/window.h"
#include "../../src/graphics/fusionbutton.h"

namespace fusion { namespace core { namespace graphics {

    class FusionMenu : public Renderable2D {

        private:
            input::Mouse& m_Mouse = input::Mouse::GetInstance();
            window::Window* m_ParentWindow;
            Texture* m_OffTexture;
            Texture* m_HoverTexture;
            Texture* m_NormalTexture;
            int m_State;
            int m_MenuType;
            std::vector<FusionMenu*> m_SubMenus;
            std::vector<float> m_Divisions;
            int m_NumMenus;
            int m_NumEntries;
            std::vector<FusionButton*> m_Buttons;

            void SetTexture() {

                if(m_State == MENU_STATE_OFF) m_Texture = m_OffTexture;
                else if (m_State == MENU_STATE_NORMAL) m_Texture = m_NormalTexture;
                else if (m_State == MENU_STATE_HOVER) checkHover();
            }

            void SetState(int state) {

                m_State = state;
                SetTexture();
            }

            void Hover(double x, double y) {

                if(m_MenuType == MENU_TYPE_HORIZONTAL) {

                    for(int i = 0; i < m_NumMenus; ++i) {

                        if(x >= m_Divisions.at(i) && x <= m_Divisions.at(i+1)) {

                            m_Buttons.at(i)->setState(BUTTON_STATE_HOVER);
                            m_SubMenus.at(i)->SetState(MENU_STATE_HOVER);
                        }
                    }
                }
                else if (m_MenuType == MENU_TYPE_VERTICAL) {

                    for(int i = 0; i < m_NumMenus; ++i) {

                        if(y >= m_Divisions.at(i) && y <= m_Divisions.at(i+1)) {

                            m_Buttons.at(i)->setState(BUTTON_STATE_HOVER);
                            m_SubMenus.at(i)->SetState(MENU_STATE_HOVER);
                        }
                    }
                }
            }

        public:
            FusionMenu(math::vec3 position, math::vec2 size, math::vec4 color, Texture* offTexture, Texture* hoverTexture, Texture* normalTexture,
                               int state, int menuType, std::vector<float> divisions, int numMenus, int numEntries, window::Window* parentWindow)
                : Renderable2D(position, size, color),
                m_OffTexture(offTexture), m_HoverTexture(hoverTexture), m_NormalTexture(normalTexture), m_State(state), 
                m_MenuType(menuType), m_Divisions(divisions), m_NumMenus(numMenus), m_NumEntries(numEntries), m_ParentWindow(parentWindow)
            {

                SetTexture();
            }

            ~FusionMenu() { }

            void addSubMenu(math::vec3 position, math::vec2 size, std::vector<float>& divisions, int numMenus, int numEntries, int menuType) {

                m_SubMenus.push_back(new FusionMenu(position, size, m_Color, m_OffTexture, m_HoverTexture, m_NormalTexture, MENU_STATE_OFF,
                                                menuType, divisions, numMenus, numEntries, m_ParentWindow));
            }

            void addSubMenu(FusionMenu* menu) {

                m_SubMenus.push_back(menu);
            }

            void addButton(math::vec3 position, math::vec2 size) {

                m_Buttons.push_back(new FusionButton(position, size, m_Color, m_NormalTexture, m_HoverTexture, m_ParentWindow));
            }

            void checkHover() {

                double x, y;
                m_Mouse.getMousePosition(x, y);
                x = (float)(x * 16.0f /((float) m_ParentWindow->getWidth()));
                y = (float)(9.0f - y * 9.0f / (float)(m_ParentWindow->getHeight()));

                if(x <= m_Size.m_x && x >= m_Position.m_x) {

                    if(y <=(m_Position.m_y + m_Size.m_y) && y >= m_Position.m_y) {

                        if(m_State != MENU_STATE_HOVER) m_State = MENU_STATE_HOVER;
                        for(int i = 0; i < m_NumMenus; ++i) {

                            m_SubMenus.at(i)->checkHover();
                        }
                        for(int i = 0; i < m_NumEntries; ++i) {

                            m_Buttons.at(i)->checkHover();
                        }
                    }
                    else {

                        SetState(MENU_STATE_NORMAL);
                        for(int i = 0; i < m_NumMenus; ++i) {

                            m_SubMenus.at(i)->checkHover();
                        }
                        for(int i = 0; i < m_NumEntries; ++i) {

                            m_Buttons.at(i)->checkHover();
                        }
                    }
                }
                else {

                    SetState(MENU_STATE_NORMAL);
                    for(int i = 0; i < m_NumMenus; ++i) {

                        m_SubMenus.at(i)->checkHover();
                    }
                    for(int i = 0; i < m_NumEntries; ++i) {

                        m_Buttons.at(i)->checkHover();
                    }
                }
            }

            void submit(Renderer2D* renderer) const override {

                for(int i = 0; i < m_NumMenus; ++i) {

                    m_SubMenus.at(i)->submit(renderer);
                }
                for(int i = 0; i < m_NumEntries; ++i) {

                    m_Buttons.at(i)->submit(renderer);
                }
            }


    };
}}}
#endif
