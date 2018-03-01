#ifndef _BATCH_RENDERER_2D
#define _BATCH_RENDERER_2D

#include "graphics/renderers/renderer2D.h"
#include "graphics/renderables/renderable2D.h"
#include "graphics/buffers/vertexarray.h"
#include "graphics/buffers/indexbuffer.h"

#include <cstddef>
//#include <FTGL/ftgl.h>

namespace fusion { namespace core { namespace graphics {

#define RENDERER_MAX_SPRITES    60000
#define RENDERER_VERTEX_SIZE    sizeof(VertexData)
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE  	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3


    class BatchRenderer2D : public Renderer2D {

        private:
            GLuint m_VAO;
			GLuint m_VBO;
			VertexData* m_Buffer;
            IndexBuffer* m_IBO;
            GLsizei m_IndexCount;
            std::vector<GLuint> m_TextureSlots;

            void init();

        public:
            BatchRenderer2D();
            ~BatchRenderer2D();
            void begin() override;
            void submit(const Renderable2D* renderable) override;
            void drawString(const std::string& text, const math::vec3& position, const math::vec4& color) override;
            void end() override;
            void flush() override;
            inline unsigned int getNumTextures() { return m_TextureSlots.size(); }
            inline std::vector<GLuint>& getTextureIDs() { return m_TextureSlots; }
    };
}}}

#endif