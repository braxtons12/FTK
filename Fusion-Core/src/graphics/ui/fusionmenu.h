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


namespace fusion { namespace core { namespace graphics { namespace ui { 

    class FusionMenu : public Renderable2D {

        private:
            input::Mouse& m_Mouse = input::Mouse::GetInstance();
            Window* m_ParentWindow;
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

            void SetColor();
            void CheckHoverInBounds();
            void CheckHoverOutOfBounds();
            void CheckHoverVertical(double x, double y);
            void CheckHoverHorizontal(double x, double y);

        public:
            FusionMenu(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover,
                       int state, int menuType,  int numMenus, int numEntries, bool alwaysVisible, Window* parentWindow)
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

            inline void addSubMenu(math::vec3 position, math::vec2 size, int numMenus, int numEntries, int menuType, bool alwaysVisible) {

                m_SubMenus.push_back(new FusionMenu(position, size, m_ColorOff, m_ColorNormal, m_ColorHover, MENU_STATE_OFF,
                                                menuType, numMenus, numEntries, alwaysVisible, m_ParentWindow));
            }

            inline void addSubMenu(FusionMenu* menu) {

                m_SubMenus.push_back(menu);
            }

            inline void addButton(math::vec3 position, math::vec2 size) {

                m_Buttons.push_back(new FusionButton(position, size, m_ColorOff, m_ColorNormal, m_ColorHover,
                                                     BUTTON_STATE_OFF, m_ParentWindow));
            }

            void checkHover();

            void submit(Renderer2D* renderer) const override;

            inline void setState(int state) { m_State = state; SetColor(); }
            inline void setVisible(bool visibile) { m_Visible = visibile; }
            inline bool getVisible() { return m_Visible; }
            inline math::vec4 getColor() { return m_Color; }


    };
}}}}

#endif
