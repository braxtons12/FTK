#ifndef _GROUP
#define _GROUP

#include "../../src/graphics/renderable2D.h"

namespace fusion { namespace core { namespace graphics {

	class Group : public Renderable2D {

		private:
			std::vector<Renderable2D*> m_Renderables;
			math::mat4 m_TranformationMatrix;

		public:
			Group(const math::mat4& transform);
			void add(Renderable2D* renderable);
			void submit(Renderer2D* renderer) const override;
	};
}}}

#endif
