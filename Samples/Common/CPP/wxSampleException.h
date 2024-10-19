#ifndef WX_SAMPLE_EXCEPTION_H_INCLUDED
#define WX_SAMPLE_EXCEPTION_H_INCLUDED

#include <wx/string.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
#else
	#include <Core/NCore.hpp>
#endif

namespace Neurotec { namespace Samples
{

class wxSampleException : public ::Neurotec::NError
{
public:
	wxSampleException(const NStringWrapper & message, NResult result = -1)
		: ::Neurotec::NError(result, message)
	{
	}
};

inline void N_NO_RETURN ThrowSampleException(const NStringWrapper & message, NResult result = -1) { throw new wxSampleException(message, result); }

}}

#endif // WX_SAMPLE_EXCEPTION_H_INCLUDED
