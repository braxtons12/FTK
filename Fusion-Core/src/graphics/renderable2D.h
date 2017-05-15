#ifndef _RENDERABLE_2D
#define _RENDERABLE_2D

#include "../src/graphics/buffers/buffer.h"
#include "../src/graphics/buffers/indexbuffer.h"
#include "../src/graphics/buffers/vertexarray.h"
#include "../src/mathLibs/mathLib.h"
#include "../src/graphics/shader.h"

namespace fusion { namespace core { namespace graphics {

    struct VertexData {
        
        math::vec3 vertex;
        math::vec4 color;

    };
    
    class Renderable2D
    {
        public:
            math::vec3 m_Position;
            math::vec2 m_Size;
            math::vec4 m_Color;

            VertexArray* m_VertexArray;
            IndexBuffer* m_IndexBuffer;
            Shader& m_Shader;

            Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color, Shader& shader)
                : m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
            {
                m_VertexArray = new VertexArray();
                GLfloat vertices[] =
                {
                    0, 0, 0,
                    0, size.m_y, 0,
                    size.m_x, size.m_y, 0,
                    size.m_x, 0, 0
                };

                GLfloat colors[] =
                {
                    color.m_x, color.m_y, color.m_z, color.m_w,
                    color.m_x, color.m_y, color.m_z, color.m_w,
                    color.m_x, color.m_y, color.m_z, color.m_w,
                    color.m_x, color.m_y, color.m_z, color.m_w,
                };

                m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
                m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
                GLushort indices[] = { 0, 1, 2, 2, 3, 0};
                m_IndexBuffer = new IndexBuffer(indices, 6);

            }

            virtual ~Renderable2D() {

                delete m_VertexArray;
                delete m_IndexBuffer;
            }

            inline const VertexArray* getVAO() const { return m_VertexArray; }
            inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
            inline Shader& getShader() const { return m_Shader; }

            inline const math::vec3& getPosition() const { return m_Position; }
            inline const math::vec2& getSize() const { return m_Size; }
            inline const math::vec4& getColor() const { return m_Color; }

    };

}}}

#endif