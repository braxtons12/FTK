#ifndef _BATCH_RENDERER_2D
#define _BATCH_RENDERER_2D

#include "../src/graphics/renderer2D.h"
#include "../src/graphics/buffers/vertexarray.h"
#include "../src/graphics/buffers/indexbuffer.h"

namespace fusion { namespace core { namespace graphics {

#define RENDERER_MAX_SPRITES    10000
#define RENDERER_VERTEX_SIZE    sizeof(VertexData)
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE  	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1


    class BatchRenderer2D : public Renderer2D {

        private:
            GLuint m_VAO;
			GLuint m_VBO;
			VertexData* m_Buffer;
            IndexBuffer* m_IBO;
            GLsizei m_IndexCount;

            void init();
        public:

            BatchRenderer2D();
            ~BatchRenderer2D();
            void begin();
            void submit(const Renderable2D* renderable) override;
            void end();
            void flush() override;
    };
}}}

#endif
