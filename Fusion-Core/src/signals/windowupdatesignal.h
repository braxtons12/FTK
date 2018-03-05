
#ifndef _WINDOW_UPDATE_SIGNAL
#define _WINDOW_UPDATE_SIGNAL

namespace fusion {
	
	class WindowUpdateSignal {
	
	private:
		static bool m_Signal;
		static int m_Width, m_Height;
	public:
		
		WindowUpdateSignal();
		
		~WindowUpdateSignal();
		
		inline void sendSignal(int width, int height) const { m_Signal = true; m_Width = width; m_Height = height; }
		
		inline bool const getSignal(double& width, double& height) const { width = m_Width; height = m_Height; return m_Signal; }
		
		inline void resetSignal() const { m_Signal = false; }
		
	};
	
}

#endif
