#pragma once

#include <iostream>
#include <stdlib.h>
#include <queue>

#include "../DllDefines.h"
#include "Error-debug.h"

#ifndef JCORELIB_ERROR_DEBUG_INFO

	#define RESULT void
	#define RETURN(X) return (void)##X

	#define MINIMUM_REPORTING_LEVEL Internal::MessageLevel::Error

	#define DISABLE_TRACE
	#define DISABLE_INFO
	#define DISABLE_DEBUG

	#ifndef JCORELIB_ERROR_SELF_WARNINGS
		#define JCORELIB_ERROR_SELF_WARNINGS true
	#endif // !JCORELIB_ERROR_SELF_WARNING

#endif // !JCORELIB_ERROR_DEBUG_INFO

#pragma region Message level based reporting defines

#define CREATE_MESSAGE(L, X) Internal::Message::Create(L, X)
#define POST(X) Internal::ErrorHandler::Get()->Post(X)

#define TRACE(X)	POST(CREATE_MESSAGE(Internal::MessageLevel::Trace,	X)); 
#define INFO(X)		POST(CREATE_MESSAGE(Internal::MessageLevel::Info,	X)); 
#define DEBUG(X)	POST(CREATE_MESSAGE(Internal::MessageLevel::Debug,	X)); 
#define WARN(X)		POST(CREATE_MESSAGE(Internal::MessageLevel::Warn,	X)); 
#define ERROR(X)	POST(CREATE_MESSAGE(Internal::MessageLevel::Error,	X)); 
#define FATAL(X)	POST(CREATE_MESSAGE(Internal::MessageLevel::Fatal,	X)); 

//Disable calls
	#ifdef DISABLE_TRACE
		#define TRACE(X) 
	#endif // DISABLE_TRACE

	#ifdef DISABLE_INFO
		#define INFO(X) 
	#endif // DISABLE_INFO

	#ifdef DISABLE_DEBUG
		#define DEBUG(X) 
	#endif // DISABLE_DEBUG

	#ifdef DISABLE_WARN
		#define WARN(X) 
	#endif // DISABLE_WARN

	#ifdef DISABLE_ERROR
		#define ERROR(X)
	#endif // DISABLE_ERROR

	#ifdef DISABLE_FATAL
		#define FATAL(X)
	#endif // DISABLE_FATAL

#pragma endregion


namespace Internal {

	enum class MessageLevel : uint8_t {
		
		Trace = 0, //trace calls should use the TRACE(Message) define.
		Info = 1,
		Debug = 2,
		Warn = 3,
		Error = 4,
		Fatal = 5
	};

	struct Message {
	
	private:
		Message(MessageLevel Level, std::string Message)
			: m_Level(Level), m_Message(Message) {}
	public:
		EXTERNAL static Message* Create(Internal::MessageLevel Level, std::string Msg) {
			Message* MSG = new Message(Level, Msg);
			return MSG;
		}

		EXTERNAL std::string& operator()() {
			if (m_Message != "") { return m_Message; }
			std::string Output = "NO_MESSAGE_FOUND";
			return Output;
		}

		EXTERNAL bool operator == (MessageLevel Level) {
			if (m_Level == Level) { return true; }
			return false;
		}

		EXTERNAL bool operator > (MessageLevel Level) {
			if (m_Level > Level) { return true; }
			return false;
		}

		EXTERNAL bool operator >= (MessageLevel Level) {
			if (m_Level >= Level) { return true; }
			return false;
		}

		EXTERNAL bool operator < (MessageLevel Level) {
			if (m_Level < Level) { return true; }
			return false;
		}

		EXTERNAL bool operator <= (MessageLevel Level) {
			if (m_Level <= Level) { return true; }
			return false;
		}
	private:
		std::string m_Message = "";
		MessageLevel m_Level = MessageLevel::Trace;
	};

	class ErrorHandler {
		ErrorHandler() 
			:m_LastMessage(Internal::Message::Create(MessageLevel::Info, "")) { }

	public:
		EXTERNAL static std::shared_ptr<ErrorHandler> Get(); // Gets the current instance, or makes a new one. Will reference count 
		EXTERNAL ~ErrorHandler() = default;

		EXTERNAL RESULT Post(Message* Msg);
		
		EXTERNAL RESULT PrintOnPost(bool Allow) { m_AutoPrint = Allow; RETURN(Success); }
		EXTERNAL RESULT SetBaseMessageLevel(MessageLevel Level) { m_ReportingLevel = Level; RETURN(Success); }

		EXTERNAL RESULT SelfWarning(bool State) { m_SelfWarn = State; RETURN(Success); }
	private:
		static inline std::shared_ptr<ErrorHandler> m_Instance = nullptr;
		MessageLevel m_ReportingLevel = MINIMUM_REPORTING_LEVEL;

		bool m_AutoPrint = false;
		bool m_SelfWarn = JCORELIB_ERROR_SELF_WARNINGS;

		Message* m_LastMessage;
	};

}