#ifndef _PANEL_SIZE_SIGNAL
#define _PANEL_SIZE_SIGNAL

namespace ftk { 

    class PanelSizeSignal {

        private:
            bool m_Signal;
            float m_Width, m_Height;

        public:
            PanelSizeSignal() 
                : m_Signal(false), m_Width(0.0f), m_Height(0.0f)
            { }
            ~PanelSizeSignal() { }

            inline void sendSignal(float width, float height) { m_Signal = true; m_Width = width; m_Height = height; }
            inline bool const getSignal(float &width, float &height) const { height = m_Height; width = m_Width; return m_Signal; }
            inline void resetSignal() { m_Signal = false; }
    };
}
#endif