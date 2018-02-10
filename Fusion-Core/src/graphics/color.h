#ifndef _COLOR
#define _COLOR

#include "../../src/mathLibs/mathLib.h"

namespace fusion { namespace core { namespace graphics { 

    class Color {

        private:
            math::vec4 m_Color;

        public:
            Color(math::vec4 color) 
                : m_Color(color)
            { }
            ~Color() { }

            inline float getR() { return m_Color.m_x; }
            inline float getG() { return m_Color.m_y; }
            inline float getB() { return m_Color.m_z; }
            inline float getA() { return m_Color.m_w; }

            inline void setR(float r) { m_Color.m_x = r; }
            inline void setG(float g) { m_Color.m_y = g; }
            inline void setB(float b) { m_Color.m_z = b; }
            inline void setA(float a) { m_Color.m_w = a; }

            inline math::vec4 getColor() { return m_Color; }
            inline void setColor(math::vec4 color) { m_Color = color; }
            inline void setColor(float r, float g, float b, float a) { m_Color.m_x = r; m_Color.m_y = b; m_Color.m_z = b; m_Color.m_w = a; }

    };
}}}

#endif