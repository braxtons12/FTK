#ifndef _FUSION_VIEWPORT
#define _FUSION_VIEWPORT

#include "mathLibs/mathLib.h"
#include "signals/panelsizesignal.h"
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
            ViewportSizeSignal* m_ViewportSignal;

            //position and size for outer bound of viewport only
            math::vec3 m_InnerPosition;
            math::vec2 m_InnerSize;

            Sprite m_Background;
            Color m_BackgroundColor;

            //left panels
            FusionPanel* m_LeftOuterPanel;
            FusionPanel* m_LeftInnerPanel;
            PanelSizeSignal* m_LeftInnerPanelSignal;
            PanelSizeSignal* m_LeftOuterPanelSignal;

            //right panels
            FusionPanel* m_RightOuterPanel;
            FusionPanel* m_RightInnerPanel;
            PanelSizeSignal* m_RightInnerPanelSignal;
            PanelSizeSignal* m_RightOuterPanelSignal;

            //top panels
            FusionPanel* m_TopOuterPanel;
            FusionPanel* m_TopInnerPanel;
            PanelSizeSignal* m_TopInnerPanelSignal;
            PanelSizeSignal* m_TopOuterPanelSignal;

            //bottom panels
            FusionPanel* m_BottomOuterPanel;
            FusionPanel* m_BottomInnerPanel;
            PanelSizeSignal* m_BottomInnerPanelSignal;
            PanelSizeSignal* m_BottomOuterPanelSignal;

            bool checkBounds(Renderable2D* renderable);
            void submitPanels(Renderer2D* renderer);
        
        public:
            FusionViewport(math::vec3 position, math::vec2 size, Color backgroundColor);
            ~FusionViewport();

            void addPanel(bool panelType, int panelPosition, FusionPanel* panel);
            void hidePanel(bool panelType, int panelPosition);
            void showPanel(bool panelType, int panelPosition);
            void removePanel(bool panelType, int panelPosition);

            void update();
            void scale(math::vec2 scale);
            void reposition(math::vec2 newPosition);

            void submit(Renderer2D* renderer) const override;

            inline math::vec3 const getPosition() const { return m_Position; }
            inline math::vec2 const getSize() const { return m_Size; }
            inline math::vec3 const getViewportOuterPosition() const { return m_ViewportOuterPosition; }
            inline math::vec2 const getViewportOuterSize() const { return m_ViewportOuterSize; }
            inline math::vec3 const getViewportInnerPosition() const { return m_ViewportInnerPosition; }
            inline math::vec2 const getViewportInnerSize() const { return m_ViewportInnerSize; }
    };

}}}}
#endif