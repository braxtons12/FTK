/**
 * Base sprite class
 * Used to draw non-ui element graphics
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _SPRITE
#define _SPRITE

#include "graphics/renderables/renderable2D.h"

namespace ftk { namespace core { namespace graphics {

	class Sprite : public Renderable2D {

		private:

		public:
			/**
			 * Constructor
			 * Takes in a position, size, and color
			 *
			 **/
			Sprite(float x, float y, float width, float height, const math::vec4& color);

			/**
			 * Constructor
			 * Takes in a position, size, and texture pointer
			 * 
			 **/
			Sprite(float x, float y, float width, float height, Texture* texture);


	};


}}}
#endif
