
#ifndef _FUSION_WINDOW
#define _FUSION_WINDOW

#include "../../src/graphics/window.h"
#include "../../src/signals/windowupdatesignal.h"
#include "../../src/input/input.h"
#include "../../src/mathLibs/mathLib.h"
#include "../../src/graphics/shader.h"
#include "../../src/graphics/renderable2D.h"
#include "../../src/graphics/static_sprite.h"
#include "../../src/graphics/renderer2D.h"
#include "../../src/graphics/batchrenderer2D.h"

#include <typeinfo>
#include <vector>

namespace fusion { namespace core { namespace graphics { namespace window {

#define MAX_SHADERS 1000

	class FusionWindow {

	private:

		Window* m_Child;
		const WindowUpdateSignal* m_Signal;
		const char* m_Name;
		int m_Width;
		int m_Height;
		input::Mouse* m_Mouse;
		input::Keyboard* m_Keyboard;
		const char* m_VertexShaderPath;
		const char* m_FragmentShaderPath;
		Shader* m_Shader;
		Renderer2D* m_Renderer;

		void init();

	public:

		FusionWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath);

		inline const char* const getName() { return m_Name; }
		inline int const getHeight() { return m_Height; }
		inline int const getWidth() { return m_Width; }
		inline void updateSize(int width, int height) { m_Width = width; m_Height = height; }

		inline void addElement(const Renderable2D* renderable) {
			if(typeid(*renderable) == (typeid(Static_Sprite))) ((Static_Sprite*)renderable)->setShader(*m_Shader);
			m_Renderer->submit(renderable);
		}

		void update();

		inline void beginRenderer() { m_Renderer->begin(); }

		// Not sure if necessary. Thinking not.
		//inline void endRenderer() { ((BatchRenderer2D*)(m_Renderer))->end(); }

		inline void setShader(Shader& shader) { *m_Shader = shader; }
		inline Shader& getShader() { return *m_Shader; }
		inline Window* const getWindow() { return m_Child; }
		inline input::Mouse* const getMouse() { return m_Mouse; }
		inline input::Keyboard* const getKeyboard() { return m_Keyboard; }

		inline void activateRenderer() { m_Renderer = new BatchRenderer2D(); }



	};
}}}}

#endif
