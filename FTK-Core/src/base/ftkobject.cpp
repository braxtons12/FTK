#include "ftkobject.h"

namespace ftk { namespace core { namespace graphics {

	std::vector<Signal<FtkObject, FtkObject, bool, void, bool>*> FtkObject::m_SignalsBool =
								std::vector<Signal<FtkObject, FtkObject, bool, void, bool>*>();
	std::vector<Signal<FtkObject, FtkObject, int, void, int>*> FtkObject::m_SignalsInt =
								std::vector<Signal<FtkObject, FtkObject, int, void, int>*>();
	std::vector<Signal<FtkObject, FtkObject, float, void, float>*> FtkObject::m_SignalsFloat =
								std::vector<Signal<FtkObject, FtkObject, float, void, float>*>();
	std::vector<Signal<FtkObject, FtkObject, math::vec2, void, math::vec2>*> FtkObject::m_SignalsVec2 =
								std::vector<Signal<FtkObject, FtkObject, math::vec2, void, math::vec2>*>();
	std::vector<Signal<FtkObject, FtkObject, math::vec3, void, math::vec3>*> FtkObject::m_SignalsVec3 =
								std::vector<Signal<FtkObject, FtkObject, math::vec3, void, math::vec3>*>();
	std::vector<Signal<FtkObject, FtkObject, math::vec4, void, math::vec4>*> FtkObject::m_SignalsVec4 =
								std::vector<Signal<FtkObject, FtkObject, math::vec4, void, math::vec4>*>();
	std::vector<Signal<FtkObject, FtkObject, std::array<float, 5>, void, std::array<float, 5>>*> FtkObject::m_SignalsFA5 =
								std::vector<Signal<FtkObject, FtkObject, std::array<float, 5>, void, std::array<float, 5>>*>();
	std::vector<Signal<FtkObject, FtkObject, std::array<float, 6>, void, std::array<float, 6>>*> FtkObject::m_SignalsFA6 =
								std::vector<Signal<FtkObject, FtkObject, std::array<float, 6>, void, std::array<float, 6>>*>();

	int FtkObject::connect(FtkObject* sender, bool (FtkObject::*signal)(bool), FtkObject* receiver,
						   void (FtkObject::*slot)(bool))
	{
		m_SignalsBool.push_back(new Signal<FtkObject, FtkObject, bool, void, bool>());
		m_SignalsBool.at(m_SignalsBool.size() - 1)->connect(sender, signal, receiver, slot);
		return m_SignalsBool.size() -1;
	}

	int FtkObject::connect(FtkObject* sender, int (FtkObject::*signal)(int), FtkObject* receiver,
						   void (FtkObject::*slot)(int))
	{
		m_SignalsInt.push_back(new Signal<FtkObject, FtkObject, int, void, int>());
		m_SignalsInt.at(m_SignalsInt.size() - 1)->connect(sender, signal, receiver, slot);
		return m_SignalsInt.size() -1;
	}

	int FtkObject::connect(FtkObject* sender, float (FtkObject::*signal)(float), FtkObject* receiver,
						void (FtkObject::*slot)(float))
	{
		m_SignalsFloat.push_back(new Signal<FtkObject, FtkObject, float, void, float>());
		m_SignalsFloat.at(m_SignalsFloat.size() - 1)->connect(sender, signal, receiver, slot);
		return m_SignalsFloat.size() -1;
	}

	int FtkObject::connect(FtkObject* sender, math::vec2 (FtkObject::*signal)(math::vec2), FtkObject* receiver,
						   void (FtkObject::*slot)(math::vec2))
	{
		m_SignalsVec2.push_back(new Signal<FtkObject, FtkObject, math::vec2, void, math::vec2>());
		m_SignalsVec2.at(m_SignalsVec2.size() - 1)->connect(sender, signal, receiver, slot);
		return m_SignalsVec2.size() -1;
	}

	int FtkObject::connect(FtkObject* sender, math::vec3 (FtkObject::*signal)(math::vec3), FtkObject* receiver,
						   void (FtkObject::*slot)(math::vec3))
	{
		m_SignalsVec3.push_back(new Signal<FtkObject, FtkObject, math::vec3, void, math::vec3>());
		m_SignalsVec3.at(m_SignalsVec3.size() - 1)->connect(sender, signal, receiver, slot);
		return m_SignalsVec3.size() -1;
	}

	int FtkObject::connect(FtkObject* sender, math::vec4 (FtkObject::*signal)(math::vec4), FtkObject* receiver,
							void (FtkObject::*slot)(math::vec4))
	{
		m_SignalsVec4.push_back(new Signal<FtkObject, FtkObject, math::vec4, void, math::vec4>());
		m_SignalsVec4.at(m_SignalsVec4.size() -1)->connect(sender, signal, receiver, slot);
		return m_SignalsVec4.size() -1;
	}

	int FtkObject::connect(FtkObject* sender, std::array<float, 5> (FtkObject::*signal)(std::array<float, 5>), FtkObject* receiver,
				void (FtkObject::*slot)(std::array<float, 5>))
	{
		m_SignalsFA5.push_back(new Signal<FtkObject, FtkObject, std::array<float, 5>, void, std::array<float, 5>>());
		m_SignalsFA5.at(m_SignalsFA5.size() -1)->connect(sender, signal, receiver, slot);
		return m_SignalsFA5.size() -1;
	}

	int FtkObject::connect(FtkObject* sender, std::array<float, 6> (FtkObject::*signal)(std::array<float, 6>), FtkObject* receiver,
				void (FtkObject::*slot)(std::array<float, 6>))
	{
		m_SignalsFA6.push_back(new Signal<FtkObject, FtkObject, std::array<float, 6>, void, std::array<float, 6>>());
		m_SignalsFA6.at(m_SignalsFA6.size() -1)->connect(sender, signal, receiver, slot);
		return m_SignalsFA6.size() -1;
	}

	void FtkObject::disconnect(int type, int index) {

		switch(type) {

			case BOOL_SIGNAL:
				if(m_SignalsBool.size() > index) {

					m_SignalsBool.at(index)->disconnect();
					m_SignalsBool.at(index) = nullptr;
					m_SignalsBool.erase(m_SignalsBool.begin() + index);
				}
				break;

			case INT_SIGNAL:
				if(m_SignalsInt.size() > index) {

					m_SignalsInt.at(index)->disconnect();
					m_SignalsInt.at(index) = nullptr;
					m_SignalsInt.erase(m_SignalsInt.begin() + index);
				}
				break;

			case FLOAT_SIGNAL:
				if(m_SignalsFloat.size() > index) {

					m_SignalsFloat.at(index)->disconnect();
					m_SignalsFloat.at(index) = nullptr;
					m_SignalsFloat.erase(m_SignalsFloat.begin() + index);
				}
				break;

			case VEC2_SIGNAL:
				if(m_SignalsVec2.size() > index) {

					m_SignalsVec2.at(index)->disconnect();
					m_SignalsVec2.at(index) = nullptr;
					m_SignalsVec2.erase(m_SignalsVec2.begin() + index);
				}
				break;

			case VEC3_SIGNAL:
				if(m_SignalsVec3.size() > index) {

					m_SignalsVec3.at(index)->disconnect();
					m_SignalsVec3.at(index) = nullptr;
					m_SignalsVec3.erase(m_SignalsVec3.begin() + index);
				}
				break;

			case VEC4_SIGNAL:
				if(m_SignalsVec4.size() > index) {

					m_SignalsVec4.at(index)->disconnect();
					m_SignalsVec4.at(index) = nullptr;
					m_SignalsVec4.erase(m_SignalsVec4.begin() + index);
				}
				break;

			case FA5_SIGNAL:
				if(m_SignalsFA5.size() > index) {

					m_SignalsFA5.at(index)->disconnect();
					m_SignalsFA5.at(index) = nullptr;
					m_SignalsFA5.erase(m_SignalsFA5.begin() + index);
				}
				break;

			case FA6_SIGNAL:
				if(m_SignalsFA6.size() > index) {

					m_SignalsFA6.at(index)->disconnect();
					m_SignalsFA6.at(index) = nullptr;
					m_SignalsFA6.erase(m_SignalsFA6.begin() + index);
				}
				break;
		}
	}
}}}
