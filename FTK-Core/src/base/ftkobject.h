/*
 * Macro class for all Ftk UI elements
 * Provides signal/slot macro functionality similar to Qt
 * Also provides bounds checking to allow easy enable/disablement of child UI elements.
 *
 * Header File
 *
 * C 2018 Braxton Salyer
 *
 */

#ifndef _FTK_OBJECT
#define _FTK_OBJECT

#include "mathLibs/mathLib.h"
#include "signals/signal.h"
#include "graphics/renderables/renderable2D.h"
#include <vector>
#include <array>

namespace ftk { namespace core { namespace graphics {

	//signal types
	#define BOOL_SIGNAL   0
	#define INT_SIGNAL        1
	#define FLOAT_SIGNAL 2
	#define VEC2_SIGNAL    3
	#define VEC3_SIGNAL    4
	#define VEC4_SIGNAL    5
	#define FA5_SIGNAL       6
	#define FA6_SIGNAL       7

	//emit macros
	#define emitBool(index, signal) \
		if(m_SignalsBool.size() > index) { \
			(*m_SignalsBool.at(index))(signal); \
		}

	#define emitInt(index, signal) \
		if(m_SignalsInt.size() > index) { \
			(*m_SignalsInt.at(index))(signal); \
		}

	#define emitFloat(index, signal) \
		if(m_SignalsFloat.size() > index) { \
			(*m_SignalsFloat.at(index))(signal);\
		}

	#define emitVec2(index, signal) \
		if(m_SignalsVec2.size() > index) { \
			(*m_SignalsVec2.at(index))(signal); \
		}

	#define emitVec3(index, signal) \
		if(m_SignalsVec3.size() > index) { \
			(*m_SignalsVec3.at(index))(signal); \
		}

	#define emitVec4(index, signal) \
		if(m_SignalsVec4.size() > index) { \
			(*m_SignalsVec4.at(index))(signal); \
		}

	#define emitFA5(index, signal) \
		if(m_SignalsFA5.size() > index) { \
			(*m_SignalsFA5.at(index))(signal); \
		}

	#define emitFA6(index, signal) \
		if(m_SignalsFA6.size() > index) { \
			(*m_SignalsFA6.at(index))(signal); \
		}

	class FtkObject : public Renderable2D {

	protected:
			FtkObject* m_Parent;
			bool m_Enabled;

		public:
			FtkObject(math::vec3 position, math::vec2 size, math::vec4 color)
				: Renderable2D(position, size, color), m_Parent(nullptr), m_Enabled(true)
			{

			}

			//static vectors storing all of the signal relationships in the UI
			static std::vector<Signal<FtkObject, FtkObject, bool, void, bool>*> m_SignalsBool;
			static std::vector<Signal<FtkObject, FtkObject, int, void, int>*> m_SignalsInt;
			static std::vector<Signal<FtkObject, FtkObject, float, void, float>*> m_SignalsFloat;
			static std::vector<Signal<FtkObject, FtkObject, math::vec2, void, math::vec2>*> m_SignalsVec2;
			static std::vector<Signal<FtkObject, FtkObject, math::vec3, void, math::vec3>*> m_SignalsVec3;
			static std::vector<Signal<FtkObject, FtkObject, math::vec4, void, math::vec4>*> m_SignalsVec4;
			static std::vector<Signal<FtkObject, FtkObject, std::array<float, 5>, void, std::array<float, 5>>*> m_SignalsFA5;
			static std::vector<Signal<FtkObject, FtkObject, std::array<float, 6>, void, std::array<float, 6>>*> m_SignalsFA6;

			//functions to connect the senders' singals to the recievers' slots
			int connect(FtkObject* sender, bool (FtkObject::*signal)(bool), FtkObject* receiver,
						void (FtkObject::*slot)(bool));

			int connect(FtkObject* sender, int (FtkObject::*signal)(int), FtkObject* receiver,
						void (FtkObject::*slot)(int));

			int connect(FtkObject* sender, float (FtkObject::*signal)(float), FtkObject* receiver,
						void (FtkObject::*slot)(float));

			int connect(FtkObject* sender, math::vec2 (FtkObject::*signal)(math::vec2), FtkObject* receiver,
						void (FtkObject::*slot)(math::vec2));

			int connect(FtkObject* sender, math::vec3 (FtkObject::*signal)(math::vec3), FtkObject* receiver,
						void (FtkObject::*slot)(math::vec3));

			int connect(FtkObject* sender, math::vec4 (FtkObject::*signal)(math::vec4), FtkObject* receiver,
						void (FtkObject::*slot)(math::vec4));

			int connect(FtkObject* sender, std::array<float, 5> (FtkObject::*signal)(std::array<float, 5>), FtkObject* receiver,
						void (FtkObject::*slot)(std::array<float, 5>));

			int connect(FtkObject* sender, std::array<float, 6> (FtkObject::*signal)(std::array<float, 6>), FtkObject* receiver,
						void (FtkObject::*slot)(std::array<float, 6>));

			//disconnect the indicated signal relationship
			void disconnect(int type, int index);

			virtual bool checkBounds(FtkObject* renderable) = 0;
			virtual bool checkBounds(Renderable2D* renderable) = 0;

			inline void setParent(FtkObject* parent) { m_Parent = parent; }
			inline bool isEnabled() const { return m_Enabled; }
	};
}}}
#endif
