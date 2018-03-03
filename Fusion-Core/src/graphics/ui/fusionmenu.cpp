#include "fusionmenu.h"

namespace fusion { namespace core { namespace graphics { namespace ui {

    void FusionMenu::SetColor() {

        if(m_State == MENU_STATE_OFF) { m_Color = m_ColorOff.getColor(); m_Visible = false; }
        else if (m_State == MENU_STATE_NORMAL) { m_Color = m_ColorNormal.getColor(); m_Visible = true; }
        else if (m_State == MENU_STATE_HOVER) { m_Visible = true; checkHover(); }
    }

    void FusionMenu::CheckHoverInBounds() {

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

    void FusionMenu::CheckHoverOutOfBounds() {

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

    void FusionMenu::CheckHoverVertical(double x, double y) {

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
            
    void FusionMenu::CheckHoverHorizontal(double x, double y) {

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

    void FusionMenu::checkHover() {

        double x, y;
        m_Mouse.getMousePosition(x, y);
        y = m_ParentWindow->getHeight() - y;

        if(m_MenuType == MENU_TYPE_HORIZONTAL) CheckHoverHorizontal(x, y);
        else CheckHoverVertical(x, y);
                
    }

    void FusionMenu::submit(Renderer2D* renderer) const {

        for(int i = 0; i < m_NumMenus; ++i) {

            if(!(m_SubMenus.at(i)->getColor().m_w <= 0))
            m_SubMenus.at(i)->submit(renderer);
        }
        for(int i = 0; i < m_NumEntries; ++i) {

            if(!(m_Buttons.at(i)->getColor().m_w <= 0))
            m_Buttons.at(i)->submit(renderer);
        }

    }

}}}}