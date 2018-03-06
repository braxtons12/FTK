/**
 * Basic Layer class.
 * Used to encapsulate render paths into a single object.
 * Simplifies render calls and allows to have multiple viewports render to screen at one time 
 * (eg: one render path for foreground objects, another for background, etc.)
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "layer.h"

namespace fusion { namespace core { namespace graphics {

	/**
	 * Constructor
	 * Layers have their own Renderer, Shader, and pr_matrix so they can render
	 * differently than other layers
	 *
	 **/
	Layer::Layer(Renderer2D* renderer, Shader* shader, math::mat4 projectionMatrix)
		: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
	{

			m_Shader->enable();
			m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
			m_Shader->disable();
	}

	/**
	 * Destructor
	 * 
	 **/
	Layer::~Layer() {

		delete m_Renderer;

		for(int i = 0; i < m_Renderables.size(); ++i) {

			delete m_Renderables[i];
		}
	}

	/**
	 * Renders the layer to the screen
	 *
	 **/
	void Layer::render() {

		m_Shader->enable();

		m_Renderer->begin();
		for(const Renderable2D* renderable: m_Renderables) {

			renderable->submit(m_Renderer);

		}

		m_Renderer->end();
		m_Renderer->flush();
	}

}}}
