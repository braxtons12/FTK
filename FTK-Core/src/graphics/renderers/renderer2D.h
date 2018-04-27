/**
 * Base Renderer class
 * Lays out the basic architecture of how a renderer should function
 * 
 * C 2018 Braxton Salyer
 **/

#ifndef _RENDERER_2D
#define _RENDERER_2D

#include "mathLibs/mathLib.h"

#include <GL/glew.h>
#include <vector>

namespace ftk { namespace core { namespace graphics {

    class Renderable2D;

    class Renderer2D {

        protected:
            std::vector<math::mat4> m_TransformationStack;
			math::mat4* m_TransformationBack;

            /**
             * Protected Constructor
             * 
             **/
            Renderer2D() {

                m_TransformationStack.push_back(math::mat4::identity());
				m_TransformationBack = &m_TransformationStack.back();
            }

        public:

            /**
             * push the matrix to the transformation stack
             * 
             **/
            void push(const math::mat4& matrix, bool override = false) {

                if (override) m_TransformationStack.push_back(matrix);
                else m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

				m_TransformationBack = &m_TransformationStack.back();
            }

            /**
             * remove the matrix from the transformation stack
             * 
             **/
            void pop() {

				if (m_TransformationStack.size() > 1) m_TransformationStack.pop_back();
				m_TransformationBack = &m_TransformationStack.back();
			}

            //start the renderer
            virtual void begin() { }

            //submit a renderable for rendering
			virtual void submit(const Renderable2D* renderable) = 0;

            //"submit" text for rendering
            virtual void drawString(const std::string& text, const math::vec3& position, const math::vec4& color) { }

            //end submissions
            virtual void end() { }

            //draw things
            virtual void flush() = 0;

            //destructor
			virtual ~Renderer2D() { }
    };

}}}


#endif
