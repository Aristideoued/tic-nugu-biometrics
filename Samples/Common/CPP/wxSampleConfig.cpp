#include <wx/config.h>
#include <wx/fileconf.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/app.h>
#include <wx/log.h>
#include "wxSampleConfig.h"
#include "wxSampleException.h"

namespace Neurotec { namespace Samples
{

wxString wxSampleConfig::sm_userDataDir;

void wxSampleConfig::Init()
{
	try
	{
		sm_userDataDir = wxStandardPaths::Get().GetUserLocalDataDir();
		sm_userDataDir = sm_userDataDir.Left(sm_userDataDir.Length() - wxApp::GetInstance()->GetAppName().Length());
		sm_userDataDir.Append(wxT("Neurotechnology"));
		if (!wxDir::Exists(sm_userDataDir))
		{
			if (!wxFileName::Mkdir(sm_userDataDir))
			{
				ThrowSampleException(wxString::Format(wxT("Failed to create data directory: %s"),
					sm_userDataDir.c_str()));
			}
		}
		sm_userDataDir.Append(wxFileName::GetPathSeparator());
		wxString shortSampleName = wxApp::GetInstance()->GetAppName();
		shortSampleName.Replace(wxT("WX"), wxEmptyString);
		sm_userDataDir.Append(shortSampleName);
		if (!wxDir::Exists(sm_userDataDir))
		{
			if (!wxFileName::Mkdir(sm_userDataDir))
			{
				ThrowSampleException(wxString::Format(wxT("Failed to create data directory: %s"),
					sm_userDataDir.c_str()));
			}
		}
	}
	catch (const NError& error)
	{
		wxLogError(wxString::Format(wxT("%s. Configuration and database will be saved to working directory."),
			((wxString)error.GetMessage()).c_str()));

		sm_userDataDir = ::wxGetCwd();
	}

	wxString appName = wxApp::GetInstance()->GetAppName().c_str();
	wxFileName configFileName(sm_userDataDir,
		wxString::Format(wxT("%s.cfg"), appName.c_str()));
	wxString configLocalPath = configFileName.GetFullPath();
	wxConfigBase::Set(new wxFileConfig(appName, wxT("Neurotechnology"),
		configLocalPath, wxEmptyString, wxCONFIG_USE_LOCAL_FILE));
}

void wxSampleConfig::Save()
{
	wxConfigBase *config = wxConfigBase::Get();
	wxConfigBase::Set(NULL);
	config->Flush();
	delete config;
}

wxString wxSampleConfig::GetUserDataDir()
{
	return sm_userDataDir;
}

}}
