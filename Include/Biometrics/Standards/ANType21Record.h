#ifndef AN_TYPE_21_RECORD_H_INCLUDED
#define AN_TYPE_21_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANAsciiBinaryRecord.h>
#include <Geometry/NGeometry.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANType21Record, ANAsciiBinaryRecord)

#define AN_TYPE_21_RECORD_FIELD_LEN AN_RECORD_FIELD_LEN
#define AN_TYPE_21_RECORD_FIELD_IDC AN_RECORD_FIELD_IDC

#define AN_TYPE_21_RECORD_FIELD_SRC AN_ASCII_BINARY_RECORD_FIELD_SRC
#define AN_TYPE_21_RECORD_FIELD_ACD AN_ASCII_BINARY_RECORD_FIELD_DAT

#define AN_TYPE_21_RECORD_FIELD_MDI  6
#define AN_TYPE_21_RECORD_FIELD_AFT  15
#define AN_TYPE_21_RECORD_FIELD_SEG  16
#define AN_TYPE_21_RECORD_FIELD_TIX  19
#define AN_TYPE_21_RECORD_FIELD_COM  20
#define AN_TYPE_21_RECORD_FIELD_ACN  21
#define AN_TYPE_21_RECORD_FIELD_ICDR 22

#define AN_TYPE_21_RECORD_FIELD_SUB AN_ASCII_BINARY_RECORD_FIELD_SUB
#define AN_TYPE_21_RECORD_FIELD_CON AN_ASCII_BINARY_RECORD_FIELD_CON

#define AN_TYPE_21_RECORD_FIELD_ANN AN_ASCII_BINARY_RECORD_FIELD_ANN

#define AN_TYPE_21_RECORD_FIELD_SAN AN_ASCII_BINARY_RECORD_FIELD_SAN
#define AN_TYPE_21_RECORD_FIELD_EFR AN_ASCII_BINARY_RECORD_FIELD_EFR
#define AN_TYPE_21_RECORD_FIELD_HAS AN_ASCII_BINARY_RECORD_FIELD_HAS
#define AN_TYPE_21_RECORD_FIELD_GEO AN_ASCII_BINARY_RECORD_FIELD_GEO

#define AN_TYPE_21_RECORD_FIELD_UDF_FROM AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM
#define AN_TYPE_21_RECORD_FIELD_UDF_TO_V5 AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5

#define AN_TYPE_21_RECORD_FIELD_DATA AN_RECORD_FIELD_DATA

#define AN_TYPE_21_RECORD_MIN_MDI_LENGTH 1
#define AN_TYPE_21_RECORD_MAX_MDI_LENGTH 500

#define AN_TYPE_21_RECORD_MIN_ASSOCIATED_CONTEXT_NUMBER  1
#define AN_TYPE_21_RECORD_MAX_ASSOCIATED_CONTEXT_NUMBER  255
#define AN_TYPE_21_RECORD_ASSOCIATED_CONTEXT_LENGTH      3

#define AN_TYPE_21_RECORD_MIN_SEGMENT_COUNT 1
#define AN_TYPE_21_RECORD_MAX_SEGMENT_COUNT 99
#define AN_TYPE_21_RECORD_MIN_SEGMENT_VERTEX_COUNT 3
#define AN_TYPE_21_RECORD_MAX_SEGMENT_VERTEX_COUNT 99
#define AN_TYPE_21_RECORD_MIN_SEGMENT_INTERNAL_FILE_POINTER_LENGTH 1
#define AN_TYPE_21_RECORD_MAX_SEGMENT_INTERNAL_FILE_POINTER_LENGTH 15

#define AN_TYPE_21_RECORD_MAX_COMMENT_LENGTH  126

struct ANMedicalDevice_
{
	HNString hDeviceType;
	HNString hDeviceManufacturer;
	HNString hDeviceMake;
	HNString hDeviceModel;
	HNString hDeviceSerialNumber;
	HNString hComment;
};
#ifndef AN_TYPE_21_RECORD_HPP_INCLUDED
typedef struct ANMedicalDevice_ ANMedicalDevice;
#endif

N_DECLARE_TYPE(ANMedicalDevice)

NResult N_API ANMedicalDeviceCreateN(HNString hDeviceType, HNString hDeviceManufacturer, HNString hDeviceMake, HNString hDeviceModel, HNString hDeviceSerialNumber, HNString hComment, struct ANMedicalDevice_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANMedicalDeviceCreateA(const NAChar * szDeviceType, const NAChar * szDeviceManufacturer, const NAChar * szDeviceMake, const NAChar * szDeviceModel, const NAChar * szDeviceSerialNumber, const NAChar * szComment, struct ANMedicalDevice_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANMedicalDeviceCreateW(const NWChar * szDeviceType, const NWChar * szDeviceManufacturer, const NWChar * szDeviceMake, const NWChar * szDeviceModel, const NWChar * szDeviceSerialNumber, const NWChar * szComment, struct ANMedicalDevice_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANMedicalDeviceCreate(const NChar * szDeviceType, const NChar * szDeviceManufacturer, const NChar * szDeviceMake, const NChar * szDeviceModel, const NChar * szDeviceSerialNumber, const NChar * szComment, structANMedicalDevice_ * pValue);
#endif
#define ANMedicalDeviceCreate N_FUNC_AW(ANMedicalDeviceCreate)

NResult N_API ANMedicalDeviceDispose(struct ANMedicalDevice_ * pValue);
NResult N_API ANMedicalDeviceCopy(const struct ANMedicalDevice_ * pSrcValue, struct ANMedicalDevice_ * pDstValue);
NResult N_API ANMedicalDeviceSet(const struct ANMedicalDevice_ * pSrcValue, struct ANMedicalDevice_ * pDstValue);

NResult N_API ANType21RecordGetMedicalDeviceCount(HANType21Record hRecord, NInt * pValue);
NResult N_API ANType21RecordGetMedicalDevice(HANType21Record hRecord, NInt index, struct ANMedicalDevice_ * pValue);
NResult N_API ANType21RecordGetMedicalDeviceCapacity(HANType21Record hRecord, NInt * pValue);
NResult N_API ANType21RecordSetMedicalDeviceCapacity(HANType21Record hRecord, NInt value);
NResult N_API ANType21RecordGetMedicalDevices(HANType21Record hRecord, struct ANMedicalDevice_ * * parValues, NInt * pValueCount);
NResult N_API ANType21RecordSetMedicalDevice(HANType21Record hRecord, NInt index, const struct ANMedicalDevice_ * pValue);
NResult N_API ANType21RecordAddMedicalDevice(HANType21Record hRecord, const struct ANMedicalDevice_ * pValue, NInt * pIndex);
NResult N_API ANType21RecordInsertMedicalDevice(HANType21Record hRecord, NInt index, const struct ANMedicalDevice_ * pValue);
NResult N_API ANType21RecordRemoveMedicalDeviceAt(HANType21Record hRecord, NInt index);
NResult N_API ANType21RecordClearMedicalDevices(HANType21Record hRecord);

NResult N_API ANType21RecordGetAssociatedContextFormat(HANType21Record hRecord, struct ANFileFormat_ * pValue, NBool * pHasValue);
NResult N_API ANType21RecordGetAssociatedContextFormatFileTypeN(HANType21Record hRecord, HNString * phDigitalFileSuffix);
NResult N_API ANType21RecordGetAssociatedContextFormatDecodingInstructionsN(HANType21Record hRecord, HNString * phValue);
NResult N_API ANType21RecordSetAssociatedContextFormatEx(HANType21Record hRecord, const struct ANFileFormat_ * pValue);

NResult N_API ANType21RecordSetAssociatedContextFormatN(HANType21Record hRecord, HNString hFileType, HNString hDecodingInstructions);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType21RecordSetAssociatedContextFormatA(HANType21Record hRecord, const NAChar * szFileType, const NAChar * szDecodingInstructions);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType21RecordSetAssociatedContextFormatW(HANType21Record hRecord, const NWChar * szFileType, const NWChar * szDecodingInstructions);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType21RecordSetAssociatedContextFormat(HANType21Record hRecord, const NChar * szFileType, const NChar * szDecodingInstructions);
#endif
#define ANType21RecordSetAssociatedContextFormat N_FUNC_AW(ANType21RecordSetAssociatedContextFormat)

NResult N_API ANType21RecordGetSegmentCount(HANType21Record hRecord, NInt * pValue);
NResult N_API ANType21RecordGetSegment(HANType21Record hRecord, NInt index, struct ANSegment_ * pValue);
NResult N_API ANType21RecordGetSegmentCapacity(HANType21Record hRecord, NInt * pValue);
NResult N_API ANType21RecordSetSegmentCapacity(HANType21Record hRecord, NInt value);
NResult N_API ANType21RecordGetSegments(HANType21Record hRecord, struct ANSegment_ * * parValues, NInt * pValueCount);
NResult N_API ANType21RecordSetSegment(HANType21Record hRecord, NInt index, const struct ANSegment_ * pValue);
NResult N_API ANType21RecordAddSegment(HANType21Record hRecord, const struct ANSegment_ * pValue, NInt * pIndex);
NResult N_API ANType21RecordInsertSegment(HANType21Record hRecord, NInt index, const struct ANSegment_ * pValue);
NResult N_API ANType21RecordRemoveSegmentAt(HANType21Record hRecord, NInt index);
NResult N_API ANType21RecordClearSegments(HANType21Record hRecord);

NResult N_API ANType21RecordGetSegmentVertexCount(HANType21Record hRecord, NInt segmentIndex, NInt * pValue);
NResult N_API ANType21RecordGetSegmentVertex(HANType21Record hRecord, NInt segmentIndex, NInt index, struct NPoint_ * pValue);
NResult N_API ANType21RecordGetSegmentVertices(HANType21Record hRecord, NInt segmentIndex, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType21RecordSetSegmentVertex(HANType21Record hRecord, NInt segmentIndex, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType21RecordAddSegmentVertex(HANType21Record hRecord, NInt segmentIndex, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API ANType21RecordInsertSegmentVertex(HANType21Record hRecord, NInt segmentIndex, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType21RecordRemoveSegmentVertexAt(HANType21Record hRecord, NInt segmentIndex, NInt index);
NResult N_API ANType21RecordClearSegmentVertices(HANType21Record hRecord, NInt segmentIndex);

NResult N_API ANType21RecordGetTimeIndexCount(HANType21Record hRecord, NInt * pValue);
NResult N_API ANType21RecordGetTimeIndex(HANType21Record hRecord, NInt index, struct ANTimeIndex_ * pValue);
NResult N_API ANType21RecordGetTimeIndexCapacity(HANType21Record hRecord, NInt * pValue);
NResult N_API ANType21RecordSetTimeIndexCapacity(HANType21Record hRecord, NInt value);
NResult N_API ANType21RecordGetTimeIndexes(HANType21Record hRecord, struct ANTimeIndex_ * * parValues, NInt * pValueCount);
NResult N_API ANType21RecordSetTimeIndex(HANType21Record hRecord, NInt index, const struct ANTimeIndex_ * pValue);
NResult N_API ANType21RecordAddTimeIndex(HANType21Record hRecord, const struct ANTimeIndex_ * pValue, NInt * pIndex);
NResult N_API ANType21RecordInsertTimeIndex(HANType21Record hRecord, NInt index, const struct ANTimeIndex_ * pValue);
NResult N_API ANType21RecordRemoveTimeIndexAt(HANType21Record hRecord, NInt index);
NResult N_API ANType21RecordClearTimeIndexes(HANType21Record hRecord);

NResult N_API ANType21RecordGetCommentN(HANType21Record hRecord, HNString * phValue);
NResult N_API ANType21RecordSetCommentN(HANType21Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType21RecordSetCommentA(HANType21Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType21RecordSetCommentW(HANType21Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType21RecordSetComment(HANType21Record hRecord, const NChar * szValue);
#endif
#define ANType21RecordSetComment N_FUNC_AW(ANType21RecordSetComment)

NResult N_API ANType21RecordGetAssociatedContextNumber(HANType21Record hRecord, NUInt * pValue);
NResult N_API ANType21RecordSetAssociatedContextNumber(HANType21Record hRecord, NUInt value);

NResult N_API ANType21RecordGetCaptureDateRangeN(HANType21Record hRecord, HNString * phValue);
NResult N_API ANType21RecordSetCaptureDateRangeN(HANType21Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType21RecordSetCaptureDateRangeA(HANType21Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType21RecordSetCaptureDateRangeW(HANType21Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType21RecordSetCaptureDateRange(HANType21Record hRecord, const NChar * szValue);
#endif
#define ANType21RecordSetCaptureDateRange N_FUNC_AW(ANType21RecordSetCaptureDateRange)

#ifdef N_CPP
}
#endif

#endif // !AN_TYPE_21_RECORD_H_INCLUDED
