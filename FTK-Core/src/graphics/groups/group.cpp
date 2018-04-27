/**
 * Class to encapsulate Renderables into Groups for purposes such as simplifying UI elements 
 * (EX: Incorporating the text and background of a button into a group)
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "group.h"

namespace ftk { namespace core { namespace graphics {

	/**
	 * Constructor
	 * Takes in a transformation matrix
	 **/
	Group::Group(const math::mat4& transform)
		: m_TransformationMatrix(transform)
	{
		
	}

	/**
	 * Submit the group for renderering
	 * 
	 **/
	void Group::submit(Renderer2D* renderer) const {

		renderer->push(m_TransformationMatrix);
		for (const Renderable2D* renderable : m_Renderables) {

			renderable->submit(renderer);
		}

		renderer->pop();
	}
}}}
