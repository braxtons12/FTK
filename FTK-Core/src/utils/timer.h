/**
 * Utility class to get the time in milliseconds
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _TIMER
#define _TIMER

#include <time.h>

namespace ftk { 
	
	class Timer {
	
		private:
			time_t start, end;
			
		public:
			
			Timer() {
				start = time(NULL);
			}
			
			inline void reset() { start = time(NULL); }
			inline float elapsed() { end = time(NULL); return (float)(end - start); }
			inline float fps() { return (float) 1/(float)(end - start); }
			
	};
}

#endif
