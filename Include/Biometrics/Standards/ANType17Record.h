#ifndef AN_TYPE_17_RECORD_H_INCLUDED
#define AN_TYPE_17_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANImageAsciiBinaryRecord.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANType17Record, ANImageAsciiBinaryRecord)

#define AN_TYPE_17_RECORD_FIELD_LEN AN_RECORD_FIELD_LEN
#define AN_TYPE_17_RECORD_FIELD_IDC AN_RECORD_FIELD_IDC

#define AN_TYPE_17_RECORD_FIELD_FID 3

#define AN_TYPE_17_RECORD_FIELD_SRC AN_ASCII_BINARY_RECORD_FIELD_SRC
#define AN_TYPE_17_RECORD_FIELD_ICD AN_ASCII_BINARY_RECORD_FIELD_DAT
#define AN_TYPE_17_RECORD_FIELD_HLL AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL
#define AN_TYPE_17_RECORD_FIELD_VLL AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL
#define AN_TYPE_17_RECORD_FIELD_SLC AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC
#define AN_TYPE_17_RECORD_FIELD_HPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS
#define AN_TYPE_17_RECORD_FIELD_VPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS
#define AN_TYPE_17_RECORD_FIELD_CGA AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA
#define AN_TYPE_17_RECORD_FIELD_BPX AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX
#define AN_TYPE_17_RECORD_FIELD_CSP AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CSP

#define AN_TYPE_17_RECORD_FIELD_RAE  14
#define AN_TYPE_17_RECORD_FIELD_RAU  15
#define AN_TYPE_17_RECORD_FIELD_IPC  16
#define AN_TYPE_17_RECORD_FIELD_DUI  17
#define AN_TYPE_17_RECORD_FIELD_GUI  18
#define AN_TYPE_17_RECORD_FIELD_MMS  19
#define AN_TYPE_17_RECORD_FIELD_ECL  20
#define AN_TYPE_17_RECORD_FIELD_COM  21
#define AN_TYPE_17_RECORD_FIELD_SHPS 22
#define AN_TYPE_17_RECORD_FIELD_SVPS 23

#define AN_TYPE_17_RECORD_FIELD_IQS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM

#define AN_TYPE_17_RECORD_FIELD_ALS 25
#define AN_TYPE_17_RECORD_FIELD_IRD 26
#define AN_TYPE_17_RECORD_FIELD_SSV 27
#define AN_TYPE_17_RECORD_FIELD_DME 28

#define AN_TYPE_17_RECORD_FIELD_DMM AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM

#define AN_TYPE_17_RECORD_FIELD_IAP 31
#define AN_TYPE_17_RECORD_FIELD_ISF 32
#define AN_TYPE_17_RECORD_FIELD_IPB 33
#define AN_TYPE_17_RECORD_FIELD_ISB 34
#define AN_TYPE_17_RECORD_FIELD_UEB 35
#define AN_TYPE_17_RECORD_FIELD_LEB 36
#define AN_TYPE_17_RECORD_FIELD_NEO 37

#define AN_TYPE_17_RECORD_FIELD_RAN 40
#define AN_TYPE_17_RECORD_FIELD_GAZ 41

#define AN_TYPE_17_RECORD_FIELD_ANN AN_ASCII_BINARY_RECORD_FIELD_ANN

#define AN_TYPE_17_RECORD_FIELD_SAN AN_ASCII_BINARY_RECORD_FIELD_SAN
#define AN_TYPE_17_RECORD_FIELD_EFR AN_ASCII_BINARY_RECORD_FIELD_EFR
#define AN_TYPE_17_RECORD_FIELD_ASC AN_ASCII_BINARY_RECORD_FIELD_ASC
#define AN_TYPE_17_RECORD_FIELD_HAS AN_ASCII_BINARY_RECORD_FIELD_HAS
#define AN_TYPE_17_RECORD_FIELD_SOR AN_ASCII_BINARY_RECORD_FIELD_SOR
#define AN_TYPE_17_RECORD_FIELD_GEO AN_ASCII_BINARY_RECORD_FIELD_GEO

#define AN_TYPE_17_RECORD_FIELD_UDF_FROM  AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM
#define AN_TYPE_17_RECORD_FIELD_UDF_TO    AN_ASCII_BINARY_RECORD_FIELD_UDF_TO
#define AN_TYPE_17_RECORD_FIELD_UDF_TO_V5 AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5

#define AN_TYPE_17_RECORD_FIELD_DATA AN_RECORD_FIELD_DATA

#define AN_TYPE_17_RECORD_MAX_IRIS_DIAMETER    9999
#define AN_TYPE_17_RECORD_MIN_IRIS_DIAMETER_V5 10

#define AN_TYPE_17_RECORD_MAX_QUALITY_SCORE_COUNT    1
#define AN_TYPE_17_RECORD_MAX_QUALITY_SCORE_COUNT_V5 9

#define AN_TYPE_17_RECORD_MIN_LOWER_SPECTRUM_BOUND 500
#define AN_TYPE_17_RECORD_MAX_LOWER_SPECTRUM_BOUND 9990
#define AN_TYPE_17_RECORD_MIN_UPPER_SPECTRUM_BOUND 510
#define AN_TYPE_17_RECORD_MAX_UPPER_SPECTRUM_BOUND 9990

#define AN_TYPE_17_RECORD_IAP_20  20
#define AN_TYPE_17_RECORD_IAP_30  30
#define AN_TYPE_17_RECORD_IAP_40  40

#define AN_TYPE_17_RECORD_MIN_IRIS_PUPIL_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MIN_CIRCLE_VERTEX_COUNT
#define AN_TYPE_17_RECORD_MAX_IRIS_PUPIL_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT

#define AN_TYPE_17_RECORD_MIN_IRIS_SCLERA_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MIN_CIRCLE_VERTEX_COUNT
#define AN_TYPE_17_RECORD_MAX_IRIS_SCLERA_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT

#define AN_TYPE_17_RECORD_MIN_EYELID_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MIN_POLYGON_VERTEX_COUNT
#define AN_TYPE_17_RECORD_MAX_EYELID_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT

#define AN_TYPE_17_RECORD_MIN_OCCLUSION_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MIN_POLYGON_VERTEX_COUNT
#define AN_TYPE_17_RECORD_MAX_OCCLUSION_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT

#define AN_TYPE_17_RECORD_MIN_RANGE 1
#define AN_TYPE_17_RECORD_MAX_RANGE 9999999

#define AN_TYPE_17_RECORD_MAX_FRONTAL_GAZE_ANGLE 90

typedef enum ANIrisAcquisitionLightingSpectrum_
{
	anialsUnspecified = 0,
	anialsNir = 1,
	anialsVis = 2,
	anialsDefined = 3,
	anialsRed = 4,
	anialsUndefined = 254,
	anialsOther = 255
} ANIrisAcquisitionLightingSpectrum;

N_DECLARE_TYPE(ANIrisAcquisitionLightingSpectrum)

struct ANIrisImageProperties_
{
	BdifIrisOrientation HorzOrientation;
	BdifIrisOrientation VertOrientation;
	BdifIrisScanType ScanType;
};
#ifndef AN_TYPE_17_RECORD_HPP_INCLUDED
typedef struct ANIrisImageProperties_ ANIrisImageProperties;
#endif

N_DECLARE_TYPE(ANIrisImageProperties)

struct ANSpectrum_
{
	NUShort lowerBound;
	NUShort upperBound;
};
#ifndef AN_TYPE_17_RECORD_HPP_INCLUDED
typedef struct ANSpectrum_ ANSpectrum;
#endif

N_DECLARE_TYPE(ANSpectrum)

typedef enum ANDamagedEye_
{
	andeUnspecified = 0,
	andeMissing = 1,
	andeUnableToCapture = 2
} ANDamagedEye;

N_DECLARE_TYPE(ANDamagedEye)

NResult N_API ANType17RecordGetFeatureIdentifier(HANType17Record hRecord, BdifEyePosition * pValue);
NResult N_API ANType17RecordSetFeatureIdentifier(HANType17Record hRecord, BdifEyePosition value);
NResult N_API ANType17RecordGetRotationAngle(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordSetRotationAngle(HANType17Record hRecord, NInt value);
NResult N_API ANType17RecordGetRotationAngleUncertainty(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordSetRotationAngleUncertainty(HANType17Record hRecord, NInt value);
NResult N_API ANType17RecordGetImageProperties(HANType17Record hRecord, struct ANIrisImageProperties_ * pValue, NBool * pHasValue);
NResult N_API ANType17RecordSetImageProperties(HANType17Record hRecord, const struct ANIrisImageProperties_ * pValue);

NResult N_API ANType17RecordGetGuid(HANRecord hRecord, struct NGuid_ * pValue, NBool * pHasValue);
NResult N_API ANType17RecordSetGuid(HANRecord hRecord, const struct NGuid_ * pValue);

NResult N_API ANType17RecordGetEyeColor(HANRecord hRecord, BdifEyeColor * pValue);
NResult N_API ANType17RecordSetEyeColor(HANRecord hRecord, BdifEyeColor value);

NResult N_API ANType17RecordGetImageQualityScoreCount(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordGetImageQualityScoreEx(HANType17Record hRecord, NInt index, struct ANQualityMetric_ * pValue);
NResult N_API ANType17RecordGetImageQualityScores(HANType17Record hRecord, struct ANQualityMetric_ * * parValues, NInt * pValueCount);
NResult N_API ANType17RecordSetImageQualityScoreEx(HANType17Record hRecord, NInt index, const struct ANQualityMetric_ * pValue);
NResult N_API ANType17RecordAddImageQualityScore(HANType17Record hRecord, const struct ANQualityMetric_ * pValue, NInt * pIndex);
NResult N_API ANType17RecordInsertImageQualityScore(HANType17Record hRecord, NInt index, const struct ANQualityMetric_ * pValue);
NResult N_API ANType17RecordRemoveImageQualityScoreAt(HANType17Record hRecord, NInt index);
NResult N_API ANType17RecordClearImageQualityScores(HANType17Record hRecord);

NResult N_API ANType17RecordGetAcquisitionLightingSpectrum(HANRecord hRecord, ANIrisAcquisitionLightingSpectrum * pValue);
NResult N_API ANType17RecordSetAcquisitionLightingSpectrum(HANRecord hRecord, ANIrisAcquisitionLightingSpectrum value);
NResult N_API ANType17RecordGetIrisDiameter(HANRecord hRecord, NInt * pValue);
NResult N_API ANType17RecordSetIrisDiameter(HANRecord hRecord, NInt value);

NResult N_API ANType17RecordGetSpecifiedSpectrumValues(HANType17Record hRecord, struct ANSpectrum_ * pValue, NBool * pHasValue);
NResult N_API ANType17RecordSetSpecifiedSpectrumValues(HANType17Record hRecord, const struct ANSpectrum_ * pValue);
NResult N_API ANType17RecordGetDamagedEye(HANType17Record hRecord, ANDamagedEye * pValue);
NResult N_API ANType17RecordSetDamagedEye(HANType17Record hRecord, ANDamagedEye value);
NResult N_API ANType17RecordGetSubjectAcquisitionProfile(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordSetSubjectAcquisitionProfile(HANType17Record hRecord, NInt value);
NResult N_API ANType17RecordGetIrisStorageFormat(HANType17Record hRecord, BdifIrisImageFormat * pValue);
NResult N_API ANType17RecordSetIrisStorageFormat(HANType17Record hRecord, BdifIrisImageFormat value);

NResult N_API ANType17RecordGetIrisPupilBoundaryCode(HANType17Record hRecord, ANBoundaryCode * pValue);
NResult N_API ANType17RecordSetIrisPupilBoundaryCode(HANType17Record hRecord, ANBoundaryCode value);

NResult N_API ANType17RecordGetIrisPupilBoundaryVertexCount(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordGetIrisPupilBoundaryVertex(HANType17Record hRecord, NInt index, struct NPoint_ * pValue);
NResult N_API ANType17RecordGetIrisPupilBoundaryVertices(HANType17Record hRecord, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType17RecordSetIrisPupilBoundaryVertex(HANType17Record hRecord, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType17RecordAddIrisPupilBoundaryVertex(HANType17Record hRecord, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API ANType17RecordInsertIrisPupilBoundaryVertex(HANType17Record hRecord, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType17RecordRemoveIrisPupilBoundaryVertexAt(HANType17Record hRecord, NInt index);
NResult N_API ANType17RecordClearIrisPupilBoundaryVertices(HANType17Record hRecord);

NResult N_API ANType17RecordGetIrisScleraBoundaryCode(HANType17Record hRecord, ANBoundaryCode * pValue);
NResult N_API ANType17RecordSetIrisScleraBoundaryCode(HANType17Record hRecord, ANBoundaryCode value);

NResult N_API ANType17RecordGetIrisScleraBoundaryVertexCount(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordGetIrisScleraBoundaryVertex(HANType17Record hRecord, NInt index, struct NPoint_ * pValue);
NResult N_API ANType17RecordGetIrisScleraBoundaryVertices(HANType17Record hRecord, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType17RecordSetIrisScleraBoundaryVertex(HANType17Record hRecord, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType17RecordAddIrisScleraBoundaryVertex(HANType17Record hRecord, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API ANType17RecordInsertIrisScleraBoundaryVertex(HANType17Record hRecord, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType17RecordRemoveIrisScleraBoundaryVertexAt(HANType17Record hRecord, NInt index);
NResult N_API ANType17RecordClearIrisScleraBoundaryVertices(HANType17Record hRecord);

NResult N_API ANType17RecordGetUpperEyelidBoundaryCode(HANType17Record hRecord, ANBoundaryCode * pValue);
NResult N_API ANType17RecordSetUpperEyelidBoundaryCode(HANType17Record hRecord, ANBoundaryCode value);

NResult N_API ANType17RecordGetUpperEyelidBoundaryVertexCount(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordGetUpperEyelidBoundaryVertex(HANType17Record hRecord, NInt index, struct NPoint_ * pValue);
NResult N_API ANType17RecordGetUpperEyelidBoundaryVertices(HANType17Record hRecord, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType17RecordSetUpperEyelidBoundaryVertex(HANType17Record hRecord, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType17RecordAddUpperEyelidBoundaryVertex(HANType17Record hRecord, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API ANType17RecordInsertUpperEyelidBoundaryVertex(HANType17Record hRecord, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType17RecordRemoveUpperEyelidBoundaryVertexAt(HANType17Record hRecord, NInt index);
NResult N_API ANType17RecordClearUpperEyelidBoundaryVertices(HANType17Record hRecord);

NResult N_API ANType17RecordGetLowerEyelidBoundaryCode(HANType17Record hRecord, ANBoundaryCode * pValue);
NResult N_API ANType17RecordSetLowerEyelidBoundaryCode(HANType17Record hRecord, ANBoundaryCode value);

NResult N_API ANType17RecordGetLowerEyelidBoundaryVertexCount(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordGetLowerEyelidBoundaryVertex(HANType17Record hRecord, NInt index, struct NPoint_ * pValue);
NResult N_API ANType17RecordGetLowerEyelidBoundaryVertices(HANType17Record hRecord, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType17RecordSetLowerEyelidBoundaryVertex(HANType17Record hRecord, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType17RecordAddLowerEyelidBoundaryVertex(HANType17Record hRecord, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API ANType17RecordInsertLowerEyelidBoundaryVertex(HANType17Record hRecord, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType17RecordRemoveLowerEyelidBoundaryVertexAt(HANType17Record hRecord, NInt index);
NResult N_API ANType17RecordClearLowerEyelidBoundaryVertices(HANType17Record hRecord);

NResult N_API ANType17RecordGetOcclusionCount(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordGetOcclusion(HANType17Record hRecord, NInt index, struct ANOcclusion_ * pValue);
NResult N_API ANType17RecordGetOcclusions(HANType17Record hRecord, struct ANOcclusion_ * * parValues, NInt * pValueCount);
NResult N_API ANType17RecordSetOcclusion(HANType17Record hRecord, NInt index, const struct ANOcclusion_ * pValue);
NResult N_API ANType17RecordAddOcclusion(HANType17Record hRecord, const struct ANOcclusion_ * pValue, NInt * pIndex);
NResult N_API ANType17RecordInsertOcclusion(HANType17Record hRecord, NInt index, const struct ANOcclusion_ * pValue);
NResult N_API ANType17RecordRemoveOcclusionAt(HANType17Record hRecord, NInt index);
NResult N_API ANType17RecordClearOcclusions(HANType17Record hRecord);

NResult N_API ANType17RecordGetOcclusionVertexCount(HANType17Record hRecord, NInt occlusionIndex, NInt * pValue);
NResult N_API ANType17RecordGetOcclusionVertex(HANType17Record hRecord, NInt occlusionIndex, NInt index, struct NPoint_ * pValue);
NResult N_API ANType17RecordGetOcclusionVertices(HANType17Record hRecord, NInt occlusionIndex, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType17RecordSetOcclusionVertex(HANType17Record hRecord, NInt occlusionIndex, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType17RecordAddOcclusionVertex(HANType17Record hRecord, NInt occlusionIndex, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API ANType17RecordInsertOcclusionVertex(HANType17Record hRecord, NInt occlusionIndex, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType17RecordRemoveOcclusionVertexAt(HANType17Record hRecord, NInt occlusionIndex, NInt index);
NResult N_API ANType17RecordClearOcclusionVertices(HANType17Record hRecord, NInt occlusionIndex);

NResult N_API ANType17RecordGetRange(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordSetRange(HANType17Record hRecord, NInt value);
NResult N_API ANType17RecordGetFrontalGazeAngle(HANType17Record hRecord, NInt * pValue);
NResult N_API ANType17RecordSetFrontalGazeAngle(HANType17Record hRecord, NInt value);

#ifdef N_CPP
}
#endif

#endif // !AN_TYPE_17_RECORD_H_INCLUDED
