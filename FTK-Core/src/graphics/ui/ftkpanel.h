#ifndef _FTK_PANEL
#define _FTK_PANEL

#include "base/ftkobject.h"
#include "mathLibs/mathLib.h"
#include "signals/signal.h"
#include "graphics/color.h"
#include "graphics/nativewindow.h"
#include "graphics/groups/group.h"
#include "graphics/renderables/sprite.h"
#include "graphics/ui/ftkbutton.h"

#include <array>

namespace ftk { namespace core { namespace graphics { namespace ui {

	#define NO_PANEL	 0 //used for signals

    #define OUTER_PANEL  1
    #define INNER_PANEL  2

    #define TOP_PANEL    1
    #define RIGHT_PANEL  2
    #define BOTTOM_PANEL 3
    #define LEFT_PANEL   4

	class FtkViewport;

    class FtkPanel : public Group, public FTKObject {

        private:
            math::vec3 m_Position;
            math::vec2 m_Size;
            math::vec2 m_ShownSize;

			int m_Type;
			int m_LayoutPosition;

			FtkViewport* m_ParentViewport;
			NativeWindow* m_ParentWindow;
			int m_ViewportSizeSignal;

            FtkButton m_DragHandle;

            Sprite m_Background;
            Color m_BackgroundColor;

            void checkBounds(Renderable2D* renderable);

        public:
            FtkPanel(math::vec3 position, math::vec2 size, Sprite background, Color backgroundColor,
						math::mat4 projectionMatrix, int type, int layoutPosition, FtkViewport* parentViewport,
						NativeWindow* parentWindow);
            ~FtkPanel();

            void update();
            void scale(math::vec2 scale) override;
            void repositon(math::vec2 newPostion);

            void submit(Renderer2D* renderer) const override;

            inline math::vec3 const getPosition() const { return m_Position; }
            inline math::vec2 const getSize() const { return m_Size; }
            inline math::vec2 const getShownSize() const { return m_Size; }
            inline NativeWindow* const getNativeWindow() const { return m_ParentWindow; }
            inline FtkViewport* const getParentViewport() const { return m_ParentViewport; }
			inline void setUpdateViewportSizeSignalIndex(int index) { m_ViewportSizeSignal = index; }

			//signals
			std::array<float, 6> updateViewportSize(std::array<float, 6> sig) {

				return sig;
			}

			//slots
            void on_PositionChanged(math::vec2 sig);
			void on_SizeChanged(math::vec2 sig);
			void on_HandleClicked(bool sig);
    };

}}}}

#endif
