#include <TutorialUtils.h>

#include <NCore.h>
#include <NBiometrics.h>
#include <bioapi.h>

static const NChar gs_title[] = N_T("Neurotechnology FIR to BIR conversion tutorial 5.1\n");

int print_usage(NChar * argv[])
{
	printf(N_T("Usage: %s <FIR file> <BIR template file> <PurposeID>\n"), argv[0]);
	printf(N_T("\t<FIR file> - serialized FIR file name\n"));
	printf(N_T("\t<BIR template file> - serialized BioAPI BIR structure file name\n"));
	printf(N_T("\t<PurposeID> - Numeric Purpose ID value. Refer to BioAPI2.0 specs for more info\n"));
	printf(N_T("Description:\n"));
	printf(N_T("This tutorial converts FIR serialized file to BioAPI BIR serialized file.\n"));
	printf(N_T("Saved file is a serialized BioAPI_BIR structure.\n"));
	printf(N_T("This saved file can be later used by either VerifyMatch or IdentifyMatch tutorials.\n"));
	printf(N_T("\nPossible PurposeID values and corresponding BioAPI names:\n"));
	printf(N_T("  0\tBioAPI_NO_PURPOSE_AVAILABLE\n"));
	printf(N_T("  1\tBioAPI_PURPOSE_VERIFY\n"));
	printf(N_T("  2\tBioAPI_PURPOSE_IDENTIFY\n"));
	printf(N_T("  3\tBioAPI_PURPOSE_ENROLL\n"));
	printf(N_T("  4\tBioAPI_PURPOSE_ENROLL_FOR_VERIFICATION_ONLY\n"));
	printf(N_T("  5\tBioAPI_PURPOSE_ENROLL_FOR_IDENTIFICATION_ONLY\n"));
	printf(N_T("  6\tBioAPI_PURPOSE_AUDIT\n"));
	printf(N_T("\nExample:\n"));
	printf(N_T("%s finger.fir intermediate.bir 1\n"), argv[0]);

	return 1;
}

int WriteBIRToFile(const NChar * fileName, BioAPI_BIR * BIR)
{
	NByte *data;
	NSizeType cursor = 0;
	NSizeType size = sizeof(BIR->Header) + 2 * sizeof(BIR->BiometricData.Length) + 
		BIR->BiometricData.Length + BIR->SecurityBlock.Length;

	NAlloc(size, &data);
	if (data == 0) 
	{
		printf(N_T("Memory error occoured while allocating temporary buffer\n"));
		return -1;
	}

	NCopy(data + cursor, &BIR->Header, sizeof(BIR->Header));
	cursor += sizeof(BIR->Header);
	NCopy(data + cursor, &BIR->BiometricData.Length, sizeof(BIR->BiometricData.Length));
	cursor += sizeof(BIR->BiometricData.Length);
	NCopy(data + cursor, &BIR->SecurityBlock.Length, sizeof(BIR->SecurityBlock.Length));
	cursor += sizeof(BIR->SecurityBlock.Length);
	NCopy(data + cursor, BIR->BiometricData.Data, BIR->BiometricData.Length);
	cursor += BIR->BiometricData.Length;
	NCopy(data + cursor, BIR->SecurityBlock.Data, BIR->SecurityBlock.Length);

	{
		NResult result = NFileWriteAllBytes(fileName, data, size);
		NFree(data);
		if (NFailed(result))
		{
			printf(N_T("Could not write BIR data to a file\n"));
			return -1;
		}
	}

	return 0;
}
int ReadFIRFromFile(const NChar * fileName, NByte * * buf, NSizeType * size)
{
	HNBuffer hBuffer = NULL;
	NResult result = NFileReadAllBytesCN(fileName, &hBuffer);
	if (NFailed(result))
	{
		printf(N_T("Could not read FIR file\n"));
		return -1;
	}
	result = NBufferToPtr(hBuffer, size, buf);
	NObjectUnref(hBuffer);
	if (NFailed(result))
	{
		printf(N_T("Could not read FIR file\n"));
		return -1;
	}

	return 0;
}

int main(int argc, NChar * argv[])
{
	BioAPI_BIR bir;
	NByte *buf;
	NSizeType size;
	BioAPI_BIR_BIOMETRIC_PRODUCT_ID bbpid = {BioAPI_NO_PRODUCT_OWNER_AVAILABLE, BioAPI_NO_PRODUCT_TYPE_AVAILABLE};
	BioAPI_DATE bad = {BioAPI_NO_YEAR_AVAILABLE,BioAPI_NO_MONTH_AVAILABLE, BioAPI_NO_DAY_AVAILABLE};
	BioAPI_TIME bat = {BioAPI_NO_HOUR_AVAILABLE, BioAPI_NO_MINUTE_AVAILABLE, BioAPI_NO_SECOND_AVAILABLE};
	BioAPI_BIR_SECURITY_BLOCK_FORMAT bsbf = {0, 0};

	printf(gs_title);
	if (argc < 3)
	{
		return print_usage(argv);
	}

	if (ReadFIRFromFile(argv[1], &buf, &size) != 0)
	{
		printf(N_T("Error reading input file\n"));
		return -1;
	}

	// conversion
	bir.SecurityBlock.Data = 0;
	bir.SecurityBlock.Length = 0;
	bir.BiometricData.Data = buf;
	bir.BiometricData.Length = (uint32_t)size;
	bir.Header.Format.FormatType = CBEFF_BDBFI_ISO_IEC_JTC_1_SC_37_BIOMETRICS_FINGER_IMAGE;
	bir.Header.Format.FormatOwner = CBEFF_BO_ISO_IEC_JTC_1_SC_37_BIOMETRICS;
	bir.Header.FactorsMask = BioAPI_TYPE_FINGERPRINT;
	bir.Header.ProductID = bbpid;
	bir.Header.ExpirationDate = bad;
	bir.Header.CreationDTG.Date = bad;
	bir.Header.CreationDTG.Time = bat;

	if (argc == 4)
		bir.Header.Purpose = (BioAPI_BIR_PURPOSE)atoi(argv[3]);
	else
		bir.Header.Purpose = BioAPI_NO_PURPOSE_AVAILABLE;

	bir.Header.Quality = BioAPIRI_QUALITY_NOTSET;
	bir.Header.HeaderVersion = 0x20;
	NFill(bir.Header.Index, 0, sizeof(bir.Header.Index));
	bir.Header.SBFormat = bsbf;
	bir.Header.Subtype = BioAPI_NO_SUBTYPE_AVAILABLE;
	bir.Header.Type = BioAPI_BIR_DATA_TYPE_INTERMEDIATE;

	//
	if (WriteBIRToFile(argv[2], &bir) < 0)
	{
		printf(N_T("error opening output file\n"));
		NFree(buf);
		return -1;
	}
	;

	NFree(buf);

	return 0;
}

