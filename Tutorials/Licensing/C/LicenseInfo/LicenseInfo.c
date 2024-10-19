#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("LicenseInfo");
const NChar description[] = N_T("Demonstrates how to get information about specified license/hardware id/serial number");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2014-2024 Neurotechnology");

static int usage()
{
	printf(N_T("usage: %s [license file name]\n"), title);
	return 1;
}

static const NChar * GetOSFamilyName(NOSFamily osFamily)
{
	switch (osFamily)
	{
	case nosfNone:
		return N_T("All");
	case nosfWindows:
		return N_T("Windows");
	case nosfWindowsCE:
		return N_T("Windows CE");
	case nosfWindowsPhone:
		return N_T("Windows Phone");
	case nosfMacOS:
		return N_T("macOS");
	case nosfIOS:
		return N_T("iOS");
	case nosfLinux:
		return N_T("Linux");
	case nosfEmbeddedLinux:
		return N_T("Embedded Linux");
	case nosfAndroid:
		return N_T("Android");
	case nosfUnix:
		return N_T("Unix");
	case nosfMobile:
		return N_T("Mobile");
	}
	return NULL;
}

static NResult PrintLicenseCount(HNLicenseProductInfo hProductInfo)
{
	NResult result;
	NUInt productId;
	NLicenseType licenseType;
	NOSFamily osFamily;
	NInt count;
	HNString hProductName = NULL;
	const NChar * szProductName;
	
	result = NLicenseProductInfoGetId(hProductInfo, &productId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseProductInfoGetId() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	result = NLicenseProductInfoGetLicenseType(hProductInfo, &licenseType);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseProductInfoGetLicenseType() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	result = NLicenseProductInfoGetOSFamily(hProductInfo, &osFamily);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseProductInfoGetOSFamily() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	result = NLicenseProductInfoGetLicenseCount(hProductInfo, &count);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseProductInfoGetLicenseCount() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	result = NLicManGetShortProductNameN(productId, licenseType, &hProductName);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManGetShortProductNameN() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}
	
	result = NStringGetBuffer(hProductName, NULL, &szProductName);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	printf(N_T("%32s OS: %15s Count: %10d\n"), szProductName, GetOSFamilyName(osFamily), count);

	result = N_OK;
FINALLY:
	{
		NResult res2 = NStringSet(NULL, &hProductName);
		if (NFailed(res2)) PrintErrorMsg(N_T("NStringSet() error has occured (code: %d)\n"), res2);
	}
	return result;
}

int main(int argc, NChar *argv[])
{
	NResult result = N_OK;
	HNString hLicense = NULL;
	HNString hLicenseType = NULL;
	HNString hSourceType = NULL;
		HNString hLicenseId = NULL;
	HNLicenseProductInfo * arhLicenses = NULL;
	const NChar * szLicenseType = NULL;
	const NChar * szSourceType = NULL;
	const NChar * szLicenseId = NULL;
	HNLicenseInfo hLicenseInfo = NULL;
	NLicenseInfoType licenseType;
	NLicenseInfoSourceType sourceType;
	NInt distributorId = 0;
	NInt sequenceNumber = 0;
	NInt licensesCount = 0;
	NInt i = 0;

	OnStart(title, description, version, copyright, argc, argv);

	if (argc != 2)
	{
		return usage();
	}
	
	result = NFileReadAllTextCN(argv[1], &hLicense);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("failed to read id from file. error code: %d\n"), result);
		goto FINALLY;
	}

	result = NLicenseGetLicenseInfoOnlineN(hLicense, &hLicenseInfo);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseGetLicenseInfoOnline() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NLicenseInfoGetType(hLicenseInfo, &licenseType);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseInfoGetType() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NLicenseInfoGetSourceType(hLicenseInfo, &sourceType);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseInfoGetSourceType() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NLicenseInfoGetDistributorId(hLicenseInfo, &distributorId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseInfoGetDistributorId() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NLicenseInfoGetSequenceNumber(hLicenseInfo, &sequenceNumber);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseInfoGetSequenceNumber() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NLicenseInfoGetLicenseId(hLicenseInfo, &hLicenseId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseInfoGetSequenceNumber() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NStringGetBuffer(hLicenseId, NULL, &szLicenseId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NEnumToStringP(N_TYPE_OF(NLicenseType), licenseType, NULL, &hLicenseType);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NEnumToStringP() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NStringGetBuffer(hLicenseType, NULL, &szLicenseType);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NEnumToStringP(N_TYPE_OF(NLicenseInfoSourceType), sourceType, NULL, &hSourceType);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NEnumToStringP() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NStringGetBuffer(hSourceType, NULL, &szSourceType);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
		goto FINALLY;
	}

	printf(N_T("Specified license information:\n"));
	printf(N_T("\tType: %s\n"), szLicenseType);
	printf(N_T("\tSource: %s\n"), szSourceType);
	printf(N_T("\tDistributor id: %d\n"), distributorId);
	printf(N_T("\tSequence number: %d\n"), sequenceNumber);
	printf(N_T("\tLicense id: %s\n"), szLicenseId);

	result = NLicenseInfoGetLicenses(hLicenseInfo, &arhLicenses, &licensesCount);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseInfoGetLicenses() failed (result = %d)!"), result);
		goto FINALLY;
	}

	printf(N_T("\tProducts:\n"));
	
	for (i = 0; i < licensesCount; i++)
	{
		PrintLicenseCount(arhLicenses[i]);
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hLicenseInfo);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet(), failed to clear data (code: %d)\n"), result2);
		result2 = NObjectUnrefArray(arhLicenses, licensesCount);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectUnrefArray(), failed to clear data (code: %d)\n"), result2);
		result2 = NStringSet(NULL, &hLicenseId);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet(), failed to clear string (code: %d)\n"), result2);
		result2 = NStringSet(NULL, &hLicenseType);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet(), failed to clear string (code: %d)\n"), result2);
		result2 = NStringSet(NULL, &hSourceType);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet(), failed to clear string (code: %d)\n"), result2);
	}

	OnExit();

	return result;
}
