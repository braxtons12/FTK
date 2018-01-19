#ifndef _RENDERER_2D
#define _RENDERER_2D

#include "../src/mathLibs/mathLib.h"

#include <GL/glew.h>

]class Renderable2D;

namespace fusion { namespace core { namespace graphics {

    class Renderer2D {

        protected:
            std::vector<const math::mat4> m_TransformationStack;
			const math::mat4* m_TransformationBack;

            Renderer2D() {

                m_TransformationStack.push_back(math::mat4::identity());
				m_TransformationBack = &m_TransformationStack.back();
            }

        public:

            void push(const math::mat4& matrix, bool override = false) {

                if (override) m_TransformationStack.push_back(matrix);
                else m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

				m_TransformationBack = &m_TransformationStack.back();
            }

            void pop() {

				if (m_TransformationStack.size() > 1) m_TransformationStack.pop_back();
				m_TransformationBack = &m_TransformationStack.back();
			}

			virtual void submit(const Renderable2D* renderable) = 0;
            virtual void flush() = 0;
			virtual void begin() {}
			virtual void end() {}
			virtual ~Renderer2D() {}
    };

}}}


#endif
