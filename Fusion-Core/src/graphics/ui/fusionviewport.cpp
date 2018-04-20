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
        m_InnerPosition(m_OuterPosition), m_InnerSize(m_OuterSize), m_ViewportSizeSignal(new ViewportSizeSignal())
    { 
        m_Position = m_OuterPosition;
        m_Size = m_OuterSize;
        m_Color = m_BackgroundColor.getColor();
    }

    FusionViewport::~FusionViewport() { }

    void FusionViewport::addPanel(bool panelType, int panelPosition, FusionPanel* panel) {

        if(panelType) {
            switch(panelPosition) {

                case TOP_PANEL:
                    m_TopInnerPanel = panel; 
                    m_TopInnerPanelSizeSignal = m_TopInnerPanel->getSizeSignal();
                    m_TopInnerPanelPositionSignal = m_TopInnerPanel->getPositionSignal();
                    m_InnerSize.m_y -= m_TopInnerPanel->getSize().m_y; 
                    break;

                case RIGHT_PANEL:
                    m_RightInnerPanel = panel;
                    m_RightInnerPanelSizeSignal = m_RightInnerPanel->getSizeSignal();
                    m_RightInnerPanelPositionSignal = m_RightInnerPanel->getPositionSignal();
                    m_InnerSize.m_x -= m_RightInnerPanel->getSize().m_x;
                    break;

                case BOTTOM_PANEL:
                    m_BottomInnerPanel = panel;
                    m_BottomInnerPanelSizeSignal = m_BottomInnerPanel->getSizeSignal();
                    m_BottomInnerPanelPositionSignal = m_BottomInnerPanel->getPositionSignal();
                    m_InnerSize.m_y -= m_BottomInnerPanel->getSize().m_y;
                    m_InnerPosition.m_y += m_BottomInnerPanel->getSize().m_y;
                    break;

                case LEFT_PANEL:
                    m_LeftInnerPanel = panel;
                    m_LeftInnerPanelSizeSignal = m_LeftInnerPanel->getSizeSignal();
                    m_LeftInnerPanelPositionSignal = m_LeftInnerPanel->getPositionSignal();
                    m_InnerSize.m_x -= m_LeftInnerPanel->getSize().m_x;
                    m_InnerPosition.m_x += m_LeftInnerPanel->getSize().m_x;
                    break;
            }
        } else {
            switch(panelPosition) {

                case TOP_PANEL:
                    m_TopOuterPanel = panel;
                    m_TopOuterPanelSizeSignal = m_TopOuterPanel->getSizeSignal();
                    m_TopOuterPanelPositionSignal = m_TopOuterPanel->getPositionSignal();
                    m_InnerSize.m_y -= m_TopOuterPanel->getSize().m_y;
                    m_OuterSize.m_y -= m_TopOuterPanel->getSize().m_y;
                    if(m_TopInnerPanel) m_TopInnerPanelPositionSignal->sendSignal(0.0f, -1 * m_TopOuterPanel->getSize().m_y);
                    break;

                case RIGHT_PANEL:
                    m_RightOuterPanel = panel;
                    m_RightOuterPanelSizeSignal = m_RightOuterPanel->getSizeSignal();
                    m_RightOuterPanelPositionSignal = m_RightOuterPanel->getPositionSignal();
                    m_InnerSize.m_x -= m_RightOuterPanel->getSize().m_x;
                    m_OuterSize.m_x -= m_RightOuterPanel->getSize().m_x;
                    if(m_RightInnerPanel) m_RightInnerPanelPositionSignal->sendSignal(-1 * m_RightOuterPanel->getSize().m_x, 0.0f);
                    break;

                case BOTTOM_PANEL:
                    m_BottomOuterPanel = panel;
                    m_BottomOuterPanelSizeSignal = m_BottomOuterPanel->getSizeSignal();
                    m_BottomOuterPanelPositionSignal = m_BottomOuterPanel->getPositionSignal();
                    m_InnerSize.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_InnerPosition.m_y += m_BottomOuterPanel->getSize().m_y;
                    m_OuterSize.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_OuterPosition.m_y += m_BottomOuterPanel->getSize().m_y;
                    if(m_BottomInnerPanel) m_BottomInnerPanelPositionSignal->sendSignal(0.0f, m_BottomOuterPanel->getSize().m_y);
                    break;

                case LEFT_PANEL:
                    m_LeftOuterPanel = panel;
                    m_LeftOuterPanelSizeSignal = m_LeftOuterPanel->getSizeSignal();
                    m_LeftOuterPanelPositionSignal = m_LeftOuterPanel->getPositionSignal();
                    m_InnerSize.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_InnerPosition.m_x += m_LeftOuterPanel->getSize().m_x;
                    m_OuterSize.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_OuterPosition.m_x += m_LeftOuterPanel->getSize().m_x;
                    if(m_LeftInnerPanel) m_LeftInnerPanelPositionSignal->sendSignal(m_LeftOuterPanel->getSize().m_x, 0.0f);
                    break;
            }
        }
    }

    void FusionViewport::hidePanel(bool panelType, int panelPosition) {

        if(panelType) {
            
            switch(panelPosition) {

                case TOP_PANEL:
                    math::vec2 size = m_TopInnerPanel->getShownSize();
                    m_TopInnerPanelSizeSignal->sendSignal(size.m_x, 0.0f);
                    m_InnerSize.m_y += m_TopInnerPanel->getSize().m_y; 
                    break;
                    
                case RIGHT_PANEL:
                    math::vec2 size = m_RightInnerPanel->getShownSize();
                    m_RightInnerPanelSizeSignal->sendSignal(0.0f, size.m_y);
                    m_InnerSize.m_x += m_RightInnerPanel->getSize().m_x;
                    break;

                case BOTTOM_PANEL:
                    math::vec2 size = m_BottomInnerPanel->getShownSize();
                    m_BottomInnerPanelSizeSignal->sendSignal(size.m_x, 0.0f);
                    m_InnerSize.m_y += m_BottomInnerPanel->getSize().m_y;
                    m_InnerPosition.m_y -= m_BottomInnerPanel->getSize().m_y;
                    break;

                case LEFT_PANEL:
                    math::vec2 size = m_LeftInnerPanel->getShownSize();
                    m_LeftInnerPanelSizeSignal->sendSignal(0.0f, size.m_y);
                    m_InnerSize.m_x += m_LeftInnerPanel->getSize().m_x;
                    m_InnerPosition.m_x -= m_LeftInnerPanel->getSize().m_x;
                    break;
            }
        } else {
            
            switch(panelPosition) {
//TODO fix these to update panel positions
                case TOP_PANEL:
                    math::vec2 size = m_TopOuterPanel->getShownSize();
                    m_TopOuterPanelSizeSignal->sendSignal(size.m_x, 0.0f);
                    m_InnerSize.m_y += m_TopOuterPanel->getSize().m_y;
                    m_OuterSize.m_y += m_TopOuterPanel->getSize().m_y;
                    break;

                case RIGHT_PANEL:
                    math::vec2 size = m_RightOuterPanel->getShownSize();
                    m_RightOuterPanelSizeSignal->sendSignal(0.0f, size.m_y);
                    m_InnerSize.m_x += m_RightOuterPanel->getSize().m_x;
                    m_OuterSize.m_x += m_RightOuterPanel->getSize().m_x;
                    break;

                case BOTTOM_PANEL:
                    math::vec2 size = m_BottomOuterPanel->getShownSize();
                    m_BottomOuterPanelSizeSignal->sendSignal(size.m_x, 0.0f);
                    m_InnerSize.m_y += m_BottomOuterPanel->getSize().m_y;
                    m_InnerPosition.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_OuterSize.m_y += m_BottomOuterPanel->getSize().m_y;
                    m_OuterPosition.m_y -= m_BottomOuterPanel->getSize().m_y;
                    break;

                case LEFT_PANEL:
                    math::vec2 size = m_LeftOuterPanel->getShownSize();
                    m_LeftOuterPanelSizeSignal->sendSignal(0.0f, size.m_y);
                    m_InnerSize.m_x += m_LeftOuterPanel->getSize().m_x;
                    m_InnerPosition.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_OuterSize.m_x += m_LeftOuterPanel->getSize().m_x;
                    m_OuterPosition.m_x -= m_LeftOuterPanel->getSize().m_x;
                    break;
            }
        }
    }

    void FusionViewport::showPanel(bool panelType, int panelPosition) {

        if(panelType) {

            switch(panelPosition) {

                case TOP_PANEL:
                    math::vec2 size = m_TopInnerPanel->getShownSize();
                    m_TopInnerPanelSizeSignal->sendSignal(size.m_x, size.m_y);
                    m_InnerSize.m_y -= m_TopInnerPanel->getSize().m_y;
                    break;
                
                case RIGHT_PANEL:
                    math::vec2 size = m_RightInnerPanel->getShownSize();
                    m_RightInnerPanelSizeSignal->sendSignal(size.m_x, size.m_y);
                    break;
                
                case BOTTOM_PANEL:
                    math::vec2 size = m_BottomInnerPanel->getShownSize();
                    m_BottomInnerPanelSizeSignal->sendSignal(size.m_x, size.m_y);
                    m_InnerSize.m_y -= size.m_y;
                    m_InnerPosition.m_y += size.m_y;
                    break;

                case LEFT_PANEL:
                    math::vec2 size = m_LeftInnerPanel->getShownSize();
                    m_LeftInnerPanelSizeSignal->sendSignal(size.m_x, size.m_y);
                    m_InnerSize.m_x -= size.m_x;
                    m_InnerPosition.m_x += size.m_x;
                    break;
            }
        } else {

            switch(panelPosition) {
//TODO fix these update panel positions
                case TOP_PANEL:
                    math::vec2 size = m_TopOuterPanel->getShownSize();
                    m_TopOuterPanelSizeSignal->sendSignal(size.m_x, size.m_y);
                    m_InnerSize.m_y -= size.m_y;
                    m_OuterSize.m_y -= size.m_y;
                    break;
                
                case RIGHT_PANEL:
                    math::vec2 size = m_RightOuterPanel->getShownSize();
                    m_RightOuterPanelSizeSignal->sendSignal(size.m_x, size.m_y);
                    m_InnerSize.m_x -= size.m_x;
                    m_OuterSize.m_x -= size.m_x;
                    break;

                case BOTTOM_PANEL:
                    math::vec2 size = m_BottomOuterPanel->getShownSize();
                    m_BottomOuterPanelSizeSignal->sendSignal(size.m_x, size.m_y);
                    m_InnerSize.m_y -= size.m_y;
                    m_InnerPosition.m_y += size.m_y;
                    m_OuterSize.m_y -= size.m_y;
                    m_OuterPosition.m_y += size.m_y;
                    break;
                
                case LEFT_PANEL:
                    math::vec2 size = m_LeftOuterPanel->getShownSize();
                    m_BottomOuterPanelSizeSignal->sendSignal(size.m_x, size.m_y);
                    m_InnerSize.m_x -= size.m_x;
                    m_InnerPosition.m_x += size.m_x;
                    m_OuterSize.m_x -= size.m_x;
                    m_OuterPosition.m_x += size.m_x;
                    break;
            }
        }
    }

    void FusionViewport::removePanel(bool panelType, int panelPosition) {
        
        hidePanel(panelType, panelPosition);

        if(panelType) {

            switch(panelPosition) {

                case TOP_PANEL:
                    delete m_TopInnerPanel;
                    delete m_TopInnerPanelSizeSignal;
                    m_TopInnerPanel = nullptr;
                    m_TopInnerPanelSizeSignal = nullptr;
                    break;

                case RIGHT_PANEL:
                    delete m_RightInnerPanel;
                    delete m_RightInnerPanelSizeSignal;
                    m_RightInnerPanel = nullptr;
                    m_RightInnerPanelSizeSignal = nullptr;
                    break;

                case BOTTOM_PANEL:
                    delete m_BottomInnerPanel;
                    delete m_BottomInnerPanelSizeSignal;
                    m_BottomInnerPanel = nullptr;
                    m_BottomInnerPanelSizeSignal = nullptr;
                    break;
                
                case LEFT_PANEL:
                    delete m_LeftInnerPanel;
                    delete m_LeftInnerPanelSizeSignal;
                    m_LeftInnerPanel = nullptr;
                    m_LeftInnerPanelSizeSignal = nullptr;
                    break;
            }
        } else {

            switch(panelPosition) {

                case TOP_PANEL:
                    delete m_TopOuterPanel;
                    delete m_TopOuterPanelSizeSignal;
                    m_TopOuterPanel = nullptr;
                    m_TopOuterPanelSizeSignal = nullptr;
                    break;

                case RIGHT_PANEL:
                    delete m_RightOuterPanel;
                    delete m_RightOuterPanelSizeSignal;
                    m_RightOuterPanel = nullptr;
                    m_RightOuterPanelSizeSignal = nullptr;
                    break;

                case BOTTOM_PANEL:
                    delete m_BottomOuterPanel;
                    delete m_BottomOuterPanelSizeSignal;
                    m_BottomOuterPanel = nullptr;
                    m_BottomOuterPanelSizeSignal = nullptr;
                    break;

                case LEFT_PANEL:
                    delete m_LeftOuterPanel;
                    delete m_LeftOuterPanelSizeSignal;
                    m_LeftOuterPanel = nullptr;
                    m_LeftOuterPanelSizeSignal = nullptr;
                    break;
            }
        }
    }

    void FusionViewport::update() {

        bool panelType;
        int panelPosition;
        float width, height, oldWidth, oldHeight;

        if(m_ViewportSizeSignal->getSignal(panelType, panelPosition, width, height, oldWidth, oldHeight)) {

            if(panelType) {

                switch(panelPosition) {

                    case TOP_PANEL:
                        m_InnerSize.m_y -= (height - oldHeight);
                        break;

                    case RIGHT_PANEL:
                        m_InnerSize.m_x -= (width = oldWidth);
                        break;
                    
                    case BOTTOM_PANEL:
                        m_InnerSize.m_y -= (height - oldHeight);
                        m_InnerPosition.m_y += (height - oldHeight);
                        break;
                    
                    case LEFT_PANEL:
                        m_InnerSize.m_x -= (width - oldWidth);
                        m_InnerPosition.m_x += (width - oldWidth);
                        break;
                }
            } else {

                switch(panelPosition) {

                    case TOP_PANEL:
                        m_InnerSize.m_y -= (height - oldHeight);
                        m_OuterSize.m_y -= (height - oldHeight);
                        break;
                    
                    case RIGHT_PANEL:
                        m_InnerSize.m_x -= (width - oldWidth);
                        m_OuterSize.m_x -= (width - oldWidth);
                        break;

                    case BOTTOM_PANEL:
                        m_InnerSize.m_y -= (height - oldHeight);
                        m_InnerPosition.m_y += (height - oldHeight);
                        m_OuterSize.m_y -= (height - oldHeight);
                        m_OuterPosition.m_y += (height - oldHeight);
                        break;

                    case LEFT_PANEL:
                        m_InnerSize.m_x -= (width - oldWidth);
                        m_InnerPosition.m_x += (width - oldWidth);
                        m_OuterSize.m_x -= (width - oldWidth);
                        m_OuterPosition.m_x += (width - oldWidth);
                        break;
                }
            }
            m_ViewportSizeSignal->resetSignal();
        }
        else if(m_ViewportSizeSignal->getSignal(width, height)) {

            width /= m_Size.m_x;
            height /= m_Size.m_y;
            scale(math::vec2(width, height));
            m_ViewportSizeSignal->resetSignal();
        }

        if(m_TopInnerPanel) m_TopInnerPanel->update();
        if(m_RightInnerPanel) m_RightInnerPanel->update();
        if(m_BottomInnerPanel) m_BottomInnerPanel->update();
        if(m_LeftInnerPanel) m_LeftInnerPanel->update();
        
        if(m_TopOuterPanel) m_TopOuterPanel->update();
        if(m_RightOuterPanel) m_RightOuterPanel->update();
        if(m_BottomOuterPanel) m_BottomOuterPanel->update();
        if(m_LeftOuterPanel) m_LeftOuterPanel->update();
    }

    void FusionViewport::scale(math::vec2 scale) {

        math::vec2 outerSize = math::vec2(m_Size.m_x * scale.m_x, m_Size.m_y * scale.m_y);
        math::vec2 innerSize = math::vec2(m_InnerSize.m_x * scale.m_x, m_InnerSize.m_x * scale.m_y);

        if(m_TopInnerPanel) m_TopInnerPanel->scale(scale);
        if(m_TopOuterPanel) m_TopOuterPanel->scale(scale);
        if(m_RightInnerPanel) m_RightInnerPanel->scale(scale);
        if(m_RightOuterPanel) m_RightOuterPanel->scale(scale);
    }


}}}}