#ifndef AN_IMAGE_ASCII_BINARY_RECORD_HPP_INCLUDED
#define AN_IMAGE_ASCII_BINARY_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANAsciiBinaryRecord.hpp>
#include <Biometrics/Standards/ANImage.hpp>
#include <Biometrics/Standards/BdifTypes.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANImageAsciiBinaryRecord.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANDeviceMonitoringMode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANBoundaryCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANOcclusionOpacity)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANOcclusionType)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANMeasurementUnits)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CSP
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM
#undef AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM

#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_LINE_LENGTH
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_LINE_LENGTH_V5
#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_LINE_LENGTH_V5

#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_PIXEL_SCALE
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_PIXEL_SCALE_V5
#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_PIXEL_SCALE_V5

#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_SCAN_PIXEL_SCALE_PPCM
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_SCAN_PIXEL_SCALE_PPI
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_PPCM
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_PPI
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_V4_PPCM
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_V4_PPI

#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_PIXEL_SCALE_PPCM
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_PIXEL_SCALE_PPI
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_PPCM
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_PPI
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_V4_PPCM
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_V4_PPI

#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_VENDOR_COMPRESSION_ALGORITHM_LENGTH
#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_VENDOR_COMPRESSION_ALGORITHM_LENGTH
#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_VENDOR_COMPRESSION_ALGORITHM_LENGTH_V5
#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_VENDOR_COMPRESSION_ALGORITHM_LENGTH_V52

#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_COMMENT_LENGTH
#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_COMMENT_LENGTH_V5

#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_RULER_MAKE_LENGTH
#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_RULER_MODEL_LENGTH
#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_RULER_FP_FORM_NUMBER_LENGTH

#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_CIRCLE_VERTEX_COUNT
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_ELLIPSE_VERTEX_COUNT
#undef AN_IMAGE_ASCII_BINARY_RECORD_MIN_POLYGON_VERTEX_COUNT
#undef AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT

const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL = 6;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL = 7;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC = 8;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS = 9;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS = 10;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA = 11;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX = 12;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CSP = 13;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS = 16;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS = 17;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM = 20;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM = 24;
const NInt AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM = 30;

const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MAX_LINE_LENGTH = 9999;
const NUInt AN_IMAGE_ASCII_BINARY_RECORD_MIN_LINE_LENGTH_V5 = 10;
const NUInt AN_IMAGE_ASCII_BINARY_RECORD_MAX_LINE_LENGTH_V5 = 99999;

const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MAX_PIXEL_SCALE = 9999;
const NUInt AN_IMAGE_ASCII_BINARY_RECORD_MIN_PIXEL_SCALE_V5 = 1;
const NUInt AN_IMAGE_ASCII_BINARY_RECORD_MAX_PIXEL_SCALE_V5 = 99999;

const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_SCAN_PIXEL_SCALE_PPCM = 195;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_SCAN_PIXEL_SCALE_PPI = 495;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_PPCM = 195;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_PPI = 495;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_V4_PPCM = 390;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_SCAN_PIXEL_SCALE_V4_PPI = 990;

const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_PIXEL_SCALE_PPCM = 195;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_PIXEL_SCALE_PPI = 495;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_PPCM = 195;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_PPI = 495;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_V4_PPCM = 390;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_LATENT_PIXEL_SCALE_V4_PPI = 990;

const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MIN_VENDOR_COMPRESSION_ALGORITHM_LENGTH = 3;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MAX_VENDOR_COMPRESSION_ALGORITHM_LENGTH = 6;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MAX_VENDOR_COMPRESSION_ALGORITHM_LENGTH_V5 = 5;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MAX_VENDOR_COMPRESSION_ALGORITHM_LENGTH_V52 = 266;

const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MAX_COMMENT_LENGTH = 127;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MAX_COMMENT_LENGTH_V5 = 126;

const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MAX_RULER_MAKE_LENGTH = 50;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MAX_RULER_MODEL_LENGTH = 50;
const NUShort AN_IMAGE_ASCII_BINARY_RECORD_MAX_RULER_FP_FORM_NUMBER_LENGTH = 99;

const NByte AN_IMAGE_ASCII_BINARY_RECORD_MIN_CIRCLE_VERTEX_COUNT = 2;
const NByte AN_IMAGE_ASCII_BINARY_RECORD_MIN_ELLIPSE_VERTEX_COUNT = 3;
const NByte AN_IMAGE_ASCII_BINARY_RECORD_MIN_POLYGON_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MIN_ELLIPSE_VERTEX_COUNT;
const NByte AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT = 99;

class ANOcclusion : public ANOcclusion_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANOcclusion)

public:
	ANOcclusion(ANOcclusionOpacity opacity, ANOcclusionType type)
	{
		this->opacity = opacity;
		this->type = type;
	}
};

class ANRuler : public ANRuler_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANRuler)

public:
	ANRuler(ANMeasurementUnits units, const NStringWrapper & make, const NStringWrapper & model, const NStringWrapper & fPFormNumber)
	{
		NCheck(ANRulerCreateN(units, make.GetHandle(), model.GetHandle(), fPFormNumber.GetHandle(), this));
	}

	NString GetMake() const
	{
		return NString(hMake, false);
	}
	void SetMake(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hMake));
	}

	NString GetModel() const
	{
		return NString(hModel, false);
	}
	void SetModel(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hModel));
	}

	NString GetFPFormNumber() const
	{
		return NString(hFPFormNumber, false);
	}
	void SetFPFormNumber(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hFPFormNumber));
	}
};

}}}

N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANOcclusion)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANRuler)

namespace Neurotec { namespace Biometrics { namespace Standards
{

class ANImageAsciiBinaryRecord : public ANAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANImageAsciiBinaryRecord, ANAsciiBinaryRecord)

public:
	static NType ANDeviceMonitoringModeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANDeviceMonitoringMode), true);
	}

	static NType ANBoundaryCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANBoundaryCode), true);
	}

	static NType ANOcclusionOpacityNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANOcclusionOpacity), true);
	}

	static NType ANOcclusionTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANOcclusionType), true);
	}

	::Neurotec::Images::NImage ToNImage(NUInt flags = 0) const
	{
		HNImage hImage;
		NCheck(ANImageAsciiBinaryRecordToNImage(GetHandle(), flags, &hImage));
		return FromHandle< ::Neurotec::Images::NImage>(hImage);
	}

	void SetImage(::Neurotec::Images::NImage & value, NUInt flags = 0) const
	{
		NCheck(ANImageAsciiBinaryRecordSetImage(GetHandle(), value.GetHandle(), flags));
	}

	NInt GetHorzLineLength() const
	{
		NInt value;
		NCheck(ANImageAsciiBinaryRecordGetHorzLineLength(GetHandle(), &value));
		return value;
	}

	void SetHorzLineLength(NInt value)
	{
		NCheck(ANImageAsciiBinaryRecordSetHorzLineLength(GetHandle(), value));
	}

	NInt GetVertLineLength() const
	{
		NInt value;
		NCheck(ANImageAsciiBinaryRecordGetVertLineLength(GetHandle(), &value));
		return value;
	}

	void SetVertLineLength(NInt value)
	{
		NCheck(ANImageAsciiBinaryRecordSetVertLineLength(GetHandle(), value));
	}

	BdifScaleUnits GetScaleUnits() const
	{
		BdifScaleUnits value;
		NCheck(ANImageAsciiBinaryRecordGetScaleUnits(GetHandle(), &value));
		return value;
	}

	void SetScaleUnits(BdifScaleUnits value)
	{
		NCheck(ANImageAsciiBinaryRecordSetScaleUnits(GetHandle(), value));
	}

	NInt GetHorzPixelScale() const
	{
		NInt value;
		NCheck(ANImageAsciiBinaryRecordGetHorzPixelScale(GetHandle(), &value));
		return value;
	}

	void SetHorzPixelScale(NInt value)
	{
		NCheck(ANImageAsciiBinaryRecordSetHorzPixelScale(GetHandle(), value));
	}

	NInt GetVertPixelScale() const
	{
		NInt value;
		NCheck(ANImageAsciiBinaryRecordGetVertPixelScale(GetHandle(), &value));
		return value;
	}

	void SetVertPixelScale(NInt value)
	{
		NCheck(ANImageAsciiBinaryRecordSetVertPixelScale(GetHandle(), value));
	}

	ANImageCompressionAlgorithm GetCompressionAlgorithm() const
	{
		ANImageCompressionAlgorithm value;
		NCheck(ANImageAsciiBinaryRecordGetCompressionAlgorithm(GetHandle(), &value));
		return value;
	}

	NString GetVendorCompressionAlgorithm() const
	{
		return GetString(ANImageAsciiBinaryRecordGetVendorCompressionAlgorithmN);
	}

	void SetCompressionAlgorithm(ANImageCompressionAlgorithm value, const NStringWrapper & vendorValue)
	{
		NCheck(ANImageAsciiBinaryRecordSetCompressionAlgorithm(GetHandle(), value, vendorValue.GetHandle()));
	}

	NSByte GetBitsPerPixel() const
	{
		NSByte value;
		NCheck(ANImageAsciiBinaryRecordGetBitsPerPixel(GetHandle(), &value));
		return value;
	}

	void SetBitsPerPixel(NSByte value)
	{
		NCheck(ANImageAsciiBinaryRecordSetBitsPerPixel(GetHandle(), value));
	}

	ANImageColorSpace GetColorSpace() const
	{
		ANImageColorSpace value;
		NCheck(ANImageAsciiBinaryRecordGetColorSpace(GetHandle(), &value));
		return value;
	}

	void SetColorSpace(ANImageColorSpace value)
	{
		NCheck(ANImageAsciiBinaryRecordSetColorSpace(GetHandle(), value));
	}

	NInt GetScanHorzPixelScale() const
	{
		NInt value;
		NCheck(ANImageAsciiBinaryRecordGetScanHorzPixelScale(GetHandle(), &value));
		return value;
	}

	void SetScanHorzPixelScale(NInt value)
	{
		NCheck(ANImageAsciiBinaryRecordSetScanHorzPixelScale(GetHandle(), value));
	}

	NInt GetScanVertPixelScale() const
	{
		NInt value;
		NCheck(ANImageAsciiBinaryRecordGetScanVertPixelScale(GetHandle(), &value));
		return value;
	}

	void SetScanVertPixelScale(NInt value)
	{
		NCheck(ANImageAsciiBinaryRecordSetScanVertPixelScale(GetHandle(), value));
	}

	NString GetComment() const
	{
		return GetString(ANImageAsciiBinaryRecordGetCommentN);
	}

	void SetComment(const NStringWrapper & value)
	{
		return SetString(ANImageAsciiBinaryRecordSetCommentN, value);
	}

	ANDeviceMonitoringMode GetDeviceMonitoringMode() const
	{
		ANDeviceMonitoringMode value;
		NCheck(ANImageAsciiBinaryRecordGetDeviceMonitoringMode(GetHandle(), &value));
		return value;
	}

	void SetDeviceMonitoringMode(ANDeviceMonitoringMode value)
	{
		NCheck(ANImageAsciiBinaryRecordSetDeviceMonitoringMode(GetHandle(), value));
	}
};

}}}

#endif // !AN_IMAGE_ASCII_BINARY_RECORD_HPP_INCLUDED
