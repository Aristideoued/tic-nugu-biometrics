#ifndef AN_TYPE_9_RECORD_H_INCLUDED
#define AN_TYPE_9_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANAsciiRecord.h>
#include <Biometrics/Standards/BdifTypes.h>
#include <Biometrics/NFRecord.h>
#include <Biometrics/Standards/CbeffBiometricOrganizations.h>
#include <Biometrics/Standards/FMRecord.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANType9Record, ANAsciiRecord)

#define AN_TYPE_9_RECORD_FIELD_LEN AN_RECORD_FIELD_LEN
#define AN_TYPE_9_RECORD_FIELD_IDC AN_RECORD_FIELD_IDC

#define AN_TYPE_9_RECORD_FIELD_IMP 3
#define AN_TYPE_9_RECORD_FIELD_FMT 4

#define AN_TYPE_9_RECORD_FIELD_OFR  5
#define AN_TYPE_9_RECORD_FIELD_FGP  6
#define AN_TYPE_9_RECORD_FIELD_FPC  7
#define AN_TYPE_9_RECORD_FIELD_CRP  8
#define AN_TYPE_9_RECORD_FIELD_DLT  9
#define AN_TYPE_9_RECORD_FIELD_MIN 10
#define AN_TYPE_9_RECORD_FIELD_RDG 11
#define AN_TYPE_9_RECORD_FIELD_MRC 12

#define AN_TYPE_9_RECORD_FIELD_M1_CBI  126
#define AN_TYPE_9_RECORD_FIELD_M1_CEI  127
#define AN_TYPE_9_RECORD_FIELD_M1_HLL  128
#define AN_TYPE_9_RECORD_FIELD_M1_VLL  129
#define AN_TYPE_9_RECORD_FIELD_M1_SLC  130
#define AN_TYPE_9_RECORD_FIELD_M1_THPS 131
#define AN_TYPE_9_RECORD_FIELD_M1_TVPS 132
#define AN_TYPE_9_RECORD_FIELD_M1_FVW  133
#define AN_TYPE_9_RECORD_FIELD_M1_FGP  134
#define AN_TYPE_9_RECORD_FIELD_M1_FQD  135
#define AN_TYPE_9_RECORD_FIELD_M1_NOM  136
#define AN_TYPE_9_RECORD_FIELD_M1_FMD  137
#define AN_TYPE_9_RECORD_FIELD_M1_RCI  138
#define AN_TYPE_9_RECORD_FIELD_M1_CIN  139
#define AN_TYPE_9_RECORD_FIELD_M1_DIN  140
#define AN_TYPE_9_RECORD_FIELD_M1_ADA  141

#define AN_TYPE_9_RECORD_FIELD_OOD 176
#define AN_TYPE_9_RECORD_FIELD_PAG 177
#define AN_TYPE_9_RECORD_FIELD_SOD 178
#define AN_TYPE_9_RECORD_FIELD_DTX 179

#define AN_TYPE_9_RECORD_FIELD_ULA 901
#define AN_TYPE_9_RECORD_FIELD_ANN 902
#define AN_TYPE_9_RECORD_FIELD_DUI 903
#define AN_TYPE_9_RECORD_FIELD_MMS 904

#define AN_TYPE_9_RECORD_FIELD_ALL_FROM AN_TYPE_9_RECORD_FIELD_LEN
#define AN_TYPE_9_RECORD_FIELD_ALL_TO   AN_TYPE_9_RECORD_FIELD_FMT

#define AN_TYPE_9_RECORD_FIELD_STANDARD_FORMAT_FEATURES_FROM AN_TYPE_9_RECORD_FIELD_OFR
#define AN_TYPE_9_RECORD_FIELD_STANDARD_FORMAT_FEATURES_TO   AN_TYPE_9_RECORD_FIELD_MRC

#define AN_TYPE_9_RECORD_FIELD_VENDOR_DEFINED_FEATURES_FROM (AN_TYPE_9_RECORD_FIELD_MRC + 1)
#define AN_TYPE_9_RECORD_FIELD_VENDOR_DEFINED_FEATURES_TO   AN_ASCII_RECORD_MAX_FIELD_NUMBER
#define AN_TYPE_9_RECORD_FIELD_VENDOR_DEFINED_FEATURES_TO_V5 225

#define AN_TYPE_9_RECORD_MAX_FINGERPRINT_X  4999
#define AN_TYPE_9_RECORD_MAX_FINGERPRINT_Y  4999
#define AN_TYPE_9_RECORD_MAX_PALMPRINT_X   13999
#define AN_TYPE_9_RECORD_MAX_PALMPRINT_Y   20999

#define AN_TYPE_9_RECORD_MINUTIA_QUALITY_MANUAL         0
#define AN_TYPE_9_RECORD_MINUTIA_QUALITY_NOT_AVAILABLE  1
#define AN_TYPE_9_RECORD_MINUTIA_QUALITY_BEST           2
#define AN_TYPE_9_RECORD_MINUTIA_QUALITY_WORST         63

#define AN_TYPE_9_RECORD_M1_CBEFF_FORMAT_OWNER   CBEFF_BO_INCITS_TC_M1_BIOMETRICS

#define AN_TYPE_9_RECORD_M1_MIN_LINE_LENGTH  10
#define AN_TYPE_9_RECORD_M1_MAX_LINE_LENGTH  65535

#define AN_TYPE_9_RECORD_M1_MIN_MINUTIAE_COUNT 1

#define AN_TYPE_9_RECORD_M1_MIN_RIDGE_COUNT_V50 1
#define AN_TYPE_9_RECORD_M1_MAX_RIDGE_COUNT     99
#define AN_TYPE_9_RECORD_M1_MAX_CORE_COUNT      9
#define AN_TYPE_9_RECORD_M1_MAX_DELTA_COUNT     9

#define AN_TYPE_9_RECORD_MAX_MAKE_LENGTH          AN_RECORD_MAX_MAKE_LENGTH
#define AN_TYPE_9_RECORD_MAX_MODEL_LENGTH         AN_RECORD_MAX_MODEL_LENGTH
#define AN_TYPE_9_RECORD_MAX_SERIAL_NUMBER_LENGTH AN_RECORD_MAX_SERIAL_NUMBER_LENGTH

#define AN_TYPE_9_RECORD_MIN_ULW_ANNOTATION_LENGTH  22
#define AN_TYPE_9_RECORD_MAX_ULW_ANNOTATION_LENGTH  300

#define AN_TYPE_9_RECORD_MAX_OFS_OWNER_LENGTH                         40
#define AN_TYPE_9_RECORD_MAX_OFS_PROCESSING_ALGORITHM_NAME_LENGTH     100
#define AN_TYPE_9_RECORD_MAX_OFS_PROCESSING_ALGORITHM_VERSION_LENGTH  100
#define AN_TYPE_9_RECORD_MAX_OFS_SYSTEM_NAME_LENGTH                   100
#define AN_TYPE_9_RECORD_MAX_OFS_SYSTEM_VERSION_LENGTH                100
#define AN_TYPE_9_RECORD_MAX_OFS_CONTACT_INFORMATION_LENGTH           1000

#define AN_TYPE_9_RECORD_OFS_NEUROTEC_OWNER           N_T("Neurotechnology")

#define AN_TYPE_9_RECORD_M1_SKIP_RIDGE_COUNTS        FMRFV_SKIP_RIDGE_COUNTS
#define AN_TYPE_9_RECORD_M1_SKIP_SINGULAR_POINTS     FMRFV_SKIP_SINGULAR_POINTS
#define AN_TYPE_9_RECORD_M1_SKIP_NEUROTEC_FIELDS     FMRFV_SKIP_NEUROTEC_FIELDS

typedef enum ANFPMinutiaeMethod_
{
	anfpmmUnspecified = 0,
	anfpmmAutomatic = 1,
	anfpmmNotEdited = 2,
	anfpmmEdited = 3,
	anfpmmManual = 4
} ANFPMinutiaeMethod;

N_DECLARE_TYPE(ANFPMinutiaeMethod)

struct ANOfrs_
{
	HNString hName;
	ANFPMinutiaeMethod method;
	HNString hEquipment;
};
#ifndef AN_TYPE_9_RECORD_HPP_INCLUDED
typedef struct ANOfrs_ ANOfrs;
#endif

N_DECLARE_TYPE(ANOfrs)

struct ANFPatternClass_
{
	BdifFPatternClass value;
	HNString hVendorValue;
};
#ifndef AN_TYPE_9_RECORD_HPP_INCLUDED
typedef struct ANFPatternClass_ ANFPatternClass;
#endif

N_DECLARE_TYPE(ANFPatternClass)

struct ANFCore_
{
	NUShort X;
	NUShort Y;
};
#ifndef AN_TYPE_9_RECORD_HPP_INCLUDED
typedef struct ANFCore_ ANFCore;
#endif

N_DECLARE_TYPE(ANFCore)

struct ANFDelta_
{
	NUShort X;
	NUShort Y;
};
#ifndef AN_TYPE_9_RECORD_HPP_INCLUDED
typedef struct ANFDelta_ ANFDelta;
#endif

N_DECLARE_TYPE(ANFDelta)

struct ANFPMinutia_
{
	NUInt X;
	NUInt Y;
	NUShort Theta;
	NByte Quality;
	BdifFPMinutiaType Type;
};
#ifndef AN_TYPE_9_RECORD_HPP_INCLUDED
typedef struct ANFPMinutia_ ANFPMinutia;
#endif

N_DECLARE_TYPE(ANFPMinutia)

struct ANUlwAnnotation_
{
	NDateTime_ dateTime;
	HNString hText;
};
#ifndef AN_TYPE_9_RECORD_HPP_INCLUDED
typedef struct ANUlwAnnotation_ ANUlwAnnotation;
#endif

N_DECLARE_TYPE(ANUlwAnnotation)


NResult N_API ANOfrsCreateN(HNString hName, ANFPMinutiaeMethod method, HNString hEquipment, struct ANOfrs_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANOfrsCreateA(const NAChar * szName, ANFPMinutiaeMethod method, const NAChar * szEquipment, struct ANOfrs_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANOfrsCreateW(const NWChar * szName, ANFPMinutiaeMethod method, const NWChar * szEquipment, struct ANOfrs_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANOfrsCreate(const NChar * szName, ANFPMinutiaeMethod method, const NChar * szEquipment, ANOfrs * pValue);
#endif
#define ANOfrsCreate N_FUNC_AW(ANOfrsCreate)

NResult N_API ANOfrsDispose(struct ANOfrs_ * pValue);
NResult N_API ANOfrsCopy(const struct ANOfrs_ * pSrcValue, struct ANOfrs_ * pDstValue);
NResult N_API ANOfrsSet(const struct ANOfrs_ * pSrcValue, struct ANOfrs_ * pDstValue);

NResult N_API ANFPatternClassCreateN(BdifFPatternClass value, HNString hVendorValue, struct ANFPatternClass_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANFPatternClassCreateA(BdifFPatternClass value, const NAChar * szVendorValue, struct ANFPatternClass_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANFPatternClassCreateW(BdifFPatternClass value, const NWChar * szVendorValue, struct ANFPatternClass_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANFPatternClassCreate(BdifFPatternClass value, const NChar * szVendorValue, ANFPatternClass * pValue);
#endif
#define ANFPatternClassCreate N_FUNC_AW(ANFPatternClassCreate)

NResult N_API ANFPatternClassDispose(struct ANFPatternClass_ * pValue);
NResult N_API ANFPatternClassCopy(const struct ANFPatternClass_ * pSrcValue, struct ANFPatternClass_ * pDstValue);
NResult N_API ANFPatternClassSet(const struct ANFPatternClass_ * pSrcValue, struct ANFPatternClass_ * pDstValue);


NResult N_API ANUlwAnnotationCreateN(NDateTime_ dateTime, HNString hText, struct ANUlwAnnotation_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANUlwAnnotationCreateA(NDateTime_ dateTime, const NAChar * szText, struct ANUlwAnnotation_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANUlwAnnotationCreateW(NDateTime_ dateTime, const NWChar * szText, struct ANUlwAnnotation_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANUlwAnnotationCreate(NDateTime_ dateTime, const NChar * szText, ANUlwAnnotation * pValue);
#endif
#define ANUlwAnnotationCreate N_FUNC_AW(ANUlwAnnotationCreate)

NResult N_API ANUlwAnnotationDispose(struct ANUlwAnnotation_ * pValue);
NResult N_API ANUlwAnnotationCopy(const struct ANUlwAnnotation_ * pSrcValue, struct ANUlwAnnotation_ * pDstValue);
NResult N_API ANUlwAnnotationSet(const struct ANUlwAnnotation_ * pSrcValue, struct ANUlwAnnotation_ * pDstValue);

NResult N_API ANType9RecordToNFRecord(HANType9Record hRecord, NUInt flags, HNFRecord * phNFRecord);

NResult N_API ANType9RecordGetPositionCount(HANType9Record hRecord, NInt * pValue);
NResult N_API ANType9RecordGetPosition(HANType9Record hRecord, NInt index, BdifFPPosition * pValue);
NResult N_API ANType9RecordGetPositions(HANType9Record hRecord, BdifFPPosition * * parValues, NInt * pValueCount);
NResult N_API ANType9RecordSetPosition(HANType9Record hRecord, NInt index, BdifFPPosition value);
NResult N_API ANType9RecordAddPositionEx(HANType9Record hRecord, BdifFPPosition value, NInt * pIndex);
NResult N_API ANType9RecordInsertPosition(HANType9Record hRecord, NInt index, BdifFPPosition value);
NResult N_API ANType9RecordRemovePositionAt(HANType9Record hRecord, NInt index);
NResult N_API ANType9RecordClearPositions(HANType9Record hRecord);

NResult N_API ANType9RecordGetPatternClassCount(HANType9Record hRecord, NInt * pValue);
NResult N_API ANType9RecordGetPatternClass(HANType9Record hRecord, NInt index, struct ANFPatternClass_ * pValue);
NResult N_API ANType9RecordSetPatternClass(HANType9Record hRecord, NInt index, const struct ANFPatternClass_ * pValue);
NResult N_API ANType9RecordAddPatternClassEx(HANType9Record hRecord, const struct ANFPatternClass_ * pValue, NInt * pIndex);
NResult N_API ANType9RecordInsertPatternClass(HANType9Record hRecord, NInt index, const struct ANFPatternClass_ * pValue);
NResult N_API ANType9RecordRemovePatternClassAt(HANType9Record hRecord, NInt index);
NResult N_API ANType9RecordClearPatternClasses(HANType9Record hRecord);

NResult N_API ANType9RecordGetCoreCount(HANType9Record hRecord, NInt * pValue);
NResult N_API ANType9RecordGetCore(HANType9Record hRecord, NInt index, struct ANFCore_ * pValue);
NResult N_API ANType9RecordGetCores(HANType9Record hRecord, struct ANFCore_ * * parValues, NInt * pValueCount);
NResult N_API ANType9RecordSetCore(HANType9Record hRecord, NInt index, const struct ANFCore_ * pValue);
NResult N_API ANType9RecordAddCoreEx(HANType9Record hRecord, const struct ANFCore_ * pValue, NInt * pIndex);
NResult N_API ANType9RecordInsertCore(HANType9Record hRecord, NInt index, const struct ANFCore_ * pValue);
NResult N_API ANType9RecordRemoveCoreAt(HANType9Record hRecord, NInt index);
NResult N_API ANType9RecordClearCores(HANType9Record hRecord);

NResult N_API ANType9RecordGetDeltaCount(HANType9Record hRecord, NInt * pValue);
NResult N_API ANType9RecordGetDelta(HANType9Record hRecord, NInt index, struct ANFDelta_ * pValue);
NResult N_API ANType9RecordGetDeltas(HANType9Record hRecord, struct ANFDelta_ * * parValues, NInt * pValueCount);
NResult N_API ANType9RecordSetDelta(HANType9Record hRecord, NInt index, const struct ANFDelta_ * pValue);
NResult N_API ANType9RecordAddDeltaEx(HANType9Record hRecord, const struct ANFDelta_ * pValue, NInt * pIndex);
NResult N_API ANType9RecordInsertDelta(HANType9Record hRecord, NInt index, const struct ANFDelta_ * pValue);
NResult N_API ANType9RecordRemoveDeltaAt(HANType9Record hRecord, NInt index);
NResult N_API ANType9RecordClearDeltas(HANType9Record hRecord);

NResult N_API ANType9RecordGetMinutiaCount(HANType9Record hRecord, NInt * pValue);
NResult N_API ANType9RecordGetMinutia(HANType9Record hRecord, NInt index, struct ANFPMinutia_ * pValue);
NResult N_API ANType9RecordGetMinutiae(HANType9Record hRecord, struct ANFPMinutia_ * * parValues, NInt * pValueCount);
NResult N_API ANType9RecordSetMinutia(HANType9Record hRecord, NInt index, const struct ANFPMinutia_ * pValue);
NResult N_API ANType9RecordAddMinutiaEx(HANType9Record hRecord, const struct ANFPMinutia_ * pValue, NInt * pIndex);
NResult N_API ANType9RecordInsertMinutia(HANType9Record hRecord, NInt index, const struct ANFPMinutia_ * pValue);
NResult N_API ANType9RecordRemoveMinutiaAt(HANType9Record hRecord, NInt index);
NResult N_API ANType9RecordClearMinutiae(HANType9Record hRecord);

NResult N_API ANType9RecordGetMinutiaNeighborCount(HANType9Record hRecord, NInt minutiaIndex, NInt * pValue);
NResult N_API ANType9RecordGetMinutiaNeighbor(HANType9Record hRecord, NInt minutiaIndex, NInt index, struct BdifFPMinutiaNeighbor_ * pValue);
NResult N_API ANType9RecordGetMinutiaNeighbors(HANType9Record hRecord, NInt minutiaIndex, struct BdifFPMinutiaNeighbor_ * * parValues, NInt * pValueCount);
NResult N_API ANType9RecordSetMinutiaNeighbor(HANType9Record hRecord, NInt minutiaIndex, NInt index, const struct BdifFPMinutiaNeighbor_ * pValue);
NResult N_API ANType9RecordAddMinutiaNeighborEx(HANType9Record hRecord, NInt minutiaIndex, const struct BdifFPMinutiaNeighbor_ * pValue, NInt * pIndex);
NResult N_API ANType9RecordInsertMinutiaNeighbor(HANType9Record hRecord, NInt minutiaIndex, NInt index, const struct BdifFPMinutiaNeighbor_ * pValue);
NResult N_API ANType9RecordRemoveMinutiaNeighborAt(HANType9Record hRecord, NInt minutiaIndex, NInt index);
NResult N_API ANType9RecordClearMinutiaNeighbors(HANType9Record hRecord, NInt minutiaIndex);

NResult N_API ANType9RecordGetImpressionType(HANType9Record hRecord, BdifFPImpressionType * pValue);
NResult N_API ANType9RecordSetImpressionType(HANType9Record hRecord, BdifFPImpressionType value);
NResult N_API ANType9RecordGetMinutiaeFormat(HANType9Record hRecord, NBool * pValue);
NResult N_API ANType9RecordSetMinutiaeFormat(HANType9Record hRecord, NBool value);
NResult N_API ANType9RecordHasMinutiae(HANType9Record hRecord, NBool * pValue);
NResult N_API ANType9RecordSetHasMinutiae(HANType9Record hRecord, NBool value);
NResult N_API ANType9RecordHasMinutiaeRidgeCounts(HANType9Record hRecord, NBool * pValue);
NResult N_API ANType9RecordHasMinutiaeRidgeCountsIndicator(HANType9Record hRecord, NBool * pValue);
NResult N_API ANType9RecordSetHasMinutiaeRidgeCounts(HANType9Record hRecord, NBool hasMinutiaeRidgeCountsIndicator, NBool rdg);

NResult N_API ANType9RecordGetOfrs(HANType9Record hRecord, struct ANOfrs_ * pValue, NBool * pHasValue);
NResult N_API ANType9RecordGetOfrsNameN(HANType9Record hRecord, HNString * phValue);
NResult N_API ANType9RecordGetOfrsMethod(HANType9Record hRecord, ANFPMinutiaeMethod * pValue);
NResult N_API ANType9RecordGetOfrsEquipmentN(HANType9Record hRecord, HNString * phValue);
NResult N_API ANType9RecordSetOfrsEx(HANType9Record hRecord, const struct ANOfrs_ * pValue);

NResult N_API ANType9RecordSetOfrsN(HANType9Record hRecord, HNString hName, ANFPMinutiaeMethod method, HNString hEquipment);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType9RecordSetOfrsA(HANType9Record hRecord, const NAChar * szName, ANFPMinutiaeMethod method, const NAChar * szEquipment);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType9RecordSetOfrsW(HANType9Record hRecord, const NWChar * szName, ANFPMinutiaeMethod method, const NWChar * szEquipment);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType9RecordSetOfrs(HANType9Record hRecord, const NChar * szName, ANFPMinutiaeMethod method, const NChar * szEquipment);
#endif
#define ANType9RecordSetOfrs N_FUNC_AW(ANType9RecordSetOfrs)

NResult N_API ANType9RecordSetFmRecord(HANType9Record hRecord, HFMRecord hFMRecord, NByte fmrFingerViewIndex, NUInt flags);
NResult N_API ANType9RecordGetFmRecordBufferN(HANType9Record hRecord, HNBuffer * phValue);

NResult N_API ANType9RecordGetUlwAnnotationCount(HANType9Record hRecord, NInt * pValue);
NResult N_API ANType9RecordGetUlwAnnotation(HANType9Record hRecord, NInt index, struct ANUlwAnnotation_ * pValue);
NResult N_API ANType9RecordGetUlwAnnotationCapacity(HANType9Record hRecord, NInt * pValue);
NResult N_API ANType9RecordSetUlwAnnotationCapacity(HANType9Record hRecord, NInt value);
NResult N_API ANType9RecordGetUlwAnnotations(HANType9Record hRecord, struct ANUlwAnnotation_ * * parValues, NInt * pValueCount);
NResult N_API ANType9RecordSetUlwAnnotation(HANType9Record hRecord, NInt index, const struct ANUlwAnnotation_ * pValue);
NResult N_API ANType9RecordAddUlwAnnotation(HANType9Record hRecord, const struct ANUlwAnnotation_ * pValue, NInt * pIndex);
NResult N_API ANType9RecordInsertUlwAnnotation(HANType9Record hRecord, NInt index, const struct ANUlwAnnotation_ * pValue);
NResult N_API ANType9RecordRemoveUlwAnnotationAt(HANType9Record hRecord, NInt index);
NResult N_API ANType9RecordClearUlwAnnotations(HANType9Record hRecord);

NResult N_API ANType9RecordGetAnnotationCount(HANType9Record hRecord, NInt * pValue);
NResult N_API ANType9RecordGetAnnotation(HANType9Record hRecord, NInt index, struct ANAnnotation_ * pValue);
NResult N_API ANType9RecordGetAnnotationCapacity(HANType9Record hRecord, NInt * pValue);
NResult N_API ANType9RecordSetAnnotationCapacity(HANType9Record hRecord, NInt value);
NResult N_API ANType9RecordGetAnnotations(HANType9Record hRecord, struct ANAnnotation_ * * parValues, NInt * pValueCount);
NResult N_API ANType9RecordSetAnnotation(HANType9Record hRecord, NInt index, const struct ANAnnotation_ * pValue);
NResult N_API ANType9RecordAddAnnotation(HANType9Record hRecord, const struct ANAnnotation_ * pValue, NInt * pIndex);
NResult N_API ANType9RecordInsertAnnotation(HANType9Record hRecord, NInt index, const struct ANAnnotation_ * pValue);
NResult N_API ANType9RecordRemoveAnnotationAt(HANType9Record hRecord, NInt index);
NResult N_API ANType9RecordClearAnnotations(HANType9Record hRecord);

NResult N_API ANType9RecordGetDeviceUniqueIdentifierN(HANType9Record hRecord, HNString * phValue);
NResult N_API ANType9RecordSetDeviceUniqueIdentifierN(HANType9Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType9RecordSetDeviceUniqueIdentifierA(HANType9Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType9RecordSetDeviceUniqueIdentifierW(HANType9Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType9RecordSetDeviceUniqueIdentifier(HANType9Record hRecord, const NChar * szValue);
#endif
#define ANType9RecordSetDeviceUniqueIdentifier N_FUNC_AW(ANType9RecordSetDeviceUniqueIdentifier)


NResult N_API ANType9RecordGetMakeModelSerialNumber(HANRecord hRecord, struct ANMakeModelSerialNumber_ * pValue, NBool * pHasValue);
NResult N_API ANType9RecordGetMakeN(HANRecord hRecord, HNString * phValue);
NResult N_API ANType9RecordGetModelN(HANRecord hRecord, HNString * phValue);
NResult N_API ANType9RecordGetSerialNumberN(HANRecord hRecord, HNString * phValue);

NResult N_API ANType9RecordSetMakeModelSerialNumberEx(HANRecord hRecord, const struct ANMakeModelSerialNumber_ * pValue);

NResult N_API ANType9RecordSetMakeModelSerialNumberN(HANRecord hRecord, HNString hMake, HNString hModel, HNString hSerialNumber);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType9RecordSetMakeModelSerialNumberA(HANRecord hRecord, const NAChar * szMake, const NAChar * szModel, const NAChar * szSerialNumber);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType9RecordSetMakeModelSerialNumberW(HANRecord hRecord, const NWChar * szMake, const NWChar * szModel, const NWChar * szSerialNumber);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType9RecordSetMakeModelSerialNumber(HANRecord hRecord, const NChar * szMake, const NChar * szModel, const NChar * szSerialNumber);
#endif
#define ANType9RecordSetMakeModelSerialNumber N_FUNC_AW(ANType9RecordSetMakeModelSerialNumber)


NResult N_API ANType9RecordHasOtherFeatureSets(HANType9Record hRecord, NBool * pValue);
NResult N_API ANType9RecordSetHasOtherFeatureSets(HANType9Record hRecord, NBool value);

NResult N_API ANType9RecordGetOfsOwnerN(HANType9Record hRecord, HNString * phValue);
NResult N_API ANType9RecordSetOfsOwnerN(HANType9Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType9RecordSetOfsOwnerA(HANType9Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType9RecordSetOfsOwnerW(HANType9Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType9RecordSetOfsOwner(HANType9Record hRecord, const NChar * szValue);
#endif
#define ANType9RecordSetOfsOwner N_FUNC_AW(ANType9RecordSetOfsOwner)

NResult N_API ANType9RecordGetOfsProcessingAlgorithmNameN(HANType9Record hRecord, HNString * phValue);
NResult N_API ANType9RecordSetOfsProcessingAlgorithmNameN(HANType9Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType9RecordSetOfsProcessingAlgorithmNameA(HANType9Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType9RecordSetOfsProcessingAlgorithmNameW(HANType9Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType9RecordSetOfsProcessingAlgorithmName(HANType9Record hRecord, const NChar * szValue);
#endif
#define ANType9RecordSetOfsProcessingAlgorithmName N_FUNC_AW(ANType9RecordSetOfsProcessingAlgorithmName)

NResult N_API ANType9RecordGetOfsProcessingAlgorithmVersionN(HANType9Record hRecord, HNString * phValue);
NResult N_API ANType9RecordSetOfsProcessingAlgorithmVersionN(HANType9Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType9RecordSetOfsProcessingAlgorithmVersionA(HANType9Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType9RecordSetOfsProcessingAlgorithmVersionW(HANType9Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType9RecordSetOfsProcessingAlgorithmVersion(HANType9Record hRecord, const NChar * szValue);
#endif
#define ANType9RecordSetOfsProcessingAlgorithmVersion N_FUNC_AW(ANType9RecordSetOfsProcessingAlgorithmVersion)

NResult N_API ANType9RecordGetOfsSystemNameN(HANType9Record hRecord, HNString * phValue);
NResult N_API ANType9RecordSetOfsSystemNameN(HANType9Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType9RecordSetOfsSystemNameA(HANType9Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType9RecordSetOfsSystemNameW(HANType9Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType9RecordSetOfsSystemName(HANType9Record hRecord, const NChar * szValue);
#endif
#define ANType9RecordSetOfsSystemName N_FUNC_AW(ANType9RecordSetOfsSystemName)

NResult N_API ANType9RecordGetOfsSystemVersionN(HANType9Record hRecord, HNString * phValue);
NResult N_API ANType9RecordSetOfsSystemVersionN(HANType9Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType9RecordSetOfsSystemVersionA(HANType9Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType9RecordSetOfsSystemVersionW(HANType9Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType9RecordSetOfsSystemVersion(HANType9Record hRecord, const NChar * szValue);
#endif
#define ANType9RecordSetOfsSystemVersion N_FUNC_AW(ANType9RecordSetOfsSystemVersion)

NResult N_API ANType9RecordGetOfsContactInformationN(HANType9Record hRecord, HNString * phValue);
NResult N_API ANType9RecordSetOfsContactInformationN(HANType9Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType9RecordSetOfsContactInformationA(HANType9Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType9RecordSetOfsContactInformationW(HANType9Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType9RecordSetOfsContactInformation(HANType9Record hRecord, const NChar * szValue);
#endif
#define ANType9RecordSetOfsContactInformation N_FUNC_AW(ANType9RecordSetOfsContactInformation)


#ifdef N_CPP
}
#endif

#endif // !AN_TYPE_9_RECORD_H_INCLUDED
