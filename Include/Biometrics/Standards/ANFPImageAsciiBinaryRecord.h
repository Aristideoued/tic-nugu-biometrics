#ifndef AN_FP_IMAGE_ASCII_BINARY_RECORD_H_INCLUDED
#define AN_FP_IMAGE_ASCII_BINARY_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANImageAsciiBinaryRecord.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANFPImageAsciiBinaryRecord, ANImageAsciiBinaryRecord)

#define AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_IMP  3
#define AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FGP 13
#define AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_PD  14
#define AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_PPC 15
#define AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_AMP 18
#define AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_SEG 21
#define AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FCT 901

#define AN_FP_IMAGE_ASCII_BINARY_RECORD_MAX_POSITION_COUNT        6
#define AN_FP_IMAGE_ASCII_BINARY_RECORD_MAX_PRINT_POSITION_COUNT 12

typedef enum ANFMajorCase_
{
	anfmcNA = 0,
	anfmcEji = 1,
	anfmcTip = 2,
	anfmcFV1 = 3,
	anfmcFV2 = 4,
	anfmcFV3 = 5,
	anfmcFV4 = 6,
	anfmcPrx = 7,
	anfmcDst = 8,
	anfmcMed = 9,
	anfmcTpp = 10,
} ANFMajorCase;

N_DECLARE_TYPE(ANFMajorCase)

struct ANFPositionDescriptor_
{
	BdifFPPosition Position;
	ANFMajorCase Portion;
};
#ifndef AN_FP_IMAGE_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANFPositionDescriptor_ ANFPositionDescriptor;
#endif

N_DECLARE_TYPE(ANFPositionDescriptor)

struct ANFPrintPosition_
{
	ANFMajorCase FingerView;
	ANFMajorCase Segment;
	NInt Left;
	NInt Right;
	NInt Top;
	NInt Bottom;
};
#ifndef AN_FP_IMAGE_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANFPrintPosition_ ANFPrintPosition;
#endif

N_DECLARE_TYPE(ANFPrintPosition)

struct ANFPQualityMetric_
{
	BdifFPPosition Position;
	NByte Score;
	NUShort AlgorithmVendorId;
	NUShort AlgorithmProductId;
};
#ifndef AN_FP_IMAGE_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANFPQualityMetric_ ANFPQualityMetric;
#endif

N_DECLARE_TYPE(ANFPQualityMetric)

typedef enum ANFRCaptureTechnology_
{
	anfrctUnknown = 0,
	anfrctOther = 1,
	anfrctScannedInkOnPaper = 2,
	anfrctOpticalTirBrightField = 3,
	anfrctOpticalTirDarkField = 4,
	anfrctOpticalDirectImagingNative = 5,
	anfrctOpticalDirectImagingLowFrequency = 6,
	anfrct3DImagingHighFrequency = 7,
	anfrctCapacitive = 9,
	anfrctCapacitiveRF = 10,
	anfrctOpticalDirectImagingElectroLuminescent = 11,
	anfrctReflectedUltrasonicImage = 12,
	anfrctUltrasonicImpediography = 13,
	anfrctThermalImaging = 14,
	anfrctDirectPressureSensitive = 15,
	anfrctIndirectPressure = 16,
	anfrctLiveTape = 17,
	anfrctLatentImpression = 18,
	anfrctLatentPhoto = 19,
	anfrctLatentMoldedImpression = 20,
	anfrctLatentTracing = 21,
	anfrctLatentLift = 22,
	anfrctUnspecified = 255
} ANFRCaptureTechnology;

N_DECLARE_TYPE(ANFRCaptureTechnology)

typedef enum ANFAmputationType_
{
	anfatAmputation = 0,
	anfatUnableToPrint = 1,
	anfatScar = 2
} ANFAmputationType;

N_DECLARE_TYPE(ANFAmputationType)

struct ANFAmputation_
{
	BdifFPPosition Position;
	ANFAmputationType Type;
};
#ifndef AN_FP_IMAGE_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANFAmputation_ ANFAmputation;
#endif

N_DECLARE_TYPE(ANFAmputation)

struct ANFSegment_
{
	BdifFPPosition Position;
	NInt Left;
	NInt Right;
	NInt Top;
	NInt Bottom;
};
#ifndef AN_FP_IMAGE_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANFSegment_ ANFSegment;
#endif

N_DECLARE_TYPE(ANFSegment)

NResult N_API ANFPImageAsciiBinaryRecordGetPositionCount(HANFPImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANFPImageAsciiBinaryRecordGetPosition(HANFPImageAsciiBinaryRecord hRecord, NInt index, BdifFPPosition * pValue);
NResult N_API ANFPImageAsciiBinaryRecordGetPositions(HANFPImageAsciiBinaryRecord hRecord, BdifFPPosition * * parValues, NInt * pValueCount);
NResult N_API ANFPImageAsciiBinaryRecordSetPosition(HANFPImageAsciiBinaryRecord hRecord, NInt index, BdifFPPosition value);
NResult N_API ANFPImageAsciiBinaryRecordAddPositionEx(HANFPImageAsciiBinaryRecord hRecord, BdifFPPosition value, NInt * pIndex);
NResult N_API ANFPImageAsciiBinaryRecordInsertPosition(HANFPImageAsciiBinaryRecord hRecord, NInt index, BdifFPPosition value);
NResult N_API ANFPImageAsciiBinaryRecordRemovePositionAt(HANFPImageAsciiBinaryRecord hRecord, NInt index);
NResult N_API ANFPImageAsciiBinaryRecordClearPositions(HANFPImageAsciiBinaryRecord hRecord);

NResult N_API ANFPImageAsciiBinaryRecordGetPrintPositionCount(HANFPImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANFPImageAsciiBinaryRecordGetPrintPosition(HANFPImageAsciiBinaryRecord hRecord, NInt index, struct ANFPrintPosition_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordGetPrintPositions(HANFPImageAsciiBinaryRecord hRecord, struct ANFPrintPosition_ * * parValues, NInt * pValueCount);
NResult N_API ANFPImageAsciiBinaryRecordSetPrintPosition(HANFPImageAsciiBinaryRecord hRecord, NInt index, const struct ANFPrintPosition_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordAddPrintPositionEx(HANFPImageAsciiBinaryRecord hRecord, const struct ANFPrintPosition_ * pValue, NInt * pIndex);
NResult N_API ANFPImageAsciiBinaryRecordInsertPrintPosition(HANFPImageAsciiBinaryRecord hRecord, NInt index, const struct ANFPrintPosition_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordRemovePrintPositionAt(HANFPImageAsciiBinaryRecord hRecord, NInt index);
NResult N_API ANFPImageAsciiBinaryRecordClearPrintPositions(HANFPImageAsciiBinaryRecord hRecord);

NResult N_API ANFPImageAsciiBinaryRecordGetAmputationCount(HANFPImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANFPImageAsciiBinaryRecordGetAmputation(HANFPImageAsciiBinaryRecord hRecord, NInt index, struct ANFAmputation_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordGetAmputations(HANFPImageAsciiBinaryRecord hRecord, struct ANFAmputation_ * * parValues, NInt * pValueCount);
NResult N_API ANFPImageAsciiBinaryRecordSetAmputation(HANFPImageAsciiBinaryRecord hRecord, NInt index, const struct ANFAmputation_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordAddAmputation(HANFPImageAsciiBinaryRecord hRecord, const struct ANFAmputation_ * pValue, NInt * pIndex);
NResult N_API ANFPImageAsciiBinaryRecordInsertAmputation(HANFPImageAsciiBinaryRecord hRecord, NInt index, const struct ANFAmputation_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordRemoveAmputationAt(HANFPImageAsciiBinaryRecord hRecord, NInt index);
NResult N_API ANFPImageAsciiBinaryRecordClearAmputations(HANFPImageAsciiBinaryRecord hRecord);

NResult N_API ANFPImageAsciiBinaryRecordGetSegmentCount(HANFPImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANFPImageAsciiBinaryRecordGetSegment(HANFPImageAsciiBinaryRecord hRecord, NInt index, struct ANFSegment_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordGetSegments(HANFPImageAsciiBinaryRecord hRecord, struct ANFSegment_ * * parValues, NInt * pValueCount);
NResult N_API ANFPImageAsciiBinaryRecordSetSegment(HANFPImageAsciiBinaryRecord hRecord, NInt index, const struct ANFSegment_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordAddSegment(HANFPImageAsciiBinaryRecord hRecord, const struct ANFSegment_ * pValue, NInt * pIndex);
NResult N_API ANFPImageAsciiBinaryRecordInsertSegment(HANFPImageAsciiBinaryRecord hRecord, NInt index, const struct ANFSegment_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordRemoveSegmentAt(HANFPImageAsciiBinaryRecord hRecord, NInt index);
NResult N_API ANFPImageAsciiBinaryRecordClearSegments(HANFPImageAsciiBinaryRecord hRecord);

NResult N_API ANFPImageAsciiBinaryRecordGetQualityMetricCount(HANFPImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANFPImageAsciiBinaryRecordGetQualityMetric(HANFPImageAsciiBinaryRecord hRecord, NInt index, struct ANFPQualityMetric_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordGetQualityMetrics(HANFPImageAsciiBinaryRecord hRecord, struct ANFPQualityMetric_ * * parValues, NInt * pValueCount);
NResult N_API ANFPImageAsciiBinaryRecordSetQualityMetric(HANFPImageAsciiBinaryRecord hRecord, NInt index, const struct ANFPQualityMetric_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordAddQualityMetricEx(HANFPImageAsciiBinaryRecord hRecord, const struct ANFPQualityMetric_ * pValue, NInt * pIndex);
NResult N_API ANFPImageAsciiBinaryRecordInsertQualityMetric(HANFPImageAsciiBinaryRecord hRecord, NInt index, const struct ANFPQualityMetric_ * pValue);
NResult N_API ANFPImageAsciiBinaryRecordRemoveQualityMetricAt(HANFPImageAsciiBinaryRecord hRecord, NInt index);
NResult N_API ANFPImageAsciiBinaryRecordClearQualityMetrics(HANFPImageAsciiBinaryRecord hRecord);

NResult N_API ANFPImageAsciiBinaryRecordGetImpressionType(HANFPImageAsciiBinaryRecord hRecord, BdifFPImpressionType * pValue);
NResult N_API ANFPImageAsciiBinaryRecordSetImpressionType(HANFPImageAsciiBinaryRecord hRecord, BdifFPImpressionType value);
NResult N_API ANFPImageAsciiBinaryRecordGetCaptureTechnology(HANFPImageAsciiBinaryRecord hRecord, ANFRCaptureTechnology * pValue);
NResult N_API ANFPImageAsciiBinaryRecordSetCaptureTechnology(HANFPImageAsciiBinaryRecord hRecord, ANFRCaptureTechnology value);

#ifdef N_CPP
}
#endif

#endif // !AN_FP_IMAGE_ASCII_BINARY_RECORD_H_INCLUDED
