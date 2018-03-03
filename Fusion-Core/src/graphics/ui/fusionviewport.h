#ifndef _FUSION_VIEWPORT
#define _FUSION_VIEWPORT

#include "graphics/color.h"
#include "graphics/groups/group.h"
#include "graphics/ui/fusionpanel.h"
#include "mathLibs/mathLib.h"

#include <vector>

#define OUTER_PANEL  0
#define INNER_PANEL  1

#define TOP_PANEL    0
#define RIGHT_PANEL  1
#define BOTTOM_PANEL 2
#define LEFT_PANEL   3

namespace fusion { namespace core { namespace graphics { namespace ui {

    class FusionViewport : public Group {

        private:
            //position and size for overall container
            math::vec3 m_Position;
            math::vec2 m_Size;

            //position and size for outer bound of viewport including inner panels
            math::vec3 m_ViewportOuterPosition;
            math::vec2 m_ViewportOuterSize;

            //position and size for outer bound of viewport only
            math::vec3 m_ViewportInnerPosition;
            math::vec2 m_ViewportInnerSize;

            Color m_BackgroundColor;

            FusionPanel* m_LeftOuterPanel;
            FusionPanel* m_LeftInnerPanel;
            FusionPanel* m_RightOuterPanel;
            FusionPanel* m_RightInnerPanel;

            FusionPanel* m_TopOuterPanel;
            FusionPanel* m_TopInnerPanel;
            FusionPanel* m_BottomOuterPanel;
            FusionPanel* m_BottomInnerPanel;

            void checkBounds(Renderable2D*);
            void submitPanels();
        
        public:
            FusionViewport(math::vec3 m_Position, math::vec2 m_Size, Color color);
            ~FusionViewport();

            void addPanel(bool panelType, int panelPosition, FusionPanel* panel);
            void hidePanel(bool panelType, int panelPosition);
            void showPanel(bool panelType, int panelPosition);
            void removePanel(bool panelType, int panelPosition);

            void update();
            void submit() const;

            inline math::vec3 getPosition() { return m_Position; }
            inline math::vec2 getSize() { return m_Size; }
            inline math::vec3 getViewportOuterPosition() { return m_ViewportOuterPosition; }
            inline math::vec2 getViewportOuterSize() { return m_ViewportOuterSize; }
            inline math::vec3 getViewportInnerPosition() { return m_ViewportInnerPosition; }
            inline math::vec2 getViewportInnerSize() { return m_ViewportInnerSize; }
    };

}}}}
#endif