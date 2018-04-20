#ifndef _FUSION_SIGNAL
#define _FUSION_SIGNAL

namespace fusion {
	
	template <typename SENDER, typename RECEIVER, typename RETURN, typename RETURN2, typename... ARGS>
	class Signal {
		
		private:
			SENDER* m_Sender = nullptr;
			RECEIVER* m_Receiver = nullptr;
			RETURN (SENDER::*m_Sig)(ARGS...) = nullptr;
			RETURN2 (RECEIVER::*m_Slot)(RETURN) = nullptr;
			
		public:
			void connect(SENDER* sender, RETURN (SENDER::*signal)(ARGS...), 
						RECEIVER* receiver, RETURN2 (RECEIVER::*slot)(RETURN))
			{
				m_Sender = sender;
				m_Receiver = receiver;
				m_Sig = signal;
				m_Slot = slot;
			}
			
			RETURN2 operator()(ARGS... args) {
				
				RETURN ret = (m_Sender->*m_Sig)(args...);
				
				return (m_Receiver->*m_Slot)(ret);
			}	
	};
}
#endif
