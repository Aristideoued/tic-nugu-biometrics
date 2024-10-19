#ifndef AN_TYPE_14_RECORD_H_INCLUDED
#define AN_TYPE_14_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANFPImageAsciiBinaryRecord.h>
#include <Geometry/NGeometry.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANType14Record, ANFPImageAsciiBinaryRecord)

#define AN_TYPE_14_RECORD_FIELD_LEN  AN_RECORD_FIELD_LEN
#define AN_TYPE_14_RECORD_FIELD_IDC  AN_RECORD_FIELD_IDC
#define AN_TYPE_14_RECORD_FIELD_IMP  AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_IMP
#define AN_TYPE_14_RECORD_FIELD_SRC  AN_ASCII_BINARY_RECORD_FIELD_SRC
#define AN_TYPE_14_RECORD_FIELD_FCD  AN_ASCII_BINARY_RECORD_FIELD_DAT
#define AN_TYPE_14_RECORD_FIELD_HLL  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL
#define AN_TYPE_14_RECORD_FIELD_VLL  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL
#define AN_TYPE_14_RECORD_FIELD_SLC  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC
#define AN_TYPE_14_RECORD_FIELD_HPS  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS
#define AN_TYPE_14_RECORD_FIELD_VPS  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS
#define AN_TYPE_14_RECORD_FIELD_CGA  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA
#define AN_TYPE_14_RECORD_FIELD_BPX  AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX
#define AN_TYPE_14_RECORD_FIELD_FGP  AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FGP
#define AN_TYPE_14_RECORD_FIELD_PPD  AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_PD
#define AN_TYPE_14_RECORD_FIELD_PPC  AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_PPC
#define AN_TYPE_14_RECORD_FIELD_SHPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS
#define AN_TYPE_14_RECORD_FIELD_SVPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS

#define AN_TYPE_14_RECORD_FIELD_AMP AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_AMP
#define AN_TYPE_14_RECORD_FIELD_COM AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM
#define AN_TYPE_14_RECORD_FIELD_SEG AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_SEG

#define AN_TYPE_14_RECORD_FIELD_NQM 22
#define AN_TYPE_14_RECORD_FIELD_SQM 23

#define AN_TYPE_14_RECORD_FIELD_FQM AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM

#define AN_TYPE_14_RECORD_FIELD_ASEG 25
#define AN_TYPE_14_RECORD_FIELD_SCF  26
#define AN_TYPE_14_RECORD_FIELD_SIF  27

#define AN_TYPE_14_RECORD_FIELD_DMM AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM
#define AN_TYPE_14_RECORD_FIELD_FAP 31

#define AN_TYPE_14_RECORD_FIELD_SUB AN_ASCII_BINARY_RECORD_FIELD_SUB
#define AN_TYPE_14_RECORD_FIELD_CON AN_ASCII_BINARY_RECORD_FIELD_CON

#define AN_TYPE_14_RECORD_FIELD_FCT AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FCT
#define AN_TYPE_14_RECORD_FIELD_ANN AN_ASCII_BINARY_RECORD_FIELD_ANN
#define AN_TYPE_14_RECORD_FIELD_DUI AN_ASCII_BINARY_RECORD_FIELD_DUI
#define AN_TYPE_14_RECORD_FIELD_MMS AN_ASCII_BINARY_RECORD_FIELD_MMS

#define AN_TYPE_14_RECORD_FIELD_SAN AN_ASCII_BINARY_RECORD_FIELD_SAN
#define AN_TYPE_14_RECORD_FIELD_EFR AN_ASCII_BINARY_RECORD_FIELD_EFR
#define AN_TYPE_14_RECORD_FIELD_ASC AN_ASCII_BINARY_RECORD_FIELD_ASC
#define AN_TYPE_14_RECORD_FIELD_HAS AN_ASCII_BINARY_RECORD_FIELD_HAS
#define AN_TYPE_14_RECORD_FIELD_SOR AN_ASCII_BINARY_RECORD_FIELD_SOR
#define AN_TYPE_14_RECORD_FIELD_GEO AN_ASCII_BINARY_RECORD_FIELD_GEO

#define AN_TYPE_14_RECORD_FIELD_UDF_FROM AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM
#define AN_TYPE_14_RECORD_FIELD_UDF_TO   AN_ASCII_BINARY_RECORD_FIELD_UDF_TO
#define AN_TYPE_14_RECORD_FIELD_UDF_TO_V5 AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5

#define AN_TYPE_14_RECORD_FIELD_DATA AN_RECORD_FIELD_DATA

#define AN_TYPE_14_RECORD_MAX_AMPUTATION_COUNT             4
#define AN_TYPE_14_RECORD_MAX_AMPUTATION_COUNT_V5          5
#define AN_TYPE_14_RECORD_MAX_SEGMENT_COUNT_V5             5
#define AN_TYPE_14_RECORD_MAX_NIST_QUALITY_METRIC_COUNT    4
#define AN_TYPE_14_RECORD_MAX_NIST_QUALITY_METRIC_COUNT_V5 5
#define AN_TYPE_14_RECORD_MAX_ALTERNATE_SEGMENT_COUNT      4
#define AN_TYPE_14_RECORD_MAX_ALTERNATE_SEGMENT_COUNT_V5   5

#define AN_TYPE_14_RECORD_MIN_ALTERNATE_SEGMENT_VERTEX_COUNT  3
#define AN_TYPE_14_RECORD_MAX_ALTERNATE_SEGMENT_VERTEX_COUNT 99

#define AN_TYPE_14_RECORD_MAX_SEGMENTATION_QUALITY_METRIC_COUNT_V5  5
#define AN_TYPE_14_RECORD_MAX_SEGMENTATION_QUALITY_METRIC_COUNT_V52 45
#define AN_TYPE_14_RECORD_MAX_FINGERPRINT_QUALITY_METRIC_COUNT_V5   5
#define AN_TYPE_14_RECORD_MAX_FINGERPRINT_QUALITY_METRIC_COUNT_V52  45

#define AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_EXCELLENT       1
#define AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_VERY_GOOD       2
#define AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_GOOD            3
#define AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_FAIR            4
#define AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_POOR            5
#define AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_NOT_AVAILABLE 254
#define AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_FAILED        255

#define AN_TYPE_14_RECORD_MIN_SIMULTANEOUS_CAPTURE_ID  1
#define AN_TYPE_14_RECORD_MAX_SIMULTANEOUS_CAPTURE_ID  255

#define AN_TYPE_14_RECORD_FAP_10       10
#define AN_TYPE_14_RECORD_FAP_20       20
#define AN_TYPE_14_RECORD_FAP_30       30
#define AN_TYPE_14_RECORD_FAP_40       40
#define AN_TYPE_14_RECORD_FAP_45       45
#define AN_TYPE_14_RECORD_FAP_50       50
#define AN_TYPE_14_RECORD_FAP_60       60
#define AN_TYPE_14_RECORD_FAP_145      145
#define AN_TYPE_14_RECORD_FAP_150      150
#define AN_TYPE_14_RECORD_FAP_160      160

struct ANNistQualityMetric_
{
	BdifFPPosition Position;
	NByte Score;
};
#ifndef AN_TYPE_14_RECORD_HPP_INCLUDED
typedef struct ANNistQualityMetric_ ANNistQualityMetric;
#endif

N_DECLARE_TYPE(ANNistQualityMetric)

struct ANFAlternateSegment_
{
	BdifFPPosition Position;
};
#ifndef AN_TYPE_14_RECORD_HPP_INCLUDED
typedef struct ANFAlternateSegment_ ANFAlternateSegment;
#endif

N_DECLARE_TYPE(ANFAlternateSegment)

NResult N_API ANType14RecordGetPrintPositionDescriptor(HANType14Record hRecord, struct ANFPositionDescriptor_ * pValue, NBool * pHasValue);
NResult N_API ANType14RecordSetPrintPositionDescriptor(HANType14Record hRecord, const struct ANFPositionDescriptor_ * pValue);

NResult N_API ANType14RecordGetNistQualityMetricCount(HANType14Record hRecord, NInt * pValue);
NResult N_API ANType14RecordGetNistQualityMetric(HANType14Record hRecord, NInt index, struct ANNistQualityMetric_ * pValue);
NResult N_API ANType14RecordGetNistQualityMetrics(HANType14Record hRecord, struct ANNistQualityMetric_ * * parValues, NInt * pValueCount);
NResult N_API ANType14RecordSetNistQualityMetric(HANType14Record hRecord, NInt index, const struct ANNistQualityMetric_ * pValue);
NResult N_API ANType14RecordAddNistQualityMetricEx(HANType14Record hRecord, const struct ANNistQualityMetric_ * pValue, NInt * pIndex);
NResult N_API ANType14RecordInsertNistQualityMetric(HANType14Record hRecord, NInt index, const struct ANNistQualityMetric_ * pValue);
NResult N_API ANType14RecordRemoveNistQualityMetricAt(HANType14Record hRecord, NInt index);
NResult N_API ANType14RecordClearNistQualityMetrics(HANType14Record hRecord);

NResult N_API ANType14RecordGetSegmentationQualityMetricCount(HANType14Record hRecord, NInt * pValue);
NResult N_API ANType14RecordGetSegmentationQualityMetric(HANType14Record hRecord, NInt index, struct ANFPQualityMetric_ * pValue);
NResult N_API ANType14RecordGetSegmentationQualityMetrics(HANType14Record hRecord, struct ANFPQualityMetric_ * * parValues, NInt * pValueCount);
NResult N_API ANType14RecordSetSegmentationQualityMetric(HANType14Record hRecord, NInt index, const struct ANFPQualityMetric_ * pValue);
NResult N_API ANType14RecordAddSegmentationQualityMetricEx(HANType14Record hRecord, const struct ANFPQualityMetric_ * pValue, NInt * pIndex);
NResult N_API ANType14RecordInsertSegmentationQualityMetric(HANType14Record hRecord, NInt index, const struct ANFPQualityMetric_ * pValue);
NResult N_API ANType14RecordRemoveSegmentationQualityMetricAt(HANType14Record hRecord, NInt index);
NResult N_API ANType14RecordClearSegmentationQualityMetrics(HANType14Record hRecord);

NResult N_API ANType14RecordGetAlternateSegmentCount(HANType14Record hRecord, NInt * pValue);
NResult N_API ANType14RecordGetAlternateSegment(HANType14Record hRecord, NInt index, struct ANFAlternateSegment_ * pValue);
NResult N_API ANType14RecordGetAlternateSegments(HANType14Record hRecord, struct ANFAlternateSegment_ * * parValues, NInt * pValueCount);
NResult N_API ANType14RecordSetAlternateSegment(HANType14Record hRecord, NInt index, const struct ANFAlternateSegment_ * pValue);
NResult N_API ANType14RecordAddAlternateSegmentEx(HANType14Record hRecord, const struct ANFAlternateSegment_ * pValue, NInt * pIndex);
NResult N_API ANType14RecordInsertAlternateSegment(HANType14Record hRecord, NInt index, const struct ANFAlternateSegment_ * pValue);
NResult N_API ANType14RecordRemoveAlternateSegmentAt(HANType14Record hRecord, NInt index);
NResult N_API ANType14RecordClearAlternateSegments(HANType14Record hRecord);

NResult N_API ANType14RecordGetAlternateSegmentVertexCount(HANType14Record hRecord, NInt segmentIndex, NInt * pValue);
NResult N_API ANType14RecordGetAlternateSegmentVertex(HANType14Record hRecord, NInt segmentIndex, NInt index, struct NPoint_ * pValue);
NResult N_API ANType14RecordGetAlternateSegmentVertices(HANType14Record hRecord, NInt segmentIndex, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType14RecordSetAlternateSegmentVertex(HANType14Record hRecord, NInt segmentIndex, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType14RecordAddAlternateSegmentVertexEx(HANType14Record hRecord, NInt segmentIndex, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API ANType14RecordInsertAlternateSegmentVertex(HANType14Record hRecord, NInt segmentIndex, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType14RecordRemoveAlternateSegmentVertexAt(HANType14Record hRecord, NInt segmentIndex, NInt index);
NResult N_API ANType14RecordClearAlternateSegmentVertices(HANType14Record hRecord, NInt segmentIndex);

NResult N_API ANType14RecordGetSimultaneousCaptureId(HANType14Record hRecord, NInt * pValue);
NResult N_API ANType14RecordSetSimultaneousCaptureId(HANType14Record hRecord, NInt value);
NResult N_API ANType14RecordGetStitchedImageFlag(HANType14Record hRecord, NBool * pValue);
NResult N_API ANType14RecordSetStitchedImageFlag(HANType14Record hRecord, NBool value);
NResult N_API ANType14RecordGetSubjectAcquisitionProfile(HANType14Record hRecord, NInt * pValue);
NResult N_API ANType14RecordSetSubjectAcquisitionProfile(HANType14Record hRecord, NInt value);

#ifdef N_CPP
}
#endif

#endif // !AN_TYPE_14_RECORD_H_INCLUDED
