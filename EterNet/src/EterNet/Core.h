#pragma once

#ifdef ETN_PLATFORM_WINDOWS
	#ifdef ETN_BUILD_DLL
		#define ETN_API __declspec(dllexport)
	#else
		#define ETN_API __declspec(dllimport)
	#endif
#endif

#define MTU 1400
