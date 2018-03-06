/**
 * Container class for entire UI
 * Manages all windows
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "fusionUI.h"

namespace fusion { namespace core { namespace graphics { namespace ui { 
	
	/**
	 * Constructor
	 * 
	 **/
	FusionUI::FusionUI() {
		
		m_Windows = new std::vector<FusionWindow*>();
		m_Iterator = m_Windows->begin();
		m_NumWindows = 0;
	}
	
	/**
	 * Destructor
	 * 
	 **/
	FusionUI::~FusionUI() {
		
		m_NumWindows = 0;
		delete m_Windows;
	}
}}}}
