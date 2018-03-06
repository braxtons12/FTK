/**
 * Batchrenderer used to quickly and efficiently draw all graphics.
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 *
 **/

#ifndef _BATCH_RENDERER_2D
#define _BATCH_RENDERER_2D

#include "graphics/renderers/renderer2D.h"
#include "graphics/renderables/renderable2D.h"
#include "graphics/buffers/vertexarray.h"
#include "graphics/buffers/indexbuffer.h"

#include <cstddef>
#include <freetype2/ft2build.h>
#include <FTGL/ftgl.h>

namespace fusion { namespace core { namespace graphics {

//define necessary macros
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

            /**
             * Initialize the Renderer
             * 
             **/
            void init();

        public:
            /**
             * Constructor
             * 
             **/
            BatchRenderer2D();

            /**
             * Destructor
             * 
             **/
            ~BatchRenderer2D();

            /**
             * Start the renderer
             * 
             **/
            void begin() override;

            /**
             * Submit a renderable for rendering
             *
             **/
            void submit(const Renderable2D* renderable) override;

            /**
             * "Submit" a text item
             * 
             **/
            void drawString(const std::string& text, const math::vec3& position, const math::vec4& color) override;

            /**
             * End submissions
             *
             **/
            void end() override;

            /**
             * Draw all the renderables
             * 
             **/
            void flush() override;

            /**
             * Get the number of active textures
             * 
             **/
            inline unsigned int getNumTextures() { return m_TextureSlots.size(); }

            /**
             * Get the active OpenGL Texture IDs
             * 
             **/
            inline std::vector<GLuint>& getTextureIDs() { return m_TextureSlots; }
    };
}}}

#endif