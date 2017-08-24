
#ifndef _WINDOW_UPDATE_SIGNAL
#define _WINDOW_UPDATE_SIGNAL

namespace fusion {
	
	class WindowUpdateSignal {
	
	private:
		static bool m_Signal;
		
	public:
		
		WindowUpdateSignal();
		
		~WindowUpdateSignal();
		
		inline void sendSignal() const { m_Signal = true; }
		
		inline bool const getSignal() const { return m_Signal; }
		
		inline void resetSignal() const { m_Signal = false; }
		
	};
	
}

#endif
