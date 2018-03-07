/**
 * Wrapper for the basic Window class.
 * Enables more UI-friendly operations
 * DOES NOT extend Window, but rather serves as a container for it
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

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

namespace fusion { namespace core { namespace graphics { namespace ui { 

	//define necessary macros
	#define WINDOW_NO_MENU     0
	#define WINDOW_HAS_MENU    1
	//#define MAX_SHADERS     1000 deprecated with static sprites

	class FusionWindow {

	private:
		Window* m_Window;
		const WindowUpdateSignal* m_Signal;
		const char* m_Name;
		double m_Width;
		double m_Height;
		input::Mouse* m_Mouse;
		input::Keyboard* m_Keyboard;
		const char* m_VertexShaderPath;
		const char* m_FragmentShaderPath;
		Shader* m_Shader;
		Renderer2D* m_Renderer;
		bool m_HasMenu;
		FusionMenu* m_Menu;
		std::vector<Renderable2D*>* m_Renderables;

		/**
		 * Initialize the window
		 * 
		 **/
		void init();

	public:
		/**
		 * Constructor
		 * 
		 **/
		FusionWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath);

		//getters
		inline const char* const getName() { return m_Name; }
		inline int const getHeight() { return m_Height; }
		inline int const getWidth() { return m_Width; }

		/**
		 * Used to scale the container when the Window is resized
		 * 
		 **/
		void scale(math::vec2 scale);

		/**
		 * Add a Renderable to the window
		 * 
		 **/
		inline void addElement(Renderable2D* renderable) {
			//if(typeid(*renderable) == (typeid(Static_Sprite))) ((Static_Sprite*)renderable)->setShader(*m_Shader); deprecated with static sprites
			m_Renderables->push_back(renderable);
		}

		/**
		 * Create the window menu from the given parameters
		 * 
		 **/
		void setMenu(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover, int state, 
					 int menuType, int numMenus, bool alwaysVisible, std::vector<FusionMenu*> subMenus);

		inline void setMenu(FusionMenu* menu) { m_Menu = menu; m_HasMenu = true; }

		/**
		 * Update the state of the window content
		 * 
		 **/
		void update();

		/**
		 * Render the contents of the window
		 * 
		 **/
		void render();

		//getters and setters
		inline void setShader(Shader& shader) { *m_Shader = shader; }
		inline Shader& getShader() { return *m_Shader; }
		inline Window* const getWindow() { return m_Window; }
		inline input::Mouse* const getMouse() { return m_Mouse; }
		inline input::Keyboard* const getKeyboard() { return m_Keyboard; }
		inline FusionMenu* const getMenu() { return m_Menu; }

		/**
		 * Activate the window's renderer
		 * 
		 **/
		inline void activateRenderer() { m_Renderer = new BatchRenderer2D(); }

		//wrap some base window functions
		inline void clear() { m_Window->clear(); }

		inline bool closed() const { return m_Window->closed(); }

		inline void convertCoords(double& x, double& y) { m_Window->convertCoords(x, y); }


	};
}}}}

#endif
