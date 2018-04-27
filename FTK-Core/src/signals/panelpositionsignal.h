#ifndef _VIEWPORT_POSITION_SIGNAL
#define _VIEWPORT_POSITION_SIGNAL

#include "mathLibs/mathLib.h"

namespace ftk {

    class PanelPositionSignal {

        private:
            bool m_Signal;
            float m_x, m_y;

        public:
            PanelPositionSignal() 
                : m_Signal(false), m_x(0.0f), m_y(0.0f)
            { }

            ~PanelPositionSignal() { }

            inline void sendSignal(float x, float y) { m_x = x; m_y = y; m_Signal = true; }
            inline bool getSignal(float&x, float& y) { x = m_x; y = m_y; return m_Signal; }
            inline void resetSignal() { m_Signal = false; }

    };
}
#endif