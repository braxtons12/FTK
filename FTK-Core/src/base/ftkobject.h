#ifndef _FTK_OBJECT
#define _FTK_OBJET

#include "signals/signal.h"
#include <vector>

namespace ftk { namespace core { 
	
	class FTKObject {
		
		private:
			std::vector<Signal<FTKObject, FTKObject, int, void, int>> m_SignalsInt;
			
	};
}}
#endif
