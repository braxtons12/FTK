#ifndef _FUSION_UI
#define _FUSION_UI

#include "graphics/ui/fusionwindow.h"

#include <vector>

namespace fusion { namespace core { namespace graphics { namespace ui { 


	class FusionUI {

	private:

		std::vector<FusionWindow*>* m_Windows;
		std::vector<FusionWindow*>::iterator m_Iterator;
		int m_NumWindows;

	public:

		FusionUI();
		~FusionUI();

		inline void addWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath, bool hasMenu) {

			m_Windows->push_back(new FusionWindow(name, width, height, vertexShaderPath, fragmentShaderPath, hasMenu));
			m_NumWindows++;
		}

		inline void addWindow(FusionWindow* window) { m_Windows->push_back(window); m_NumWindows++;}

		inline void removeWindow(int i) { m_Iterator = m_Windows->begin(); m_Windows->erase(m_Iterator+(i)); }

		inline FusionWindow* windowAt(int i) { return m_Windows->at(i); }

		inline int getSize() { return m_NumWindows; }


	};

}}}}

#endif
