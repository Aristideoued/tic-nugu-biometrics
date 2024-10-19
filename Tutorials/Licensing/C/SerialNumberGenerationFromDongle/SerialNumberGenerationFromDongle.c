#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("SerialNumberGenerationFromDongle");
const NChar description[] = N_T("Demonstrates serial number generation for given sequence number and product id");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2008-2024 Neurotechnology");

static NResult LoadArguments(int argc, const NChar ** argv, NInt * sequenceNumber, NUInt * productId);
static void ListProductNames();

static int usage()
{
	printf(N_T("usage: %s [sequence number] [product id]\n"), title);
	printf(N_T("\nproduct name : id:\n"));
	ListProductNames();
	printf(N_T("\n"));

	return 1;
}

int main(int argc, NChar *argv[])
{
	NInt sequenceNumber;
	NUInt productId;
	NResult result = N_OK;
	HNString hSerialNumber = NULL;
	NInt distributorId;

	OnStart(title, description, version, copyright, argc, argv);

	if (NFailed(LoadArguments(argc, (const NChar **) argv, &sequenceNumber, &productId)))
	{
		return usage();
	}

	result = NLicManGenerateSerialN(productId, sequenceNumber, &distributorId, &hSerialNumber);
	if (NSucceeded(result))
	{
		const NChar * szSerialNumber;
		result = NStringGetBuffer(hSerialNumber, NULL, &szSerialNumber);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed, error has occured (code: %d)\n"), result);
			goto FINALLY;
		}
		printf(N_T("serial number: %s\n"), szSerialNumber);
		printf(N_T("distributor id: %d\n"), distributorId);
	}
	else
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManGenerateSerialN() failed, error has occured (code: %d)\n"), result);
	}

FINALLY:
	{
		NResult result2 = NStringSet(NULL, &hSerialNumber);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet() failed, error has occured (code: %d)\n"), result2);
	}

	OnExit();

	return result;
}

static NResult LoadArguments(int argc, const NChar ** argv, NInt * sequenceNumber, NUInt * productId)
{
	if (argc != 3)
		return N_E_FAILED;

	if (sscanf(argv[1], N_T("%d"), sequenceNumber) != 1)
	{
		printf(N_T("sequence number is invalid\n"));
		return N_E_FAILED;
	}

	if (sscanf(argv[2], N_T("%d"), productId) != 1)
	{
		printf(N_T("product id is invalid\n"));
		return N_E_FAILED;
	}

	return N_OK;
}

static void ListProductNames()
{
	NUInt i;
	NUInt idCount;
	NUInt * arIdList = NULL;
	NResult result = N_OK;
	HNString hProductName = NULL;

	result = NLicManGetProductIds(NULL);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManGetProductIds(), error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	idCount = result;

	result = NAlloc(idCount * sizeof(NUInt), (void **)&arIdList);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NAlloc(), error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	result = NLicManGetProductIds(arIdList);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManGetProductIds(), error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	for (i = 0; i < idCount; i++)
	{
		if (arIdList[i])
		{
			result = NLicManGetShortProductNameN(arIdList[i], nltSingleComputer, &hProductName);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("NLicManGetShortProductNameN(), error has occured (code: %d)\n"), result);
				goto FINALLY;
			}

			{
				const NChar * szProductName;
				result = NStringGetBuffer(hProductName, NULL, &szProductName);
				if (NFailed(result))
				{
					result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer(), error has occured (code: %d)\n"), result);
					goto FINALLY;
				}
				printf(N_T("%32s : %d\n"), szProductName, arIdList[i]);
			}
			
			result = NStringSet(NULL, &hProductName);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("NStringSet(), error has occured (code: %d)\n"), result);
				goto FINALLY;
			}
		}
	}
FINALLY:
	{
		NResult res2 = NStringSet(NULL, &hProductName);
		if (NFailed(res2)) PrintErrorMsg(N_T("NStringSet(), error has occured (code: %d)\n"), res2);
		if (arIdList) NFree(arIdList);
	}
}
