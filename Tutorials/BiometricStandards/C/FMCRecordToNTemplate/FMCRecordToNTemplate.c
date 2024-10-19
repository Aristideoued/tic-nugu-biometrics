#include <TutorialUtils.h>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
	#include <NBiometrics/NBiometrics.h>
	#include <NMedia/NMedia.h>
	#include <NLicensing/NLicensing.h>
#else
	#include <NCore.h>
	#include <NBiometrics.h>
	#include <NMedia.h>
	#include <NLicensing.h>
#endif

const NChar title[] = N_T("FMCRecordToNTemplate");
const NChar description[] = N_T("Demonstrates creation of NTemplate from FMCRecord");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2017-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [FMCRecord] [NTemplate] [Version] [MinutiaeFormat] [ReadBerTlvDo]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tFMCRecord - filename with FMCRecord\n"));
	printf(N_T("\tNTemplate - filename for NTemplate\n"));
	printf(N_T("\tVersion - FMCRecord version\n"));
	printf(N_T("\t\tISO2 - ISO/IEC 19794-2:2005\n"));
	printf(N_T("\t\tISO3 - ISO/IEC 19794-2:2011\n"));
	printf(N_T("\tMinutiaeFormat - card format of minutiae data\n"));
	printf(N_T("\t\tC - compact size\n"));
	printf(N_T("\t\tN - normal size (ISO2 only)\n"));
	printf(N_T("\tReadBerTlvDo - FMCRecord read from buffer option\n"));
	printf(N_T("\t\t1 - Biometric Data Template (BDT) or Cardholder\n"));
	printf(N_T("\t\t    Biometric Data (CBD) BER-TLV DO (Data Object)\n"));
	printf(N_T("\t\t0 - minutiae data buffer only.\n"));
	printf(N_T("example:\n"));
	printf(N_T("\t%s fmcRecord.FMCRecord template.NTemplate ISO3 C 1\n"), title);

	return 1;
}

NResult StoredFMCRecordToPackedNFRecord(
	HNBuffer hBuffer, // buffer that contains FMCRecord
	HNBuffer * phBuffer,// buffer that contains packed NTemplate
	BdifStandard standard,
	NVersion standardVersion,
	FmcrMinutiaFormat minutiaFormat,
	NBool isBerTlv,
	NUInt flags
)
{
	HFMCRecord hFMCRecord = NULL; // handle to FMCRecord object
	HNFRecord hNFRecord = NULL; // handle to NFRecord object
	HNTemplate hNTemplate = NULL; // handle to NTemplate object
	HNFTemplate hNFTemplate = NULL; // handle to NFTemplate object
	NResult result;

	if (isBerTlv)
	{

		// Create FMCRecord object from FMCRecord BER-TLV Data Object (DO) stored in memory (e.g., BDT or CBD BER-TLV DO)
		result = FMCRecordCreateFromMemoryN(hBuffer, standard, standardVersion, minutiaFormat, flags, NULL, &hFMCRecord);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in FMCRecordCreateFromMemory, error code: %d\n"), result);
			goto FINALLY;
		}
	}
	else if (!isBerTlv)
	{
		// Create FMCRecord object
		result = FMCRecordCreate(standard, standardVersion, minutiaFormat, 0, &hFMCRecord);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in FMCRecordCreate, error code: %d\n"), result);
			goto FINALLY;
		}

		// Read minutiae data from buffer to FMCRecord
		result = FMCRecordSetMinutiaeBuffer(hFMCRecord,  hBuffer);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in FMCRecordSetMinutiaeBuffer, error code: %d\n"), result);
			goto FINALLY;
		}
	}
	// Explicitly check minutiae uniqueness for FMCRecord v2.0 as well (since mandatory implicit check since v3.0 only)
	if (standardVersion == FMCR_VERSION_ISO_2_0)
	{
		NBool isUnique = NFalse;
		result = FMCRecordValidateMinutiaeUniqueness(hFMCRecord, &isUnique);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in FMCRecordValidateMinutiaeUniqueness, error code: %d\n"), result);
			goto FINALLY;
		}
		if (!isUnique)
		{
			printf(N_T("!!!WARNING!!!:\nNot all minutiae in FMCRecord are unique!\nPlease, try using ISO3 version with BDIF_NON_STRICT_READ flag to remove non-unique minutiae while reading.\n"));
		}
	}

	// Convert FMCRecord to NFRecord
	result = FMCRecordToNFRecord(hFMCRecord, 0, &hNFRecord);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in FMCRecordToNFRecord, error code: %d\n"), result);
		goto FINALLY;
	}

	// Create NTemplate
	result = NTemplateCreateEx(0, &hNTemplate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NTemplateCreate() failed (result = %d)!"), result);
		goto FINALLY;
	}

	// Create NFTemplate
	result = NFTemplateCreateEx(NFalse, 0, &hNFTemplate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NFTemplateCreateEx() failed (result = %d)!"), result);
		goto FINALLY;
	}

	// Set NFTemplate to NTemplate
	result = NTemplateSetFingers(hNTemplate, hNFTemplate);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NTemplateSetFingers() failed (result = %d)!"), result);
		goto FINALLY;
	}

	// Add NFRecord to NFTemplate
	result = NFTemplateAddRecordEx(hNFTemplate, hNFRecord, NULL);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NFTemplateAddRecordEx() failed (result = %d)!"), result);
		goto FINALLY;
	}

	// Pack NTemplate object
	result = NObjectSaveToMemoryN(hNTemplate, 0, phBuffer);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NObjectSaveToMemoryN, error code: %d\n"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hFMCRecord);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hNFRecord);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hNFTemplate);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hNTemplate);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	return result;
}

int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	HNBuffer hBuffer = NULL;
	HNBuffer hBufferIn = NULL;
	NBool available = NFalse;
	BdifStandard standard = bsIso;
	NVersion standardVersion;
	FmcrMinutiaFormat minutiaFormat;
	NUInt flags = 0; // BDIF_NON_STRICT_READ - removes non-unique minutiae for FMCR_VERSION_ISO_3_0 only
	NBool isBerTlv;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * license = N_T("FingerClient");
	//const NChar * license = N_T("FingerFastExtractor");

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 6)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// TRIAL MODE
	//=========================================================================
	// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
	// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
	// Also you can just set TRUE to "TrialMode" property in code.
	{
		NBool isTrialMode = NFalse;
		result = GetTrialModeFlag(&isTrialMode);
		if (NFailed(result))
		{
			goto FINALLY;
		}
		result = NLicManSetTrialMode(isTrialMode);
		if (NFailed(result))
		{
			goto FINALLY;
		}
		printf(N_T("Trial mode: %d\n"), (int)isTrialMode);
	}
	//=========================================================================

	// check the license first
	result = NLicenseObtain(N_T("/local"), N_T("5000"), license, &available);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseObtain() failed, result = %d\n"), result);
		goto FINALLY;
	}

	if (!available)
	{
		printf(N_T("License %s not available\n"), license);
		result = N_E_NOT_ACTIVATED;
		goto FINALLY;
	}

	if (!strcmp(argv[3], N_T("ISO2")))
	{
		standardVersion = FMCR_VERSION_ISO_2_0;
	}
	else if (!strcmp(argv[3], N_T("ISO3")))
	{
		standardVersion = FMCR_VERSION_ISO_3_0;
	}
	else
	{
		printf(N_T("wrong version!"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	if (!strcmp(argv[4], N_T("C")))
	{
		minutiaFormat = fmcrmfCompactSize;
	}
	else if (!strcmp(argv[4], N_T("N")))
	{
		minutiaFormat = fmcrmfNormalSize;
	}
	else
	{
		printf(N_T("wrong minutia format!"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	// check if full FMCRecord BER-TLV Data Object (DO) (e.g., Biometric Data Template (BDT) or Cardholder Biometric Data (CBD)) or minutiae buffer only is available
	isBerTlv = !strcmp(argv[5], N_T("1")) ? NTrue : NFalse;

	result = NFileReadAllBytesCN(argv[1], &hBufferIn);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NFileReadAllBytesCN, error code: %d\n"), result);
		goto FINALLY;
	}

	result = StoredFMCRecordToPackedNFRecord(hBufferIn, &hBuffer, standard, standardVersion, minutiaFormat, isBerTlv, flags);
	if(NFailed(result))
	{
		goto FINALLY;
	}

	result = NFileWriteAllBytesCN(argv[2], hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NFileWriteAllBytesCN, error code: %d\n"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hBuffer);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hBufferIn);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	OnExit();
	return result;
}
