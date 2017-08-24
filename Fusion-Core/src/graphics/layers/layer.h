#ifndef _LAYER
#define _LAYER

#include "../src/graphics/renderer2D.h"
#include "../src/graphics/renderable2D.h"
#include "../src/mathLibs/mathLib.h"

namespace fusion { namespace core { namespace graphics {
	
	class Layer {
		
	protected: 
		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader* m_Shader;
		math::mat4 m_ProjectionMatrix;
		
		Layer(Renderer2D* renderer, Shader* shader, math::mat4 projectionMatrix);
		
	public:
		virtual ~Layer();
			
		inline virtual void add(Renderable2D* renderable) {
				
			m_Renderables.push_back(renderable);
		}
			
		virtual void render();
		
	};
}}}
#endif
