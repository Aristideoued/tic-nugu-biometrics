#ifndef AN_TYPE_99_RECORD_H_INCLUDED
#define AN_TYPE_99_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANAsciiBinaryRecord.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANType99Record, ANAsciiBinaryRecord)

#define AN_TYPE_99_RECORD_FIELD_LEN AN_RECORD_FIELD_LEN
#define AN_TYPE_99_RECORD_FIELD_IDC AN_RECORD_FIELD_IDC
#define AN_TYPE_99_RECORD_FIELD_SRC AN_ASCII_BINARY_RECORD_FIELD_SRC
#define AN_TYPE_99_RECORD_FIELD_BCD AN_ASCII_BINARY_RECORD_FIELD_DAT

#define AN_TYPE_99_RECORD_FIELD_HDV 100
#define AN_TYPE_99_RECORD_FIELD_BTY 101
#define AN_TYPE_99_RECORD_FIELD_BDQ 102
#define AN_TYPE_99_RECORD_FIELD_BFO 103
#define AN_TYPE_99_RECORD_FIELD_BFT 104

#define AN_TYPE_99_RECORD_FIELD_ANN AN_ASCII_BINARY_RECORD_FIELD_ANN
#define AN_TYPE_99_RECORD_FIELD_DUI AN_ASCII_BINARY_RECORD_FIELD_DUI
#define AN_TYPE_99_RECORD_FIELD_MMS AN_ASCII_BINARY_RECORD_FIELD_MMS

#define AN_TYPE_99_RECORD_FIELD_SAN AN_ASCII_BINARY_RECORD_FIELD_SAN
#define AN_TYPE_99_RECORD_FIELD_ASC AN_ASCII_BINARY_RECORD_FIELD_ASC
#define AN_TYPE_99_RECORD_FIELD_HAS AN_ASCII_BINARY_RECORD_FIELD_HAS
#define AN_TYPE_99_RECORD_FIELD_SOR AN_ASCII_BINARY_RECORD_FIELD_SOR
#define AN_TYPE_99_RECORD_FIELD_GEO AN_ASCII_BINARY_RECORD_FIELD_GEO

#define AN_TYPE_99_RECORD_FIELD_UDF_FROM  AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM
#define AN_TYPE_99_RECORD_FIELD_UDF_TO    AN_ASCII_BINARY_RECORD_FIELD_UDF_TO
#define AN_TYPE_99_RECORD_FIELD_UDF_TO_V5 AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5

#define AN_TYPE_99_RECORD_FIELD_BDB AN_RECORD_FIELD_DATA

#define AN_TYPE_99_RECORD_HEADER_VERSION_1_0 0x0100
#define AN_TYPE_99_RECORD_HEADER_VERSION_1_1 0x0101

#define AN_TYPE_99_RECORD_MAX_BIOMETRIC_DATA_QUALITY_COUNT    1
#define AN_TYPE_99_RECORD_MAX_BIOMETRIC_DATA_QUALITY_COUNT_V5 9

typedef enum ANBiometricType_
{
	anbtNoInformationGiven     = 0x00000000,
	anbtMultipleBiometricsUsed = 0x00000001,
	anbtFacialFeatures         = 0x00000002,
	anbtVoice                  = 0x00000004,
	anbtFingerprint            = 0x00000008,
	anbtIris                   = 0x00000010,
	anbtRetina                 = 0x00000020,
	anbtHandGeometry           = 0x00000040,
	anbtSignatureDynamics      = 0x00000080,
	anbtKeystrokeDynamics      = 0x00000100,
	anbtLipMovement            = 0x00000200,
	anbtThermalFaceImage       = 0x00000400,
	anbtThermalHandImage       = 0x00000800,
	anbtGait                   = 0x00001000,
	anbtBodyOdor               = 0x00002000,
	anbtDna                    = 0x00004000,
	anbtEarShape               = 0x00008000,
	anbtFingerGeometry         = 0x00010000,
	anbtPalmPrint              = 0x00020000,
	anbtVeinPattern            = 0x00040000,
	anbtFootPrint              = 0x00080000
} ANBiometricType;

N_DECLARE_TYPE(ANBiometricType)

NResult N_API ANType99RecordGetHeaderVersion(HANType99Record hRecord, NVersion_ * pValue);
NResult N_API ANType99RecordSetHeaderVersion(HANType99Record hRecord, NVersion_ value);
NResult N_API ANType99RecordGetBiometricType(HANType99Record hRecord, ANBiometricType * pValue);
NResult N_API ANType99RecordSetBiometricType(HANType99Record hRecord, ANBiometricType value);

NResult N_API ANType99RecordGetBiometricDataQualityCount(HANType99Record hRecord, NInt * pValue);
NResult N_API ANType99RecordGetBiometricDataQualityEx(HANType99Record hRecord, NInt index, struct ANQualityMetric_ * pValue);
NResult N_API ANType99RecordGetBiometricDataQualities(HANType99Record hRecord, struct ANQualityMetric_ * * parValues, NInt * pValueCount);
NResult N_API ANType99RecordSetBiometricDataQualityEx(HANType99Record hRecord, NInt index, const struct ANQualityMetric_ * pValue);
NResult N_API ANType99RecordAddBiometricDataQuality(HANType99Record hRecord, const struct ANQualityMetric_ * pValue, NInt * pIndex);
NResult N_API ANType99RecordInsertBiometricDataQuality(HANType99Record hRecord, NInt index, const struct ANQualityMetric_ * pValue);
NResult N_API ANType99RecordRemoveBiometricDataQualityAt(HANType99Record hRecord, NInt index);
NResult N_API ANType99RecordClearBiometricDataQualities(HANType99Record hRecord);

NResult N_API ANType99RecordGetBdbFormatOwner(HANType99Record hRecord, NUShort * pValue);
NResult N_API ANType99RecordSetBdbFormatOwner(HANType99Record hRecord, NUShort value);
NResult N_API ANType99RecordGetBdbFormatType(HANType99Record hRecord, NUShort * pValue);
NResult N_API ANType99RecordSetBdbFormatType(HANType99Record hRecord, NUShort value);

#ifdef N_CPP
}
#endif

#endif // !AN_TYPE_99_RECORD_H_INCLUDED
