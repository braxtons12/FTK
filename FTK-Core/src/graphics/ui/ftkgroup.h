#ifndef _FTK_GROUP
#define _FTK_GROUP

#include "base/ftkobject.h"

namespace ftk { namespace core { namespace graphics{ namespace ui {

	class FtkGroup : public FtkObject {

		private:
			std::vector<FtkObject*> m_Elements;
			std::vector<Renderable2D*> m_Renderables;
			math::mat4 m_TransformationMatrix;

		public:
			FtkGroup(math::vec3 position, math::vec2 size, math::vec4 color, const math::mat4& transform)
				: FtkObject(position, size, color), m_TransformationMatrix(transform)
			{

			}

			inline void addElement(FtkObject* element) { m_Elements.push_back(element); }
			inline void addRenderable(Renderable2D* renderable) { m_Renderables.push_back(renderable); }

			inline const math::mat4& getTransform() const { return m_TransformationMatrix; }
			inline const std::vector<Renderable2D*> getRenderables() const { return m_Renderables; }
			inline const std::vector<FtkObject*> getElements() const { return m_Elements; }

			virtual bool checkBounds(FtkObject* renderable) override {

				return checkBounds((Renderable2D*)renderable);
			}

			virtual bool checkBounds(Renderable2D* renderable) override {

				math::vec3 renderablePos = renderable->getPosition();
				math::vec2 renderableSize = renderable->getSize();
				if(renderablePos.m_x + renderableSize.m_x < m_Position.m_x) return false;
				else if(renderablePos.m_y + renderableSize.m_y < m_Position.m_y) return false;
				else if(renderablePos.m_x > m_Position.m_x + m_Size.m_x) return false;
				else if(renderablePos.m_y > m_Position.m_y + m_Size.m_y) return false;
				return true;
			}

			virtual void submit(Renderer2D* renderer) const override {
				renderer->push(m_TransformationMatrix);
				for (const Renderable2D* renderable : m_Renderables) {

					renderable->submit(renderer);
				}
				for(const FtkObject* element : m_Elements) {

					element->submit(renderer);
				}

				renderer->pop();
			}
	};
}}}}
#endif
