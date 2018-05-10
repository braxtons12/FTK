/**
 * Wrapper for the basic Window class.
 * Enables more UI-friendly operations
 * DOES NOT extend Window, but rather serves as a container for it
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "ftkwindow.h"

namespace ftk { namespace core { namespace graphics { namespace ui { 
	
	/**
	 * Initialize the window
	 * 
	 **/
	void FtkWindow::init() {
		
		m_Window = new NativeWindow(m_Name, m_Width, m_Height);
		
		m_Window->setSignalIndex(connect(m_Window, (math::vec2 (FTKObject::*)(math::vec2))&NativeWindow::updateSignal, 
				this, (void (FTKObject::*)(math::vec2))&FtkWindow::on_WindowUpdate));
		
		m_Mouse = &input::Mouse::GetInstance();
		m_Keyboard = &input::Keyboard::GetInstance();
		
		m_Shader = new Shader(m_VertexShaderPath, m_FragmentShaderPath);
		m_Shader->enable();

		m_Renderables = new std::vector<Renderable2D*>;

		m_Shader->enable();
	}
	
	/**
	 * Constructor
	 * 
	 **/
	FtkWindow::FtkWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath)
		: m_Name(name), m_Width(width), m_Height(height), m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath),
		m_HasMenu(false)
	{
		init();
	}
	
	/**
	 * Used to scale the container when the Window is resized
	 * 
	 **/
	void FtkWindow::scale(math::vec2 scale) {

		m_Width *= scale.m_x;
		m_Height *= scale.m_y;
		m_Window->setWidth(((int)m_Width));
		m_Window->setHeight(((int)m_Height));
		
	}

	/**
	 * Create the window menu from the given parameters
	 * 
	 **/
	void FtkWindow::setMenu(math::vec3 position, math::vec2 size, Color colorOff, Color colorNormal, Color colorHover, 
							   int state, int menuType, int numMenus, bool alwaysVisible, std::vector<FtkMenu*> subMenus) 
	{
		m_Menu = new FtkMenu(position, size, colorOff, colorNormal, colorHover, state, menuType, alwaysVisible, m_Window);
		for (int i = 0; i < numMenus; ++i) {
			m_Menu->addSubMenu(subMenus.at(i));
		}
		m_HasMenu = true;
	}

	/**
	 * Update the state of the window content
	 * 
	 **/
	void FtkWindow::update() {

		if(m_HasMenu) {

			m_Menu->update();
		}
		
	}

	/**
	 * Render the contents of the window
	 * 
	 **/
	void FtkWindow::render() {

		for(int i = 0; i < m_Renderables->size(); ++i) {

			m_Renderables->at(i)->submit(m_Renderer);
		}

		if(m_HasMenu) m_Menu->submit(m_Renderer);

		m_Renderer->end();
		m_Renderer->flush();

		m_Window->update();
		
		delete m_Renderables;
		m_Renderables = new std::vector<Renderable2D*>; 
	}

}}}}
