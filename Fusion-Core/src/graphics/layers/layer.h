/**
 * Basic Layer class.
 * Used to encapsulate render paths into a single object.
 * Simplifies render calls and allows to have multiple viewports render to screen at one time (eg: one render path for foreground objects, another for background, etc.)
 * Header
 * 
 * Version: 0.0.1
 * 0 2017 Braxton Salyer and Logan Tibbetts
 * 
 **/

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
            
            /*
             * Constructor
             */
            Layer(Renderer2D* renderer, Shader* shader, math::mat4 projectionMatrix);
		
	public:
            
            virtual ~Layer();
            
            inline virtual void add(Renderable2D* renderable) { m_Renderables.push_back(renderable); }
			
            virtual void render();
		
	};
}}}
#endif
