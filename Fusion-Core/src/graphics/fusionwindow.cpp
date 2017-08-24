#include "fusionwindow.h"

namespace fusion { namespace core { namespace graphics { namespace window {
	
	
	void FusionWindow::init() {
		
		m_Child = new Window(m_Name, m_Width, m_Height);
		m_Signal = m_Child->getSignalServer();
		
		m_Mouse = &input::Mouse::GetInstance();
		m_Keyboard = &input::Keyboard::GetInstance();
		
		m_Shader = new Shader(m_VertexShaderPath, m_FragmentShaderPath);
		m_Shader->enable();
		
	}
	
	FusionWindow::FusionWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath)
		: m_Name(name), m_Width(width), m_Height(height), m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath) 
	{
		init();
	}
	
	void FusionWindow::update() {
		
		if (m_Signal->getSignal()) {
			
			this->updateSize(m_Child->getWidth(), m_Child->getHeight());
			m_Signal->resetSignal();
		}
		
		m_Child->clear();
		
		m_Renderer->end();
		m_Renderer->flush();
		m_Child->update();
		
	}

}}}}
