#ifndef FIR_FINGER_VIEW_H_INCLUDED
#define FIR_FINGER_VIEW_H_INCLUDED

#include <Biometrics/Standards/BdifTypes.h>
#include <Images/NImage.h>
#include <Core/NDateTime.h>
#include <Geometry/NGeometry.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(FirFingerView, NObject)
N_DECLARE_OBJECT_TYPE(FirFingerViewSegmentation, NObject)
N_DECLARE_OBJECT_TYPE(FirFingerViewSegment, NObject)

#ifdef N_CPP
}
#endif

#include <Biometrics/Standards/FIRecord.h>

#ifdef N_CPP
extern "C"
{
#endif

#define FIRFV_MAX_ANNOTATION_COUNT 4
#define FIRFV_MAX_FINGER_SEGMENT_COUNT 4
#define FIRFV_MAX_SEGMENTATION_COUNT 0xFEFF
#define FIRFV_MAX_VENDOR_EXTENDED_DATA_COUNT 0xFEFF
#define FIRFV_MIN_COORDINATE_PAIR_COUNT 2
#define FIRFV_MAX_COORDINATE_PAIR_COUNT 99

NResult N_API FirFingerViewSetImage(HFirFingerView hFingerView, NUInt flags, HNImage hImage);
NResult N_API FirFingerViewToNImage(HFirFingerView hFingerView, NUInt flags, HNImage * phImage);

NResult N_API FirFingerViewGetStandard(HFirFingerView hFingerView, BdifStandard * pValue);
NResult N_API FirFingerViewGetVersion(HFirFingerView hFingerView, NVersion_ * pValue);
NResult N_API FirFingerViewGetPosition(HFirFingerView hFingerView, BdifFPPosition * pValue);
NResult N_API FirFingerViewSetPosition(HFirFingerView hFingerView, BdifFPPosition value);
NResult N_API FirFingerViewGetViewNumber(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewGetImageQuality(HFirFingerView hFingerView, NByte * pValue);
NResult N_API FirFingerViewSetImageQuality(HFirFingerView hFingerView, NByte value);
NResult N_API FirFingerViewGetImpressionType(HFirFingerView hFingerView, BdifFPImpressionType * pValue);
NResult N_API FirFingerViewSetImpressionType(HFirFingerView hFingerView, BdifFPImpressionType value);
NResult N_API FirFingerViewGetHorzLineLength(HFirFingerView hFingerView, NUShort * pValue);
NResult N_API FirFingerViewSetHorzLineLength(HFirFingerView hFingerView, NUShort value);
NResult N_API FirFingerViewGetVertLineLength(HFirFingerView hFingerView, NUShort * pValue);
NResult N_API FirFingerViewSetVertLineLength(HFirFingerView hFingerView, NUShort value);
NResult N_API FirFingerViewGetImageDataN(HFirFingerView hFingerView, HNBuffer * phValue);
NResult N_API FirFingerViewSetImageDataN(HFirFingerView hFingerView, HNBuffer hValue);
NResult N_API FirFingerViewSetImageDataEx(HFirFingerView hFingerView, const void * pValue, NSizeType valueSize, NBool copy);

NResult N_API FirFingerViewGetCaptureDateAndTime(HFirFingerView hFingerView, struct BdifCaptureDateTime_ * pValue);
NResult N_API FirFingerViewSetCaptureDateAndTime(HFirFingerView hFingerView, struct BdifCaptureDateTime_ value);
NResult N_API FirFingerViewGetCaptureDeviceTechnology(HFirFingerView hFingerView, BdifFPCaptureDeviceTechnology * pValue);
NResult N_API FirFingerViewSetCaptureDeviceTechnology(HFirFingerView hFingerView, BdifFPCaptureDeviceTechnology value);
NResult N_API FirFingerViewGetCaptureDeviceVendorId(HFirFingerView hFingerView, NUShort * pValue);
NResult N_API FirFingerViewSetCaptureDeviceVendorId(HFirFingerView hFingerView, NUShort value);
NResult N_API FirFingerViewGetCaptureDeviceTypeId(HFirFingerView hFingerView, NUShort * pValue);
NResult N_API FirFingerViewSetCaptureDeviceTypeId(HFirFingerView hFingerView, NUShort value);

NResult N_API FirFingerViewGetQualityBlockCount(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewGetQualityBlock(HFirFingerView hFingerView, NInt index, struct BdifQualityBlock_ * pValue);
NResult N_API FirFingerViewSetQualityBlock(HFirFingerView hFingerView, NInt index, const struct BdifQualityBlock_ * pValue);
NResult N_API FirFingerViewGetQualityBlocks(HFirFingerView hFingerView, struct BdifQualityBlock_ * * parValues, NInt * pValueCount);
NResult N_API FirFingerViewGetQualityBlockCapacity(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewSetQualityBlockCapacity(HFirFingerView hFingerView, NInt value);
NResult N_API FirFingerViewAddQualityBlock(HFirFingerView hFingerView, const struct BdifQualityBlock_ * pValue, NInt * pIndex);
NResult N_API FirFingerViewInsertQualityBlock(HFirFingerView hFingerView, NInt index, const struct BdifQualityBlock_ * pValue);
NResult N_API FirFingerViewRemoveQualityBlockAt(HFirFingerView hFingerView, NInt index);
NResult N_API FirFingerViewClearQualityBlocks(HFirFingerView hFingerView);

NResult N_API FirFingerViewGetCertificationBlockCount(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewGetCertificationBlock(HFirFingerView hFingerView, NInt index, struct BdifCertificationBlock_ * pValue);
NResult N_API FirFingerViewSetCertificationBlock(HFirFingerView hFingerView, NInt index, const struct BdifCertificationBlock_ * pValue);
NResult N_API FirFingerViewGetCertificationBlocks(HFirFingerView hFingerView, struct BdifCertificationBlock_ * * parValues, NInt * pValueCount);
NResult N_API FirFingerViewGetCertificationBlockCapacity(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewSetCertificationBlockCapacity(HFirFingerView hFingerView, NInt value);
NResult N_API FirFingerViewAddCertificationBlock(HFirFingerView hFingerView, const struct BdifCertificationBlock_ * pValue, NInt * pIndex);
NResult N_API FirFingerViewInsertCertificationBlock(HFirFingerView hFingerView, NInt index, const struct BdifCertificationBlock_ * pValue);
NResult N_API FirFingerViewRemoveCertificationBlockAt(HFirFingerView hFingerView, NInt index);
NResult N_API FirFingerViewClearCertificationBlocks(HFirFingerView hFingerView);

NResult N_API FirFingerViewGetScaleUnits(HFirFingerView hFingerView, BdifScaleUnits * pValue);
NResult N_API FirFingerViewSetScaleUnits(HFirFingerView hFingerView, BdifScaleUnits value);
NResult N_API FirFingerViewGetHorzScanResolution(HFirFingerView hFingerView, NUShort * pValue);
NResult N_API FirFingerViewSetHorzScanResolution(HFirFingerView hFingerView, NUShort value);
NResult N_API FirFingerViewGetVertScanResolution(HFirFingerView hFingerView, NUShort * pValue);
NResult N_API FirFingerViewSetVertScanResolution(HFirFingerView hFingerView, NUShort value);
NResult N_API FirFingerViewGetHorzImageResolution(HFirFingerView hFingerView, NUShort * pValue);
NResult N_API FirFingerViewSetHorzImageResolution(HFirFingerView hFingerView, NUShort value);
NResult N_API FirFingerViewGetVertImageResolution(HFirFingerView hFingerView, NUShort * pValue);
NResult N_API FirFingerViewSetVertImageResolution(HFirFingerView hFingerView, NUShort value);
NResult N_API FirFingerViewGetPixelDepth(HFirFingerView hFingerView, NByte * pValue);
NResult N_API FirFingerViewSetPixelDepth(HFirFingerView hFingerView, NByte value);
NResult N_API FirFingerViewGetImageCompressionAlgorithm(HFirFingerView hFingerView, FirImageCompressionAlgorithm * pValue);
NResult N_API FirFingerViewSetImageCompressionAlgorithm(HFirFingerView hFingerView, FirImageCompressionAlgorithm value);
NResult N_API FirFingerViewGetImageCompressionAlgorithmVendorId(HFirFingerView hFingerView, NUShort * pValue);
NResult N_API FirFingerViewSetImageCompressionAlgorithmVendorId(HFirFingerView hFingerView, NUShort value);
NResult N_API FirFingerViewGetImageCompressionAlgorithmId(HFirFingerView hFingerView, NUShort * pValue);
NResult N_API FirFingerViewSetImageCompressionAlgorithmId(HFirFingerView hFingerView, NUShort value);

NResult N_API FirFingerViewSegmentationGetFingerSegmentCount(HFirFingerViewSegmentation hSegmentation, NInt * pValue);
NResult N_API FirFingerViewSegmentationGetFingerSegment(HFirFingerViewSegmentation hSegmentation, NInt index, HFirFingerViewSegment * phValue);
NResult N_API FirFingerViewSegmentationGetFingerSegments(HFirFingerViewSegmentation hSegmentation, HFirFingerViewSegment * * parhValues, NInt * pValueCount);
NResult N_API FirFingerViewSegmentationSetFingerSegment(HFirFingerViewSegmentation hSegmentation, NInt index, HFirFingerViewSegment hValue);
NResult N_API FirFingerViewSegmentationGetFingerSegmentCapacity(HFirFingerViewSegmentation hSegmentation, NInt * pValue);
NResult N_API FirFingerViewSegmentationSetFingerSegmentCapacity(HFirFingerViewSegmentation hSegmentation, NInt value);
NResult N_API FirFingerViewSegmentationAddFingerSegment(HFirFingerViewSegmentation hSegmentation, HFirFingerViewSegment hValue, NInt * pIndex);
NResult N_API FirFingerViewSegmentationAddFingerSegmentEx(HFirFingerViewSegmentation hSegmentation, HFirFingerViewSegment * phSegment);
NResult N_API FirFingerViewSegmentationInsertFingerSegment(HFirFingerViewSegmentation hSegmentation, NInt index, HFirFingerViewSegment hValue);
NResult N_API FirFingerViewSegmentationInsertFingerSegmentEx(HFirFingerViewSegmentation hSegmentation, NInt index, HFirFingerViewSegment * phSegment);
NResult N_API FirFingerViewSegmentationRemoveFingerSegmentAt(HFirFingerViewSegmentation hSegmentation, NInt index);
NResult N_API FirFingerViewSegmentationClearFingerSegments(HFirFingerViewSegmentation hSegmentation);

NResult N_API FirFingerViewSegmentationGetStatus(HFirFingerViewSegmentation hSegmentation, BdifFPSegmentationStatus * pValue);
NResult N_API FirFingerViewSegmentationSetStatus(HFirFingerViewSegmentation hSegmentation, BdifFPSegmentationStatus value);
NResult N_API FirFingerViewSegmentationGetAlgorithmOwnerId(HFirFingerViewSegmentation hSegmentation, NUShort * pValue);
NResult N_API FirFingerViewSegmentationSetAlgorithmOwnerId(HFirFingerViewSegmentation hSegmentation, NUShort value);
NResult N_API FirFingerViewSegmentationGetAlgorithmId(HFirFingerViewSegmentation hSegmentation, NUShort * pValue);
NResult N_API FirFingerViewSegmentationSetAlgorithmId(HFirFingerViewSegmentation hSegmentation, NUShort value);
NResult N_API FirFingerViewSegmentationGetAlgorithmQuality(HFirFingerViewSegmentation hSegmentation, NByte * pValue);
NResult N_API FirFingerViewSegmentationSetAlgorithmQuality(HFirFingerViewSegmentation hSegmentation, NByte value);
NResult N_API FirFingerViewSegmentationGetFingerImageQualityAlgorithmOwnerId(HFirFingerViewSegmentation hSegmentation, NUShort * pValue);
NResult N_API FirFingerViewSegmentationSetFingerImageQualityAlgorithmOwnerId(HFirFingerViewSegmentation hSegmentation, NUShort value);
NResult N_API FirFingerViewSegmentationGetFingerImageQualityAlgorithmId(HFirFingerViewSegmentation hSegmentation, NUShort * pValue);
NResult N_API FirFingerViewSegmentationSetFingerImageQualityAlgorithmId(HFirFingerViewSegmentation hSegmentation, NUShort value);

NResult N_API FirFingerViewGetSegmentationCount(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewGetSegmentations(HFirFingerView hFingerView, HFirFingerViewSegmentation * * parhValues, NInt * pValueCount);
NResult N_API FirFingerViewGetSegmentation(HFirFingerView hFingerView, NInt index, HFirFingerViewSegmentation * phValue);
NResult N_API FirFingerViewSetSegmentation(HFirFingerView hFingerView, NInt index, HFirFingerViewSegmentation hValue);
NResult N_API FirFingerViewGetSegmentationCapacity(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewSetSegmentationCapacity(HFirFingerView hFingerView, NInt value);
NResult N_API FirFingerViewAddSegmentation(HFirFingerView hFingerView, HFirFingerViewSegmentation * phSegmentation);
NResult N_API FirFingerViewInsertSegmentation(HFirFingerView hFingerView, NInt index, HFirFingerViewSegmentation * phSegmentation);
NResult N_API FirFingerViewRemoveSegmentationAt(HFirFingerView hFingerView, NInt index);
NResult N_API FirFingerViewClearSegmentations(HFirFingerView hFingerView);

NResult N_API FirFingerViewGetAnnotationCount(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewGetAnnotation(HFirFingerView hFingerView, NInt index, struct BdifFPAnnotation_ * pValue);
NResult N_API FirFingerViewGetAnnotations(HFirFingerView hFingerView, struct BdifFPAnnotation_ * * parValues, NInt * pValueCount);
NResult N_API FirFingerViewSetAnnotation(HFirFingerView hFingerView, NInt index, const struct BdifFPAnnotation_ * pValue);
NResult N_API FirFingerViewGetAnnotationCapacity(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewSetAnnotationCapacity(HFirFingerView hFingerView, NInt value);
NResult N_API FirFingerViewAddAnnotation(HFirFingerView hFingerView, const struct BdifFPAnnotation_ * pValue, NInt * pIndex);
NResult N_API FirFingerViewInsertAnnotation(HFirFingerView hFingerView, NInt index, const struct BdifFPAnnotation_ * pValue);
NResult N_API FirFingerViewRemoveAnnotationAt(HFirFingerView hFingerView, NInt index);
NResult N_API FirFingerViewClearAnnotations(HFirFingerView hFingerView);

NResult N_API FirFingerViewGetCommentCount(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewGetCommentCapacity(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewSetCommentCapacity(HFirFingerView hFingerView, NInt value);
NResult N_API FirFingerViewAddComment(HFirFingerView hFingerView, HNString hValue, NInt * pIndex);
NResult N_API FirFingerViewInsertComment(HFirFingerView hFingerView, NInt index, HNString hValue);
NResult N_API FirFingerViewRemoveCommentAt(HFirFingerView hFingerView, NInt index);
NResult N_API FirFingerViewClearComments(HFirFingerView hFingerView);
NResult N_API FirFingerViewRemoveCommentRange(HFirFingerView hFingerView, NInt index, NInt count);
NResult N_API FirFingerViewGetCommentEx(HFirFingerView hFingerView, NInt index, HNString * phValue);
NResult N_API FirFingerViewSetCommentExN(HFirFingerView hFingerView, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API FirFingerViewSetCommentExA(HFirFingerView hFingerView, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API FirFingerViewSetCommentExW(HFirFingerView hFingerView, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API FirFingerViewSetCommentEx(HFirFingerView hFingerView, NInt index, const NChar * szValue);
#endif
#define FirFingerViewSetCommentEx N_FUNC_AW(FirFingerViewSetCommentEx)

NResult N_API FirFingerViewGetVendorExtendedDataCount(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewGetVendorExtendedData(HFirFingerView hFingerView, NInt index, struct BdifFPExtendedData_ * pValue);
NResult N_API FirFingerViewSetVendorExtendedData(HFirFingerView hFingerView, NInt index, const struct BdifFPExtendedData_ * pValue);
NResult N_API FirFingerViewGetVendorExtendedDatas(HFirFingerView hFingerView, struct BdifFPExtendedData_ * * parValues, NInt * pValueCount);
NResult N_API FirFingerViewGetVendorExtendedDataCapacity(HFirFingerView hFingerView, NInt * pValue);
NResult N_API FirFingerViewSetVendorExtendedDataCapacity(HFirFingerView hFingerView, NInt value);
NResult N_API FirFingerViewAddVendorExtendedData(HFirFingerView hFingerView, const struct BdifFPExtendedData_ * pValue, NInt * pIndex);
NResult N_API FirFingerViewInsertVendorExtendedData(HFirFingerView hFingerView, NInt index, const struct BdifFPExtendedData_ * pValue);
NResult N_API FirFingerViewRemoveVendorExtendedDataAt(HFirFingerView hFingerView, NInt index);
NResult N_API FirFingerViewClearVendorExtendedData(HFirFingerView hFingerView);

NResult N_API FirFingerViewSegmentCreate(HFirFingerViewSegment * phSegment);
NResult N_API FirFingerViewSegmentGetFingerPosition(HFirFingerViewSegment hFingerViewSegment, BdifFPPosition * pValue);
NResult N_API FirFingerViewSegmentSetFingerPosition(HFirFingerViewSegment hFingerViewSegment, BdifFPPosition value);
NResult N_API FirFingerViewSegmentGetFingerQuality(HFirFingerViewSegment hFingerViewSegment, NByte * pValue);
NResult N_API FirFingerViewSegmentSetFingerQuality(HFirFingerViewSegment hFingerViewSegment, NByte value);
NResult N_API FirFingerViewSegmentGetFingerQualityAlgorithmOwnerId(HFirFingerViewSegment hFingerViewSegment, NUShort * pValue);
NResult N_API FirFingerViewSegmentSetFingerQualityAlgorithmOwnerId(HFirFingerViewSegment hFingerViewSegment, NUShort value);
NResult N_API FirFingerViewSegmentGetFingerQualityAlgorithmId(HFirFingerViewSegment hFingerViewSegment, NUShort * pValue);
NResult N_API FirFingerViewSegmentSetFingerQualityAlgorithmId(HFirFingerViewSegment hFingerViewSegment, NUShort value);
NResult N_API FirFingerViewSegmentGetFingerOrientation(HFirFingerViewSegment hFingerViewSegment, NByte * pValue);
NResult N_API FirFingerViewSegmentSetFingerOrientation(HFirFingerViewSegment hFingerViewSegment, NByte value);

NResult N_API FirFingerViewSegmentGetCoordinateCount(HFirFingerViewSegment hFingerViewSegment, NInt * pValue);
NResult N_API FirFingerViewSegmentGetCoordinate(HFirFingerViewSegment hFingerViewSegment, NInt index, struct NPoint_ * pValue);
NResult N_API FirFingerViewSegmentSetCoordinate(HFirFingerViewSegment hFingerViewSegment, NInt index, const struct NPoint_ * pValue);
NResult N_API FirFingerViewSegmentGetCoordinates(HFirFingerViewSegment hFingerViewSegment, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API FirFingerViewSegmentGetCoordinateCapacity(HFirFingerViewSegment hFingerViewSegment, NInt * pValue);
NResult N_API FirFingerViewSegmentSetCoordinateCapacity(HFirFingerViewSegment hFingerViewSegment, NInt value);
NResult N_API FirFingerViewSegmentAddCoordinate(HFirFingerViewSegment hFingerViewSegment, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API FirFingerViewSegmentInsertCoordinate(HFirFingerViewSegment hFingerViewSegment, NInt index, const struct NPoint_ * pValue);
NResult N_API FirFingerViewSegmentRemoveCoordinateAt(HFirFingerViewSegment hFingerViewSegment, NInt index);
NResult N_API FirFingerViewSegmentClearCoordinates(HFirFingerViewSegment hFingerViewSegment);

#ifdef N_CPP
}
#endif

#endif // !FIR_FINGER_VIEW_H_INCLUDED
