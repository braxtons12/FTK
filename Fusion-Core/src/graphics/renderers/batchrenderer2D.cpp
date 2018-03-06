/**
 * Batchrenderer used to quickly and efficiently draw all graphics.
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 *
 **/

#include "batchrenderer2D.h"

namespace fusion { namespace core { namespace graphics {

    /**
     * Constructor
     * 
     **/
    BatchRenderer2D::BatchRenderer2D() {

        init();
    }

    /**
     * Destructor
     * 
     **/
    BatchRenderer2D::~BatchRenderer2D() {

        delete m_IBO;
        glDeleteBuffers(1, &m_VBO);
    }

    /**
     * Initialize the Renderer
     * 
     **/
    void BatchRenderer2D::init() {

        m_IndexCount = 0;

        //generate the buffers
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        //bind them
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

        //enable our attributes
        glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
        glEnableVertexAttribArray(SHADER_UV_INDEX);
        glEnableVertexAttribArray(SHADER_TID_INDEX);
        glEnableVertexAttribArray(SHADER_COLOR_INDEX);

        //tell OpenGL where our attribues are at in our VertexData
        glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) 0);
        glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE,
							 (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
        glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE,
							 (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
        glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE,
							 (const GLvoid*)(offsetof(VertexData, VertexData::color)));
        
        //unbind our vertex data buffer
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //initialize our index buffer object
        GLuint indices[RENDERER_INDICES_SIZE];

		int offset = 0;
        for(int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {

            indices[  i  ] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

        //unbind our vertex array
        glBindVertexArray(0);
    }

    /**
     * Start the renderer
     * 
     **/
    void BatchRenderer2D::begin() {

        //rebind our vertex data buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        //get the start of our buffer
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

    /**
     * Submit a renderable for rendering
     *
     **/
    void BatchRenderer2D::submit(const Renderable2D* renderable) {

        //get our data from the renderable
		const math::vec3& position = renderable->getPosition();
		const math::vec2& size = renderable->getSize();
		const math::vec4& color = renderable->getColor();
        const std::vector<math::vec2>& uv = renderable->getUV();
        const GLuint tid = renderable->getTID();

        unsigned int c = 0;

        //shaders use floats for -- BOUND -- texture IDs
        float ts = 0.0f;

        //if we have a tid
        if (tid > 0) {

            //check if we're already using it
            bool found = false;
            for (int i = 0; i < m_TextureSlots.size(); ++i) {

                if(m_TextureSlots[i] == tid) {

                    ts = (float)(i + 1); //set ts to the slot
                    found = true;
                    break;
                }
            }

            if (!found) { //if we aren't already using it

                //check if we're past our 32 texture limit, if yes, flush and restart the renderer
                if (m_TextureSlots.size() >= 32) {

                    end();
                    flush();
                    begin();
                }
                //add the ID to m_TextureSlots and set ts to the slot
                m_TextureSlots.push_back(tid);
                ts = (float)(m_TextureSlots.size());
            }

        } else { //if we don't have a tid, get the color instead and convert it to an int

            int r = color.m_x * 255.0f;
            int g = color.m_y * 255.0f;
            int b = color.m_z * 255.0f;
            int a = color.m_w * 255.0f;

            c = a << 24 | b << 16 | g << 8 | r;
        }

        //add our vertex data to the buffer and increment our location 4 times because rectangle
		m_Buffer->vertex = *m_TransformationBack * position;
        m_Buffer->uv = uv[0];
        m_Buffer->tid = ts;
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * math::vec3(position.m_x, position.m_y + size.m_y, position.m_z);
        m_Buffer->uv = uv[1];
        m_Buffer->tid = ts;
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * math::vec3(position.m_x + size.m_x, position.m_y + size.m_y, position.m_z);
        m_Buffer->uv = uv[2];
        m_Buffer->tid = ts;
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = *m_TransformationBack * math::vec3(position.m_x + size.m_x, position.m_y, position.m_z);
        m_Buffer->uv = uv[3];
        m_Buffer->tid = ts;
		m_Buffer->color = c;
		m_Buffer++;

		m_IndexCount += 6; //we increment our index 6 times because a rectangle takes two triangles = 6 vertices = 6 indices pointing to vertices
    }

    /**
     * "Submit" a text item
     * 
     **/
    void BatchRenderer2D::drawString(const std::string& text, const math::vec3& position, const math::vec4& color) {

    }

    /**
     * End submissions
     *
     **/
    void BatchRenderer2D::end() {

		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

    /**
     * Draw all the renderables
     * 
     **/
    void BatchRenderer2D::flush() {

        //activate and bind our textures
        for (int i = 0; i < m_TextureSlots.size(); ++i) {

            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
        }

        //bind our buffers
		glBindVertexArray(m_VAO);
		m_IBO->bind();

        //draw things
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

        //unbind buffers
		m_IBO->unbind();
		glBindVertexArray(0);

        //reset the number of indices queued for drawing
		m_IndexCount = 0;
	}

}}}
