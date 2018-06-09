#ifndef _FTK_VIEWPORT
#define _FTK_VIEWPORT

#include "mathLibs/mathLib.h"
#include "signals/signal.h"
#include "graphics/color.h"
#include "graphics/renderables/sprite.h"
#include "graphics/ui/ftkgroup.h"
#include "graphics/ui/ftkpanel.h"

#include <array>

namespace ftk { namespace core { namespace graphics { namespace ui {

    class FtkViewport : public FtkGroup {

        private:
            //position and size for outer bound of viewport including inner panels
            math::vec3 m_OuterPosition;
            math::vec2 m_OuterSize;

            //position and size for outer bound of viewport only
            math::vec3 m_InnerPosition;
            math::vec2 m_InnerSize;

            Color m_BackgroundColor;

            //left panels
            FtkPanel* m_LeftOuterPanel;
            FtkPanel* m_LeftInnerPanel;
            int m_LeftInnerPanelSizeSignal;
            int m_LeftOuterPanelSizeSignal;
            int m_LeftInnerPanelPositionSignal;
            int m_LeftOuterPanelPositionSignal;

            //right panels
            FtkPanel* m_RightOuterPanel;
            FtkPanel* m_RightInnerPanel;
            int m_RightInnerPanelSizeSignal;
            int m_RightOuterPanelSizeSignal;
            int m_RightInnerPanelPositionSignal;
            int m_RightOuterPanelPositionSignal;

            //top panels
            FtkPanel* m_TopOuterPanel;
            FtkPanel* m_TopInnerPanel;
            int m_TopInnerPanelSizeSignal;
            int m_TopOuterPanelSizeSignal;
            int m_TopInnerPanelPositionSignal;
            int m_TopOuterPanelPositionSignal;

            //bottom panels
            FtkPanel* m_BottomOuterPanel;
            FtkPanel* m_BottomInnerPanel;
            int m_BottomInnerPanelSizeSignal;
            int m_BottomOuterPanelSizeSignal;
            int m_BottomInnerPanelPositionSignal;
            int m_BottomOuterPanelPositionSignal;

            void submitPanels(Renderer2D* renderer);
            void scalePanels(math::vec2 scale);

        public:
            FtkViewport(math::vec3 position, math::vec2 size, Color backgroundColor, const math::mat4& transformationMatrix);
            ~FtkViewport();

            void addPanel(bool panelType, int panelPosition, FtkPanel* panel);
            void hidePanel(bool panelType, int panelPosition);
            void showPanel(bool panelType, int panelPosition);
            void removePanel(bool panelType, int panelPosition);

			virtual bool checkBounds(FtkObject* renderable) override;
			virtual bool checkBounds(Renderable2D* renderable) override;

            void update();
            void scale(math::vec2 scale) override;

            void submit(Renderer2D* renderer) const override;

            inline math::vec3 const getOuterPosition() const { return m_OuterPosition; }
            inline math::vec2 const getOuterSize() const { return m_OuterSize; }
            inline math::vec3 const getInnerPosition() const { return m_InnerPosition; }
            inline math::vec2 const getInnerSize() const { return m_InnerSize; }

			//signals
			math::vec2 updatePanelPosition(math::vec2 pos) {

				return pos;
			}

			math::vec2 updatePanelSize(math::vec2 size) {

				return size;
			}

			//slots
			void on_ViewportPanelResized(std::array<float, 6> sig);
			void on_ViewportResized(math::vec2 sig);
    };

}}}}
#endif
