#ifndef _SIMPLE_2D_RENDERER
#define _SIMPLE_2D_RENDERER

#include "renderer2D.h"
#include "static_sprite.h"

#include <deque>

namespace fusion { namespace core { namespace graphics { 

    class Simple2DRenderer : public Renderer2D {

        private:
            std::deque<const Static_Sprite*> m_RenderQueue;

        public:
            void submit(const Renderable2D* renderable) override;
            void flush() override;
    };


}}}

#endif
