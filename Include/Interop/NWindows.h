#ifndef N_WINDOWS_H_INCLUDED
#define N_WINDOWS_H_INCLUDED

#include <Core/NDefs.h>

#ifdef N_WINDOWS
	#ifdef N_MSVC
		#pragma warning(push)
		#pragma warning(disable: 4005)
		#ifdef N_WINDOWS_CE
			#pragma warning(disable: 4201 4214 4115)
		#endif
	#endif
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#ifndef _WIN32_WINNT
	// for Windows 7 support:
	#define _WIN32_WINNT 0x0601
#endif
	#define PSAPI_VERSION 1
	#include <windows.h>
	#ifdef N_MSVC
		#pragma warning(pop)
	#endif
#endif

#endif // !N_WINDOWS_H_INCLUDED
