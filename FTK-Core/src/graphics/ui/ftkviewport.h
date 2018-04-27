#ifndef _FTK_VIEWPORT
#define _FTK_VIEWPORT

#include "mathLibs/mathLib.h"
#include "signals/signal.h"
#include "graphics/color.h"
#include "graphics/renderables/sprite.h"
#include "graphics/groups/group.h"
#include "graphics/ui/ftkpanel.h"

#include <array>

namespace ftk { namespace core { namespace graphics { namespace ui {

    class FtkViewport : public Group {

        private:
            //position and size for outer bound of viewport including inner panels
            math::vec3 m_OuterPosition;
            math::vec2 m_OuterSize;
		
            //position signal for our viewport
            Signal<FtkViewport, FtkPanel, std::array<float, 6>, void, std::array<float, 6>>* m_ViewportSizeSignal;

            //position and size for outer bound of viewport only
            math::vec3 m_InnerPosition;
            math::vec2 m_InnerSize;

            Color m_BackgroundColor;

            //left panels
            FtkPanel* m_LeftOuterPanel;
            FtkPanel* m_LeftInnerPanel;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_LeftInnerPanelSizeSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_LeftOuterPanelSizeSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_LeftInnerPanelPositionSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_LeftOuterPanelPositionSignal;

            //right panels
            FtkPanel* m_RightOuterPanel;
            FtkPanel* m_RightInnerPanel;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_RightInnerPanelSizeSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_RightOuterPanelSizeSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_RightInnerPanelPositionSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_RightOuterPanelPositionSignal;

            //top panels
            FtkPanel* m_TopOuterPanel;
            FtkPanel* m_TopInnerPanel;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_TopInnerPanelSizeSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_TopOuterPanelSizeSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_TopInnerPanelPositionSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_TopOuterPanelPositionSignal;

            //bottom panels
            FtkPanel* m_BottomOuterPanel;
            FtkPanel* m_BottomInnerPanel;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_BottomInnerPanelSizeSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_BottomOuterPanelSizeSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_BottomInnerPanelPositionSignal;
            Signal<FtkViewport, FtkPanel, math::vec2, void, math::vec2>* m_BottomOuterPanelPositionSignal;

            bool checkBounds(Renderable2D* renderable);
            void submitPanels(Renderer2D* renderer);
            void scalePanels(math::vec2 scale);
        
        public:
            FtkViewport(math::vec3 position, math::vec2 size, Color backgroundColor);
            ~FtkViewport();

            void addPanel(bool panelType, int panelPosition, FtkPanel* panel);
            void hidePanel(bool panelType, int panelPosition);
            void showPanel(bool panelType, int panelPosition);
            void removePanel(bool panelType, int panelPosition);

            void update();
            void scale(math::vec2 scale) override;

            void submit(Renderer2D* renderer) const override;

            inline math::vec3 const getOuterPosition() const { return m_OuterPosition; }
            inline math::vec2 const getOuterSize() const { return m_OuterSize; }
            inline math::vec3 const getInnerPosition() const { return m_InnerPosition; }
            inline math::vec2 const getInnerSize() const { return m_InnerSize; }
            inline Signal<FtkViewport, FtkPanel, std::array<float, 6>, void, std::array<float, 6>>* 
            const getSizeSignal() const { return m_ViewportSizeSignal; }
			
			math::vec2 updatePanelPosition(math::vec2 pos) {
				
				return pos;
			}
			
			math::vec2 updatePanelSize(math::vec2 size) {
				
				return size;
			}
			
			void on_ViewportResized(std::array<float, 6> sig);
    };

}}}}
#endif
