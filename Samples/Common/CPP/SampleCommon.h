#ifndef SAMPLE_COMMON_H_INCLUDED
#define SAMPLE_COMMON_H_INCLUDED

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NMedia/NMedia.hpp>
#else
	#include <NCore.hpp>
	#include <NMedia.hpp>
#endif

namespace Neurotec { namespace Samples { namespace Common
{

NString GetOpenFileFilter();

NString GetSaveFileFilter();

NString GetOpenFileFilterString(bool addAllImage, bool addAllFiles);

NString GetSaveFileFilterString();

bool GetTrialModeFlag();

}}}

#endif // SAMPLE_COMMON_H_INCLUDED
