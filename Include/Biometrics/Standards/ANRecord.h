#ifndef AN_RECORD_H_INCLUDED
#define AN_RECORD_H_INCLUDED

#include <Core/NDateTime.h>
#include <Biometrics/Standards/ANField.h>
#include <Biometrics/Standards/ANRecordType.h>
#include <Biometrics/Standards/BdifTypes.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANRecord, NObject)

#define AN_RECORD_MAX_FIELD_NUMBER 999

#define AN_RECORD_FIELD_LEN    1
#define AN_RECORD_FIELD_IDC    2

#define AN_RECORD_FIELD_DATA 999

#define AN_RECORD_MAX_IDC     255
#define AN_RECORD_MAX_IDC_V5 99

#define ANR_MERGE_DUPLICATE_FIELDS   0x00000100
#define ANR_RECOVER_FROM_BINARY_DATA 0x00000200

#define AN_RECORD_MAX_MAKE_LENGTH          50
#define AN_RECORD_MAX_MODEL_LENGTH         50
#define AN_RECORD_MAX_SERIAL_NUMBER_LENGTH 50

#define AN_RECORD_ANN_MIN_PROCESSING_ALGORITHM_NAME_LENGTH      1
#define AN_RECORD_ANN_MAX_PROCESSING_ALGORITHM_NAME_LENGTH_V50  64
#define AN_RECORD_ANN_MIN_PROCESSING_ALGORITHM_OWNER_LENGTH     1
#define AN_RECORD_ANN_MAX_PROCESSING_ALGORITHM_OWNER_LENGTH     64
#define AN_RECORD_ANN_MIN_PROCESS_DESCRIPTION_LENGTH            1
#define AN_RECORD_ANN_MAX_PROCESS_DESCRIPTION_LENGTH_V50        255

#define AN_RECORD_ANN_UNKNOWN_PROCESSING_ALGORITHM_OWNER  N_T("N/A")

#define AN_RECORD_MIN_DEVICE_UNIQUE_IDENTIFIER_LENGTH 13
#define AN_RECORD_MAX_DEVICE_UNIQUE_IDENTIFIER_LENGTH 16

struct ANAnnotation_
{
	NDateTime_ gmt;
	HNString hProcessingAlgorithmName;
	HNString hAlgorithmOwner;
	HNString hProcessDescription;
};
#ifndef AN_RECORD_HPP_INCLUDED
typedef struct ANAnnotation_ ANAnnotation;
#endif

N_DECLARE_TYPE(ANAnnotation)

struct ANMakeModelSerialNumber_
{
	HNString hMake;
	HNString hModel;
	HNString hSerialNumber;
};
#ifndef AN_RECORD_HPP_INCLUDED
typedef struct ANMakeModelSerialNumber_ ANMakeModelSerialNumber;
#endif

N_DECLARE_TYPE(ANMakeModelSerialNumber)

NResult N_API ANAnnotationCreateN(NDateTime_ gmt, HNString hProcessingAlgorithm, HNString hAlgorithmOwner, HNString hProcessDescription, struct ANAnnotation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANAnnotationCreateA(NDateTime_ gmt, const NAChar * szProcessingAlgorithm, const NAChar * szAlgorithmOwner, const NAChar * szProcessDescription, struct ANAnnotation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANAnnotationCreateW(NDateTime_ gmt, const NWChar * szProcessingAlgorithm, const NWChar * szAlgorithmOwner, const NWChar * szProcessDescription, struct ANAnnotation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANAnnotationCreate(NDateTime_ gmt, const NChar * szProcessingAlgorithm, const NChar * szAlgorithmOwner, const NChar * szProcessDescription, struct ANAnnotation_ * pValue);
#endif
#define ANAnnotationCreate N_FUNC_AW(ANAnnotationCreate)

NResult N_API ANAnnotationDispose(struct ANAnnotation_ * pValue);
NResult N_API ANAnnotationCopy(const struct ANAnnotation_ * pSrcValue, struct ANAnnotation_ * pDstValue);
NResult N_API ANAnnotationSet(const struct ANAnnotation_ * pSrcValue, struct ANAnnotation_ * pDstValue);

NResult N_API ANMakeModelSerialNumberCreateN(HNString hMake, HNString hModel, HNString hSerialNumber, struct ANMakeModelSerialNumber_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANMakeModelSerialNumberCreateA(const NAChar * szMake, const NAChar * szModel, const NAChar * szSerialNumber, struct ANMakeModelSerialNumber_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANMakeModelSerialNumberCreateW(const NWChar * szMake, const NWChar * szModel, const NWChar * szSerialNumber, struct ANMakeModelSerialNumber_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANMakeModelSerialNumberCreate(const NChar * szMake, const NChar * szModel, const NChar * szSerialNumber, struct ANMakeModelSerialNumber_ * pValue);
#endif
#define ANMakeModelSerialNumberCreate N_FUNC_AW(ANMakeModelSerialNumberCreate)

NResult N_API ANMakeModelSerialNumberDispose(struct ANMakeModelSerialNumber_ * pValue);
NResult N_API ANMakeModelSerialNumberCopy(const struct ANMakeModelSerialNumber_ * pSrcValue, struct ANMakeModelSerialNumber_ * pDstValue);
NResult N_API ANMakeModelSerialNumberSet(const struct ANMakeModelSerialNumber_ * pSrcValue, struct ANMakeModelSerialNumber_ * pDstValue);

NResult N_API ANRecordGetFieldCount(HANRecord hRecord, NInt * pValue);
NResult N_API ANRecordGetFieldEx(HANRecord hRecord, NInt index, HANField * phValue);
NResult N_API ANRecordGetFieldCapacity(HANRecord hRecord, NInt * pValue);
NResult N_API ANRecordSetFieldCapacity(HANRecord hRecord, NInt value);

NResult N_API ANRecordAddFieldN(HANRecord hRecord, NInt fieldNumber, HNString hValue, NInt * pFieldIndex, HANField * phField);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANRecordAddFieldExA(HANRecord hRecord, NInt fieldNumber, const NAChar * szValue, NInt * pFieldIndex, HANField * phField);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANRecordAddFieldExW(HANRecord hRecord, NInt fieldNumber, const NWChar * szValue, NInt * pFieldIndex, HANField * phField);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANRecordAddFieldEx(HANRecord hRecord, NInt fieldNumber, const NChar * szValue, NInt * pFieldIndex, HANField * phField);
#endif
#define ANRecordAddFieldEx N_FUNC_AW(ANRecordAddFieldEx)


NResult N_API ANRecordAddFieldExN(HANRecord hRecord, NInt fieldNumber, HNString hFieldName, HNString hValue, NInt * pFieldIndex, HANField * phField);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANRecordAddFieldEx2A(HANRecord hRecord, NInt fieldNumber, const NAChar * szFieldName, const NAChar * szValue, NInt * pFieldIndex, HANField * phField);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANRecordAddFieldEx2W(HANRecord hRecord, NInt fieldNumber, const NWChar * szFieldName, const NWChar * szValue, NInt * pFieldIndex, HANField * phField);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANRecordAddFieldEx2(HANRecord hRecord, NInt fieldNumber, const NChar * szFieldName, const NChar * szValue, NInt * pFieldIndex, HANField * phField);
#endif
#define ANRecordAddFieldEx2 N_FUNC_AW(ANRecordAddFieldEx2)


NResult N_API ANRecordInsertFieldN(HANRecord hRecord, NInt index, NInt fieldNumber, HNString hValue, HANField * phField);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANRecordInsertFieldA(HANRecord hRecord, NInt index, NInt fieldNumber, const NAChar * szValue, HANField * phField);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANRecordInsertFieldW(HANRecord hRecord, NInt index, NInt fieldNumber, const NWChar * szValue, HANField * phField);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANRecordInsertField(HANRecord hRecord, NInt index, NInt fieldNumber, const NChar * szValue, HANField * phField);
#endif
#define ANRecordInsertField N_FUNC_AW(ANRecordInsertField)


NResult N_API ANRecordInsertFieldExN(HANRecord hRecord, NInt index, NInt fieldNumber, HNString hFieldName, HNString hValue, HANField * phField);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANRecordInsertFieldExA(HANRecord hRecord, NInt index, NInt fieldNumber, const NAChar * szFieldName, const NAChar * szValue, HANField * phField);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANRecordInsertFieldExW(HANRecord hRecord, NInt index, NInt fieldNumber, const NWChar * szFieldName, const NWChar * szValue, HANField * phField);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANRecordInsertFieldEx(HANRecord hRecord, NInt index, NInt fieldNumber, const NChar * szFieldName, const NChar * szValue, HANField * phField);
#endif
#define ANRecordInsertFieldEx N_FUNC_AW(ANRecordInsertFieldEx)


NResult N_API ANRecordRemoveFieldAt(HANRecord hRecord, NInt index);

NResult N_API ANRecordGetFieldByNumberEx(HANRecord hRecord, NInt fieldNumber, HANField * phField);
NResult N_API ANRecordGetFieldIndexByNumber(HANRecord hRecord, NInt fieldNumber, NInt * pValue);

NResult N_API ANRecordBeginUpdate(HANRecord hRecord);
NResult N_API ANRecordEndUpdate(HANRecord hRecord);
NResult N_API ANRecordIsValidated(HANRecord hRecord, NBool * pValue);
NResult N_API ANRecordCheckValidity(HANRecord hRecord, NBool * pValue);

NResult N_API ANRecordGetConformanceTestResultCount(HANRecord hRecord, NInt * pValue);
NResult N_API ANRecordGetConformanceTestResult(HANRecord hRecord, NInt index, struct BdifConformanceTest_ * pValue);
NResult N_API ANRecordGetConformanceTestResults(HANRecord hRecord, struct BdifConformanceTest_ * * pConformanceTests, NInt * pCount);

NResult N_API ANRecordGetRecordTypeEx(HANRecord hRecord, HANRecordType * phValue);
NResult N_API ANRecordGetLength(HANRecord hRecord, NSizeType * pValue);

NResult N_API ANRecordGetVersion(HANRecord hRecord, NVersion_ * pValue);
NResult N_API ANRecordGetIdc(HANRecord hRecord, NInt * pValue);
NResult N_API ANRecordSetIdc(HANRecord hRecord, NInt value);
NResult N_API ANRecordGetDataN(HANRecord hRecord, HNBuffer * phValue);
NResult N_API ANRecordSetDataN(HANRecord hRecord, HNBuffer hValue);
NResult N_API ANRecordSetDataEx(HANRecord hRecord, const void * pValue, NSizeType valueSize, NBool copy);

#ifdef N_CPP
}
#endif

#endif // !AN_RECORD_H_INCLUDED
