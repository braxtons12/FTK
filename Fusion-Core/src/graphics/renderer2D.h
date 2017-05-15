#ifndef _RENDERER_2D
#define _RENDERER_2D

#include "../src/graphics/renderable2D.h"
#include "GL/glew.h"
#include "../src/mathLibs/mathLib.h"

namespace fusion { namespace core { namespace graphics {

    class Renderer2D
    {
        public:
            virtual void submit(const Renderable2D* renderable) = 0;
            virtual void flush() = 0;
    };

}}}


#endif