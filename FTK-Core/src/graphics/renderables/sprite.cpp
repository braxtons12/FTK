/**
 * Base sprite class
 * Used to draw non-ui element graphics
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "sprite.h"

namespace ftk { namespace core { namespace graphics {

	/**
	 * Constructor
	 * Takes in a position, size, and color
	 *
	 **/
	Sprite::Sprite(float x, float y, float width, float height, const math::vec4& color)
		: Renderable2D(math::vec3 (x, y, 0), math::vec2(width, height), color)
	{
		
	}

	/**
	 * Constructor
	 * Takes in a position, size, and texture pointer
	 * 
	 **/
	Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
		: Renderable2D(math::vec3 (x, y, 0), math::vec2(width, height), math::vec4(1, 0, 1, 1))
	{
		m_Texture = texture;
	}
}}}
