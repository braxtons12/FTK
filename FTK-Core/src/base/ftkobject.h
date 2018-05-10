/*
 * Macro class for all FTK UI elements
 * Provides signal/slot macro functionality similar to Qt
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
#include <vector>
#include <array>

namespace ftk { namespace core {

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

	class FTKObject {

		public:
			static std::vector<Signal<FTKObject, FTKObject, bool, void, bool>*> m_SignalsBool;
			static std::vector<Signal<FTKObject, FTKObject, int, void, int>*> m_SignalsInt;
			static std::vector<Signal<FTKObject, FTKObject, float, void, float>*> m_SignalsFloat;
			static std::vector<Signal<FTKObject, FTKObject, math::vec2, void, math::vec2>*> m_SignalsVec2;
			static std::vector<Signal<FTKObject, FTKObject, math::vec3, void, math::vec3>*> m_SignalsVec3;
			static std::vector<Signal<FTKObject, FTKObject, math::vec4, void, math::vec4>*> m_SignalsVec4;
			static std::vector<Signal<FTKObject, FTKObject, std::array<float, 5>, void, std::array<float, 5>>*> m_SignalsFA5;
			static std::vector<Signal<FTKObject, FTKObject, std::array<float, 6>, void, std::array<float, 6>>*> m_SignalsFA6;

			int connect(FTKObject* sender, bool (FTKObject::*signal)(bool), FTKObject* receiver,
						void (FTKObject::*slot)(bool));

			int connect(FTKObject* sender, int (FTKObject::*signal)(int), FTKObject* receiver,
						void (FTKObject::*slot)(int));

			int connect(FTKObject* sender, float (FTKObject::*signal)(float), FTKObject* receiver,
						void (FTKObject::*slot)(float));

			int connect(FTKObject* sender, math::vec2 (FTKObject::*signal)(math::vec2), FTKObject* receiver,
						void (FTKObject::*slot)(math::vec2));

			int connect(FTKObject* sender, math::vec3 (FTKObject::*signal)(math::vec3), FTKObject* receiver,
						void (FTKObject::*slot)(math::vec3));

			int connect(FTKObject* sender, math::vec4 (FTKObject::*signal)(math::vec4), FTKObject* receiver,
						void (FTKObject::*slot)(math::vec4));

			int connect(FTKObject* sender, std::array<float, 5> (FTKObject::*signal)(std::array<float, 5>), FTKObject* receiver,
						void (FTKObject::*slot)(std::array<float, 5>));

			int connect(FTKObject* sender, std::array<float, 6> (FTKObject::*signal)(std::array<float, 6>), FTKObject* receiver,
						void (FTKObject::*slot)(std::array<float, 6>));

			void disconnect(int type, int index);
	};
}}
#endif
