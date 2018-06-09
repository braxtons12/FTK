/**
 * UI Menu class
 * Used for creating any kind of traditional dropdown or cascading menu
 *
 * Header File
 *
 * C 2018 Braxton Salyer
 *
 **/

#ifndef _FTK_MENU
#define _FTK_MENU

#include "base/ftkobject.h"
#include "input/input.h"
#include "graphics/color.h"
#include "graphics/nativewindow.h"
#include "graphics/ui/ftkbutton.h"


namespace ftk { namespace core { namespace graphics { namespace ui {

    //define menu states
    #define MENU_STATE_OFF       0
    #define MENU_STATE_NORMAL    1
    #define MENU_STATE_HOVER     2

    //define menu types
    #define MENU_TYPE_HORIZONTAL 0
    #define MENU_TYPE_VERTICAL   1

    class FtkMenu : public Renderable2D, public FtkObject {

        private:
            input::Mouse& m_Mouse = input::Mouse::GetInstance();
            NativeWindow* m_ParentWindow;
            Color m_ColorOff;
            Color m_ColorNormal;
            Color m_ColorHover;
            int m_State;
            int m_MenuType;
            std::vector<FtkMenu*> m_SubMenus;
            int m_NumMenus;
            int m_NumEntries;
            std::vector<FtkButton*> m_Buttons;
            bool m_AlwaysVisible;
            bool m_Visible;
			int m_EntryClickedSignal;

            //set the color based on the current state
            void SetColor();

			/**
             * check if the menu is currently being hovered by the mouse
             *
             **/
            void checkHover();

            //check if the menu hierarchy is hovered and the mouse is in bounds of the current menu
            void CheckHoverInBounds();

            //check if the menu hierarchy is hovered and the mouse is not in bounds of the current menu
            void CheckHoverOutOfBounds();

            //check if the menu hierarchy is hovered and the menu is a vertical menu
            void CheckHoverVertical(double x, double y);

            //check if the menu hierarchy is hovered and the menu is a horizontal menu
            void CheckHoverHorizontal(double x, double y);

        public:
            /**
             * Constructor
             *
             * Huge. :/
             * takes in position, size, colors for ever state, an initial state, whether it should always be visible,
             * and a parent Window pointer
             *
             **/
            FtkMenu(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover,
                       int state, int menuType,  bool alwaysVisible, NativeWindow* parentWindow)
                : Renderable2D(math::vec3(position.m_x, parentWindow->getHeight() - position.m_y, position.m_z), size, colorOff.getColor()),
                m_ColorOff(colorOff), m_ColorNormal(colorNormal), m_ColorHover(colorHover), m_State(state),
                m_MenuType(menuType), m_NumMenus(0), m_NumEntries(0), m_AlwaysVisible(alwaysVisible),
                m_ParentWindow(parentWindow)
            {
                m_Visible = m_AlwaysVisible;
                SetColor();
            }

            /**
             * Destructor
             *
             **/
            ~FtkMenu() { }

            /**
             * Add a not-yet-created subMenu from the given parameters
             *
             **/
            inline void addSubMenu(math::vec3 position, math::vec2 size, int menuType, bool alwaysVisible) {

                m_SubMenus.push_back(new FtkMenu(position, size, m_ColorOff, m_ColorNormal, m_ColorHover, MENU_STATE_OFF,
                                                menuType, alwaysVisible, m_ParentWindow));
                m_NumMenus++;
            }

            /**
             * Add a subMenu
             *
             **/
            inline void addSubMenu(FtkMenu* menu) {

                m_SubMenus.push_back(menu);
                m_NumMenus++;
            }

            /**
             * Add a not-yet-created button from the given parameters
             *
             **/
            inline void addButton(math::vec3 position, math::vec2 size) {

                m_Buttons.push_back(new FtkButton(position, size, m_ColorOff, m_ColorNormal, m_ColorHover,
                                                     BUTTON_STATE_OFF, m_ParentWindow));
                m_NumEntries++;
            }

			void update();

            /**
             * Submit the menu for rendering
             *
             **/
            void submit(Renderer2D* renderer) const override;

            //getters and setters
            inline void setState(int state) { m_State = state; SetColor(); }
            inline void setVisible(bool visibile) { m_Visible = visibile; }
            inline bool getVisible() { return m_Visible; }
            inline math::vec4 getColor() { return m_Color; }

			FtkMenu* submenuAt(int index);
			FtkMenu* submenuAt(std::vector<int> indices);
			FtkButton* entryAt(int index);
			FtkButton* entryAt(std::vector<int> indices);
    };
}}}}

#endif
