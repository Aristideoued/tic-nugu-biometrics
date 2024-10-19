#ifndef AN_TYPE_13_RECORD_H_INCLUDED
#define AN_TYPE_13_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANFPImageAsciiBinaryRecord.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANType13Record, ANFPImageAsciiBinaryRecord)

#define AN_TYPE_13_RECORD_FIELD_LEN  AN_RECORD_FIELD_LEN
#define AN_TYPE_13_RECORD_FIELD_IDC  AN_RECORD_FIELD_IDC
#define AN_TYPE_13_RECORD_FIELD_IMP  AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_IMP
#define AN_TYPE_13_RECORD_FIELD_SRC  AN_ASCII_BINARY_RECORD_FIELD_SRC
#define AN_TYPE_13_RECORD_FIELD_LCD  AN_ASCII_BINARY_RECORD_FIELD_DAT
#define AN_TYPE_13_RECORD_FIELD_HLL  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL
#define AN_TYPE_13_RECORD_FIELD_VLL  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL
#define AN_TYPE_13_RECORD_FIELD_SLC  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC
#define AN_TYPE_13_RECORD_FIELD_HPS  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS
#define AN_TYPE_13_RECORD_FIELD_VPS  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS
#define AN_TYPE_13_RECORD_FIELD_CGA  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA
#define AN_TYPE_13_RECORD_FIELD_BPX  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX
#define AN_TYPE_13_RECORD_FIELD_FGP  AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FGP
#define AN_TYPE_13_RECORD_FIELD_SPD  AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_PD
#define AN_TYPE_13_RECORD_FIELD_PPC  AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_PPC
#define AN_TYPE_13_RECORD_FIELD_SHPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS
#define AN_TYPE_13_RECORD_FIELD_SVPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS

#define AN_TYPE_13_RECORD_FIELD_RSP 18
#define AN_TYPE_13_RECORD_FIELD_REM 19

#define AN_TYPE_13_RECORD_FIELD_COM  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM
#define AN_TYPE_13_RECORD_FIELD_LQM  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM

#define AN_TYPE_13_RECORD_FIELD_SUB AN_ASCII_BINARY_RECORD_FIELD_SUB
#define AN_TYPE_13_RECORD_FIELD_CON AN_ASCII_BINARY_RECORD_FIELD_CON

#define AN_TYPE_13_RECORD_FIELD_FCT AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FCT
#define AN_TYPE_13_RECORD_FIELD_ANN AN_ASCII_BINARY_RECORD_FIELD_ANN
#define AN_TYPE_13_RECORD_FIELD_DUI AN_ASCII_BINARY_RECORD_FIELD_DUI
#define AN_TYPE_13_RECORD_FIELD_MMS AN_ASCII_BINARY_RECORD_FIELD_MMS

#define AN_TYPE_13_RECORD_FIELD_SAN AN_ASCII_BINARY_RECORD_FIELD_SAN
#define AN_TYPE_13_RECORD_FIELD_EFR AN_ASCII_BINARY_RECORD_FIELD_EFR
#define AN_TYPE_13_RECORD_FIELD_ASC AN_ASCII_BINARY_RECORD_FIELD_ASC
#define AN_TYPE_13_RECORD_FIELD_HAS AN_ASCII_BINARY_RECORD_FIELD_HAS
#define AN_TYPE_13_RECORD_FIELD_SOR AN_ASCII_BINARY_RECORD_FIELD_SOR
#define AN_TYPE_13_RECORD_FIELD_GEO AN_ASCII_BINARY_RECORD_FIELD_GEO

#define AN_TYPE_13_RECORD_FIELD_UDF_FROM     AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM
#define AN_TYPE_13_RECORD_FIELD_UDF_TO       AN_ASCII_BINARY_RECORD_FIELD_UDF_TO
#define AN_TYPE_13_RECORD_FIELD_UDF_TO_V5   AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5

#define AN_TYPE_13_RECORD_FIELD_DATA AN_RECORD_FIELD_DATA

#define AN_TYPE_13_RECORD_MAX_SEARCH_POSITION_DESCRIPTOR_COUNT 9
#define AN_TYPE_13_RECORD_MAX_QUALITY_METRIC_COUNT             4
#define AN_TYPE_13_RECORD_MAX_QUALITY_METRIC_COUNT_V5          9

#define AN_TYPE_13_RECORD_MIN_RESOUTION_SCALE_LENGTH 1
#define AN_TYPE_13_RECORD_MAX_RESOUTION_SCALE_LENGTH 99900

#define AN_TYPE_13_RECORD_MAX_RESOUTION_COORDINATE 99999
#define AN_TYPE_13_RECORD_MAX_RESOUTION_COMMENT_LENGTH 99

typedef enum ANResolutionDetermination_
{
	anrdFlatbedScanner = 1,
	anrdFixedResolutionDevice = 2,
	anrdRuler = 3,
	anrdStandardForm = 4,
	anrdHuman = 5,
	anrdAutomatedProcess = 6
} ANResolutionDetermination;

N_DECLARE_TYPE(ANResolutionDetermination)

struct ANResolutionMethod_
{
	ANResolutionDetermination resolutionDetermination;
	NInt scaleLength;
	ANMeasurementUnits scaleUnits;
	NInt pointAX;
	NInt pointAY;
	NInt pointBX;
	NInt pointBY;
	HNString hComment;
};
#ifndef AN_TYPE_13_RECORD_HPP_INCLUDED
typedef struct ANResolutionMethod_ ANResolutionMethod;
#endif

N_DECLARE_TYPE(ANResolutionMethod)

NResult N_API ANResolutionMethodCreateN(ANResolutionDetermination resolutionDetermination, NInt scaleLength, ANMeasurementUnits scaleUnits, 
								NInt pointAX, NInt pointAY, NInt pointBX, NInt pointBY, HNString hComment, struct ANResolutionMethod_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANResolutionMethodCreateA(ANResolutionDetermination resolutionDetermination, NInt scaleLength, ANMeasurementUnits scaleUnits, 
								NInt pointAX, NInt pointAY, NInt pointBX, NInt pointBY, const NAChar * szComment, struct ANResolutionMethod_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANResolutionMethodCreateW(ANResolutionDetermination resolutionDetermination, NInt scaleLength, ANMeasurementUnits scaleUnits, 
								NInt pointAX, NInt pointAY, NInt pointBX, NInt pointBY, const NWChar * szComment, struct ANResolutionMethod_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANResolutionMethodCreate(ANResolutionDetermination resolutionDetermination, NInt scaleLength, ANMeasurementUnits scaleUnits, 
								NInt pointAX, NInt pointAY, NInt pointBX, NInt pointBY, const NChar * szComment, ANResolutionMethod * pValue);
#endif
#define ANResolutionMethodCreate N_FUNC_AW(ANResolutionMethodCreate)

NResult N_API ANResolutionMethodDispose(struct ANResolutionMethod_ * pValue);
NResult N_API ANResolutionMethodCopy(const struct ANResolutionMethod_ * pSrcValue, struct ANResolutionMethod_ * pDstValue);
NResult N_API ANResolutionMethodSet(const struct ANResolutionMethod_ * pSrcValue, struct ANResolutionMethod_ * pDstValue);

NResult N_API ANType13RecordGetSearchPositionDescriptorCount(HANType13Record hRecord, NInt * pValue);
NResult N_API ANType13RecordGetSearchPositionDescriptor(HANType13Record hRecord, NInt index, struct ANFPositionDescriptor_ * pValue);
NResult N_API ANType13RecordGetSearchPositionDescriptors(HANType13Record hRecord, struct ANFPositionDescriptor_ * * parValues, NInt * pValueCount);
NResult N_API ANType13RecordSetSearchPositionDescriptor(HANType13Record hRecord, NInt index, const struct ANFPositionDescriptor_ * pValue);
NResult N_API ANType13RecordAddSearchPositionDescriptorEx(HANType13Record hRecord, const struct ANFPositionDescriptor_ * pValue, NInt * pIndex);
NResult N_API ANType13RecordInsertSearchPositionDescriptor(HANType13Record hRecord, NInt index, const struct ANFPositionDescriptor_ * pValue);
NResult N_API ANType13RecordRemoveSearchPositionDescriptorAt(HANType13Record hRecord, NInt index);
NResult N_API ANType13RecordClearSearchPositionDescriptors(HANType13Record hRecord);

NResult N_API ANType13RecordGetRuler(HANType13Record hRecord, struct ANRuler_ * pValue, NBool * pHasValue);
NResult N_API ANType13RecordSetRuler(HANType13Record hRecord, const struct ANRuler_ * pValue);
NResult N_API ANType13RecordGetResolutionMethod(HANType13Record hRecord, struct ANResolutionMethod_ * pValue, NBool * pHasValue);
NResult N_API ANType13RecordSetResolutionMethod(HANType13Record hRecord, const struct ANResolutionMethod_ * pValue);


#ifdef N_CPP
}
#endif

#endif // !AN_TYPE_13_RECORD_H_INCLUDED
