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

typedef enum RecordType {
	rtANTemplate,
	rtFCRecord,
	rtFIRecord,
	rtFMRecord,
	rtIIRecord
} RecordType;

typedef struct RecordInfo {
	NChar * recordFile;
	BdifStandard standard;
	RecordType recordType;
	NUInt patronFormat;
} RecordInfo;

const NChar title[] = N_T("ComplexCbeffRecord");
const NChar description[] = N_T("Creating a complex CbeffRecord");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2014-2024 Neurotechnology");

#define MAX_LICENSES 4

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [ComplexCbeffRecord] [PatronFormat] [[Record] [RecordType] [RecordStandard] [PatronFormat]] ...\n"), title);
	printf(N_T("\n"));
	printf(N_T("\t[ComplexCbeffRecord] - filename of CbeffRecord which will be created\n"));
	printf(N_T("\t[PatronFormat] - hex number identifying root record patron format (all supported values can be found in CbeffRecord class documentation)\n"));
	printf(N_T("\t[[Record] [RecordType] [RecordStandard] [PatronFormat]] - record information. Block can be specified more than once\n"));
	printf(N_T("\t\t[Record] - filename containing the record.\n"));
	printf(N_T("\t\t[RecordType] - number indicating record type(0 - ANTemplate, 1 - FCRecord, 2 - FIRecord, 3 - FMRecord, 4 - IIRecord)\n"));
	printf(N_T("\t\t[RecordStandard] - number indicating record standard value(0 - Iso, 1 - Ansi or -1 - Unspecified if ANTemplate type is used)\n"));
	printf(N_T("\t\t[PatronFormat] - hex number identifying patron format\n"));
	printf(N_T("\n"));
	return 1;
}

NResult ParseArguments(NChar **args, int argc, RecordInfo ** recordInfo, NInt * recordInfoCount)
{
	NResult result = N_OK;
	NInt recordCount = (argc - 3) / 4;
	NInt i = 0, counter = 0;
	NUInt argPatronFormat = 0;

	if (recordCount <= 0 || (argc - 3) % 4 != 0)
	{
		printf(N_T("Wrong argument count!\n"));
		result = N_E_FAILED;
		goto FINALLY;
	}

	*recordInfo = (RecordInfo *)calloc(recordCount, sizeof(RecordInfo));
	*recordInfoCount = recordCount;

	for (i = 3; i < argc; i += 4)
	{
		(*recordInfo)[counter].recordFile = args[i];
		(*recordInfo)[counter].recordType = (RecordType)atoi(args[i + 1]);
		(*recordInfo)[counter].standard = (BdifStandard)atoi(args[i + 2]);
		result = NUInt32Parse(args[i + 3], N_T("X"), &argPatronFormat);
		if (NFailed(result))
		{ 
			result = PrintErrorMsgWithLastError(N_T("NUInt32Parse() failed, result = %d\n"), result);
			goto FINALLY;
		}
		(*recordInfo)[counter].patronFormat = (NUInt)argPatronFormat;

		counter++;
	}

	result = N_OK;
FINALLY:
	{
	}
	return result;
}

NResult AddRecord(HCbeffRecord rootRecord, RecordInfo info)
{
	NResult result;
	HCbeffRecord hCbeffRecord = NULL;
	HNBuffer hRecordBuffer = NULL;
	HANTemplate hANTemplate = NULL;
	HFCRecord hFCRecord = NULL;
	HFIRecord hFIRecord = NULL;
	HFMRecord hFMRecord = NULL;
	HIIRecord hIIRecord = NULL;
	NBool isValid;

	result = NFileReadAllBytesCN(info.recordFile, &hRecordBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NFileReadAllBytesN() failed, result = %d\n"), result);
		goto FINALLY;
	}

	switch(info.recordType)
	{
		case rtANTemplate :
			result = ANTemplateCreateFromMemoryEx2N(hRecordBuffer, 0, NULL, &hANTemplate);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("ANTemplateCreateFromMemoryEx2N() failed, result = %d\n"), result);
				goto FINALLY;
			}
			result = ANTemplateIsValidated(hANTemplate, &isValid);
			if (!isValid)
			{
				result = PrintErrorMsg(N_T("ANSI/NIST template is not valid"), N_E_FAILED);
				goto FINALLY;
			}
			result = CbeffRecordCreateFromANTemplateEx(hANTemplate, info.patronFormat, 0, &hCbeffRecord);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("CbeffRecordCreateFromANTemplate() failed, result = %d\n"), result);
				goto FINALLY;
			}
			break;
		case rtFCRecord :
			result = FCRecordCreateFromMemoryN(hRecordBuffer, 0, info.standard, NULL, &hFCRecord);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("FCRecordCreateFromMemoryN() failed, result = %d\n"), result);
				goto FINALLY;
			}
			result = CbeffRecordCreateFromFCRecordEx(hFCRecord, info.patronFormat, 0, &hCbeffRecord);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("CbeffRecordCreateFromFCRecord() failed, result = %d\n"), result);
				goto FINALLY;
			}
			break;
		case rtFIRecord :
			result = FIRecordCreateFromMemoryN(hRecordBuffer, 0, info.standard, NULL, &hFIRecord);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("FIRecordCreateFromMemoryN() failed, result = %d\n"), result);
				goto FINALLY;
			}
			result = CbeffRecordCreateFromFIRecordEx(hFIRecord, info.patronFormat, 0, &hCbeffRecord);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("CbeffRecordCreateFromFIRecord() failed, result = %d\n"), result);
				goto FINALLY;
			}
			break;
		case rtFMRecord :
			result = FMRecordCreateFromMemoryN(hRecordBuffer, 0, info.standard, NULL, &hFMRecord);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("FMRecordCreateFromMemoryN() failed, result = %d\n"), result);
				goto FINALLY;
			}
			result = CbeffRecordCreateFromFMRecordEx(hFMRecord, info.patronFormat, 0, &hCbeffRecord);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("CbeffRecordCreateFromFMRecord() failed, result = %d\n"), result);
				goto FINALLY;
			}
			break;
		case rtIIRecord :
			result = IIRecordCreateFromMemoryN(hRecordBuffer, 0, info.standard, NULL, &hIIRecord);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("IIRecordCreateFromMemoryN() failed, result = %d\n"), result);
				goto FINALLY;
			}
			result = CbeffRecordCreateFromIIRecordEx(hFMRecord, info.patronFormat, 0, &hCbeffRecord);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("CbeffRecordCreateFromIIRecord() failed, result = %d\n"), result);
				goto FINALLY;
			}
			break;
	}
	result = CbeffRecordAddRecord(rootRecord, hCbeffRecord, NULL);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("CbeffRecordAddRecord() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hCbeffRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hRecordBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hANTemplate);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFCRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFIRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hFMRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hIIRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}
	return result;
}
int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	HCbeffRecord hRootRecord = NULL; // handle to CbeffRecord object
	HNBuffer hBuffer = NULL;
	NUInt patronFormat = 0;
	NInt obtainedLicensesCount = 0, i = 0;
	RecordInfo * recordInfo = NULL;
	NInt recordInfoCount = 0;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * Licenses[MAX_LICENSES] = { N_T("FingerClient"), N_T("PalmClient"), N_T("FaceClient"), N_T("IrisClient") };
	//const NChar * Licenses[MAX_LICENSES] = { N_T("FingerFastExtractor"), N_T("PalmClient"), N_T("FaceFastExtractor"), N_T("IrisFastExtractor") };

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if(argc < 6 || (argc - 3) % 4 != 0)
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
	for (i = 0; i < MAX_LICENSES; i++)
	{
		NBool available;
		result = NLicenseObtain(N_T("/local"), N_T("5000"), Licenses[i], &available);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NLicenseObtain() failed, result = %d\n"), result);
			goto FINALLY;
		}
		if (available)
		{
			obtainedLicensesCount++;
		}
	}

	if (obtainedLicensesCount == 0)
	{
		printf(N_T("Could not obtain any matching license\n"));
		result = N_E_NOT_ACTIVATED;
		goto FINALLY;
	}

	result = ParseArguments(argv, argc, &recordInfo, &recordInfoCount);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("ParseArguments() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// get CbeffRecord patron format
	result = NUInt32Parse(argv[2], N_T("X"), &patronFormat);
	if (NFailed(result))
	{ 
		result = PrintErrorMsgWithLastError(N_T("NUInt32Parse() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// create CbeffRecord
	result = CbeffRecordCreate(patronFormat, &hRootRecord);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("CbeffRecordCreate() failed, result = %d\n"), result);
		goto FINALLY;
	}

	for (i = 0; i < recordInfoCount; i++)
	{
		result = AddRecord(hRootRecord, recordInfo[i]);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("AddRecord() failed, result = %d\n"), result);
			goto FINALLY;
		}
	}

	// get CbeffRecord buffer
	result = NObjectSaveToMemoryN(hRootRecord, 0, &hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NObjectSaveToMemoryN() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// save CbeffRecord buffer to file
	result = NFileWriteAllBytesCN(argv[1], hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NFileWriteAllBytesCN() failed, result = %d\n"), result);
		goto FINALLY;
	}

	printf(N_T("CbeffRecord was successfully saved"));

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hRootRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		if (recordInfo != NULL) free(recordInfo); recordInfo = NULL;
	}

	OnExit();
	return result;
}
