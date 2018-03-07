#include "fusionviewport.h"

namespace fusion { namespace core { namespace graphics { namespace ui {

    bool FusionViewport::checkBounds(Renderable2D* renderable) {

        math::vec3 position = renderable->getPosition();
        math::vec2 size = renderable->getSize();

        if(position.m_x > (m_InnerPosition.m_x + m_InnerSize.m_x)) return false;
        else if(position.m_x > (m_OuterPosition.m_x + m_OuterSize.m_x)) return false;
        else if((position.m_x + size.m_x) < m_OuterPosition.m_x) return false;
        else if((position.m_x + size.m_x) < m_InnerPosition.m_x) return false;
        else if(position.m_y > (m_InnerPosition.m_y + m_InnerSize.m_y)) return false;
        else if(position.m_y > (m_OuterPosition.m_y + m_OuterSize.m_y)) return false;
        else if((position.m_y + size.m_y) < m_OuterPosition.m_y) return false;
        else if((position.m_y + size.m_y) < m_InnerPosition.m_y) return false;
        else return true;
    }

    void FusionViewport::submitPanels(Renderer2D* renderer) {

        if(m_RightInnerPanel) m_RightInnerPanel->submit(renderer);
        if(m_RightOuterPanel) m_RightOuterPanel->submit(renderer);
        if(m_LeftInnerPanel) m_LeftInnerPanel->submit(renderer);
        if(m_LeftOuterPanel) m_LeftOuterPanel->submit(renderer);
        if(m_TopInnerPanel) m_TopInnerPanel->submit(renderer);
        if(m_TopOuterPanel) m_TopOuterPanel->submit(renderer);
        if(m_BottomInnerPanel) m_BottomInnerPanel->submit(renderer);
        if(m_BottomOuterPanel) m_BottomOuterPanel->submit(renderer);
    }

    FusionViewport::FusionViewport(math::vec3 position, math::vec2 size, Color backgroundColor)
        : Group(math::mat4::identity()), m_OuterPosition(position), m_OuterSize(size), m_BackgroundColor(backgroundColor), 
        m_Background(Sprite(m_OuterPosition.m_x, m_OuterPosition.m_y, m_OuterSize.m_x, m_OuterSize.m_y, m_BackgroundColor.getColor())),
        m_InnerPosition(m_OuterPosition), m_InnerSize(m_OuterSize), m_ViewportSignal(new ViewportSizeSignal())
    { }

    FusionViewport::~FusionViewport() { }

    void FusionViewport::addPanel(bool panelType, int panelPosition, FusionPanel* panel) {

        if(panelType) {
            switch(panelPosition) {

                case TOP_PANEL:
                    m_TopInnerPanel = panel; 
                    m_TopInnerPanelSignal = m_TopInnerPanel->getSignal();
                    m_InnerSize.m_y -= m_TopInnerPanel->getSize().m_y; 
                    break;

                case RIGHT_PANEL:
                    m_RightInnerPanel = panel;
                    m_RightInnerPanelSignal = m_RightInnerPanel->getSignal();
                    m_InnerSize.m_x -= m_RightInnerPanel->getSize().m_x;
                    break;

                case BOTTOM_PANEL:
                    m_BottomInnerPanel = panel;
                    m_BottomInnerPanelSignal = m_BottomInnerPanel->getSignal();
                    m_InnerSize.m_y -= m_BottomInnerPanel->getSize().m_y;
                    m_InnerPosition.m_y += m_BottomInnerPanel->getSize().m_y;
                    break;

                case LEFT_PANEL:
                    m_LeftInnerPanel = panel;
                    m_LeftInnerPanelSignal = m_LeftInnerPanel->getSignal();
                    m_InnerSize.m_x -= m_LeftInnerPanel->getSize().m_x;
                    m_InnerPosition.m_x += m_LeftInnerPanel->getSize().m_x;
                    break;
            }
        }
        else {
            switch(panelPosition) {
                
                case TOP_PANEL:
                    m_TopOuterPanel = panel;
                    m_TopOuterPanelSignal = m_TopOuterPanel->getSignal();
                    m_InnerSize.m_y -= m_TopOuterPanel->getSize().m_y;
                    m_OuterSize.m_y -= m_TopOuterPanel->getSize().m_y;
                    break;

                case RIGHT_PANEL:
                    m_RightOuterPanel = panel;
                    m_RightOuterPanelSignal = m_RightOuterPanel->getSignal();
                    m_InnerSize.m_x -= m_RightOuterPanel->getSize().m_x;
                    m_OuterSize.m_x -= m_RightOuterPanel->getSize().m_x;
                    break;

                case BOTTOM_PANEL:
                    m_BottomOuterPanel = panel;
                    m_BottomOuterPanelSignal = m_BottomOuterPanel->getSignal();
                    m_InnerSize.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_InnerPosition.m_y += m_BottomOuterPanel->getSize().m_y;
                    m_OuterSize.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_OuterPosition.m_y += m_BottomOuterPanel->getSize().m_y;
                    break;

                case LEFT_PANEL:
                    m_LeftOuterPanel = panel;
                    m_LeftOuterPanelSignal = m_LeftOuterPanel->getSignal();
                    m_InnerSize.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_InnerPosition.m_x += m_LeftOuterPanel->getSize().m_x;
                    m_OuterSize.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_OuterPosition.m_x += m_LeftOuterPanel->getSize().m_x;
                    break;
            }
        }
    }

    void FusionViewport::hidePanel(bool panelType, int panelPosition) {

        if(panelType) {
            
            switch(panelPosition) {

                case TOP_PANEL: 
                    m_InnerSize.m_y += m_TopInnerPanel->getSize().m_y; 
                    break;
                    
                case RIGHT_PANEL:
                    m_InnerSize.m_x += m_RightInnerPanel->getSize().m_x;
                    break;

                case BOTTOM_PANEL:
                    m_InnerSize.m_y += m_BottomInnerPanel->getSize().m_y;
                    m_InnerPosition.m_y -= m_BottomInnerPanel->getSize().m_y;
                    break;

                case LEFT_PANEL:
                    m_InnerSize.m_x += m_LeftInnerPanel->getSize().m_x;
                    m_InnerPosition.m_x -= m_LeftInnerPanel->getSize().m_x;
                    break;
            }
        }
        else {
            
            switch(panelPosition) {

                case TOP_PANEL:
                    m_InnerSize.m_y += m_TopOuterPanel->getSize().m_y;
                    m_OuterSize.m_y += m_TopOuterPanel->getSize().m_y;
                    break;

                case RIGHT_PANEL:

            }
        }
    }

}}}}