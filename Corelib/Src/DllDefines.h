#pragma once

#ifdef SYSTEM_WINDOWS
	#ifdef SYSTEM_BUILD_DLL
		#define EXTERNAL __declspec(dllexport) 
	#else
		#define EXTERNAL __declspec(dllimport)
	#endif // SYSTEM_BUILD_DLL

#endif
