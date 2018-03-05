/**
 * Basic Label class used for text rendering
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/ 

#include "label.h"

namespace fusion { namespace core { namespace graphics {

    /**
     * Constructor
     * Takes in the actual text, a position, and the color
     * 
     **/
    Label::Label(std::string text, float x, float y, math::vec4 color)
        : Renderable2D(), m_Text(text)
    {

        m_Position = math::vec3(x, y, 0.0f);
        m_Color = color;
    }

    /**
     * Submit the label for rendering
     *
     **/
    void Label::submit(Renderer2D* renderer) const {

        renderer->drawString(m_Text, m_Position, m_Color);
    }
}}}