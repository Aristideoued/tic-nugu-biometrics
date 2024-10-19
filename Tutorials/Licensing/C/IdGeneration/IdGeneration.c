#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("IdGeneration");
const NChar description[] = N_T("Demonstrates how to generate Id from serial number (either generated using LicenseManager API or given by Neurotechnology or distributor)");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2011-2024 Neurotechnology");

static int usage()
{
	printf(N_T("usage: %s [serial file name] [id file name]\n"), title);
	return 1;
}

int main(int argc, NChar *argv[])
{
	NResult result = N_OK;
	HNString hSerial = NULL;
	HNString hId = NULL;

	OnStart(title, description, version, copyright, argc, argv);

	if (argc != 3)
	{
		return usage();
	}

	/* Accept only non-unicode files */
	result = NFileReadAllTextCN(argv[1], &hSerial);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to read serial number from file. error code: %d\n"), result);
		goto FINALLY;
	}

	/* Point to correct place for id_gen.exe or pass NULL to search in current directory */
	result = NLicenseGenerateIdN(NULL, hSerial, &hId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("id generation failed. error code: %d\n"), result);
		goto FINALLY;
	}

	/* Write license to file */
	result = NFileWriteAllTextCN(argv[2], hId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to write id to file. error code: %d\n"), result);
		goto FINALLY;
	}

	printf(N_T("id saved to file %s, it can now be activated using LicenseActivation tutorial, web page, etc.\n"), argv[2]);

	result = N_OK;
FINALLY:
	{
		NResult res2 = NStringSet(NULL, &hSerial);
		if (NFailed(res2)) PrintErrorMsg(N_T("NStringSet() error has occured (code: %d)\n"), res2);
		res2 = NStringSet(NULL, &hId);
		if (NFailed(res2)) PrintErrorMsg(N_T("NStringSet() error has occured (code: %d)\n"), res2);
	}

	OnExit();

	return result;
}
