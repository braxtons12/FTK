/**
 * Container class for entire UI
 * Manages all windows
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "ftkUI.h"

namespace ftk { namespace core { namespace graphics { namespace ui { 
	
	/**
	 * Constructor
	 * 
	 **/
	FtkUI::FtkUI() {
		
		m_Windows = new std::vector<FtkWindow*>();
		m_Iterator = m_Windows->begin();
		m_NumWindows = 0;
	}
	
	/**
	 * Destructor
	 * 
	 **/
	FtkUI::~FtkUI() {
		
		m_NumWindows = 0;
		delete m_Windows;
	}
}}}}
