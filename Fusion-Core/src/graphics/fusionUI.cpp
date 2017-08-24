#include "fusionUI.h"

namespace fusion { namespace core { namespace graphics {
	
	FusionUI::FusionUI() {
		
		m_Windows = new std::vector<window::FusionWindow*>();
		m_Iterator = m_Windows->begin();
		m_NumWindows = 0;
	}
	
	FusionUI::~FusionUI() {
		
		m_NumWindows = 0;
		delete m_Windows;
	}
}}}
