#pragma once

//Basic DLL setup stuff

#ifdef SYSTEM_BUILD_DLL
#define __Reference __declspec(dllexport)

#else
#define __Reference __declspec(dllimport)
#endif