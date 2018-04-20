/**
 * Container class for entire UI
 * Manages all windows
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

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
			/**
			* Constructor
			* 
			**/
			FusionUI();

			/**
			* Destructor
			* 
			**/
			~FusionUI();

			/**
			* add a window to the ui from the given parameters
			* 
			**/
			inline void addWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath) {

				m_Windows->push_back(new FusionWindow(name, width, height, vertexShaderPath, fragmentShaderPath));
				m_NumWindows++;
			}

			/**
			* add an already created window to the ui
			* 
			**/
			inline void addWindow(FusionWindow* window) { m_Windows->push_back(window); m_NumWindows++;}

			/**
			* remove the window at i from the ui
			* 
			**/
			inline void removeWindow(int i) { m_Iterator = m_Windows->begin(); m_Windows->erase(m_Iterator+(i)); }

			/**
			* get the window at i
			* 
			**/
			inline FusionWindow* windowAt(int i) { return m_Windows->at(i); }

			//get the number of active windows
			inline int getSize() { return m_NumWindows; }


	};

}}}}

#endif
