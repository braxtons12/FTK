#include "ftkviewport.h"

namespace ftk { namespace core { namespace graphics { namespace ui {

    bool FtkViewport::checkBounds(Renderable2D* renderable) {

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

    void FtkViewport::submitPanels(Renderer2D* renderer) {

        if(m_RightInnerPanel) m_RightInnerPanel->submit(renderer);
        if(m_RightOuterPanel) m_RightOuterPanel->submit(renderer);
        if(m_LeftInnerPanel) m_LeftInnerPanel->submit(renderer);
        if(m_LeftOuterPanel) m_LeftOuterPanel->submit(renderer);
        if(m_TopInnerPanel) m_TopInnerPanel->submit(renderer);
        if(m_TopOuterPanel) m_TopOuterPanel->submit(renderer);
        if(m_BottomInnerPanel) m_BottomInnerPanel->submit(renderer);
        if(m_BottomOuterPanel) m_BottomOuterPanel->submit(renderer);
    }

    FtkViewport::FtkViewport(math::vec3 position, math::vec2 size, Color backgroundColor)
        : Group(math::mat4::identity()), m_OuterPosition(position), m_OuterSize(size), m_BackgroundColor(backgroundColor),
        m_InnerPosition(m_OuterPosition), m_InnerSize(m_OuterSize),
        m_ViewportSizeSignal(new Signal<FtkViewport, FtkPanel, std::array<float, 6>, void, std::array<float, 6>>())
    { 
        m_Position = m_OuterPosition;
        m_Size = m_OuterSize;
        m_Color = m_BackgroundColor.getColor();
    }

    FtkViewport::~FtkViewport() { }

    void FtkViewport::addPanel(bool panelType, int panelPosition, FtkPanel* panel) {

        if(panelType) {
            switch(panelPosition) {

                case TOP_PANEL:
                    m_TopInnerPanel = panel; 
                    m_TopInnerPanelSizeSignal = m_TopInnerPanel->getSizeSignal();
                    m_TopInnerPanelPositionSignal = m_TopInnerPanel->getPositionSignal();
					m_TopInnerPanelSizeSignal->connect(this, &FtkViewport::updatePanelSize, 
													   m_TopInnerPanel, &FtkPanel::on_SizeChanged);
					m_TopInnerPanelPositionSignal->connect(this, &FtkViewport::updatePanelPosition, 
													   m_TopInnerPanel, &FtkPanel::on_PositionChanged);
                    m_InnerSize.m_y -= m_TopInnerPanel->getSize().m_y;
                    break;

                case RIGHT_PANEL:
                    m_RightInnerPanel = panel;
                    m_RightInnerPanelSizeSignal = m_RightInnerPanel->getSizeSignal();
                    m_RightInnerPanelPositionSignal = m_RightInnerPanel->getPositionSignal();
					m_RightInnerPanelSizeSignal->connect(this, &FtkViewport::updatePanelSize, 
													   m_RightInnerPanel, &FtkPanel::on_SizeChanged);
					m_RightInnerPanelPositionSignal->connect(this, &FtkViewport::updatePanelPosition, 
													   m_RightInnerPanel, &FtkPanel::on_PositionChanged);
                    m_InnerSize.m_x -= m_RightInnerPanel->getSize().m_x;
                    break;

                case BOTTOM_PANEL:
                    m_BottomInnerPanel = panel;
                    m_BottomInnerPanelSizeSignal = m_BottomInnerPanel->getSizeSignal();
                    m_BottomInnerPanelPositionSignal = m_BottomInnerPanel->getPositionSignal();
					m_BottomInnerPanelSizeSignal->connect(this, &FtkViewport::updatePanelSize, 
													   m_BottomInnerPanel, &FtkPanel::on_SizeChanged);
					m_BottomInnerPanelPositionSignal->connect(this, &FtkViewport::updatePanelPosition, 
													   m_BottomInnerPanel, &FtkPanel::on_PositionChanged);
                    m_InnerSize.m_y -= m_BottomInnerPanel->getSize().m_y;
                    m_InnerPosition.m_y += m_BottomInnerPanel->getSize().m_y;
                    break;

                case LEFT_PANEL:
                    m_LeftInnerPanel = panel;
                    m_LeftInnerPanelSizeSignal = m_LeftInnerPanel->getSizeSignal();
                    m_LeftInnerPanelPositionSignal = m_LeftInnerPanel->getPositionSignal();
					m_LeftInnerPanelSizeSignal->connect(this, &FtkViewport::updatePanelSize, 
													   m_LeftInnerPanel, &FtkPanel::on_SizeChanged);
					m_LeftInnerPanelPositionSignal->connect(this, &FtkViewport::updatePanelPosition, 
													   m_LeftInnerPanel, &FtkPanel::on_PositionChanged);
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
					m_TopOuterPanelSizeSignal->connect(this, &FtkViewport::updatePanelSize, 
													   m_TopOuterPanel, &FtkPanel::on_SizeChanged);
					m_TopOuterPanelPositionSignal->connect(this, &FtkViewport::updatePanelPosition, 
													   m_TopOuterPanel, &FtkPanel::on_PositionChanged);
                    m_InnerSize.m_y -= m_TopOuterPanel->getSize().m_y;
                    m_OuterSize.m_y -= m_TopOuterPanel->getSize().m_y;
                    if(m_TopInnerPanel) {
						math::vec2 position(0.0f, -1 * m_TopOuterPanel->getSize().m_y);
						(*m_TopInnerPanelPositionSignal)(position);
					}
                    break;

                case RIGHT_PANEL:
                    m_RightOuterPanel = panel;
                    m_RightOuterPanelSizeSignal = m_RightOuterPanel->getSizeSignal();
                    m_RightOuterPanelPositionSignal = m_RightOuterPanel->getPositionSignal();
					m_RightOuterPanelSizeSignal->connect(this, &FtkViewport::updatePanelSize, 
													   m_RightOuterPanel, &FtkPanel::on_SizeChanged);
					m_RightOuterPanelPositionSignal->connect(this, &FtkViewport::updatePanelPosition, 
													   m_RightOuterPanel, &FtkPanel::on_PositionChanged);
                    m_InnerSize.m_x -= m_RightOuterPanel->getSize().m_x;
                    m_OuterSize.m_x -= m_RightOuterPanel->getSize().m_x;
                    if(m_RightInnerPanel) {
						math::vec2 position(-1 * m_RightOuterPanel->getSize().m_x, 0.0f);
						(*m_RightInnerPanelPositionSignal)(position);
					}
                    break;

                case BOTTOM_PANEL:
                    m_BottomOuterPanel = panel;
                    m_BottomOuterPanelSizeSignal = m_BottomOuterPanel->getSizeSignal();
                    m_BottomOuterPanelPositionSignal = m_BottomOuterPanel->getPositionSignal();
					m_BottomOuterPanelSizeSignal->connect(this, &FtkViewport::updatePanelSize, 
													   m_BottomOuterPanel, &FtkPanel::on_SizeChanged);
					m_BottomOuterPanelPositionSignal->connect(this, &FtkViewport::updatePanelPosition, 
													   m_BottomOuterPanel, &FtkPanel::on_PositionChanged);
                    m_InnerSize.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_InnerPosition.m_y += m_BottomOuterPanel->getSize().m_y;
                    m_OuterSize.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_OuterPosition.m_y += m_BottomOuterPanel->getSize().m_y;
                    if(m_BottomInnerPanel) {
						math::vec2 position(0.0f, m_BottomOuterPanel->getSize().m_y);
						(*m_BottomInnerPanelPositionSignal)(position);
					}
                    break;

                case LEFT_PANEL:
                    m_LeftOuterPanel = panel;
                    m_LeftOuterPanelSizeSignal = m_LeftOuterPanel->getSizeSignal();
                    m_LeftOuterPanelPositionSignal = m_LeftOuterPanel->getPositionSignal();
					m_LeftOuterPanelSizeSignal->connect(this, &FtkViewport::updatePanelSize, 
													   m_LeftOuterPanel, &FtkPanel::on_SizeChanged);
					m_LeftOuterPanelPositionSignal->connect(this, &FtkViewport::updatePanelPosition, 
													   m_LeftOuterPanel, &FtkPanel::on_PositionChanged);
                    m_InnerSize.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_InnerPosition.m_x += m_LeftOuterPanel->getSize().m_x;
                    m_OuterSize.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_OuterPosition.m_x += m_LeftOuterPanel->getSize().m_x;
                    if(m_LeftInnerPanel) {
						math::vec2 position(m_LeftOuterPanel->getSize().m_x, 0.0f);
						(*m_LeftInnerPanelPositionSignal)(position);
					}
                    break;
            }
        }
    }

    void FtkViewport::hidePanel(bool panelType, int panelPosition) {

		math::vec2 size;
		math::vec2 position;
        if(panelType) {
            
            switch(panelPosition) {

                case TOP_PANEL:
                    size = math::vec2(m_TopInnerPanel->getShownSize().m_x, 0.0f);
                    (*m_TopInnerPanelSizeSignal)(size);
                    m_InnerSize.m_y += m_TopInnerPanel->getSize().m_y; 
                    break;
                    
                case RIGHT_PANEL:
                    size = math::vec2(0.0f, m_RightInnerPanel->getShownSize().m_y);
                    (*m_RightInnerPanelSizeSignal)(size);
                    m_InnerSize.m_x += m_RightInnerPanel->getSize().m_x;
                    break;

                case BOTTOM_PANEL:
                    size = math::vec2(m_BottomInnerPanel->getShownSize().m_x, 0.0f);
                    (*m_BottomInnerPanelSizeSignal)(size);
                    m_InnerSize.m_y += m_BottomInnerPanel->getSize().m_y;
                    m_InnerPosition.m_y -= m_BottomInnerPanel->getSize().m_y;
                    break;

                case LEFT_PANEL:
                    size = math::vec2(0.0f, m_LeftInnerPanel->getShownSize().m_y);
                    (*m_LeftInnerPanelSizeSignal)(size);
                    m_InnerSize.m_x += m_LeftInnerPanel->getSize().m_x;
                    m_InnerPosition.m_x -= m_LeftInnerPanel->getSize().m_x;
                    break;
            }
        } else {
            
            switch(panelPosition) {
				
                case TOP_PANEL:
					size = math::vec2(m_TopOuterPanel->getShownSize().m_x, 0.0f);
					position = math::vec2(m_TopInnerPanel->getPosition().m_x, m_TopOuterPanel->getPosition().m_y);
                    m_InnerSize.m_y += m_TopOuterPanel->getSize().m_y;
                    m_OuterSize.m_y += m_TopOuterPanel->getSize().m_y;
					(*m_TopOuterPanelSizeSignal)(size);
					(*m_TopInnerPanelPositionSignal)(position);
                    break;

                case RIGHT_PANEL:
                    size = math::vec2(0.0f, m_RightOuterPanel->getShownSize().m_y);
					position = math::vec2(m_RightOuterPanel->getPosition().m_x, m_RightInnerPanel->getPosition().m_y);
                    m_InnerSize.m_x += m_RightOuterPanel->getSize().m_x;
                    m_OuterSize.m_x += m_RightOuterPanel->getSize().m_x;
					(*m_RightOuterPanelSizeSignal)(size);
					(*m_RightInnerPanelPositionSignal)(position);
                    break;

                case BOTTOM_PANEL:
                    size = math::vec2(m_BottomOuterPanel->getShownSize().m_x, 0.0f);
					position = math::vec2(m_BottomInnerPanel->getPosition().m_x, m_BottomOuterPanel->getPosition().m_y);
                    m_InnerSize.m_y += m_BottomOuterPanel->getSize().m_y;
                    m_InnerPosition.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_OuterSize.m_y += m_BottomOuterPanel->getSize().m_y;
                    m_OuterPosition.m_y -= m_BottomOuterPanel->getSize().m_y;
					(*m_BottomOuterPanelSizeSignal)(size);
					(*m_BottomInnerPanelPositionSignal)(position);
                    break;

                case LEFT_PANEL:
                    size = math::vec2(0.0f, m_LeftOuterPanel->getShownSize().m_y);
					position = math::vec2(m_LeftOuterPanel->getPosition().m_x, m_LeftInnerPanel->getPosition().m_y);
                    m_InnerSize.m_x += m_LeftOuterPanel->getSize().m_x;
                    m_InnerPosition.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_OuterSize.m_x += m_LeftOuterPanel->getSize().m_x;
                    m_OuterPosition.m_x -= m_LeftOuterPanel->getSize().m_x;
					(*m_LeftOuterPanelSizeSignal)(size);
					(*m_LeftInnerPanelPositionSignal)(position);
                    break;
            }
        }
    }

    void FtkViewport::showPanel(bool panelType, int panelPosition) {
	
		math::vec2 size;
		math::vec2 position;
        if(panelType) {

            switch(panelPosition) {

                case TOP_PANEL:
                    size = m_TopInnerPanel->getShownSize();
                    (*m_TopInnerPanelSizeSignal)(size);
                    m_InnerSize.m_y -= m_TopInnerPanel->getSize().m_y;
                    break;
                
                case RIGHT_PANEL:
                    size = m_RightInnerPanel->getShownSize();
                    (*m_RightInnerPanelSizeSignal)(size);
                    break;
                
                case BOTTOM_PANEL:
                    size = m_BottomInnerPanel->getShownSize();
                    (*m_BottomInnerPanelSizeSignal)(size);
                    m_InnerSize.m_y -= size.m_y;
                    m_InnerPosition.m_y += size.m_y;
                    break;

                case LEFT_PANEL:
                    size = m_LeftInnerPanel->getShownSize();
                    (*m_LeftInnerPanelSizeSignal)(size);
                    m_InnerSize.m_x -= size.m_x;
                    m_InnerPosition.m_x += size.m_x;
                    break;
            }
        } else {

            switch(panelPosition) {

                case TOP_PANEL:
                    size = m_TopOuterPanel->getShownSize();
					position = math::vec2(m_TopInnerPanel->getPosition().m_x, m_TopInnerPanel->getPosition().m_y - m_TopOuterPanel->getShownSize().m_y);
                    m_InnerSize.m_y -= size.m_y;
                    m_OuterSize.m_y -= size.m_y;
					(*m_TopOuterPanelSizeSignal)(size);
					(*m_TopInnerPanelPositionSignal)(position);
                    break;
                
                case RIGHT_PANEL:
                    size = m_RightOuterPanel->getShownSize();
					position = math::vec2(m_RightInnerPanel->getPosition().m_x - m_RightOuterPanel->getShownSize().m_x, m_RightInnerPanel->getPosition().m_y);
                    m_InnerSize.m_x -= size.m_x;
                    m_OuterSize.m_x -= size.m_x;
					(*m_RightOuterPanelSizeSignal)(size);
					(*m_RightInnerPanelPositionSignal)(position);
                    break;

                case BOTTOM_PANEL:
                    size = m_BottomOuterPanel->getShownSize();
					position = math::vec2(m_BottomInnerPanel->getPosition().m_x, m_BottomInnerPanel->getPosition().m_y - m_BottomOuterPanel->getShownSize().m_y);
                    m_InnerSize.m_y -= size.m_y;
                    m_InnerPosition.m_y += size.m_y;
                    m_OuterSize.m_y -= size.m_y;
                    m_OuterPosition.m_y += size.m_y;
					(*m_BottomOuterPanelSizeSignal)(size);
					(*m_BottomInnerPanelPositionSignal)(position);
                    break;
                
                case LEFT_PANEL:
                    size = m_LeftOuterPanel->getShownSize();
					position = math::vec2(m_LeftInnerPanel->getPosition().m_x - m_LeftOuterPanel->getShownSize().m_x, m_LeftInnerPanel->getPosition().m_y);
                    m_InnerSize.m_x -= size.m_x;
                    m_InnerPosition.m_x += size.m_x;
                    m_OuterSize.m_x -= size.m_x;
                    m_OuterPosition.m_x += size.m_x;
					(*m_LeftOuterPanelSizeSignal)(size);
					(*m_LeftInnerPanelPositionSignal)(position);
                    break;
            }
        }
    }

    void FtkViewport::removePanel(bool panelType, int panelPosition) {
        
        hidePanel(panelType, panelPosition);

        if(panelType) {

            switch(panelPosition) {

                case TOP_PANEL:
					m_TopInnerPanelSizeSignal->disconnect();
					m_TopInnerPanelPositionSignal->disconnect();
                    delete m_TopInnerPanel;
                    delete m_TopInnerPanelSizeSignal;
                    m_TopInnerPanel = nullptr;
                    m_TopInnerPanelSizeSignal = nullptr;
                    break;

                case RIGHT_PANEL:
					m_RightInnerPanelSizeSignal->disconnect();
					m_RightInnerPanelPositionSignal->disconnect();
                    delete m_RightInnerPanel;
                    delete m_RightInnerPanelSizeSignal;
                    m_RightInnerPanel = nullptr;
                    m_RightInnerPanelSizeSignal = nullptr;
                    break;

                case BOTTOM_PANEL:
					m_BottomInnerPanelSizeSignal->disconnect();
					m_BottomInnerPanelPositionSignal->disconnect();
                    delete m_BottomInnerPanel;
                    delete m_BottomInnerPanelSizeSignal;
                    m_BottomInnerPanel = nullptr;
                    m_BottomInnerPanelSizeSignal = nullptr;
                    break;
                
                case LEFT_PANEL:
					m_LeftInnerPanelSizeSignal->disconnect();
					m_LeftInnerPanelPositionSignal->disconnect();
                    delete m_LeftInnerPanel;
                    delete m_LeftInnerPanelSizeSignal;
                    m_LeftInnerPanel = nullptr;
                    m_LeftInnerPanelSizeSignal = nullptr;
                    break;
            }
        } else {

            switch(panelPosition) {

                case TOP_PANEL:
					m_TopOuterPanelSizeSignal->disconnect();
					m_TopOuterPanelPositionSignal->disconnect();
                    delete m_TopOuterPanel;
                    delete m_TopOuterPanelSizeSignal;
                    m_TopOuterPanel = nullptr;
                    m_TopOuterPanelSizeSignal = nullptr;
                    break;

                case RIGHT_PANEL:
					m_RightOuterPanelSizeSignal->disconnect();
					m_RightOuterPanelPositionSignal->disconnect();
                    delete m_RightOuterPanel;
                    delete m_RightOuterPanelSizeSignal;
                    m_RightOuterPanel = nullptr;
                    m_RightOuterPanelSizeSignal = nullptr;
                    break;

                case BOTTOM_PANEL:
					m_BottomOuterPanelSizeSignal->disconnect();
					m_BottomOuterPanelPositionSignal->disconnect();
                    delete m_BottomOuterPanel;
                    delete m_BottomOuterPanelSizeSignal;
                    m_BottomOuterPanel = nullptr;
                    m_BottomOuterPanelSizeSignal = nullptr;
                    break;

                case LEFT_PANEL:
					m_LeftOuterPanelSizeSignal->disconnect();
					m_LeftOuterPanelPositionSignal->disconnect();
                    delete m_LeftOuterPanel;
                    delete m_LeftOuterPanelSizeSignal;
                    m_LeftOuterPanel = nullptr;
                    m_LeftOuterPanelSizeSignal = nullptr;
                    break;
            }
        }
    }

    void FtkViewport::update() {

        if(m_TopInnerPanel) m_TopInnerPanel->update();
        if(m_RightInnerPanel) m_RightInnerPanel->update();
        if(m_BottomInnerPanel) m_BottomInnerPanel->update();
        if(m_LeftInnerPanel) m_LeftInnerPanel->update();
        
        if(m_TopOuterPanel) m_TopOuterPanel->update();
        if(m_RightOuterPanel) m_RightOuterPanel->update();
        if(m_BottomOuterPanel) m_BottomOuterPanel->update();
        if(m_LeftOuterPanel) m_LeftOuterPanel->update();
    }

    void FtkViewport::scale(math::vec2 scale) {

		m_Size *= scale;
        m_OuterSize *= scale;
        m_InnerSize *= scale;

        if(m_TopInnerPanel) m_TopInnerPanel->scale(math::vec2(scale.m_x, 1.0f));
        if(m_TopOuterPanel) m_TopOuterPanel->scale(math::vec2(scale.m_x, 1.0f));
        if(m_RightInnerPanel) m_RightInnerPanel->scale(math::vec2(1.0f, scale.m_y));
        if(m_RightOuterPanel) m_RightOuterPanel->scale(math::vec2(1.0f, scale.m_y));
		if(m_BottomInnerPanel) m_BottomInnerPanel->scale(math::vec2(scale.m_x, 1.0f));
		if(m_BottomOuterPanel) m_BottomOuterPanel->scale(math::vec2(scale.m_x, 1.0f));
		if(m_LeftInnerPanel) m_LeftInnerPanel->scale(math::vec2(1.0f, scale.m_y));
		if(m_LeftOuterPanel) m_LeftOuterPanel->scale(math::vec2(1.0f, scale.m_y));
    }

	void FtkViewport::on_ViewportResized(std::array<float, 6> sig) {
		
		switch((int)(sig[0] + 0.5)) {
				
			case OUTER_PANEL: {
				
				switch((int)(sig[1] + 0.5)) {

					case TOP_PANEL:
						m_InnerSize.m_y -= (sig[3] - sig[5]);
						break;

					case RIGHT_PANEL:
						m_InnerSize.m_x -= (sig[2] = sig[4]);
						break;
					
					case BOTTOM_PANEL:
						m_InnerSize.m_y -= (sig[3] - sig[5]);
						m_InnerPosition.m_y += (sig[3] - sig[5]);
						break;
					
					case LEFT_PANEL:
						m_InnerSize.m_x -= (sig[2] - sig[4]);
						m_InnerPosition.m_x += (sig[2] - sig[4]);
						break;
				}
			}
			break;
				
			case INNER_PANEL: {
				switch((int)(sig[1] + 0.5)) {

					case TOP_PANEL:
						m_InnerSize.m_y -= (sig[3] - sig[5]);
						m_OuterSize.m_y -= (sig[3] - sig[5]);
						break;
					
					case RIGHT_PANEL:
						m_InnerSize.m_x -= (sig[2] - sig[4]);
						m_OuterSize.m_x -= (sig[2] - sig[4]);
						break;

					case BOTTOM_PANEL:
						m_InnerSize.m_y -= (sig[3] - sig[5]);
						m_InnerPosition.m_y += (sig[3] - sig[5]);
						m_OuterSize.m_y -= (sig[3] - sig[5]);
						m_OuterPosition.m_y += (sig[3] - sig[5]);
						break;

					case LEFT_PANEL:
						m_InnerSize.m_x -= (sig[2] - sig[4]);
						m_InnerPosition.m_x += (sig[2] - sig[4]);
						m_OuterSize.m_x -= (sig[2] - sig[4]);
						m_OuterPosition.m_x += (sig[2] - sig[4]);
						break;
				}
			}
			break;
			
			case NO_PANEL:
				
				float width = sig[2] / m_Size.m_x;
				float height = sig[3] / m_Size.m_y;
				scale(math::vec2(width, height));
				break;
		}
	}
}}}}
