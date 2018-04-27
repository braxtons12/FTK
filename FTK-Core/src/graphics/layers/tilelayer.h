#ifndef _TILE_LAYER
#define _TILE_LAYER

#include "graphics/renderers/batchrenderer2D.h"
#include "graphics/layers/layer.h"

namespace ftk { namespace core { namespace graphics {

	class TileLayer : public Layer {

	public:
		TileLayer(Shader* shader);
		~TileLayer();

	};
}}}

#endif
