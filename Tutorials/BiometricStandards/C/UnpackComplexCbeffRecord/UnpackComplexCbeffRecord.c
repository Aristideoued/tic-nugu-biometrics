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

const NChar title[] = N_T("UnpackComplexCbeffRecord");
const NChar description[] = N_T("Unpack Complex CbeffRecord");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2014-2024 Neurotechnology");

#define MAX_LICENSES 4

typedef enum BdbFormat {
	bdbfANTemplate = 0x001B8019,
	bdbfFCRecordAnsi = 0x001B0501,
	bdbfFCRecordIso = 0x01010008,
	bdbfFIRecordAnsi = 0x001B0401,
	bdbfFIRecordIso = 0x01010007,
	bdbfFMRecordAnsi = 0x001B0202,
	bdbfFMRecordIso = 0x01010002,
	bdbfIIRecordAnsiPolar = 0x001B0602,
	bdbfIIRecordIsoPolar = 0x0101000B,
	bdbfIIRecordAnsiRectilinear = 0x001B0601,
	bdbfIIRecordIsoRectilinear = 0x01010009
} BdbFormat;

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [CbeffRecord] [PatronFormat]\n"), title);
	printf(N_T("\n"));
	printf(N_T("\t[CbeffRecord] - filename for CbeffRecord\n"));
	printf(N_T("\t[PatronFormat] - hex number identifying patron format (all supported values can be found in CbeffRecord class documentation)\n"));
	return 1;
}

NResult RecordToFile(HCbeffRecord hCbeffRecord, NInt recordNumber)
{
	NResult result;
	const NChar * format = N_T("Record{I}_{S}.dat");
	const NChar * recordType = NULL;
	HNString hFileName = NULL;
	HNBuffer hRecordBuffer = NULL;
	NUInt bdbFormat = 0;

	// get record type
	result = CbeffRecordGetBdbFormat(hCbeffRecord, &bdbFormat);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("CbeffRecordGetBdbFormat() failed, result = %d\n"), result);
		goto FINALLY;
	}

	switch(bdbFormat)
	{
		case bdbfANTemplate :
			recordType = N_T("ANTemplate");
			break;
		case bdbfFCRecordAnsi :
			recordType = N_T("FCRecordAnsi");
			break;
		case bdbfFCRecordIso :
			recordType = N_T("FCRecordIso");
			break;
		case bdbfFIRecordAnsi :
			recordType = N_T("FIRecordAnsi");
			break;
		case bdbfFIRecordIso :
			recordType = N_T("FIRecordIso");
			break;
		case bdbfFMRecordAnsi :
			recordType = N_T("FMRecordAnsi");
			break;
		case bdbfFMRecordIso :
			recordType = N_T("FMRecordIso");
			break;
		case bdbfIIRecordAnsiPolar :
			recordType = N_T("IIRecordAnsiPolar");
			break;
		case bdbfIIRecordIsoPolar :
			recordType = N_T("IIRecordIsoPolar");
			break;
		case bdbfIIRecordAnsiRectilinear :
			recordType = N_T("IIRecordAnsiRectilinear");
			break;
		case bdbfIIRecordIsoRectilinear :
			recordType = N_T("IIRecordIsoRectilinear");
			break;
		default :
			recordType = N_T("UnknownFormat");
			break;
	}

	// make filename
	result = NStringFormat(&hFileName, format, recordNumber, recordType); 
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NStringFormat() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// get record buffer
	result = CbeffRecordGetBdbBuffer(hCbeffRecord, &hRecordBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("CbeffRecordGetBdbBuffer() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// save buffer to file
	result = NFileWriteAllBytesN(hFileName, hRecordBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("CbeffRecordGetBdbBuffer() failed, result = %d\n"), result);
		goto FINALLY;
	}

	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hRecordBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NStringSet(NULL, &hFileName);
		if NFailed((result2)) PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result2);
	}
	return result;
}

NResult UnpackRecords(HCbeffRecord hCbeffRecord, NInt * recordNumber)
{
	NInt recordCount = 0, i = 0;
	NResult result = N_OK;
	HCbeffRecord * arhRecords;

	result = CbeffRecordGetRecords(hCbeffRecord, &arhRecords, &recordCount);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("CbeffRecordGetRecords() failed, result = %d\n"), result);
		return N_E_FAILED;
	}

	if (recordCount == 0)
	{
		result = RecordToFile(hCbeffRecord, (*recordNumber)++);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("RecordToFile() failed, result = %d\n"), result);
			goto FINALLY;
		}
	}
	else
	{
		for (i = 0; i < recordCount; i++)
		{
			result = UnpackRecords(arhRecords[i], recordNumber);
			if (NFailed(result))
			{
				result = PrintErrorMsgWithLastError(N_T("UnpackRecords() failed, result = %d\n"), result);
				goto FINALLY;
			}
		}
	}
FINALLY:
	{
		NResult result2 = NObjectUnrefArray(arhRecords, recordCount);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}
	return result;
}

int main(int argc, NChar **argv)
{
	NResult result = N_OK;
	HNBuffer hBuffer = NULL;
	HCbeffRecord hCbeffRecord = NULL; // handle to CbeffRecord object
	NUInt patronFormat = 0;
	NInt recordNumber = 0;
	NInt obtainedLicensesCount = 0, i = 0;
	
	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NChar * Licenses[MAX_LICENSES] = { N_T("FingerClient"), N_T("PalmClient"), N_T("FaceClient"), N_T("IrisClient") };
	//const NChar * Licenses[MAX_LICENSES] = { N_T("FingerFastExtractor"), N_T("PalmClient"), N_T("FaceFastExtractor"), N_T("IrisFastExtractor") };

	//=========================================================================

	OnStart(title, description, version, copyright, argc, argv);

	if(argc != 3)
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

	// read CbeffRecord
	result = NFileReadAllBytesCN(argv[1], &hBuffer);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NFileReadAllBytesN() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// get CbeffRecord patron format
	result = NUInt32Parse(argv[2], N_T("X"), &patronFormat);
	if (NFailed(result))
	{ 
		result = PrintErrorMsgWithLastError(N_T("NUInt32Parse() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// create CbeffRecord from buffer
	result = CbeffRecordCreateFromMemoryNEx(hBuffer, patronFormat, 0, NULL, &hCbeffRecord);
	if (NFailed(result))
	{ 
		result = PrintErrorMsgWithLastError(N_T("CbeffRecordCreateFromMemoryN() failed, result = %d\n"), result);
		goto FINALLY;
	}

	// start unpacking CbeffRecord
	result = UnpackRecords(hCbeffRecord, &recordNumber);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("UnpackRecords() failed, result = %d\n"), result);
		goto FINALLY;
	}

	printf(N_T("records successfully saved!"));
	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hCbeffRecord);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
		result2 = NObjectSet(NULL, &hBuffer);
		if NFailed((result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	OnExit();
	return result;
}
