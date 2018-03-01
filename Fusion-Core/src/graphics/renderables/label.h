#ifndef _LABEL
#define _LABEL

#include "graphics/renderables/renderable2D.h"

namespace fusion { namespace core { namespace graphics {

    class Label : public Renderable2D {

        private:
            std::string m_Text;

        public:
            Label(std::string text, float x, float y, math::vec4 color);

            void submit(Renderer2D* renderer) const override;
    };
}}}
#endif