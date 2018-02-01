#include "fusionwindow.h"

namespace fusion { namespace core { namespace graphics { namespace window {
	
	
	void FusionWindow::init() {
		
		m_Window = new Window(m_Name, m_Width, m_Height);
		m_Signal = m_Window->getSignalServer();
		
		m_Mouse = &input::Mouse::GetInstance();
		m_Keyboard = &input::Keyboard::GetInstance();
		
		m_Shader = new Shader(m_VertexShaderPath, m_FragmentShaderPath);
		m_Shader->enable();

		m_PermanentRenderables = new std::vector<const Renderable2d*>;
		
	}
	
	FusionWindow::FusionWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath, bool hasMenu)
		: m_Name(name), m_Width(width), m_Height(height), m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath),
		m_HasMenu(hasMenu)
	{
		init();
	}
	
	void FusionWindow::setMenu(math::vec3 position, math::vec2 size, math::vec4 color, Texture* offTexture, Texture* hoverTexture, 
							   Texture* normalTexture, int state, int menuType std::vector<float> divisions, int numMenus, 
							   std::vector<FusionMenu&> subMenus) 
	{
		m_Menu(position, size, color, offTexture, hoverTexter, normalTexture, state, menuType, divisions, numMenus, m_Window);
		for (int i = 0; i < numMenus; ++i) {
			m_Menu.addSubMenu(subMenus.at(i));
		}
	}
	void FusionWindow::update() {
		
		if (m_Signal->getSignal()) {
			
			this->updateSize(m_Window->getWidth(), m_Window->getHeight());
			m_Signal->resetSignal();
		}

		m_Menu.checkHover();
		m_Menu.submit(m_Renderer);

		for(int i = 0; i < m_PermanentRenderables.size(); ++i) {

			m_PermanentRenderables.at(i)->submit(m_Renderer);
		}
		
		m_Window->clear();
		
		m_Renderer->end();
		m_Renderer->flush();
		m_Window->update();
		
	}

}}}}
