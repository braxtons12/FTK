/**
 * Class to encapsulate Renderables into Groups for purposes such as simplifying UI elements 
 * (EX: Incorporating the text and background of a button into a group)
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _GROUP
#define _GROUP

#include "graphics/renderables/renderable2D.h"

namespace fusion { namespace core { namespace graphics {

	class Group : public Renderable2D {

		private:
			std::vector<Renderable2D*> m_Renderables;
			math::mat4 m_TransformationMatrix;

		public:
			/**
			 * Constructor
			 * Takes in a transformation matrix
			 **/
			Group(const math::mat4& transform);

			/**
			 * Add a Renderable to the group
			 * 
			 **/
			inline void add(Renderable2D* renderable) { m_Renderables.push_back(renderable); }

			/**
			 * Submit the group for renderering
			 * 
			 **/
			virtual void submit(Renderer2D* renderer) const override;
	};
}}}

#endif
