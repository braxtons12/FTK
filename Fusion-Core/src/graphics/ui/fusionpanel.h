#ifndef _FUSION_PANEL
#define _FUSION_PANEL

#include "mathLibs/mathLib.h"
#include "signals/panelsizesignal.h"
#include "signals/viewportsizesignal.h"
#include "graphics/color.h"
#include "graphics/groups/group.h"
#include "graphics/renderables/sprite.h"
#include "graphics/ui/fusionbutton.h"


namespace fusion { namespace core { namespace graphics { namespace ui {

    class FusionPanel : Group {

        private:
            math::vec3 m_Position;
            math::vec2 m_Size;
            PanelSizeSignal* m_PanelSignal;
            ViewportSizeSignal* m_ViewportSignal;

            FusionButton m_DragHandle;

            Sprite m_Background;
            Color m_BackgroundColor;

            void checkBounds(Renderable2D* renderable);

        public:
            FusionPanel(math::vec3 position, math::vec2 size, Sprite background, Color backgroundColor, math::mat4 projectionMatrix);
            ~FusionPanel();

            void update();
            void scale();
            void repositon(math::vec2 newPostion);

            void submit(Renderer2D* renderer) const override;

            inline math::vec3 const getPosition() const { return m_Position; }
            inline math::vec2 const getSize() const { return m_Size; }

    };
    
}}}}

#endif