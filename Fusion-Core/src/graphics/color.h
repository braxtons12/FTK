/**
 * Class used to wrap mat4s into a dedicated Color object
 * values should be in [0.0f,1.0f]
 * 
 * C 2018 Braxton Salyer
 * 
 **/
#ifndef _COLOR
#define _COLOR

#include "mathLibs/mathLib.h"

namespace fusion { namespace core { namespace graphics { 

    class Color {

        private:
            math::vec4 m_Color;

        public:
            /**
             * Constructor
             * 
             **/
            Color(math::vec4 color) 
                : m_Color(color)
            { }

            /**
             * Destructor
             * 
             **/
            ~Color() { }

            //getters individual color components
            inline float getR() { return m_Color.m_x; }
            inline float getG() { return m_Color.m_y; }
            inline float getB() { return m_Color.m_z; }
            inline float getA() { return m_Color.m_w; }

            //setters for individual color components
            inline void setR(float r) { m_Color.m_x = r; }
            inline void setG(float g) { m_Color.m_y = g; }
            inline void setB(float b) { m_Color.m_z = b; }
            inline void setA(float a) { m_Color.m_w = a; }

            //getter and setters for entire color
            inline math::vec4 getColor() { return m_Color; }
            inline void setColor(math::vec4 color) { m_Color = color; }
            inline void setColor(float r, float g, float b, float a) { m_Color.m_x = r; m_Color.m_y = b; m_Color.m_z = b; m_Color.m_w = a; }

    };
}}}

#endif