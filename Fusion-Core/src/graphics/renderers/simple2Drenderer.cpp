/**
 * Simple renderer that draws static sprites one by one
 * Deprecated
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "simple2Drenderer.h"

namespace fusion { namespace core { namespace graphics {

    void Simple2DRenderer::submit(const Renderable2D* renderable) {

        m_RenderQueue.push_back((Static_Sprite*) renderable);

    }

    void Simple2DRenderer::flush() {

        while(!m_RenderQueue.empty()) {

			const Static_Sprite* sprite = m_RenderQueue.front();
            sprite->getVAO()->bind();
            sprite->getIBO()->bind();

            sprite->getShader().setUniformMat4("ml_matrix", math::mat4::translation(sprite->getPosition()));

            glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

            sprite->getIBO()->unbind();
            sprite->getVAO()->unbind();
            m_RenderQueue.pop_front();
        }

    }
}}}
