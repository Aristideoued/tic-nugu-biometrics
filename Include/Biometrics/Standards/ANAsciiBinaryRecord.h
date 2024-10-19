#ifndef AN_ASCII_BINARY_RECORD_H_INCLUDED
#define AN_ASCII_BINARY_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANRecord.h>
#include <Core/NDateTime.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANAsciiBinaryRecord, ANRecord)

#define AN_ASCII_BINARY_RECORD_FIELD_SRC 4
#define AN_ASCII_BINARY_RECORD_FIELD_DAT 5

#define AN_ASCII_BINARY_RECORD_FIELD_SUB 46
#define AN_ASCII_BINARY_RECORD_FIELD_CON 47

#define AN_ASCII_BINARY_RECORD_FIELD_ANN  902
#define AN_ASCII_BINARY_RECORD_FIELD_DUI  903
#define AN_ASCII_BINARY_RECORD_FIELD_MMS  904

#define AN_ASCII_BINARY_RECORD_FIELD_SAN 993
#define AN_ASCII_BINARY_RECORD_FIELD_EFR 994
#define AN_ASCII_BINARY_RECORD_FIELD_ASC 995
#define AN_ASCII_BINARY_RECORD_FIELD_HAS 996
#define AN_ASCII_BINARY_RECORD_FIELD_SOR 997
#define AN_ASCII_BINARY_RECORD_FIELD_GEO 998

#define AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM 200
#define AN_ASCII_BINARY_RECORD_FIELD_UDF_TO   998
#define AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5   900

#define AN_ASCII_BINARY_RECORD_MIN_SOURCE_AGENCY_LENGTH     9
#define AN_ASCII_BINARY_RECORD_MIN_SOURCE_AGENCY_LENGTH_V5  1
#define AN_ASCII_BINARY_RECORD_MAX_SOURCE_AGENCY_LENGTH    20
#define AN_ASCII_BINARY_RECORD_MAX_SOURCE_AGENCY_LENGTH_V4 35

#define AN_ASCII_BINARY_RECORD_QUALITY_METRIC_SCORE_NOT_AVAILABLE 254
#define AN_ASCII_BINARY_RECORD_QUALITY_METRIC_SCORE_FAILED        255

#define AN_ASCII_BINARY_RECORD_MAX_QUALITY_METRIC_SCORE 100

#define AN_ASCII_BINARY_RECORD_MIN_SOURCE_AGENCY_NAME_LENGTH    1
#define AN_ASCII_BINARY_RECORD_MAX_SOURCE_AGENCY_NAME_LENGTH    125

#define AN_ASCII_BINARY_RECORD_MIN_CAPTURE_ORGANIZATION_NAME_LENGTH 1
#define AN_ASCII_BINARY_RECORD_MAX_CAPTURE_ORGANIZATION_NAME_LENGTH 1000

#define AN_ASCII_BINARY_RECORD_MIN_SOURCE_CONTEXT_REPRESENTATION_NUMBER           1
#define AN_ASCII_BINARY_RECORD_MAX_SOURCE_CONTEXT_REPRESENTATION_NUMBER           255
#define AN_ASCII_BINARY_RECORD_MIN_SOURCE_CONTEXT_REPRESENTATION_SEGMENT_POSITION 1
#define AN_ASCII_BINARY_RECORD_MAX_SOURCE_CONTEXT_REPRESENTATION_SEGMENT_POSITION 99

#define AN_ASCII_BINARY_RECORD_MAX_MAKE_LENGTH          AN_RECORD_MAX_MAKE_LENGTH
#define AN_ASCII_BINARY_RECORD_MAX_MODEL_LENGTH         AN_RECORD_MAX_MODEL_LENGTH
#define AN_ASCII_BINARY_RECORD_MAX_SERIAL_NUMBER_LENGTH AN_RECORD_MAX_SERIAL_NUMBER_LENGTH

#define AN_ASCII_BINARY_RECORD_HASH_LENGTH    64

#define AN_ASCII_BINARY_RECORD_MIN_GEO_LATITUTE_DEGREE   -90
#define AN_ASCII_BINARY_RECORD_MAX_GEO_LATITUTE_DEGREE   90

#define AN_ASCII_BINARY_RECORD_MIN_GEO_LONGITUDE_DEGREE  -180
#define AN_ASCII_BINARY_RECORD_MAX_GEO_LONGITUDE_DEGREE  180

#define AN_ASCII_BINARY_RECORD_MIN_GEO_MINUTE  0
#define AN_ASCII_BINARY_RECORD_MAX_GEO_MINUTE  59

#define AN_ASCII_BINARY_RECORD_MIN_GEO_SECOND  0
#define AN_ASCII_BINARY_RECORD_MAX_GEO_SECOND  59

#define AN_ASCII_BINARY_RECORD_MIN_GEO_ELEVATION  -422
#define AN_ASCII_BINARY_RECORD_MAX_GEO_ELEVATION  8848

#define AN_ASCII_BINARY_RECORD_MIN_GEODETIC_DATUM_CODE_LENGTH 3
#define AN_ASCII_BINARY_RECORD_MAX_GEODETIC_DATUM_CODE_LENGTH 6
#define AN_ASCII_BINARY_RECORD_GEO_DEFAULT_COORDINATE_SYSTEM  angcsWgs84

#define AN_ASCII_BINARY_RECORD_MIN_GEO_UTM_ZONE_LENGTH  2
#define AN_ASCII_BINARY_RECORD_MAX_GEO_UTM_ZONE_LENGTH  3

#define AN_ASCII_BINARY_RECORD_MAX_GEO_UTM_EASTING    999999
#define AN_ASCII_BINARY_RECORD_MAX_GEO_UTM_NORTHING   99999999

#define AN_ASCII_BINARY_RECORD_MAX_GEO_REFERENCE_TEXT_LENGTH  150

#define AN_ASCII_BINARY_RECORD_MAX_GEO_ALTERNATIVE_COORD_SYS_ID_LENGTH    10
#define AN_ASCII_BINARY_RECORD_MAX_GEO_ALTERNATIVE_COORD_SYS_VALUE_LENGTH 126

#define AN_ASCII_BINARY_RECORD_MAX_GEO_LATITUTE_DEGREE_LENGTH   9
#define AN_ASCII_BINARY_RECORD_MAX_GEO_LONGITUDE_DEGREE_LENGTH  10
#define AN_ASCII_BINARY_RECORD_MAX_GEO_MINUTE_LENGTH            8
#define AN_ASCII_BINARY_RECORD_MAX_GEO_SECOND_LENGTH            8
#define AN_ASCII_BINARY_RECORD_MAX_GEO_ELEVATION_LENGTH         8

#define AN_ASCII_BINARY_RECORD_MIN_FILE_TYPE_LENGTH      3
#define AN_ASCII_BINARY_RECORD_MAX_FILE_TYPE_LENGTH      6
#define AN_ASCII_BINARY_RECORD_MAX_DECODING_INSTR_LENGTH 1000

#define AN_ASCII_BINARY_RECORD_MIN_EXTERNAL_FILE_REFERENCE_LENGTH 1
#define AN_ASCII_BINARY_RECORD_MAX_EXTERNAL_FILE_REFERENCE_LENGTH 200

#define AN_ASCII_BINARY_RECORD_MIN_TIME_INDEX_COUNT  1
#define AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_COUNT  99

#define AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_LENGTH      12
#define AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_HOUR        99
#define AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_MINUTE      59
#define AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_SECOND      59
#define AN_ASCII_BINARY_RECORD_MAX_TIME_INDEX_MILLISECOND 999

#define AN_ASCII_BINARY_RECORD_MIN_ICDR_LENGTH      3
#define AN_ASCII_BINARY_RECORD_MIN_ICDR_LENGTH_V51  2
#define AN_ASCII_BINARY_RECORD_MAX_ICDR_LENGTH      9

struct ANQualityMetric_
{
	NByte Score;
	NUShort AlgorithmVendorId;
	NUShort AlgorithmProductId;
};
#ifndef AN_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANQualityMetric_ ANQualityMetric;
#endif

N_DECLARE_TYPE(ANQualityMetric)

typedef enum ANSubjectStatusCode_
{
	ansscUnknown = 0,
	ansscLivingPerson = 1,
	ansscNonLivingPerson = 2
} ANSubjectStatusCode;

N_DECLARE_TYPE(ANSubjectStatusCode)

typedef enum ANSubjectBodyStatusCode_
{
	ansbscUnspecified = 0,
	ansbscWhole = 1,
	ansbscFragment = 2
} ANSubjectBodyStatusCode;

N_DECLARE_TYPE(ANSubjectBodyStatusCode)

typedef enum ANSubjectBodyClassCode_
{
	ansbccUnspecified = 0,
	ansbccNaturalTissue = 1,
	ansbccDecomposed = 2,
	ansbccSkeletal = 3
} ANSubjectBodyClassCode;

N_DECLARE_TYPE(ANSubjectBodyClassCode)

struct ANSubjectCondition_
{
	ANSubjectStatusCode SubjectStatus;
	ANSubjectBodyStatusCode SubjectBodyStatus;
	ANSubjectBodyClassCode SubjectBodyClass;
};
#ifndef AN_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANSubjectCondition_ ANSubjectCondition;
#endif

N_DECLARE_TYPE(ANSubjectCondition)


struct ANFileFormat_
{
	HNString hFileType;
	HNString hDecodingInstructions;
};
#ifndef AN_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANFileFormat_ ANFileFormat;
#endif

N_DECLARE_TYPE(ANFileFormat)

struct ANSegment_
{
	NByte SegmentPosition;
	HNString hInternalFilePointer;
};
#ifndef AN_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANSegment_ ANSegment;
#endif

N_DECLARE_TYPE(ANSegment)

struct ANSourceContextRepresentation_
{
	NUInt ReferenceNumber;
	NUInt SegmentPosition;
};
#ifndef AN_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANSourceContextRepresentation_ ANSourceContextRepresentation;
#endif

N_DECLARE_TYPE(ANSourceContextRepresentation)


struct ANTimeIndex_
{
	NLong TimeIndexStart;
	NLong TimeIndexEnd;
};
#ifndef AN_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANTimeIndex_ ANTimeIndex;
#endif

N_DECLARE_TYPE(ANTimeIndex)

typedef enum ANGeographicCoordinateSystem_
{
	angcsUnspecified = 0,
	angcsAiry = 1,
	angcsAustralianNational = 2,
	angcsBessel1841 = 3,
	angcsBessel1841Namibia = 4,
	angcsClarke1866 = 5,
	angcsClarke1880 = 6,
	angcsEverest = 7,
	angcsFischer1960 = 8,
	angcsFischer1968 = 9,
	angcsGrs1967 = 10,
	angcsHelmert1906 = 11,
	angcsHough = 12,
	angcsInternational = 13,
	angcsKrassovsky = 14,
	angcsModifiedAiry = 15,
	angcsModifiedEverest = 16,
	angcsModifiedFischer1960 = 17,
	angcsSouthAmerican1969 = 18,
	angcsWgs60 = 19,
	angcsWgs66 = 20,
	angcsWgs72 = 21,
	angcsWgs84 = 22,
	angcsOther = 255
} ANGeographicCoordinateSystem;

N_DECLARE_TYPE(ANGeographicCoordinateSystem)

struct ANGeographicLocation_
{
	NBool hasUniversalTimeEntry;
	NDateTime_ universalTimeEntry;
	NBool hasLatitude;
	NDouble latitudeDegree;
	NDouble latitudeMinute;
	NDouble latitudeSecond;
	NBool hasLongitude;
	NDouble longitudeDegree;
	NDouble longitudeMinute;
	NDouble longitudeSecond;
	NBool hasElevation;
	NDouble elevation;
	ANGeographicCoordinateSystem geodeticDatumCode;
	HNString hOtherGeodeticDatumCode;
	HNString hUtmZone;
	NInt utmEasting;
	NInt utmNorthing;
	HNString hReferenceText;
	HNString hOtherSystemId;
	HNString hOtherSystemValue;
};
#ifndef AN_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANGeographicLocation_ ANGeographicLocation;
#endif

N_DECLARE_TYPE(ANGeographicLocation)

NResult N_API ANGeographicLocationCreateN(const NDateTime_ * pUniversalTimeEntry, const NDouble * pLatitudeDegree, NDouble latitudeMinute, NDouble latitudeSecond, 
		const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode, 
		HNString szOtherGeodeticDatumCode, HNString hUtmZone, NInt utmEasting, NInt utmNorthing, HNString hReferenceText, HNString hOtherSystemId, HNString hOtherSystemValue, struct ANGeographicLocation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANGeographicLocationCreateA(const NDateTime_ * pUniversalTimeEntry, const NDouble * pLatitudeDegree, NDouble latitudeMinute, NDouble latitudeSecond, 
		const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode, 
		const NAChar * szOtherGeodeticDatumCode, const NAChar * szUtmZone, NInt utmEasting, NInt utmNorthing, const NAChar * szReferenceText, const NAChar * szOtherSystemId, const NAChar * hOtherSystemValue, struct ANGeographicLocation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANGeographicLocationCreateW(const NDateTime_ * pUniversalTimeEntry, const NDouble * pLatitudeDegree, NDouble latitudeMinute, NDouble latitudeSecond, 
		const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode, 
		const NWChar * szOtherGeodeticDatumCode, const NWChar * szUtmZone, NInt utmEasting, NInt utmNorthing, const NWChar * szReferenceText, const NWChar * szOtherSystemId, const NWChar * hOtherSystemValue, struct ANGeographicLocation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANGeographicLocationCreate(const NDateTime_ * pUniversalTimeEntry, const NDouble * pLatitudeDegree, NDouble latitudeMinute, NDouble latitudeSecond, 
		const NDouble * pLongitudeDegree, NDouble longitudeMinute, NDouble longitudeSecond, const NDouble * pElevation, ANGeographicCoordinateSystem geodeticDatumCode, 
		const NChar * hOtherGeodeticDatumCode, const NChar * szUtmZone, NInt utmEasting, NInt utmNorthing, const NChar * szReferenceText, const NChar * szOtherSystemId, const NChar * hOtherSystemValue, ANGeographicLocation * pValue);
#endif
#define ANGeographicLocationCreate N_FUNC_AW(ANGeographicLocationCreate)

NResult N_API ANGeographicLocationDispose(struct ANGeographicLocation_ * pValue);
NResult N_API ANGeographicLocationCopy(const struct ANGeographicLocation_ * pSrcValue, struct ANGeographicLocation_ * pDstValue);
NResult N_API ANGeographicLocationSet(const struct ANGeographicLocation_ * pSrcValue, struct ANGeographicLocation_ * pDstValue);


NResult N_API ANFileFormatCreateN(HNString hFileType, HNString hDecodingInstructions, struct ANFileFormat_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFileFormatCreateA(const NAChar * szFileType, const NAChar * szDecodingInstructions, struct ANFileFormat_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFileFormatCreateW(const NWChar * szFileType, const NWChar * szDecodingInstructions, struct ANFileFormat_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFileFormatCreate(const NChar * szFileType, const NChar * szDecodingInstructions, ANFileFormat * pValue);
#endif
#define ANFileFormatCreate N_FUNC_AW(ANFileFormatCreate)

NResult N_API ANFileFormatDispose(struct ANFileFormat_ * pValue);
NResult N_API ANFileFormatCopy(const struct ANFileFormat_ * pSrcValue, struct ANFileFormat_ * pDstValue);
NResult N_API ANFileFormatSet(const struct ANFileFormat_ * pSrcValue, struct ANFileFormat_ * pDstValue);


NResult N_API ANSegmentCreateN(NByte segmentPosition, HNString hInternalFilePointer, struct ANSegment_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API AANSegmentCreateA(NByte segmentPosition, const NAChar * szInternalFilePointer, struct ANSegment_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSegmentCreateW(NByte segmentPosition, const NWChar * szInternalFilePointer, struct ANSegment_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSegmentCreate(NByte segmentPosition, const NChar * szInternalFilePointer, ANSegment * pValue);
#endif
#define ANSegmentCreate N_FUNC_AW(ANSegmentCreate)

NResult N_API ANSegmentDispose(struct ANSegment_ * pValue);
NResult N_API ANSegmentCopy(const struct ANSegment_ * pSrcValue, struct ANSegment_ * pDstValue);
NResult N_API ANSegmentSet(const struct ANSegment_ * pSrcValue, struct ANSegment_ * pDstValue);

typedef enum ANAcquisitionSourceType_
{
	anastUnspecified = 0,
	anastStaticDigitalImageFromUnknownSource = 1,
	anastStaticDigitalImageFromDigitalCamera = 2,
	anastStaticDigitalImageFromScanner = 3,
	anastSingleVideoFrameFromUnknownSource = 4,
	anastSingleVideoFrameFromAnalogCamera = 5,
	anastSingleVideoFrameFromDigitalCamera = 6,
	anastVideoSequenceFromUnknownSource = 7,
	anastVideoSequenceFromAnalogCameraInAnalogFormat = 8,
	anastVideoSequenceFromAnalogSourceInDigitalFormat = 9,
	anastVideoSequenceFromDigitalCamera = 10,
	anastComputerScreenImageCapture = 11,
	anastAnalogAudioRecordingDeviceInAnalogForm = 12,
	anastAnalogAudioRecordingDeviceInDigitalForm = 13,
	anastDigitalAudioRecordingDevice = 14,
	anastLandlineTelephoneBothSenderAndReceiver = 15,
	anastMobileTelephoneBothSenderAndReceiver = 16,
	anastSatelliteTelephoneBothSenderAndReceiver = 17,
	anastTelephoneUnknownOrMixedSource = 18,
	anastTelevisionNstc = 19,
	anastTelevisionPal = 20,
	anastTelevisionOther = 21,
	anastVoip = 22,
	anastRadioTransmissionShortWave = 23,
	anastRadioTransmissionAmateurRadio = 24,
	anastRadioTransmissionFm = 25,
	anastRadioTransmissionLongWave = 26,
	anastRadioTransmissionAm = 27,
	anastRadioTransmissionAircraftFrequencies = 28,
	anastRadioTransmissionShipAndCoastalStationFrequencies = 29,
	anastVendorSpecificCaptureFormat = 30,
	anastOther = 31
} ANAcquisitionSourceType;

N_DECLARE_TYPE(ANAcquisitionSourceType)

struct ANAcquisitionSource_
{
	ANAcquisitionSourceType acquisitionSourceType;
	HNString hAnalogToDigital;
	HNString hRadioTransmissionFormat;
	HNString hSpecialCharacteristics;
};
#ifndef AN_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANAcquisitionSource_ ANAcquisitionSource;
#endif

N_DECLARE_TYPE(ANAcquisitionSource)

NResult N_API ANAcquisitionSourceCreateN(ANAcquisitionSourceType acquisitionSourceType, HNString hAnalogToDigital, HNString hRadioTransmissionFormat, HNString hSpecialCharacteristics, struct ANAcquisitionSource_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANAcquisitionSourceCreateA(ANAcquisitionSourceType acquisitionSourceType, const NAChar * szAnalogToDigital, const NAChar * hszRadioTransmissionFormat, const NAChar * szSpecialCharacteristics, struct ANAcquisitionSource_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANAcquisitionSourceCreateW(ANAcquisitionSourceType acquisitionSourceType, const NWChar * szAnalogToDigital, const NWChar * hszRadioTransmissionFormat, const NWChar * szSpecialCharacteristics, struct ANAcquisitionSource_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANAcquisitionSourceCreate(ANAcquisitionSourceType acquisitionSourceType, const NChar * szAnalogToDigital, const NChar * hszRadioTransmissionFormat, const NChar * szSpecialCharacteristics, struct ANAcquisitionSource_ * pValue);
#endif
#define ANAcquisitionSourceCreate N_FUNC_AW(ANAcquisitionSourceCreate)

NResult N_API ANAcquisitionSourceDispose(struct ANAcquisitionSource_ * pValue);
NResult N_API ANAcquisitionSourceCopy(const struct ANAcquisitionSource_ * pSrcValue, struct ANAcquisitionSource_ * pDstValue);
NResult N_API ANAcquisitionSourceSet(const struct ANAcquisitionSource_ * pSrcValue, struct ANAcquisitionSource_ * pDstValue);

NResult N_API ANTimeIndexCreateTime(NInt hour, NInt minute, NInt second, NInt millisecond, NLong * pTime);
NResult N_API ANTimeIndexDecodeTime(NLong time, NInt * pHour, NInt * pMinute, NInt * pSecond, NInt * pMillisecond);

typedef enum ANEndianCode_
{
	anecUnspecified = -1,
	anecBigEndian = 0,
	anecLittleEndian = 1
} ANEndianCode;

N_DECLARE_TYPE(ANEndianCode)


NResult N_API ANAsciiBinaryRecordGetSourceAgencyN(HANAsciiBinaryRecord hRecord, HNString * phValue);

NResult N_API ANAsciiBinaryRecordSetSourceAgencyN(HANAsciiBinaryRecord hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANAsciiBinaryRecordSetSourceAgencyA(HANAsciiBinaryRecord hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANAsciiBinaryRecordSetSourceAgencyW(HANAsciiBinaryRecord hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANAsciiBinaryRecordSetSourceAgency(HANAsciiBinaryRecord hRecord, const NChar * szValue);
#endif
#define ANAsciiBinaryRecordSetSourceAgency N_FUNC_AW(ANAsciiBinaryRecordSetSourceAgency)

NResult N_API ANAsciiBinaryRecordGetDate(HANAsciiBinaryRecord hRecord, NDateTime_ * pValue);
NResult N_API ANAsciiBinaryRecordSetDate(HANAsciiBinaryRecord hRecord, NDateTime_ value);

NResult N_API ANAsciiBinaryRecordGetSubjectCondition(HANAsciiBinaryRecord hRecord, struct ANSubjectCondition_ * pValue, NBool * pHasValue);
NResult N_API ANAsciiBinaryRecordSetSubjectCondition(HANAsciiBinaryRecord hRecord, const struct ANSubjectCondition_ * pValue);

NResult N_API ANAsciiBinaryRecordGetCaptureOrganizationNameN(HANAsciiBinaryRecord hRecord, HNString * phValue);
NResult N_API ANAsciiBinaryRecordSetCaptureOrganizationNameN(HANAsciiBinaryRecord hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANAsciiBinaryRecordSetCaptureOrganizationNameA(HANAsciiBinaryRecord hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANAsciiBinaryRecordSetCaptureOrganizationNameW(HANAsciiBinaryRecord hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANAsciiBinaryRecordSetCaptureOrganizationName(HANAsciiBinaryRecord hRecord, const NChar * szValue);
#endif
#define ANAsciiBinaryRecordSetCaptureOrganizationName N_FUNC_AW(ANAsciiBinaryRecordSetCaptureOrganizationName)

NResult N_API ANAsciiBinaryRecordGetAnnotationCount(HANAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANAsciiBinaryRecordGetAnnotation(HANAsciiBinaryRecord hRecord, NInt index, struct ANAnnotation_ * pValue);
NResult N_API ANAsciiBinaryRecordGetAnnotationCapacity(HANAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANAsciiBinaryRecordSetAnnotationCapacity(HANAsciiBinaryRecord hRecord, NInt value);
NResult N_API ANAsciiBinaryRecordGetAnnotations(HANAsciiBinaryRecord hRecord, struct ANAnnotation_ * * parValues, NInt * pValueCount);
NResult N_API ANAsciiBinaryRecordSetAnnotation(HANAsciiBinaryRecord hRecord, NInt index, const struct ANAnnotation_ * pValue);
NResult N_API ANAsciiBinaryRecordAddAnnotation(HANAsciiBinaryRecord hRecord, const struct ANAnnotation_ * pValue, NInt * pIndex);
NResult N_API ANAsciiBinaryRecordInsertAnnotation(HANAsciiBinaryRecord hRecord, NInt index, const struct ANAnnotation_ * pValue);
NResult N_API ANAsciiBinaryRecordRemoveAnnotationAt(HANAsciiBinaryRecord hRecord, NInt index);
NResult N_API ANAsciiBinaryRecordClearAnnotations(HANAsciiBinaryRecord hRecord);

NResult N_API ANAsciiBinaryRecordGetDeviceUniqueIdentifierN(HANAsciiBinaryRecord hRecord, HNString * phValue);

NResult N_API ANAsciiBinaryRecordSetDeviceUniqueIdentifierN(HANAsciiBinaryRecord hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANAsciiBinaryRecordSetDeviceUniqueIdentifierA(HANAsciiBinaryRecord hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANAsciiBinaryRecordSetDeviceUniqueIdentifierW(HANAsciiBinaryRecord hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANAsciiBinaryRecordSetDeviceUniqueIdentifier(HANAsciiBinaryRecord hRecord, const NChar * szValue);
#endif
#define ANAsciiBinaryRecordSetDeviceUniqueIdentifier N_FUNC_AW(ANAsciiBinaryRecordSetDeviceUniqueIdentifier)


NResult N_API ANAsciiBinaryRecordGetMakeModelSerialNumber(HANAsciiBinaryRecord hRecord, struct ANMakeModelSerialNumber_ * pValue, NBool * pHasValue);
NResult N_API ANAsciiBinaryRecordGetMakeN(HANAsciiBinaryRecord hRecord, HNString * phValue);
NResult N_API ANAsciiBinaryRecordGetModelN(HANAsciiBinaryRecord hRecord, HNString * phValue);
NResult N_API ANAsciiBinaryRecordGetSerialNumberN(HANAsciiBinaryRecord hRecord, HNString * phValue);
NResult N_API ANAsciiBinaryRecordSetMakeModelSerialNumberEx(HANAsciiBinaryRecord hRecord, const struct ANMakeModelSerialNumber_ * pValue);

NResult N_API ANAsciiBinaryRecordSetMakeModelSerialNumberN(HANAsciiBinaryRecord hRecord, HNString hMake, HNString hModel, HNString hSerialNumber);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANAsciiBinaryRecordSetMakeModelSerialNumberA(HANAsciiBinaryRecord hRecord, const NAChar * szMake, const NAChar * szModel, const NAChar * szSerialNumber);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANAsciiBinaryRecordSetMakeModelSerialNumberW(HANAsciiBinaryRecord hRecord, const NWChar * szMake, const NWChar * szModel, const NWChar * szSerialNumber);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANAsciiBinaryRecordSetMakeModelSerialNumber(HANAsciiBinaryRecord hRecord, const NChar * szMake, const NChar * szModel, const NChar * szSerialNumber);
#endif
#define ANAsciiBinaryRecordSetMakeModelSerialNumber N_FUNC_AW(ANAsciiBinaryRecordSetMakeModelSerialNumber)


NResult N_API ANAsciiBinaryRecordGetSourceAgencyNameN(HANAsciiBinaryRecord hRecord, HNString * phValue);

NResult N_API ANAsciiBinaryRecordSetSourceAgencyNameN(HANAsciiBinaryRecord hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANAsciiBinaryRecordSetSourceAgencyNameA(HANAsciiBinaryRecord hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANAsciiBinaryRecordSetSourceAgencyNameW(HANAsciiBinaryRecord hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANAsciiBinaryRecordSetSourceAgencyName(HANAsciiBinaryRecord hRecord, const NChar * szValue);
#endif
#define ANAsciiBinaryRecordSetSourceAgencyName N_FUNC_AW(ANAsciiBinaryRecordSetSourceAgencyName)


NResult N_API ANAsciiBinaryRecordGetExternalFileReferenceN(HANAsciiBinaryRecord hRecord, HNString * phValue);

NResult N_API ANAsciiBinaryRecordSetExternalFileReferenceN(HANAsciiBinaryRecord hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANAsciiBinaryRecordSetExternalFileReferenceA(HANAsciiBinaryRecord hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANAsciiBinaryRecordSetExternalFileReferenceW(HANAsciiBinaryRecord hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANAsciiBinaryRecordSetExternalFileReference(HANAsciiBinaryRecord hRecord, const NChar * szValue);
#endif
#define ANAsciiBinaryRecordSetExternalFileReference N_FUNC_AW(ANAsciiBinaryRecordExternalFileReference)

NResult N_API ANAsciiBinaryRecordGetAssociatedContextCount(HANAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANAsciiBinaryRecordGetAssociatedContext(HANAsciiBinaryRecord hRecord, NInt index, struct ANSourceContextRepresentation_ * pValue);
NResult N_API ANAsciiBinaryRecordGetAssociatedContextCapacity(HANAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANAsciiBinaryRecordSetAssociatedContextCapacity(HANAsciiBinaryRecord hRecord, NInt value);
NResult N_API ANAsciiBinaryRecordGetAssociatedContexts(HANAsciiBinaryRecord hRecord, struct ANSourceContextRepresentation_ * * parValues, NInt * pValueCount);
NResult N_API ANAsciiBinaryRecordSetAssociatedContext(HANAsciiBinaryRecord hRecord, NInt index, const struct ANSourceContextRepresentation_ * pValue);
NResult N_API ANAsciiBinaryRecordAddAssociatedContext(HANAsciiBinaryRecord hRecord, const struct ANSourceContextRepresentation_ * pValue, NInt * pIndex);
NResult N_API ANAsciiBinaryRecordInsertAssociatedContext(HANAsciiBinaryRecord hRecord, NInt index, const struct ANSourceContextRepresentation_ * pValue);
NResult N_API ANAsciiBinaryRecordRemoveAssociatedContextAt(HANAsciiBinaryRecord hRecord, NInt index);
NResult N_API ANAsciiBinaryRecordClearAssociatedContexts(HANAsciiBinaryRecord hRecord);

NResult N_API ANAsciiBinaryRecordGetDataHashN(HANAsciiBinaryRecord hRecord, HNString * phValue);
NResult N_API ANAsciiBinaryRecordSetDataHashN(HANAsciiBinaryRecord hRecord, HNString hValue);

NResult N_API ANAsciiBinaryRecordGetSourceRepresentationCount(HANAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANAsciiBinaryRecordGetSourceRepresentation(HANAsciiBinaryRecord hRecord, NInt index, struct ANSourceContextRepresentation_ * pValue);
NResult N_API ANAsciiBinaryRecordGetSourceRepresentationCapacity(HANAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANAsciiBinaryRecordSetSourceRepresentationCapacity(HANAsciiBinaryRecord hRecord, NInt value);
NResult N_API ANAsciiBinaryRecordGetSourceRepresentations(HANAsciiBinaryRecord hRecord, struct ANSourceContextRepresentation_ * * parValues, NInt * pValueCount);
NResult N_API ANAsciiBinaryRecordSetSourceRepresentation(HANAsciiBinaryRecord hRecord, NInt index, const struct ANSourceContextRepresentation_ * pValue);
NResult N_API ANAsciiBinaryRecordAddSourceRepresentation(HANAsciiBinaryRecord hRecord, const struct ANSourceContextRepresentation_ * pValue, NInt * pIndex);
NResult N_API ANAsciiBinaryRecordInsertSourceRepresentation(HANAsciiBinaryRecord hRecord, NInt index, const struct ANSourceContextRepresentation_ * pValue);
NResult N_API ANAsciiBinaryRecordRemoveSourceRepresentationAt(HANAsciiBinaryRecord hRecord, NInt index);
NResult N_API ANAsciiBinaryRecordClearSourceRepresentations(HANAsciiBinaryRecord hRecord);

NResult N_API ANAsciiBinaryRecordGetGeographicLocation(HANAsciiBinaryRecord hRecord, struct ANGeographicLocation_ * pValue, NBool * pHasValue);
NResult N_API ANAsciiBinaryRecordSetGeographicLocation(HANAsciiBinaryRecord hRecord, const struct ANGeographicLocation_ * pValue);

#ifdef N_CPP
}
#endif

#endif // !AN_ASCII_BINARY_RECORD_H_INCLUDED
