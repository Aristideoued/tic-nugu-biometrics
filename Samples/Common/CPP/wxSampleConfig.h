#ifndef WX_SAMPLE_CONFIG_H_INCLUDED
#define WX_SAMPLE_CONFIG_H_INCLUDED

#include <wx/string.h>

namespace Neurotec { namespace Samples
{

class wxSampleConfig
{
public:
	static void Init();
	static void Save();
	static wxString GetUserDataDir();

private:
	static wxString sm_userDataDir;
};

}}

#endif // WX_SAMPLE_CONFIG_H_INCLUDED
