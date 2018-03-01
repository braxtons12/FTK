#include "fusionUI.h"

namespace fusion { namespace core { namespace graphics { namespace ui { 
	
	FusionUI::FusionUI() {
		
		m_Windows = new std::vector<FusionWindow*>();
		m_Iterator = m_Windows->begin();
		m_NumWindows = 0;
	}
	
	FusionUI::~FusionUI() {
		
		m_NumWindows = 0;
		delete m_Windows;
	}
}}}}
