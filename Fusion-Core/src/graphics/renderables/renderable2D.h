/**
 * Base Renderable 2D graphics class, used for the base of all other graphics
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _RENDERABLE_2D
#define _RENDERABLE_2D

#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexbuffer.h"
#include "graphics/buffers/vertexarray.h"
#include "mathLibs/mathLib.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/renderers/renderer2D.h"

namespace fusion { namespace core { namespace graphics {

    /**
     * structure holding the data for each vertex of the renderable
     * 
     **/
    struct VertexData {

        math::vec3 vertex;
        math::vec2 uv;
        float tid;
		unsigned int color;

    };

    class Renderable2D
    {
        private:
            /**
             * Set the default texture coordinates
             *
             **/
            void setUVDefaults() {

                m_UV.push_back(math::vec2(0,0));
                m_UV.push_back(math::vec2(0,1));
                m_UV.push_back(math::vec2(1,1));
                m_UV.push_back(math::vec2(1,0));
            }
        protected:
            math::vec3 m_Position;
            math::vec2 m_Size;
            math::vec4 m_Color;
            std::vector<math::vec2> m_UV;
            Texture* m_Texture;

            //default protected constructor nulling the texture pointer
			Renderable2D() : m_Texture(nullptr) { setUVDefaults(); }

		public:
            /**
             * Constructor taking in the position size and color
             * 
             **/
            Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color)
                : m_Position(position), m_Size(size), m_Color(color)
			{

                setUVDefaults();
            }

            /**
             * Destructor
             * 
             **/
            virtual ~Renderable2D() {

            }

            /**
             * Submit the renderable for rendering
             * 
             **/
			virtual void submit(Renderer2D* renderer) const {

				renderer->submit(this);
			}

            //getters
            inline const math::vec3& getPosition() const { return m_Position; }
            inline const math::vec2& getSize() const { return m_Size; }
            inline const math::vec4& getColor() const { return m_Color; }
            inline const std::vector<math::vec2>& getUV() const { return m_UV; }
            inline const GLuint getTID() const { return m_Texture ? m_Texture->getID() : 0; }

            /**
             * Scale the renderable
             * Used by ui containers when the window is resized
             *
             **/
            virtual void scale(float x, float y) {

                m_Position.m_x *= x;
                m_Position.m_y *= y;
                
                m_Size.m_x *= x;
                m_Size.m_y *= y;
            }

    };

}}}

#endif
