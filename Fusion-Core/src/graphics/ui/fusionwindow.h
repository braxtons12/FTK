
#ifndef _FUSION_WINDOW
#define _FUSION_WINDOW

#include "graphics/window.h"
#include "signals/windowupdatesignal.h"
#include "input/input.h"
#include "mathLibs/mathLib.h"
#include "graphics/shader.h"
#include "graphics/renderables/renderable2D.h"
#include "graphics/renderables/static_sprite.h"
#include "graphics/renderers/renderer2D.h"
#include "graphics/renderers/batchrenderer2D.h"
#include "graphics/ui/fusionmenu.h"

#include <typeinfo>
#include <vector>
#include <GL/glew.h>

#define WINDOW_NO_MENU  0
#define WINDOW_HAS_MENU 1
#define MAX_SHADERS 1000

namespace fusion { namespace core { namespace graphics { namespace ui { 


	class FusionWindow {

	private:

		Window* m_Window;
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
		bool m_HasMenu;
		FusionMenu* m_Menu;
		std::vector<Renderable2D*>* m_Renderables;

		void init();

	public:

		FusionWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath, bool hasMenu);

		inline const char* const getName() { return m_Name; }
		inline int const getHeight() { return m_Height; }
		inline int const getWidth() { return m_Width; }
		void scale(float x, float y);

		inline void addElement(Renderable2D* renderable) {
			//if(typeid(*renderable) == (typeid(Static_Sprite))) ((Static_Sprite*)renderable)->setShader(*m_Shader);
			m_Renderables->push_back(renderable);
		}

		void setMenu(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover, int state, 
					 int menuType, int numMenus, int numEntries, bool alwaysVisible, std::vector<FusionMenu*> subMenus);

		inline void setMenu(FusionMenu* menu) { m_Menu = menu; }

		void update();
		void render();

		inline void setShader(Shader& shader) { *m_Shader = shader; }
		inline Shader& getShader() { return *m_Shader; }
		inline Window* const getWindow() { return m_Window; }
		inline input::Mouse* const getMouse() { return m_Mouse; }
		inline input::Keyboard* const getKeyboard() { return m_Keyboard; }
		inline FusionMenu* const getMenu() { return m_Menu; }

		inline void activateRenderer() { m_Renderer = new BatchRenderer2D(); }



	};
}}}}

#endif
