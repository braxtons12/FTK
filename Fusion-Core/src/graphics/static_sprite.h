#ifndef _STATIC_SPRITE
#define _STATIC_SPRITE

#include "renderable2D.h"

namespace fusion { namespace core { namespace graphics {
	
	class Static_Sprite : public Renderable2D {
		
		private:
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			Shader& m_Shader;
			
		public:
			Static_Sprite(float x, float y, float width, float height, const math::vec4& color, Shader& shader);
			~Static_Sprite();
			
			inline const VertexArray* getVAO() const { return m_VertexArray; }
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
			inline Shader& getShader() const { return m_Shader; }
			inline void setShader(Shader& shader) { m_Shader = shader; }
		
		
	};
	
}}}

#endif
