#ifndef _FUSION_MENU
#define _FUSION_MENU

#define MENU_STATE_OFF    0
#define MENU_STATE_NORMAL 1
#define MENU_STATE_HOVER  2

#define MENU_TYPE_HORIZONTAL 0
#define MENU_TYPE_VERTICAL   1

#include "../../src/input/input.h"
#include "../../src/graphics/window.h"
#include "../../src/graphics/fusiontogglebutton.h"

namespace fusion { namespace core { namespace graphics {

    class FusionMenu : Renderable2D {

        private:
            Input::Mouse m_Mouse;
            Window* m_ParentWindow;
            Texture* m_OffTexture;
            Texture* m_HoverTexture;
            Texture* m_NormalTexture;
            int m_State;
            int m_MenuType;
            std::vector<FusionMenu&> m_SubMenus;
            std::vector<float> m_Divisions;
            int m_NumMenus;
            std::vector<FusionToggleButton&> m_Buttons;

            inline void init() {

                m_Mouse = Input::Mouse::GetInstace();
            }

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

                    for(i = 0; i < m_NumMenus; ++i) {

                        if(x >= m_Divisons.at(i) && x <= m_Divisions.at(i+1)) {

                            m_Buttons.at(i).setMenuClicked();
                            m_SubMenus.at(i).SetState(MENU_STATE_HOVER);
                        }
                    }
                }
                else if (m_MenuType == MENU_TYPE_VERTICAL) {

                    for(i = 0; i < m_NumMenus; ++i) {

                        if(y >= m_Divisions.at(i) && y <= m_Divisions.at(i+1)) {

                            m_Buttons.at(i).SetMenuClicked();
                            m_SubMenus.at(i).SetState(MENU_STATE_HOVER);
                        }
                    }
                }
            }

        public:
            FusionMenu(math::vec3 position, math::vec2 size, math::vec4 color, Texture* offTexture, Texture* hoverTexture, Texture* normalTexture,
                               int state, int menuType std::vector<float> divisions, int numMenus, Window* parentWindow)
                : Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color),
                m_OffTexture(offTexture), m_HoverTexture(hoverTexture), m_NormalTexture(normalTexture), m_State(state), 
                m_MenuType(menuType), m_Divisions(divisions), m_NumMenus(numMenus), m_ParentWindow(parentWindow)
            {

                init();
                SetTexture();
            }

            ~FusionMenu() { }

            void addSubMenu(math::vec3 position, math::vec2 size, std::vector<float> divisions, int numMenus) {

                m_SubMenus.push_back(FusionMenu(position, size, m_Color, m_HoverTexture, m_NormalTexture, false,
                                                divisions, numMenus, m_ParentWindow));
            }

            void addSubMenu(FusionMenu& menu) {

                m_SubMenus.push_back(menu);
            }

            void addButon(math::vec3 position, math::vec2 size) {

                m_Buttons.push_back(FusionToggleButton(position, size, m_Color, m_NormalTexture, m_HoverTexture, false, m_ParentWindow))
            }

            void checkHover() {

                double x, y = 0.0f;
                m_Mouse.getMousePosition(x, y);
                x = (x * 32.0f / m_ParentWindow.getWidth() - 16.0f);
                y = (9.0f - y * 18.0f / m_ParentWindow.getHeight());

                if(x <= m_Size.m_x && x >= m_Position.m_x) {

                    if(y <= m_Size.m_y && y >= m_Position.m_y) {

                        if(m_State != MENU_STATE_HOVER) m_State = MENU_STATE_HOVER;
                        Hover(x, y);
                    }
                    else {

                        SetState(MENU_STATE_NORMAL);
                        for(i = 0; i < m_NumMenus; ++i) {

                            m_Buttons.at(i).setMenuNotClicked();
                            m_SubMenus.at(i).SetState(MENU_STATE_OFF);
                        }
                    }
                }
                else {

                    SetState(MENU_STATE_NORMAL);
                    for(i = 0; i < m_NumMenus; ++i) {

                        m_Buttons.at(i).setMenuNotClicked();
                        m_SubMenus.at(i).SetState(MENU_STATE_OFF);
                    }
                }
            }

            void submit(Renderer2D* renderer) const override {

                renderer->submit(this);
                for(int i = 0; i < m_NumMenus; ++i) {

                    renderer->submit(m_SubMenus.at(i));
                }
            }


    };
}}}
#endif