#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("DongleUpdate");
const NChar description[] = N_T("Demonstrates dongle online update using ticket");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2014-2024 Neurotechnology");

static int usage()
{
	printf(N_T("usage: %s [ticket number]\n"), title);
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
	HNLicManDongleUpdateTicketInfo hTicket = NULL;
	HNString hNumber = NULL;
	HNString hTicketStatus = NULL;
	HNString hDate = NULL;
	NDateTime date;
	NLicManDongleUpdateTicketStatus ticketStatus;
	const NChar * szNumber = NULL;
	const NChar * szTicketStatus = NULL;
	const NChar * szDate = NULL;
	HNLicenseProductInfo * arhLicenses = NULL;
	NInt i = 0, licensesCount = 0, distributorId = 0, dongleCount = 0;
	NUInt hardwareId = 0;
	HNLicManDongle * arhDongles = NULL;
	HNLicManDongle hFoundDongle = NULL;

	OnStart(title, description, version, copyright, 0, NULL);

	if (argc != 2)
	{
		return usage();
	}

	result = NLicManGetUpdateTicketInfo(argv[1], &hTicket);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManGetUpdateTicketInfo() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	result = NLicManDongleUpdateTicketInfoGetNumber(hTicket, &hNumber);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManDongleUpdateTicketInfoGetNumber() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	result = NLicManDongleUpdateTicketInfoGetStatus(hTicket, &ticketStatus);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManDongleUpdateTicketInfoGetStatus() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	result = NLicManDongleUpdateTicketInfoGetIssueDate(hTicket, &date);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManDongleUpdateTicketInfoGetIssueDate() error has occured (code: %d)\n"), result);
		goto FINALLY;
	}

	result = NStringGetBuffer(hNumber, NULL, &szNumber);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NEnumToStringP(N_TYPE_OF(NLicManDongleUpdateTicketStatus), ticketStatus, NULL, &hTicketStatus);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NEnumToStringP() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NStringGetBuffer(hTicketStatus, NULL, &szTicketStatus);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NDateTimeToString(date, NULL, &hDate); 
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NDateTimeToString() failed (result = %d)!"), result);
		goto FINALLY;
	}
	
	result = NStringGetBuffer(hDate, NULL, &szDate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
		goto FINALLY;
	}

	printf(N_T("ticket: %s, status: %s, issue date: %s"), szNumber, szTicketStatus, szDate);

	result = NLicManDongleUpdateTicketInfoGetDongleDistributorId(hTicket, &distributorId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManDongleUpdateTicketInfoGetDongleDistributorId() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = NLicManDongleUpdateTicketInfoGetDongleHardwareId(hTicket, &hardwareId);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManDongleUpdateTicketInfoGetDongleHardwareId() failed (result = %d)!"), result);
		goto FINALLY;
	}

	if (distributorId != 0 && hardwareId != 0)
	{
		printf(N_T("ticket assigned to dongle: %d (hardware id: %d)"), distributorId, hardwareId);
	}

	result = NLicManDongleUpdateTicketInfoGetLicenses(hTicket, &arhLicenses, &licensesCount);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManDongleUpdateTicketInfoGetLicenses() failed (result = %d)!"), result);
		goto FINALLY;
	}

	for (i = 0; i < licensesCount; i++)
	{
		PrintLicenseCount(arhLicenses[i]);
	}

	if (ticketStatus != nlmdutsEnabled)
	{
		printf(N_T("specified ticket can not be used as ticket status is: %s"), szTicketStatus);
	}

	result = NLicManGetDongles(&arhDongles, &dongleCount);

	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManGetDongles(), failed to check for dongles (code: %d)\n"), result);
		goto FINALLY;
	}

	for (i = 0; i < dongleCount; i++)
	{
		NInt dongleDistributorId = 0;
		NUInt dongleHardwareId = 0;
		
		result = NLicManDongleGetDistributorId(arhDongles[i], &dongleDistributorId);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NLicManDongleGetDistributorId() error has occured (code: %d)\n"), result);
			goto FINALLY;
		}

		result = NLicManDongleGetHardwareId(arhDongles[i], &dongleHardwareId);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NLicManDongleGetHardwareId() error has occured (code: %d)\n"), result);
			goto FINALLY;
		}

		if (distributorId != 0 && hardwareId != 0)
		{
			if (distributorId == dongleDistributorId && hardwareId == dongleHardwareId)
			{
				hFoundDongle = arhDongles[i];
				arhDongles[i] = NULL;
				break;
			}
		}
	}

	if(hFoundDongle == NULL && dongleCount > 0)
	{
		hFoundDongle = arhDongles[dongleCount-1];
		arhDongles[dongleCount-1] = NULL;
	}

	if (hFoundDongle == NULL)
	{
		printf(N_T("No dongles found (that could be used)"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	result = NLicManDongleUpdateOnline(hFoundDongle, hTicket);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicManDongleUpdateOnline(), failed to check for dongles (code: %d)\n"), result);
		goto FINALLY;
	}
	
	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hTicket);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet(), failed to clear data (code: %d)\n"), result2);
		result2 = NObjectUnrefArray(arhDongles, dongleCount);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet(), failed to clear data (code: %d)\n"), result2);
		result2 = NObjectSet(NULL, &hFoundDongle);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet(), failed to clear data (code: %d)\n"), result2);
		result2 = NObjectUnrefArray(arhLicenses, licensesCount);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectUnrefArray(), failed to clear data (code: %d)\n"), result2);
		result2 = NStringSet(NULL, &hNumber);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet(), failed to clear string (code: %d)\n"), result2);
		result2 = NStringSet(NULL, &hTicketStatus);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet(), failed to clear string (code: %d)\n"), result2);
		result2 = NStringSet(NULL, &hDate);
		if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet(), failed to clear string (code: %d)\n"), result2);
	}

	OnExit();

	return result;
}
