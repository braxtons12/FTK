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
            math::vec3 m_ViewportOuterPosition;
            math::vec2 m_ViewportOuterSize;
            ViewportSizeSignal* m_ViewportSignal;

            //position and size for outer bound of viewport only
            math::vec3 m_ViewportInnerPosition;
            math::vec2 m_ViewportInnerSize;

            Sprite m_Backround;
            Color m_BackgroundColor;

            //left panels
            FusionPanel* m_LeftOuterPanel;
            FusionPanel* m_LeftInnerPanel;
            PanelSizeSignal* m_LeftPanelSignal;

            //right panels
            FusionPanel* m_RightOuterPanel;
            FusionPanel* m_RightInnerPanel;
            PanelSizeSignal* m_RightPanelSignal;

            //top panels
            FusionPanel* m_TopOuterPanel;
            FusionPanel* m_TopInnerPanel;
            PanelSizeSignal* m_TopPanelSignal;

            //bottom panels
            FusionPanel* m_BottomOuterPanel;
            FusionPanel* m_BottomInnerPanel;
            PanelSizeSignal* m_BottomPanelSignal;

            void checkBounds(Renderable2D* renderable);
            void submitPanels();
        
        public:
            FusionViewport(math::vec3 m_Position, math::vec2 m_Size, Sprite background, Color backgroundColor);
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