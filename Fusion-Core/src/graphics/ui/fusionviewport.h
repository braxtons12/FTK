#ifndef _FUSION_VIEWPORT
#define _FUSION_VIEWPORT

#include "mathLibs/mathLib.h"
#include "signals/panelsizesignal.h"
#include "signals/panelpositionsignal.h"
#include "signals/viewportsizesignal.h"
#include "graphics/color.h"
#include "graphics/renderables/sprite.h"
#include "graphics/groups/group.h"
#include "graphics/ui/fusionpanel.h"


namespace fusion { namespace core { namespace graphics { namespace ui {

    #define OUTER_PANEL  0
    #define INNER_PANEL  1

    #define TOP_PANEL    0
    #define RIGHT_PANEL  1
    #define BOTTOM_PANEL 2
    #define LEFT_PANEL   3

    class FusionViewport : public Group {

        private:
            //position and size for outer bound of viewport including inner panels
            math::vec3 m_OuterPosition;
            math::vec2 m_OuterSize;

            //position signal for our viewport
            ViewportSizeSignal* m_ViewportSizeSignal;

            //position and size for outer bound of viewport only
            math::vec3 m_InnerPosition;
            math::vec2 m_InnerSize;

            Color m_BackgroundColor;

            //left panels
            FusionPanel* m_LeftOuterPanel;
            FusionPanel* m_LeftInnerPanel;
            PanelSizeSignal* m_LeftInnerPanelSizeSignal;
            PanelSizeSignal* m_LeftOuterPanelSizeSignal;
            PanelPositionSignal* m_LeftInnerPanelPositionSignal;
            PanelPositionSignal* m_LeftOuterPanelPositionSignal;

            //right panels
            FusionPanel* m_RightOuterPanel;
            FusionPanel* m_RightInnerPanel;
            PanelSizeSignal* m_RightInnerPanelSizeSignal;
            PanelSizeSignal* m_RightOuterPanelSizeSignal;
            PanelPositionSignal* m_RightInnerPanelPositionSignal;
            PanelPositionSignal* m_RightOuterPanelPositionSignal;

            //top panels
            FusionPanel* m_TopOuterPanel;
            FusionPanel* m_TopInnerPanel;
            PanelSizeSignal* m_TopInnerPanelSizeSignal;
            PanelSizeSignal* m_TopOuterPanelSizeSignal;
            PanelPositionSignal* m_TopInnerPanelPositionSignal;
            PanelPositionSignal* m_TopOuterPanelPositionSignal;

            //bottom panels
            FusionPanel* m_BottomOuterPanel;
            FusionPanel* m_BottomInnerPanel;
            PanelSizeSignal* m_BottomInnerPanelSizeSignal;
            PanelSizeSignal* m_BottomOuterPanelSizeSignal;
            PanelPositionSignal* m_BottomInnerPanelPositionSignal;
            PanelPositionSignal* m_BottomOuterPanelPositionSignal;

            bool checkBounds(Renderable2D* renderable);
            void submitPanels(Renderer2D* renderer);
            void scalePanels(math::vec2 scale);
        
        public:
            FusionViewport(math::vec3 position, math::vec2 size, Color backgroundColor);
            ~FusionViewport();

            void addPanel(bool panelType, int panelPosition, FusionPanel* panel);
            void hidePanel(bool panelType, int panelPosition);
            void showPanel(bool panelType, int panelPosition);
            void removePanel(bool panelType, int panelPosition);

            void update();
            void scale(math::vec2 scale);

            void submit(Renderer2D* renderer) const override;

            inline math::vec3 const getOuterPosition() const { return m_OuterPosition; }
            inline math::vec2 const getOuterSize() const { return m_OuterSize; }
            inline math::vec3 const getInnerPosition() const { return m_InnerPosition; }
            inline math::vec2 const getInnerSize() const { return m_InnerSize; }
            inline ViewportSizeSignal* const getSizeSignal() const { return m_ViewportSizeSignal; }

    };

}}}}
#endif