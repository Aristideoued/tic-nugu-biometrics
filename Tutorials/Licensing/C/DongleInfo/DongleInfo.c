#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("DongleInfo");
const NChar description[] = N_T("Demonstrates dongle information retrieval");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2008-2024 Neurotechnology");

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
	default:
		return N_T("Unknown");
	}
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

int main()
{
	NResult result = N_OK;
	HNLicenseProductInfo * arhProductInfo = NULL;
	NInt i, productInfoCount = 0, dongleCount = 0;
	HNLicManDongle * arhDongles = NULL;

	OnStart(title, description, version, copyright, 0, NULL);
	
	result = NLicManGetDongles(&arhDongles, &dongleCount);

	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManGetDongles(), failed to check for dongles (code: %d)\n"), result);
		goto FINALLY;
	}

	if (dongleCount == 0)
	{
		printf(N_T("no dongles found\n"));
		result = N_OK;
		goto FINALLY;
	}

	for (i = 0; i < dongleCount; i++)
	{
		NInt distributorId;
		NInt p;
		result = NLicManDongleGetDistributorId(arhDongles[i], &distributorId);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NLicManDongleGetDistributorId() error has occured (code: %d)\n"), result);
			goto FINALLY;
		}
		printf(N_T("=== Dongle Id: %d ===\n"), distributorId);

		result = NLicManDongleGetLicenses(arhDongles[i], &arhProductInfo, &productInfoCount);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NLicManDongleGetLicenses() error has occured (code: %d)\n"), result);
			goto FINALLY;
		}

		for (p = 0; p < productInfoCount; p++)
		{
			PrintLicenseCount(arhProductInfo[p]);
		}

		result = NObjectUnrefArray(arhProductInfo, productInfoCount);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectUnrefArray(), failed to clear data (code: %d)\n"), result);
			goto FINALLY;
		}
		arhProductInfo = NULL;
	}
	printf(N_T("no more dongles found\n"));

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectUnrefArray(arhDongles, dongleCount);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectUnrefArray(), failed to clear data (code: %d)\n"), result2);
		if (arhProductInfo) 
		{
			result2 = NObjectUnrefArray(arhProductInfo, productInfoCount);
			if (NFailed(result2)) PrintErrorMsg(N_T("NObjectUnrefArray(), failed to clear data (code: %d)\n"), result2);
		}
	}

	OnExit();

	return result;
}
