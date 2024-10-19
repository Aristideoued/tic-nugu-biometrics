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

const NChar title[] = N_T("NTemplateToFMRecord");
const NChar description[] = N_T("Demonstrates creation of FMRecord from NTemplate");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2008-2024 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [NTemplate] [FMRecord] [Standard&Version] [FlagUseNeurotecFields] [Encoding]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\tNTemplate - filename with NTemplate\n"));
	printf(N_T("\tFMRecord  - filename with FMRecord\n"));
	printf(N_T("\tStandard & Version - FMRecord standard & version\n"));
	printf(N_T("\t\tANSI2 - ANSI/INCITS 378-2004\n"));
	printf(N_T("\t\tANSI3.5 - ANSI/INCITS 378-2009\n"));
	printf(N_T("\t\tISO2 - ISO/IEC 19794-2:2005\n"));
	printf(N_T("\t\tISO3 - ISO/IEC 19794-2:2011\n"));
	printf(N_T("\t\tMINEX - Minex compliant record (ANSI/INCITS 378-2004 without extended data)\n"));
	printf(N_T("\tFlagUseNeurotecFields - 1 if FMRFV_USE_NEUROTEC_FIELDS flag is used; otherwise, 0 flag was not used. For Minex compliant record must be 0.\n"));
	printf(N_T("example:\n"));
	printf(N_T("\t%s template.NTemplate fmrecord.FMRecord ISO3 1\n"), title);
	printf(N_T("\t%s template.NTemplate fmrecord.FMRecord MINEX 0\n"), title);
	printf(N_T("\tEncoding - specifies FMRecord encoding type\n"));
	printf(N_T("\t\t0 - Traditional binary encoding \n"));
	printf(N_T("\t\t1 - XML encoding (supported only for ISO3)\n"));
	return 1;
}

NResult StoredNTemplateToPackedFMRecord(
	HNBuffer hBuffer, // buffer that contains packed NTemplate
	HNBuffer * phBuffer, // buffer that will contain FMRecord
	BdifStandard standard,
	NVersion standardVersion,
	BdifEncodingType encoding,
	NUInt flags
)
{
	HNTemplate hNTemplate = NULL; // handle to NTemplate object
	HNFTemplate hNFTemplate = NULL; // handle to NFTemplate object
	HFMRecord hFMRecord = NULL; // handle to FMRecord object
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
		printf(N_T("no fingers found in template\n"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	// Create FMRecord object from NFTemplate object
	result = FMRecordCreateFromNFTemplateEx(hNFTemplate, 0, standard, standardVersion, &hFMRecord);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in FMRecordCreateFromNFTemplate, error code: %d\n"), result);
		goto FINALLY;
	}

	// Store FMRecord object in memory
	result = FMRecordSaveToMemoryN(hFMRecord, encoding, flags, phBuffer);
	if(NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in FMRecordSaveToMemoryN, error code: %d\n"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hNTemplate);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hNFTemplate);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFMRecord);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	return result;
}

int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	HNBuffer hBuffer = NULL;
	HNBuffer hBufferIn = NULL;
	BdifStandard standard;
	NVersion standardVersion;
	NBool available = NFalse;
	NUInt flags = 0;
	BdifEncodingType encoding;
	
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

	if (!strcmp(argv[3], N_T("ANSI2")))
	{
		standard = bsAnsi;
		standardVersion = FMR_VERSION_ANSI_2_0;
	}
	else if (!strcmp(argv[3], N_T("ISO2")))
	{
		standard = bsIso;
		standardVersion = FMR_VERSION_ISO_2_0;
	}
	else if (!strcmp(argv[3], N_T("ISO3")))
	{
		standard = bsIso;
		standardVersion = FMR_VERSION_ISO_3_0;
	}
	else if (!strcmp(argv[3], N_T("ANSI3.5")))
	{
		standard = bsAnsi;
		standardVersion = FMR_VERSION_ANSI_3_5;
	}
	else if (!strcmp(argv[3], N_T("MINEX")))
	{
		if (!strcmp(argv[4], N_T("1"))) // check if Neurotec flags are used
		{
			printf(N_T("MINEX and FlagUseNeurotecFields is incompatible"));
			result = N_E_FAILED;
			goto FINALLY;
		}
		standard = bsAnsi;
		standardVersion = FMR_VERSION_ANSI_3_5;
		flags = FMRFV_SKIP_RIDGE_COUNTS | FMRFV_SKIP_SINGULAR_POINTS | FMRFV_SKIP_NEUROTEC_FIELDS;
	}
	else
	{
		printf(N_T("wrong version!"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	// check if Neurotec flags are used
	flags |= (!strcmp(argv[4], N_T("1")) ? FMRFV_USE_NEUROTEC_FIELDS : 0);

	result = NFileReadAllBytesCN(argv[1], &hBufferIn);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("error in NFileReadAllBytesCN, error code: %d\n"), result);
		goto FINALLY;
	}

	//sets encoding for FMRecord
	encoding = strcmp(argv[5], N_T("1")) == 0 ? betXml : betTraditional;

	result = StoredNTemplateToPackedFMRecord(hBufferIn, &hBuffer, standard, standardVersion, encoding, flags);
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

	printf(N_T("FMRecord successfully saved to file %s\n"), argv[2]);

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
