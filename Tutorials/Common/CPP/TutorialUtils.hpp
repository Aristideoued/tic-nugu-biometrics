#ifndef TUTORIAL_UTILS_HPP_INCLUDED
#define TUTORIAL_UTILS_HPP_INCLUDED

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
#else
	#include <NCore.hpp>
#endif

// system headers
#ifndef N_WINDOWS
	#ifndef _GNU_SOURCE
		#define _GNU_SOURCE
	#endif
#else
	#ifndef _CRT_SECURE_NO_WARNINGS
		#define _CRT_SECURE_NO_WARNINGS
	#endif // !defined(_CRT_SECURE_NO_WARNINGS)
	#ifndef _CRT_NON_CONFORMING_SWPRINTFS
		#define _CRT_NON_CONFORMING_SWPRINTFS
	#endif // !defined(_CRT_NON_CONFORMING_SWPRINTFS)
#endif

#ifndef N_APPLE_FRAMEWORKS
	#include <NCore.hpp>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef N_WINDOWS

#ifndef TEMP_FAILURE_RETRY
#define TEMP_FAILURE_RETRY
#endif

#ifdef N_UNICODE

#include <tchar.h>

#define main			_tmain
#define printf			_tprintf
#define sprintf			_stprintf
#define sprintf_s		_stprintf_s
#define strcpy			_tcscpy
#define strcmp			_tcscmp
#define _stricmp		_tcsicmp
#define strlen			_tcslen
#define fopen			_tfopen
#define fputc			_fputtc
#define fopen_s			_tfopen_s
#define atoi			_ttoi
#define atof			_wtof
#define getc			_gettc
#define getchar			_gettchar
#define sscanf			_stscanf
#define sscanf_s		_stscanf_s
#define fputs			_fputts
#define scanf			_tscanf
#define scanf_s			_tscanf_s
#define _makepath		_tmakepath
#define _makepath_s		_tmakepath_s
#define _splitpath_s	_tsplitpath_s
#define _splitpath		_tsplitpath
#define fgets			_fgetts
#define fprintf			_ftprintf
#endif

#else

#ifdef N_UNICODE
#error "Tutorial string operations do not support UNICODE"
#endif

#include <errno.h>
#ifndef TEMP_FAILURE_RETRY
#define TEMP_FAILURE_RETRY(expr) \
	({ \
		long int _res; \
		do _res = (long int) (expr); \
		while (_res == -1L && errno == EINTR); \
		_res; \
	})
#endif

#define _stricmp strcasecmp

#endif

#if defined(N_CPP) || defined(N_GCC) || defined(N_CLANG)
	#define TUTORIAL_INLINE inline
#else
	#define TUTORIAL_INLINE
#endif

namespace Neurotec
{
inline std::ostream& operator<<(std::ostream& stream, HNString hString)
{
N_TRY_NR
	if (hString)
	{
		const NAChar * szBuffer = NULL;
		NInt bufferLength;
		N_CHECK(NStringGetBufferA(hString, &bufferLength, &szBuffer));
		stream << szBuffer;
	}
	else
	{
		stream << "(null)";
	}
N_TRY_ENR
	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const NString & value)
{
	stream << value.GetHandle();
	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const NChar * szValue)
{
	stream << NString(szValue);
	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, HNObject hObject)
{
N_TRY_NR
	HNString hString = NULL;
	if (hObject)
	{
		N_CHECK(NObjectToStringN(hObject, NULL, &hString));
		stream << hString;
	}
	else
	{
		stream << "(null)";
	}
N_FINALLY
	NStringFree(hString);
N_TRY_ENDNR
	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const NObject & value)
{
	stream << value.GetHandle();
	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, NByte value)
{
	stream << (int)value;
	return stream;
}

static TUTORIAL_INLINE NResult PrintError(NResult result)
{
	NErrorReport(result);
	return result;
}

static NResult LastError(NError error)
{	
	if (error.GetCode() == N_E_AGGREGATE)
	{
		error = error.GetInnerError();
		return LastError(error);
	}
	NError::Report(error.GetCode(),error);
	return error.GetCode();
}

static TUTORIAL_INLINE void OnStart(const NChar * szTitle, const NChar * szDescription, const NChar * szVersion, const NChar * szCopyright, int argc, NChar * * argv)
{
	int i;

	printf(N_T("%s tutorial\n"), szTitle);
	printf(N_T("description: %s\n"), szDescription);
	printf(N_T("version: %s\n"), szVersion);
	printf(N_T("copyright: %s\n\n"), szCopyright);

	if(argc > 1)
	{
		printf(N_T("arguments:\n"));
		for(i = 1; i < argc; i++)
		{
			printf(N_T("\t%s\n"), argv[i]);
		}
		printf(N_T("\n"));
	}

	NCore::OnStart();
}

static TUTORIAL_INLINE void OnExit()
{
	NCore::OnExit(NFalse);
}

static TUTORIAL_INLINE bool GetTrialModeFlag()
{
#ifdef N_MAC
	NString binDir = IO::NPath::Combine(IO::NPath::GetDirectoryName(IO::NPath::GetDirectoryName(IO::NPath::GetDirectoryName(IO::NPath::GetDirectoryName(IO::NPath::GetDirectoryName(IO::NPath::GetDirectoryName(NCore::NativeModuleOf().GetFileName())))))), "Bin");
#else
	NString binDir = IO::NPath::GetDirectoryName(IO::NPath::GetDirectoryName(NCore::NativeModuleOf().GetFileName()));
#endif
	NString filePath = IO::NPath::Combine(IO::NPath::Combine(binDir, "Licenses"), "TrialFlag.txt");
	if (IO::NFile::Exists(filePath))
	{
		NArrayWrapper< ::Neurotec::NString> lines = IO::NFile::ReadAllLines(filePath);
		if (lines.GetCount() > 0 && lines[0].Trim().ToLower() == N_T("true"))
		{
			return true;
		}
	}
	else
	{
		printf(N_T("Failed to locate file: %s\n"), filePath.GetBuffer());
	}
	return false;
}
}
#endif // TUTORIAL_UTILS_HPP_INCLUDED
