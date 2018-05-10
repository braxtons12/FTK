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
        m_InnerPosition(m_OuterPosition), m_InnerSize(m_OuterSize)
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
                    m_TopInnerPanelSizeSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelSize,
																							   m_TopInnerPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_SizeChanged);
                    m_TopInnerPanelPositionSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelPosition,
																									   m_TopInnerPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_PositionChanged);
                    m_InnerSize.m_y -= m_TopInnerPanel->getSize().m_y;
					m_TopInnerPanel->setUpdateViewportSizeSignalIndex(connect(m_TopInnerPanel,
															(std::array<float, 6> (FTKObject::*)(std::array<float, 6>))&FtkPanel::updateViewportSize,
															this, (void (FTKObject::*)(std::array<float, 6>))&FtkViewport::on_ViewportPanelResized));
                    break;

                case RIGHT_PANEL:
                    m_RightInnerPanel = panel;
                    m_RightInnerPanelSizeSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelSize,
																								   m_RightInnerPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_SizeChanged);
                    m_RightInnerPanelPositionSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelPosition,
																									   	 m_RightInnerPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_PositionChanged);
                    m_InnerSize.m_x -= m_RightInnerPanel->getSize().m_x;
					m_RightInnerPanel->setUpdateViewportSizeSignalIndex(connect(m_RightInnerPanel,
															(std::array<float, 6> (FTKObject::*)(std::array<float, 6>))&FtkPanel::updateViewportSize,
															this, (void (FTKObject::*)(std::array<float, 6>))&FtkViewport::on_ViewportPanelResized));
                    break;

                case BOTTOM_PANEL:
                    m_BottomInnerPanel = panel;
                    m_BottomInnerPanelSizeSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelSize,
																								   	  m_BottomInnerPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_SizeChanged);
                    m_BottomInnerPanelPositionSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelPosition,
																									   	 	  m_BottomInnerPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_PositionChanged);
                    m_InnerSize.m_y -= m_BottomInnerPanel->getSize().m_y;
                    m_InnerPosition.m_y += m_BottomInnerPanel->getSize().m_y;
					m_BottomInnerPanel->setUpdateViewportSizeSignalIndex(connect(m_BottomInnerPanel,
															(std::array<float, 6> (FTKObject::*)(std::array<float, 6>))&FtkPanel::updateViewportSize,
															this, (void (FTKObject::*)(std::array<float, 6>))&FtkViewport::on_ViewportPanelResized));
                    break;

                case LEFT_PANEL:
                    m_LeftInnerPanel = panel;
                    m_LeftInnerPanelSizeSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelSize,
																								m_LeftInnerPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_SizeChanged);
                    m_LeftInnerPanelPositionSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelPosition,
																									   m_LeftInnerPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_PositionChanged);
                    m_InnerSize.m_x -= m_LeftInnerPanel->getSize().m_x;
                    m_InnerPosition.m_x += m_LeftInnerPanel->getSize().m_x;
					m_LeftInnerPanel->setUpdateViewportSizeSignalIndex(connect(m_LeftInnerPanel,
															(std::array<float, 6> (FTKObject::*)(std::array<float, 6>))&FtkPanel::updateViewportSize,
															this, (void (FTKObject::*)(std::array<float, 6>))&FtkViewport::on_ViewportPanelResized));
                    break;
            }
        } else {
            switch(panelPosition) {

                case TOP_PANEL:
                    m_TopOuterPanel = panel;
                    m_TopOuterPanelSizeSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelSize,
																								m_TopOuterPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_SizeChanged);
                    m_TopOuterPanelPositionSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelPosition,
																									    m_TopOuterPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_PositionChanged);
                    m_InnerSize.m_y -= m_TopOuterPanel->getSize().m_y;
                    m_OuterSize.m_y -= m_TopOuterPanel->getSize().m_y;
                    if(m_TopInnerPanel) {
						math::vec2 position(0.0f, -1 * m_TopOuterPanel->getSize().m_y);
						emitVec2(m_TopInnerPanelPositionSignal, position);
					}
					m_TopOuterPanel->setUpdateViewportSizeSignalIndex(connect(m_TopOuterPanel,
															(std::array<float, 6> (FTKObject::*)(std::array<float, 6>))&FtkPanel::updateViewportSize,
															this, (void (FTKObject::*)(std::array<float, 6>))&FtkViewport::on_ViewportPanelResized));
                    break;

                case RIGHT_PANEL:
                    m_RightOuterPanel = panel;
                    m_RightOuterPanelSizeSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelSize,
																									m_RightOuterPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_SizeChanged);
                    m_RightOuterPanelPositionSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelPosition,
																									       m_RightOuterPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_PositionChanged);
                    m_InnerSize.m_x -= m_RightOuterPanel->getSize().m_x;
                    m_OuterSize.m_x -= m_RightOuterPanel->getSize().m_x;
                    if(m_RightInnerPanel) {
						math::vec2 position(-1 * m_RightOuterPanel->getSize().m_x, 0.0f);
						emitVec2(m_RightInnerPanelPositionSignal, position);
					}
					m_RightOuterPanel->setUpdateViewportSizeSignalIndex(connect(m_RightOuterPanel,
															(std::array<float, 6> (FTKObject::*)(std::array<float, 6>))&FtkPanel::updateViewportSize,
															this, (void (FTKObject::*)(std::array<float, 6>))&FtkViewport::on_ViewportPanelResized));
                    break;

                case BOTTOM_PANEL:
                    m_BottomOuterPanel = panel;
                    m_BottomOuterPanelSizeSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelSize,
																										m_BottomOuterPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_SizeChanged);
                    m_BottomOuterPanelPositionSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelPosition,
																									    	   m_BottomOuterPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_PositionChanged);
                    m_InnerSize.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_InnerPosition.m_y += m_BottomOuterPanel->getSize().m_y;
                    m_OuterSize.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_OuterPosition.m_y += m_BottomOuterPanel->getSize().m_y;
                    if(m_BottomInnerPanel) {
						math::vec2 position(0.0f, m_BottomOuterPanel->getSize().m_y);
						emitVec2(m_BottomInnerPanelPositionSignal, position);
					}
					m_BottomOuterPanel->setUpdateViewportSizeSignalIndex(connect(m_BottomOuterPanel,
															(std::array<float, 6> (FTKObject::*)(std::array<float, 6>))&FtkPanel::updateViewportSize,
															this, (void (FTKObject::*)(std::array<float, 6>))&FtkViewport::on_ViewportPanelResized));
                    break;

                case LEFT_PANEL:
                    m_LeftOuterPanel = panel;
                    m_LeftOuterPanelSizeSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelSize,
																								 m_LeftOuterPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_SizeChanged);
                    m_LeftOuterPanelPositionSignal = connect(this, (math::vec2 (FTKObject::*)(math::vec2))&FtkViewport::updatePanelPosition,
																									    m_LeftOuterPanel, (void (FTKObject::*)(math::vec2))&FtkPanel::on_PositionChanged);
                    m_InnerSize.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_InnerPosition.m_x += m_LeftOuterPanel->getSize().m_x;
                    m_OuterSize.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_OuterPosition.m_x += m_LeftOuterPanel->getSize().m_x;
                    if(m_LeftInnerPanel) {
						math::vec2 position(m_LeftOuterPanel->getSize().m_x, 0.0f);
						emitVec2(m_LeftInnerPanelPositionSignal, position);
					}
					m_LeftOuterPanel->setUpdateViewportSizeSignalIndex(connect(m_LeftOuterPanel,
															(std::array<float, 6> (FTKObject::*)(std::array<float, 6>))&FtkPanel::updateViewportSize,
															this, (void (FTKObject::*)(std::array<float, 6>))&FtkViewport::on_ViewportPanelResized));
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
                    emitVec2(m_TopInnerPanelSizeSignal, size);
                    m_InnerSize.m_y += m_TopInnerPanel->getSize().m_y;
                    break;

                case RIGHT_PANEL:
                    size = math::vec2(0.0f, m_RightInnerPanel->getShownSize().m_y);
                    emitVec2(m_RightInnerPanelSizeSignal, size);
                    m_InnerSize.m_x += m_RightInnerPanel->getSize().m_x;
                    break;

                case BOTTOM_PANEL:
                    size = math::vec2(m_BottomInnerPanel->getShownSize().m_x, 0.0f);
                    emitVec2(m_BottomInnerPanelSizeSignal, size);
                    m_InnerSize.m_y += m_BottomInnerPanel->getSize().m_y;
                    m_InnerPosition.m_y -= m_BottomInnerPanel->getSize().m_y;
                    break;

                case LEFT_PANEL:
                    size = math::vec2(0.0f, m_LeftInnerPanel->getShownSize().m_y);
                    emitVec2(m_LeftInnerPanelSizeSignal, size);
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
					emitVec2(m_TopOuterPanelSizeSignal, size);
					emitVec2(m_TopInnerPanelPositionSignal, position);
                    break;

                case RIGHT_PANEL:
                    size = math::vec2(0.0f, m_RightOuterPanel->getShownSize().m_y);
					position = math::vec2(m_RightOuterPanel->getPosition().m_x, m_RightInnerPanel->getPosition().m_y);
                    m_InnerSize.m_x += m_RightOuterPanel->getSize().m_x;
                    m_OuterSize.m_x += m_RightOuterPanel->getSize().m_x;
					emitVec2(m_RightOuterPanelSizeSignal, size);
					emitVec2(m_RightInnerPanelPositionSignal, position);
                    break;

                case BOTTOM_PANEL:
                    size = math::vec2(m_BottomOuterPanel->getShownSize().m_x, 0.0f);
					position = math::vec2(m_BottomInnerPanel->getPosition().m_x, m_BottomOuterPanel->getPosition().m_y);
                    m_InnerSize.m_y += m_BottomOuterPanel->getSize().m_y;
                    m_InnerPosition.m_y -= m_BottomOuterPanel->getSize().m_y;
                    m_OuterSize.m_y += m_BottomOuterPanel->getSize().m_y;
                    m_OuterPosition.m_y -= m_BottomOuterPanel->getSize().m_y;
					emitVec2(m_BottomOuterPanelSizeSignal, size);
					emitVec2(m_BottomInnerPanelPositionSignal, position);
                    break;

                case LEFT_PANEL:
                    size = math::vec2(0.0f, m_LeftOuterPanel->getShownSize().m_y);
					position = math::vec2(m_LeftOuterPanel->getPosition().m_x, m_LeftInnerPanel->getPosition().m_y);
                    m_InnerSize.m_x += m_LeftOuterPanel->getSize().m_x;
                    m_InnerPosition.m_x -= m_LeftOuterPanel->getSize().m_x;
                    m_OuterSize.m_x += m_LeftOuterPanel->getSize().m_x;
                    m_OuterPosition.m_x -= m_LeftOuterPanel->getSize().m_x;
					emitVec2(m_LeftOuterPanelSizeSignal, size);
					emitVec2(m_LeftInnerPanelPositionSignal, position);
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
                    emitVec2(m_TopInnerPanelSizeSignal, size);
                    m_InnerSize.m_y -= m_TopInnerPanel->getSize().m_y;
                    break;

                case RIGHT_PANEL:
                    size = m_RightInnerPanel->getShownSize();
                    emitVec2(m_RightInnerPanelSizeSignal, size);
                    break;

                case BOTTOM_PANEL:
                    size = m_BottomInnerPanel->getShownSize();
                    emitVec2(m_BottomInnerPanelSizeSignal, size);
                    m_InnerSize.m_y -= size.m_y;
                    m_InnerPosition.m_y += size.m_y;
                    break;

                case LEFT_PANEL:
                    size = m_LeftInnerPanel->getShownSize();
                    emitVec2(m_LeftInnerPanelSizeSignal, size);
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
					emitVec2(m_TopOuterPanelSizeSignal, size);
					emitVec2(m_TopInnerPanelPositionSignal, position);
                    break;

                case RIGHT_PANEL:
                    size = m_RightOuterPanel->getShownSize();
					position = math::vec2(m_RightInnerPanel->getPosition().m_x - m_RightOuterPanel->getShownSize().m_x, m_RightInnerPanel->getPosition().m_y);
                    m_InnerSize.m_x -= size.m_x;
                    m_OuterSize.m_x -= size.m_x;
					emitVec2(m_RightOuterPanelSizeSignal, size);
					emitVec2(m_RightInnerPanelPositionSignal, position);
                    break;

                case BOTTOM_PANEL:
                    size = m_BottomOuterPanel->getShownSize();
					position = math::vec2(m_BottomInnerPanel->getPosition().m_x, m_BottomInnerPanel->getPosition().m_y - m_BottomOuterPanel->getShownSize().m_y);
                    m_InnerSize.m_y -= size.m_y;
                    m_InnerPosition.m_y += size.m_y;
                    m_OuterSize.m_y -= size.m_y;
                    m_OuterPosition.m_y += size.m_y;
					emitVec2(m_BottomOuterPanelSizeSignal, size);
					emitVec2(m_BottomInnerPanelPositionSignal, position);
                    break;

                case LEFT_PANEL:
                    size = m_LeftOuterPanel->getShownSize();
					position = math::vec2(m_LeftInnerPanel->getPosition().m_x - m_LeftOuterPanel->getShownSize().m_x, m_LeftInnerPanel->getPosition().m_y);
                    m_InnerSize.m_x -= size.m_x;
                    m_InnerPosition.m_x += size.m_x;
                    m_OuterSize.m_x -= size.m_x;
                    m_OuterPosition.m_x += size.m_x;
					emitVec2(m_LeftOuterPanelSizeSignal, size);
					emitVec2(m_LeftInnerPanelPositionSignal, position);
                    break;
            }
        }
    }

    void FtkViewport::removePanel(bool panelType, int panelPosition) {

        hidePanel(panelType, panelPosition);

        if(panelType) {

            switch(panelPosition) {

                case TOP_PANEL:
					disconnect(VEC2_SIGNAL, m_TopInnerPanelSizeSignal);
					disconnect(VEC2_SIGNAL, m_TopInnerPanelPositionSignal);
                    delete m_TopInnerPanel;
                    m_TopInnerPanel = nullptr;
                    break;

                case RIGHT_PANEL:
					disconnect(VEC2_SIGNAL, m_RightInnerPanelSizeSignal);
					disconnect(VEC2_SIGNAL, m_RightInnerPanelPositionSignal);
                    delete m_RightInnerPanel;
                    m_RightInnerPanel = nullptr;
                    break;

                case BOTTOM_PANEL:
					disconnect(VEC2_SIGNAL, m_BottomInnerPanelSizeSignal);
					disconnect(VEC2_SIGNAL, m_BottomInnerPanelPositionSignal);
                    delete m_BottomInnerPanel;
                    m_BottomInnerPanel = nullptr;
                    break;

                case LEFT_PANEL:
					disconnect(VEC2_SIGNAL, m_LeftInnerPanelSizeSignal);
					disconnect(VEC2_SIGNAL, m_LeftInnerPanelPositionSignal);
                    delete m_LeftInnerPanel;
                    m_LeftInnerPanel = nullptr;
                    break;
            }
        } else {

            switch(panelPosition) {

                case TOP_PANEL:
					disconnect(VEC2_SIGNAL, m_TopOuterPanelSizeSignal);
					disconnect(VEC2_SIGNAL, m_TopOuterPanelPositionSignal);
                    delete m_TopOuterPanel;
                    m_TopOuterPanel = nullptr;
                    break;

                case RIGHT_PANEL:
					disconnect(VEC2_SIGNAL, m_RightOuterPanelSizeSignal);
					disconnect(VEC2_SIGNAL, m_RightOuterPanelPositionSignal);
                    delete m_RightOuterPanel;
                    m_RightOuterPanel = nullptr;
                    break;

                case BOTTOM_PANEL:
					disconnect(VEC2_SIGNAL, m_BottomOuterPanelSizeSignal);
					disconnect(VEC2_SIGNAL, m_BottomOuterPanelPositionSignal);
                    delete m_BottomOuterPanel;
                    m_BottomOuterPanel = nullptr;
                    break;

                case LEFT_PANEL:
					disconnect(VEC2_SIGNAL, m_LeftOuterPanelSizeSignal);
					disconnect(VEC2_SIGNAL, m_LeftOuterPanelPositionSignal);
                    delete m_LeftOuterPanel;
                    m_LeftOuterPanel = nullptr;
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

	void FtkViewport::on_ViewportPanelResized(std::array<float, 6> sig) {

		switch((int)(sig[0] + 0.5)) {

			case OUTER_PANEL: {

				switch((int)(sig[1] + 0.5)) {

					case TOP_PANEL:
						m_InnerSize.m_y -= (sig[3] - sig[5]);
						break;

					case RIGHT_PANEL:
						m_InnerSize.m_x -= (sig[2] - sig[4]);
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
		}
	}

	void FtkViewport::on_ViewportResized(math::vec2 sig) {

		float width = sig.m_x / m_Size.m_x;
		float height = sig.m_y / m_Size.m_y;
		scale(math::vec2(width, height));
	}
}}}}
