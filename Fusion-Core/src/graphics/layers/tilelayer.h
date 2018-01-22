#ifndef _TILE_LAYER
#define _TILE_LAYER

#include "../../../src/graphics/layers/layer.h"
#include "../../../src/graphics/batchrenderer2D.h"

namespace fusion { namespace core { namespace graphics {

	class TileLayer : public Layer {

	public:
		TileLayer(Shader* shader);
		~TileLayer();

	};
}}}

#endif
