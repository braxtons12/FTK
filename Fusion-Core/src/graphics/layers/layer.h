/**
 * Basic Layer class.
 * Used to encapsulate render paths into a single object.
 * Simplifies render calls and allows to have multiple viewports render to screen at one time 
 * (eg: one render path for foreground objects, another for background, etc.)
 * 
 * Header File
 *
 * Version: 0.0.1
 * C 2018 Braxton Salyer
 *
 **/

#ifndef _LAYER
#define _LAYER

#include "graphics/renderers/renderer2D.h"
#include "graphics/renderables/renderable2D.h"
#include "mathLibs/mathLib.h"

namespace fusion { namespace core { namespace graphics {

	class Layer {

		protected:
            Renderer2D* m_Renderer;
            std::vector<Renderable2D*> m_Renderables;
            Shader* m_Shader;
            math::mat4 m_ProjectionMatrix;

            /**
             * Constructor
             * Layers have their own Renderer, Shader, and pr_matrix so they can render
             * differently than other layers
             *
             **/
            Layer(Renderer2D* renderer, Shader* shader, math::mat4 projectionMatrix);

		public:

            /**
             * Destructor
             * 
             **/
            virtual ~Layer();

            /**
             * Add a renderable to the layer
             * 
             **/
            inline virtual void add(Renderable2D* renderable) { m_Renderables.push_back(renderable); }

            /**
             * Render the layer
             *
             **/
            virtual void render();

	};
}}}
#endif
