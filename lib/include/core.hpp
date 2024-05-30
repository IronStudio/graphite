#pragma once


#ifdef GR_STATIC
	#define GR_CORE
#elif defined(GR_SHARED)
	#ifdef GR_WINDOWS
		#ifdef GR_BUILD_LIB
			#define GR_CORE __declspec(dllexport)
		#else
			#define GR_CORE __declspec(dllimport)
		#endif
	#else
		#define GR_CORE
	#endif
#else
	#error You must define either 'GR_STATIC' or 'GR_SHARED'
#endif