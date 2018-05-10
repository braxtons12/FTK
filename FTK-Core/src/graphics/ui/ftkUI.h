/**
 * Container class for entire UI
 * Manages all windows
 * 
 * Header File
 * 
 * C 2018 Braxton Salyer
 * 
 **/

#ifndef _FTK_UI
#define _FTK_UI

#include "graphics/ui/ftkwindow.h"

#include <vector>

namespace ftk { namespace core { namespace graphics { namespace ui { 


	class FtkUI : public FTKObject {

		private:
			std::vector<FtkWindow*>* m_Windows;
			std::vector<FtkWindow*>::iterator m_Iterator;
			int m_NumWindows;

		public:
			/**
			* Constructor
			* 
			**/
			FtkUI();

			/**
			* Destructor
			* 
			**/
			~FtkUI();

			/**
			* add a window to the ui from the given parameters
			* 
			**/
			inline void addWindow(const char* name, int width, int height, const char* vertexShaderPath, const char* fragmentShaderPath) {

				m_Windows->push_back(new FtkWindow(name, width, height, vertexShaderPath, fragmentShaderPath));
				m_NumWindows++;
			}

			/**
			* add an already created window to the ui
			* 
			**/
			inline void addWindow(FtkWindow* window) { m_Windows->push_back(window); m_NumWindows++;}

			/**
			* remove the window at i from the ui
			* 
			**/
			inline void removeWindow(int i) { m_Iterator = m_Windows->begin(); m_Windows->erase(m_Iterator+(i)); }

			/**
			* get the window at i
			* 
			**/
			inline FtkWindow* windowAt(int i) { return m_Windows->at(i); }

			//get the number of active windows
			inline int getSize() { return m_NumWindows; }


	};

}}}}

#endif
