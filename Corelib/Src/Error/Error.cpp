#include "Error.h"

std::shared_ptr<Internal::ErrorHandler> Internal::ErrorHandler::Get()
{
	if (m_Instance == nullptr) {
		std::shared_ptr<ErrorHandler> Ptr(new ErrorHandler());
		m_Instance = Ptr;
	}

	return m_Instance;
}

RESULT Internal::ErrorHandler::Post(Message* Msg)
{
	if (*Msg >= m_ReportingLevel) { m_LastMessage = Msg; }
	else
	{
#ifndef DISABLE_WARN
		if (m_SelfWarn) {
			WARN("Attempting to report messages below minimum reporting level. This may cause unnesscary computations to occour. To disable this warning, call SelfWarning(false)");
		}
#endif // !DISABLE_WARN

		RETURN(Flagged);
	}

	if (m_AutoPrint) { std::cout << Msg->operator()() << "\n"; }

	RETURN(Success);
}
