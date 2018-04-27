/**
 * Basic Label class used for text rendering
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 * 
 **/ 

#ifndef _LABEL
#define _LABEL

#include "graphics/renderables/renderable2D.h"

namespace ftk { namespace core { namespace graphics {

    class Label : public Renderable2D {

        private:
            std::string m_Text;

        public:
            /**
             * Constructor
             * Takes in the actual text, a position, and the color
             * 
             **/
            Label(std::string text, math::vec3 position, math::vec4 color);

            /**
             * Submit the label for rendering
             *
             **/
            void submit(Renderer2D* renderer) const override;
    };
}}}
#endif
