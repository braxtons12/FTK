#ifndef _VIEWPORT_SIZE_SIGNAL
#define _VIEWPORT_SIZE_SIGNAL

namespace fusion {

    class ViewportSizeSignal {

        private:
            bool m_Signal;
            float m_Width, m_Height;
        public:
            ViewportSizeSignal()
                : m_Signal(false), m_Width(0.0f), m_Height(0.0f) 
            { }
            ~ViewportSizeSignal() { }

            inline void sendSignal(float width, float height) { m_Width = width; m_Height = height; m_Signal = true; }
            inline bool getSignal(float& width, float& height) { width = m_Width; height = m_Height; return m_Signal; }
            inline void resetSignal() { m_Signal = false; }
    };
}
#endif