#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("LicenseActivation");
const NChar description[] = N_T("Demonstrates license activation online using generated diagnostics Id");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2011-2024 Neurotechnology");

static int usage()
{
	printf(N_T("usage: %s [id file name] [lic file name]\n"), title);
	return 1;
}

int main(int argc, NChar *argv[])
{
	NResult result = N_OK;
	HNString hId = NULL;
	HNString hLicense = NULL;

	OnStart(title, description, version, copyright, argc, argv);

	if (argc != 3)
	{
		return usage();
	}
	
	/* Load id file (it can be generated using IdGeneration tutorial or ActivationWizardDotNet) */
	result = NFileReadAllTextCN(argv[1], &hId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to read id from file. error code: %d\n"), result);
		goto FINALLY;
	}

	/* Generate license for specified id */
	result = NLicenseActivateOnlineN(hId, &hLicense);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("online activation failed. error code: %d\n"), result);
		goto FINALLY;
	}

	/* Write license to file */
	result = NFileWriteAllTextCN(argv[2], hLicense);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to write license to file. error code: %d\n"), result);
		goto FINALLY;
	}
	
	printf(N_T("license saved to file %s\n"), argv[2]);

	result = N_OK;
FINALLY:
	{
		NResult res2 = NStringSet(NULL, &hLicense);
		if (NFailed(res2)) PrintErrorMsg(N_T("NStringSet() error has occured (code: %d)\n"), res2);
		res2 = NStringSet(NULL, &hId);
		if (NFailed(res2)) PrintErrorMsg(N_T("NStringSet() error has occured (code: %d)\n"), res2);
	}

	OnExit();

	return result;
}
