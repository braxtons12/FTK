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

#ifndef _FTK_WINDOW
#define _FTK_WINDOW

//#include "graphics/nativewindow.h"
#include "signals/signal.h"
#include "input/input.h"
#include "mathLibs/mathLib.h"
#include "graphics/shader.h"
#include "graphics/nativewindow.h"
#include "graphics/renderables/renderable2D.h"
#include "graphics/renderables/static_sprite.h"
#include "graphics/renderers/renderer2D.h"
#include "graphics/renderers/batchrenderer2D.h"
#include "graphics/ui/ftkmenu.h"

#include <typeinfo>
#include <vector>
#include <array>
#include <GL/glew.h>

namespace ftk { namespace core { namespace graphics { namespace ui { 

	//define necessary macros
	#define WINDOW_NO_MENU     0
	#define WINDOW_HAS_MENU    1
	//#define MAX_SHADERS     1000 deprecated with static sprites

	class FtkWindow {

		private:
			NativeWindow* m_Window;
			Signal<NativeWindow, FtkWindow, std::array<int, 2>, void, std::array<int, 2>>* m_Signal;
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
			FtkMenu* m_Menu;
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
			FtkWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath);

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
						int menuType, int numMenus, bool alwaysVisible, std::vector<FtkMenu*> subMenus);

			inline void setMenu(FtkMenu* menu) { m_Menu = menu; m_HasMenu = true; }

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
			
			inline void beginRender() { m_Renderer->begin(); }

			//getters and setters
			inline void setShader(Shader& shader) { *m_Shader = shader; }
			inline const Shader& getShader() const { return *m_Shader; }
			inline NativeWindow* const getWindow() const { return m_Window; }
			inline input::Mouse* const getMouse() const { return m_Mouse; }
			inline input::Keyboard* const getKeyboard() const { return m_Keyboard; }
			inline FtkMenu* const getMenu() const { return m_Menu; }

			/**
			* Activate the window's renderer
			* 
			**/
			inline void activateRenderer() { m_Renderer = new BatchRenderer2D(); }

			//wrap some base window functions
			inline void clear() { m_Window->clear(); }
			inline bool closed() const { return m_Window->closed(); }

			inline void convertCoords(double& x, double& y) { m_Window->convertCoords(x, y); }

			
			//slot for Window::updateSignal
			void on_WindowUpdate(std::array<int, 2> sig) {
				
				double x = sig[0];
				double y = sig[1];
				
				x /= m_Width;
				y /= m_Height;
				m_Window->m_XScaleFactor *= x;
				m_Window->m_YScaleFactor *= y;
				scale(math::vec2(x, y));
			}
	};
}}}}

#endif
