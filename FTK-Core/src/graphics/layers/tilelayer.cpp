#include "tilelayer.h"

namespace ftk { namespace core { namespace graphics {

	TileLayer::TileLayer(Shader* shader)
		: Layer((Renderer2D*)(new BatchRenderer2D()), shader, math::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) {

	}

	TileLayer::~TileLayer() {

	}
}}}
