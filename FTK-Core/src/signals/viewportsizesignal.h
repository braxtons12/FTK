#ifndef _VIEWPORT_SIZE_SIGNAL
#define _VIEWPORT_SIZE_SIGNAL

namespace ftk {

    class ViewportSizeSignal {

        private:
            bool m_ViewSignal, m_PanelSignal;
            int m_WhichSignal;
            float m_Width, m_Height;
            float m_PanelWidth, m_PanelHeight, m_OldPanelWidth, m_OldPanelHeight;
            bool m_PanelType;
            int m_PanelPosition;
        public:
            ViewportSizeSignal()
                : m_ViewSignal(false), m_PanelSignal(false), m_WhichSignal(0), m_Width(0.0f), m_Height(0.0f), m_PanelWidth(0.0f), 
                m_PanelHeight(0.0f), m_PanelType(false), m_PanelPosition(0)
            { }
            ~ViewportSizeSignal() { }

            void sendSignal(float width, float height) {

                m_Width = width; 
                m_Height = height; 
                m_ViewSignal = true; 
                m_WhichSignal = 1;
            }

            inline bool getSignal(float& width, float& height) { width = m_Width; height = m_Height; return m_ViewSignal; }

            void sendSignal(bool panelType, int panelPosition, float panelWidth, float panelHeight, 
                            float oldPanelWidth, float oldPanelHeight) {

                m_PanelType = panelType;
                m_PanelPosition = panelPosition;
                m_PanelWidth = panelWidth;
                m_PanelHeight = panelHeight;
                m_OldPanelWidth = oldPanelWidth;
                m_OldPanelHeight = oldPanelHeight;
                m_PanelSignal = true;
                m_WhichSignal = 2;
            }

            bool getSignal(bool& panelType, int& panelPosition, float& panelWidth, float& panelHeight,
                            float& oldPanelWidth, float& oldPanelHeight) {
                
                panelType = m_PanelType;
                panelPosition = m_PanelPosition;
                panelWidth = m_PanelWidth;
                panelHeight = m_PanelHeight;
                oldPanelWidth = m_OldPanelWidth;
                oldPanelHeight = m_OldPanelHeight;
                return m_PanelSignal;
            }

            void resetSignal() { 
                
                if(m_WhichSignal == 1) {
                    m_ViewSignal = false;
                    if(m_PanelSignal) m_WhichSignal = 2;
                    else m_WhichSignal = 0;
                } else if(m_WhichSignal == 2) {
                    m_PanelSignal = false;
                    if(m_ViewSignal) m_WhichSignal = 1;
                    else m_WhichSignal = 0;
                }
            }
    };
}
#endif