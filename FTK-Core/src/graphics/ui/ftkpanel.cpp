#include "ftkpanel.h"

namespace ftk { namespace core { namespace graphics { namespace ui {

	FtkPanel::FtkPanel(math::vec3 position, math::vec2 size, Sprite background, Color backgroundColor,
						math::mat4 projectionMatrix, int type, int layoutPosition, FtkViewport* parentViewport,
						NativeWindow* parentWindow)
		: Group(projectionMatrix), m_Position(position), m_Size(size), m_Background(background),
		m_BackgroundColor(backgroundColor), m_Type(type), m_LayoutPosition(layoutPosition),
		m_ParentViewport(parentViewport), m_ParentWindow(parentWindow),
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
	}

	FtkPanel::~FtkPanel() {

		disconnect(FA6_SIGNAL, m_ViewportSizeSignal);
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

	void on_HandleClicked(bool sig) {

	}

}}}}
