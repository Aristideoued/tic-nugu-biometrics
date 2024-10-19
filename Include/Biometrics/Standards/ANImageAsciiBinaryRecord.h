#ifndef AN_IMAGE_ASCII_BINARY_RECORD_H_INCLUDED
#define AN_IMAGE_ASCII_BINARY_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANAsciiBinaryRecord.h>
#include <Biometrics/Standards/ANImage.h>
#include <Biometrics/Standards/BdifTypes.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANImageAsciiBinaryRecord, ANAsciiBinaryRecord)

#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL   6
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL   7
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC   8
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS   9
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS  10
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA  11
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX  12
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CSP  13
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS 16
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS 17
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM  20
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM  24
#define AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM  30

#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_LINE_LENGTH   9999
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_LINE_LENGTH_V5 10
#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_LINE_LENGTH_V5 99999

#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_PIXEL_SCALE    9999
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_PIXEL_SCALE_V5 1
#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_PIXEL_SCALE_V5 99999

#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_SCAN_PIXEL_SCALE_PPCM        195
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_SCAN_PIXEL_SCALE_PPI         495
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_PPCM 195
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_PPI  495
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_V4_PPCM 390
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_V4_PPI  990

#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_PIXEL_SCALE_PPCM           195
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_PIXEL_SCALE_PPI            495
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_PPCM    195
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_PPI     495
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_V4_PPCM 390
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_V4_PPI  990

#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_VENDOR_COMPRESSION_ALGORITHM_LENGTH     3
#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_VENDOR_COMPRESSION_ALGORITHM_LENGTH     6
#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_VENDOR_COMPRESSION_ALGORITHM_LENGTH_V5  5
#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_VENDOR_COMPRESSION_ALGORITHM_LENGTH_V52 266

#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_COMMENT_LENGTH       127
#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_COMMENT_LENGTH_V5    126

#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_RULER_MAKE_LENGTH           50
#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_RULER_MODEL_LENGTH          50
#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_RULER_FP_FORM_NUMBER_LENGTH 99

#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_CIRCLE_VERTEX_COUNT  2
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_ELLIPSE_VERTEX_COUNT 3
#define AN_IMAGE_ASCII_BINARY_RECORD_MIN_POLYGON_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MIN_ELLIPSE_VERTEX_COUNT
#define AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT         99


typedef enum ANDeviceMonitoringMode_
{
	andmmUnspecified = 0,
	andmmControlled = 1,
	andmmAssisted = 2,
	andmmObserved = 3,
	andmmUnattended = 4,
	andmmUnknown = 255
} ANDeviceMonitoringMode;

N_DECLARE_TYPE(ANDeviceMonitoringMode)

typedef enum ANBoundaryCode_
{
	anbcUnspecified = 0,
	anbcCircle = 1,
	anbcEllipse = 2,
	anbcPolygon = 3,
} ANBoundaryCode;

N_DECLARE_TYPE(ANBoundaryCode)

typedef enum ANOcclusionOpacity_
{
	anooTotal = 1,
	anooInterference = 2,
	anooPartialLight = 3,
	anooPartialShadow = 4
} ANOcclusionOpacity;

N_DECLARE_TYPE(ANOcclusionOpacity)

typedef enum ANOcclusionType_
{
	anotLashes = 1,
	anotHeadCovering = 2,
	anotSpecular = 3,
	anotShadow = 4,
	anotReflection = 5,
	anotOther = 255
} ANOcclusionType;

N_DECLARE_TYPE(ANOcclusionType)

struct ANOcclusion_
{
	ANOcclusionOpacity opacity;
	ANOcclusionType type;
};
#ifndef AN_IMAGE_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANOcclusion_ ANOcclusion;
#endif

N_DECLARE_TYPE(ANOcclusion)

typedef enum ANMeasurementUnits_
{
	anmuUnspecified = 0,
	anmuInches = 1,
	anmuMillimeters = 2,
	anmuInchesAndMillimeters = 3
} ANMeasurementUnits;

N_DECLARE_TYPE(ANMeasurementUnits)

struct ANRuler_
{
	ANMeasurementUnits units;
	HNString hMake;
	HNString hModel;
	HNString hFPFormNumber;
};
#ifndef AN_IMAGE_ASCII_BINARY_RECORD_HPP_INCLUDED
typedef struct ANRuler_ ANRuler;
#endif

N_DECLARE_TYPE(ANRuler)

NResult N_API ANRulerCreateN(ANMeasurementUnits units, HNString hMake, HNString hModel, HNString hFPFormNumber, struct ANRuler_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANRulerCreateA(ANMeasurementUnits units, const NAChar * szMake, const NAChar * szModel, const NAChar * szFPFormNumber, struct ANRuler_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANRulerCreateW(ANMeasurementUnits units, const NWChar * szMake, const NWChar * szModel, const NWChar * szFPFormNumber, struct ANRuler_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANRulerCreate(ANMeasurementUnits units, const NChar * szMake, const NChar * szModel, const NChar * szFPFormNumber, ANRuler * pValue);
#endif
#define ANRulerCreate N_FUNC_AW(ANRulerCreate)

NResult N_API ANRulerDispose(struct ANRuler_ * pValue);
NResult N_API ANRulerCopy(const struct ANRuler_ * pSrcValue, struct ANRuler_ * pDstValue);
NResult N_API ANRulerSet(const struct ANRuler_ * pSrcValue, struct ANRuler_ * pDstValue);


NResult N_API ANImageAsciiBinaryRecordToNImage(HANImageAsciiBinaryRecord hRecord, NUInt flags, HNImage * phImage);

NResult N_API ANImageAsciiBinaryRecordSetImage(HANImageAsciiBinaryRecord hRecord, HNImage hImage, NUInt flags);

NResult N_API ANImageAsciiBinaryRecordGetHorzLineLength(HANImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANImageAsciiBinaryRecordSetHorzLineLength(HANImageAsciiBinaryRecord hRecord, NInt value);
NResult N_API ANImageAsciiBinaryRecordGetVertLineLength(HANImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANImageAsciiBinaryRecordSetVertLineLength(HANImageAsciiBinaryRecord hRecord, NInt value);
NResult N_API ANImageAsciiBinaryRecordGetScaleUnits(HANImageAsciiBinaryRecord hRecord, BdifScaleUnits * pValue);
NResult N_API ANImageAsciiBinaryRecordSetScaleUnits(HANImageAsciiBinaryRecord hRecord, BdifScaleUnits value);
NResult N_API ANImageAsciiBinaryRecordGetHorzPixelScale(HANImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANImageAsciiBinaryRecordSetHorzPixelScale(HANImageAsciiBinaryRecord hRecord, NInt value);
NResult N_API ANImageAsciiBinaryRecordGetVertPixelScale(HANImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANImageAsciiBinaryRecordSetVertPixelScale(HANImageAsciiBinaryRecord hRecord, NInt value);

NResult N_API ANImageAsciiBinaryRecordGetCompressionAlgorithm(HANImageAsciiBinaryRecord hRecord, ANImageCompressionAlgorithm * pValue);
NResult N_API ANImageAsciiBinaryRecordGetVendorCompressionAlgorithmN(HANImageAsciiBinaryRecord hRecord, HNString * phValue);
NResult N_API ANImageAsciiBinaryRecordSetCompressionAlgorithm(HANImageAsciiBinaryRecord hRecord, ANImageCompressionAlgorithm value, HNString hVendorValue);

NResult N_API ANImageAsciiBinaryRecordGetBitsPerPixel(HANImageAsciiBinaryRecord hRecord, NSByte * pValue);
NResult N_API ANImageAsciiBinaryRecordSetBitsPerPixel(HANImageAsciiBinaryRecord hRecord, NSByte value);
NResult N_API ANImageAsciiBinaryRecordGetColorSpace(HANImageAsciiBinaryRecord hRecord, ANImageColorSpace * pValue);
NResult N_API ANImageAsciiBinaryRecordSetColorSpace(HANImageAsciiBinaryRecord hRecord, ANImageColorSpace value);
NResult N_API ANImageAsciiBinaryRecordGetScanHorzPixelScale(HANImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANImageAsciiBinaryRecordSetScanHorzPixelScale(HANImageAsciiBinaryRecord hRecord, NInt value);
NResult N_API ANImageAsciiBinaryRecordGetScanVertPixelScale(HANImageAsciiBinaryRecord hRecord, NInt * pValue);
NResult N_API ANImageAsciiBinaryRecordSetScanVertPixelScale(HANImageAsciiBinaryRecord hRecord, NInt value);

NResult N_API ANImageAsciiBinaryRecordGetCommentN(HANImageAsciiBinaryRecord hRecord, HNString * phValue);
NResult N_API ANImageAsciiBinaryRecordSetCommentN(HANImageAsciiBinaryRecord hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANImageAsciiBinaryRecordSetCommentA(HANImageAsciiBinaryRecord hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANImageAsciiBinaryRecordSetCommentW(HANImageAsciiBinaryRecord hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANImageAsciiBinaryRecordSetComment(HANImageAsciiBinaryRecord hRecord, const NChar * szValue);
#endif
#define ANImageAsciiBinaryRecordSetComment N_FUNC_AW(ANImageAsciiBinaryRecordSetComment)

NResult N_API ANImageAsciiBinaryRecordGetDeviceMonitoringMode(HANImageAsciiBinaryRecord hRecord, ANDeviceMonitoringMode * pValue);
NResult N_API ANImageAsciiBinaryRecordSetDeviceMonitoringMode(HANImageAsciiBinaryRecord hRecord, ANDeviceMonitoringMode value);

#ifdef N_CPP
}
#endif

#endif // !AN_IMAGE_ASCII_BINARY_RECORD_H_INCLUDED
