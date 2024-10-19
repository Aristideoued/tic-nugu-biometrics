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

const NChar title[] = N_T("NTemplateToFMCRecord");
const NChar description[] = N_T("Demonstrates creation of FMCRecord from NTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2017-2024 Neurotechnology");

const NByte minutiaTruncationQualityThreshold = 0;
 /* NOTE: ISO/IEC 19794-2 (informative) minutiae count range recommendations for card formats:
  - FMCR_DEFAULT_MIN_ENROLL_MC to FMCR_DEFAULT_MAX_ENROLL_MC for enroll, 
  - FMCR_DEFAULT_MIN_VERIFY_MC to FMCR_DEFAULT_MAX_VERIFY_MC for verify.
  */
const NInt minutiaTruncationMaximalCount = 48;
const NFMinutiaTruncationAlgorithm minutiaTruncationAlgorithm = nfmtaQualityAndCenterOfMass;

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [NTemplate] [FMCRecord] [Version] [MinutiaeFormat] [SaveBiometricDataTemplate]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tNTemplate - filename with NTemplate\n"));
	printf(N_T("\tFMCRecord - filename with FMCRecord\n"));
	printf(N_T("\tVersion - ISO standard version for FMCRecord\n"));
	printf(N_T("\t\tISO2 - ISO/IEC 19794-2:2005\n"));
	printf(N_T("\t\tISO3 - ISO/IEC 19794-2:2011\n"));
	printf(N_T("\tMinutiaeFormat - card format of minutiae data\n"));
	printf(N_T("\t\tC - compact size \n"));
	printf(N_T("\t\tN - normal size (ISO2 only)\n"));
	printf(N_T("\tSaveBiometricDataTemplate - FMCRecord save to buffer option\n"));
	printf(N_T("\t\t1 - full Biometric Data Template (BDT) BER-TLV DO (Data Object)\n"));
	printf(N_T("\t\t0 - minutiae data only\n"));
	printf(N_T("example:\n"));
	printf(N_T("\t%s template.NTemplate fmcrecord.FMCRecord ISO3 C 1\n"), title);
	return 1;
}

NResult StoredNTemplateToPackedFMCRecord(
	HNBuffer hBuffer, // buffer that contains packed NTemplate
	HNBuffer * phBuffer, // buffer that will contain packed FMCRecord
	BdifStandard standard,
	NVersion standardVersion,
	FmcrMinutiaFormat minutiaFormat,
	FmcrMinutiaOrder minutiaOrder,
	NBool isBdtBerTlv,
	NUInt flags
)
{
	HNTemplate hNTemplate = NULL; // handle to NTemplate object
	HNFTemplate hNFTemplate = NULL; // handle to NFTemplate object
	HNFRecord hNFRecord = NULL; // handle to NFRecord object
	HFMCRecord hFMCRecord = NULL; // handle to FMCRecord object
	NResult result;

	// Create NTemplate object from packed NTemplate
	result = NTemplateCreateFromMemoryN(hBuffer, 0, NULL, &hNTemplate);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NTemplateCreateFromMemory, error code: %d\n"), result);
		goto FINALLY;
	}

	// Retrieve NFTemplate object from NTemplate object
	result = NTemplateGetFingersEx(hNTemplate, &hNFTemplate);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NTemplateGetFingers, error code: %d\n"), result);
		goto FINALLY;
	}

	if (!hNFTemplate)
	{
		printf(N_T("no finger template found in template\n"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	// Retrieve NFRecord object from NFTemplate object
	result = NFTemplateGetRecordEx(hNFTemplate, 0, &hNFRecord);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NFTemplateGetRecord, error code: %d\n"), result);
		goto FINALLY;
	}

	if (!hNFRecord)
	{
		printf(N_T("no finger record found in template\n"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	// Truncate minutiae by quality
	result = NFRecordTruncateMinutiaeByQuality(hNFRecord, minutiaTruncationQualityThreshold, minutiaTruncationMaximalCount);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NFRecordTruncateMinutiaeByQuality, error code: %d\n"), result);
		goto FINALLY;
	}

	// Truncate minutiae using specified truncation algorithm (if more than desired minutiae with quality above minutiaTruncationQualityThreshold remain)
	result = NFRecordTruncateMinutiaeEx(hNFRecord, minutiaTruncationAlgorithm, minutiaTruncationMaximalCount);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NFRecordTruncateMinutiaeEx, error code: %d\n"), result);
		goto FINALLY;
	}

	// Create FMCRecord object from NFRecord object
	result = FMCRecordCreateFromNFRecord(hNFRecord, standard, standardVersion, minutiaFormat, minutiaOrder, 0, &hFMCRecord);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in FMCRecordCreateFromNFRecord, error code: %d\n"), result);
		goto FINALLY;
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
			printf(N_T("!!!WARNING!!!:\nNot all minutiae in FMCRecord are unique!\nPlease, try using ISO3 version to remove non-unique minutiae while conversion.\n"));
		}
	}

	if (isBdtBerTlv)
	{
		// Store FMCRecord object in memory as ISO/IEC 19794-2 and ISO/IEC 7816-11 compliant Biometric Data Template (BDT) BER-TLV Data Object (DO)
		result = NObjectSaveToMemoryN(hFMCRecord, flags, phBuffer);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in NObjectSaveToMemoryN, error code: %d\n"), result);
			goto FINALLY;
		}
	}
	else
	{
		// Get minutiae data as buffer
		result = FMCRecordGetMinutiaeBuffer(hFMCRecord, phBuffer);
		if(NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("error in FMCRecordGetMinutiaeBuffer, error code: %d\n"), result);
			goto FINALLY;
		}
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hNTemplate);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hNFTemplate);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hNFRecord);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFMCRecord);
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
	NUInt flags = FMCR_SKIP_ALL_EXTENDED_DATA | FMCR_USE_BIOMETRIC_DATA_TEMPLATE; // the most common use case of minutiae data only within on-card records
	BdifStandard standard = bsIso;
	NVersion standardVersion;
	FmcrMinutiaFormat minutiaFormat;
	FmcrMinutiaOrder minutiaOrder = fmcrmoNone;
	NBool isBdtBerTlv;
	
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

	// check if full FMCRecord Biometric Data Template (BDT) BER-TLV Data Object (DO) or minutiae buffer only to be saved
	isBdtBerTlv = !strcmp(argv[5], N_T("1")) ? NTrue : NFalse;

	result = NFileReadAllBytesCN(argv[1], &hBufferIn);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NFileReadAllBytesCN, error code: %d\n"), result);
		goto FINALLY;
	}

	result = StoredNTemplateToPackedFMCRecord(hBufferIn, &hBuffer, standard, standardVersion, minutiaFormat, minutiaOrder, isBdtBerTlv, flags);
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
