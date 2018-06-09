#include "ftkpanel.h"

namespace ftk { namespace core { namespace graphics { namespace ui {

	FtkPanel::FtkPanel(math::vec3 position, math::vec2 size, Color backgroundColor,
						math::mat4 projectionMatrix, int type, int layoutPosition, FtkViewport* parentViewport,
						NativeWindow* parentWindow)
		: FtkGroup(position, size, backgroundColor.getColor(), projectionMatrix), m_Type(type),
		m_LayoutPosition(layoutPosition), m_ParentViewport(parentViewport),
		m_ParentWindow(parentWindow),
		m_DragHandle(FtkButton(math::vec3(0.0f, 0.0f, 0.0f), math::vec2(0.0f, 0.0f),
									   backgroundColor, backgroundColor, backgroundColor,
									   BUTTON_STATE_OFF, m_ParentWindow))
	{
		switch(layoutPosition) {

			case TOP_PANEL:
				m_DragHandle = FtkButton(m_Position, math::vec2(m_Size.m_x, 2.0f), backgroundColor,
											backgroundColor, Color(0.5f, 0.5f, 1.0f, 1.0f),
											BUTTON_STATE_NORMAL, m_ParentWindow);
				break;

			case RIGHT_PANEL:
				m_DragHandle = FtkButton(m_Position, math::vec2(2.0f, m_Size.m_y), backgroundColor,
											backgroundColor, Color(0.5f, 0.5f, 1.0f, 1.0f),
											BUTTON_STATE_NORMAL, m_ParentWindow);
				break;

			case BOTTOM_PANEL:
				m_DragHandle = FtkButton(m_Position + m_Size, math::vec2(m_Size.m_x, 2.0f),
											backgroundColor, backgroundColor, Color(0.5f, 0.5f, 1.0f, 1.0f),
											BUTTON_STATE_NORMAL, m_ParentWindow);
				break;

			case LEFT_PANEL:
				m_DragHandle = FtkButton(m_Position + m_Size, math::vec2(2.0f, m_Size.m_y),
											backgroundColor, backgroundColor, Color(0.5f, 0.5f, 1.0f, 1.0f),
											BUTTON_STATE_NORMAL, m_ParentWindow);
				break;
		}

		m_DragHandle.setClickedSignalIndex(connect(&m_DragHandle, (bool (FtkObject::*)(bool))&FtkButton::clickedSignal,
																					this, (void (FtkObject::*)(bool))&FtkPanel::on_HandleClicked));
	}

	FtkPanel::~FtkPanel() {

		disconnect(FA6_SIGNAL, m_ViewportSizeSignal);
	}

	bool FtkPanel::checkBounds(FtkObject* renderable) {

		return checkBounds((Renderable2D*)renderable);
	}

	bool FtkPanel::checkBounds(Renderable2D* renderable) {

		if(renderable->getPosition().m_x < m_Position.m_x) return false;
		else if(renderable->getPosition().m_y < m_Position.m_y) return false;
		else if(renderable->getPosition().m_x + renderable->getSize().m_x < m_Position.m_x + m_Size.m_x) return false;
		else if(renderable->getPosition().m_y + renderable->getSize().m_y < m_Position.m_y + m_Size.m_y) return false;
		return true;
	}

	void FtkPanel::submit(Renderer2D* renderer) const {

		renderer->push(getTransform());
		for (const Renderable2D* renderable : getRenderables()) {

			renderable->submit(renderer);
		}
		for(const FtkObject* element : getElements()) {
			if(element->isEnabled()) element->submit(renderer);
		}

		renderer->pop();
	}

	/****************************
	***********START***********
	***********SLOTS***********
	****************************/

	void FtkPanel::on_PositionChanged(math::vec2 sig) {

				m_Position.m_x = sig.m_x;
				m_Position.m_y = sig.m_y;
	}

	void FtkPanel::on_SizeChanged(math::vec2 sig) {

					scale(math::vec2(sig.m_x / m_Size.m_x, sig.m_y / m_Size.m_y));
	}

	void FtkPanel::on_HandleClicked(bool sig) {

		math::vec3 position = m_DragHandle.getPosition();
		math::vec2 old = m_Size;
		m_Size += math::vec2(position.m_x - m_Size.m_x, position.m_y - m_Size.m_y);
		m_ShownSize = m_Size;
		std::array<float, 6> signal = {(float)m_Type, (float)m_LayoutPosition, m_Size.m_x, m_Size.m_y, old.m_x, old.m_y};
		emitFA6(m_ViewportSizeSignal, signal);
	}

}}}}
