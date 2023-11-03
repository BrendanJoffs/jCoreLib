#pragma once

#include <stdio.h>
#include <iostream>

#include "../Include/DLL.h"

#ifdef DEBUG
#define LOGGER_DEFAULT_REPORT_LEVEL Core::LogLevel::Info;
#endif //DEBUG

#ifdef RELEASE
#define LOGGER_DEFAULT_REPORT_LEVEL Core::LogLevel::Warn;
#endif // RELEASE

#ifdef DIST
#define LOGGER_DEFAULT_REPORT_LEVEL Core::LogLevel::Fatal;
#endif // DIST

namespace Core
{

	enum class LogLevel
	{
		Trace,
		Info,
		Debug,
		Warn,
		Error,
		Fatal
	};
	

	class __Reference Logger
	{
	public:
		
	private:
		static inline LogLevel DefaultReportLevel = LOGGER_DEFAULT_REPORT_LEVEL;
	};
}