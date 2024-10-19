#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("IdInfo");
const NChar description[] = N_T("Demonstrates id information retrieval from id file");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2008-2024 Neurotechnology");

NBool LoadIdFile(const NChar * szIdFileName, HNString * phId);

static int usage()
{
	printf(N_T("usage: %s [id file name]\n"), title);
	return 1;
}

int main(int argc, NChar *argv[])
{
	NResult result;
	HNString hId = NULL;
	NInt sequenceNumber;
	NUInt productId;
	NInt distributorId;
	HNString hProductName = NULL;

	OnStart(title, description, version, copyright, argc, argv);

	/* Check arguments */
	if (argc != 2)
	{
		return usage();
	}

	/* Load id file */
	result = NFileReadAllTextCN(argv[1], &hId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to read id from file. error code: %d\n"), result);
		goto FINALLY;
	}

	result = NLicManGetLicenseDataN(hId, &sequenceNumber, &productId, &distributorId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManGetLicenseDataN() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	result = NLicManGetShortProductNameN(productId, nltSingleComputer, &hProductName);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManGetShortProductNameN() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	printf(N_T("sequence number: %5d\n"), sequenceNumber);
	if (hProductName)
	{
		const NChar * szProductName;
		result = NStringGetBuffer(hProductName, NULL, &szProductName);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() error has occured (code: %d)\n"), result);
			goto FINALLY;
		}
		printf(N_T("product id: %5d (%s)\n"), productId, szProductName);
	}
	else
		printf(N_T("product id: %5d\n"), productId);
	printf(N_T("distributor id: %5d\n"), distributorId);

	result = N_OK;
FINALLY:
	{
		NResult res2 = NStringSet(NULL, &hProductName);
		if (NFailed(res2)) PrintErrorMsg(N_T("NStringSet() error has occured (code: %d)\n"), res2);
		res2 = NStringSet(NULL, &hId);
		if (NFailed(res2)) PrintErrorMsg(N_T("NStringSet() error has occured (code: %d)\n"), res2);
	}

	OnExit();

	return result;
}
