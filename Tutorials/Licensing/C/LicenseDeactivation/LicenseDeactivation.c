#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("LicenseDeactivation");
const NChar description[] = N_T("Demonstrates license deactivation");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2011-2024 Neurotechnology");

static int usage()
{
	printf(N_T("usage: %s [lic file name] (optional: [deactivation id file name])\n"), title);
	printf(N_T("NOTE: Please always deactivate license on the same computer it was activated on!\n"));
	return 1;
}

int main(int argc, NChar *argv[])
{
	NResult result = N_OK;
	HNString hLicense = NULL;
	HNString hId = NULL;

	OnStart(title, description, version, copyright, argc, argv);

	if (argc != 2)
	{
		return usage();
	}
	
	/* Load license file */
	result = NFileReadAllTextCN(argv[1], &hLicense);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to read license from file. error code: %d\n"), result);
		goto FINALLY;
	}

	printf(N_T("WARNING: deactivating a license will make\nit and product(for which it was generated) disabled on current pc. Continue? (y/n) "));
	if (getchar() != N_T('y'))
	{
		printf(N_T("not generating\n"));
		result = N_OK;
		goto FINALLY;
	}

	result = NLicenseDeactivateOnlineN(NULL, hLicense);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("online deactivation failed. error code: %d\n"), result);
		printf(N_T("generating deactivation id, which you can send to support@neurotechnology.com for manual deactivation\n"));
		if (argc != 3)
		{
			printf(N_T("missing deactivation id argument, please specify it\n"));
			result = N_E_FAILED;
			goto FINALLY;
		}
		result = NLicenseGenerateDeactivationIdForLicenseN(NULL, hLicense, &hId);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("generation of deactivation id failed. error code: %d\n"), result);
			goto FINALLY;
		}

		/* Write deactivation id to file */
		result = NFileWriteAllTextCN(argv[2], hId);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("failed to write deactivation id to file. error code: %d\n"), result);
			goto FINALLY;
		}
		
		printf(N_T("deactivation id saved to file %s. please send it to support@neurotechnology.com to complete deactivation process\n"), argv[2]);
	}
	else
	{
		printf(N_T("online deactivation succeeded. you can now use serial number again\n"));
	}

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
