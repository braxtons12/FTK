/**
 * Window Signal class
 * Signals to the UI window container to update its relevant attributes
 * 
 * Implementation File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#include "windowupdatesignal.h"

namespace fusion {
	
	bool WindowUpdateSignal::m_Signal = false;
	int WindowUpdateSignal::m_Width = 800;
	int WindowUpdateSignal::m_Height = 600;
	
	WindowUpdateSignal::WindowUpdateSignal() {
		
	}
	
	WindowUpdateSignal::~WindowUpdateSignal() {
		
	}
}
