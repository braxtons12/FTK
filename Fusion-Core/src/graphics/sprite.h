#ifndef _SPRITE
#define _SPRITE

#include "renderable2D.h"

namespace fusion { namespace core { namespace graphics {
	
	class Sprite : public Renderable2D {
		
		private:
			
		public:
			Sprite(float x, float y, float width, float height, const math::vec4& color);
		
		
	};
	
	
}}}
#endif
