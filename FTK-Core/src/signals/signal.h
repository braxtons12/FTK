/**
 * Generic Implementation of Signals and Slots
 * Modeled somewhat after the method used by QT
 *
 * Header File
 *
 * C 2018 Braxton Salyer
 *
 **/

#ifndef _FTK_SIGNAL
#define _FTK_SIGNAL

namespace ftk {

	template <typename SENDER, typename RECEIVER, typename RETURN, typename RETURN2, typename... ARGS>
	class Signal {

		private:
			SENDER* m_Sender = nullptr;
			RECEIVER* m_Receiver = nullptr;
			RETURN (SENDER::*m_Sig)(ARGS...) = nullptr;
			RETURN2 (RECEIVER::*m_Slot)(RETURN) = nullptr;

		public:
			/*
			 * Connect the sender's signal to the receiver's slot
			 */
			void connect(SENDER* sender, RETURN (SENDER::*signal)(ARGS...),
						  RECEIVER* receiver, RETURN2 (RECEIVER::*slot)(RETURN))
			{
				m_Sender = sender;
				m_Receiver = receiver;
				m_Sig = signal;
				m_Slot = slot;
			}

			/*
			 * disconnect the sender's signal from the receiver's slot
			 */
			void disconnect()
			{
				m_Sender = nullptr;
				m_Receiver = nullptr;
				m_Sig = nullptr;
				m_Slot = nullptr;
			}

			/*
			 * Execute the slot when the signal is fired
			 */
			RETURN2 operator()(ARGS... args) {

				RETURN ret = (m_Sender->*m_Sig)(args...);

				return (m_Receiver->*m_Slot)(ret);
			}
	};
}
#endif
