#ifndef AN_TYPE_10_RECORD_HPP_INCLUDED
#define AN_TYPE_10_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANImageAsciiBinaryRecord.hpp>
#include <Geometry/NGeometry.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
using ::Neurotec::Geometry::NSize_;
#include <Biometrics/Standards/ANType10Record.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANImageType)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSubjectPose)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSmtSource)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANTattooClass)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANTattooSubclass)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANColor)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANFacePosition)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANDistortionCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANDistortionMeasurementCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANDistortionSeverityCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANLightingArtifact)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANTieredMarkupCollection)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANFeatureContourCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANCheiloscopicCharacterizationCode)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANLPContactLine)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANLipPathology)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANLPSurface)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANLPMedium)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANDentalImageCode)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_10_RECORD_FIELD_LEN
#undef AN_TYPE_10_RECORD_FIELD_IDC

#undef AN_TYPE_10_RECORD_FIELD_IMT

#undef AN_TYPE_10_RECORD_FIELD_SRC
#undef AN_TYPE_10_RECORD_FIELD_PHD
#undef AN_TYPE_10_RECORD_FIELD_HLL
#undef AN_TYPE_10_RECORD_FIELD_VLL
#undef AN_TYPE_10_RECORD_FIELD_SLC
#undef AN_TYPE_10_RECORD_FIELD_HPS
#undef AN_TYPE_10_RECORD_FIELD_VPS
#undef AN_TYPE_10_RECORD_FIELD_CGA

#undef AN_TYPE_10_RECORD_FIELD_CSP
#undef AN_TYPE_10_RECORD_FIELD_SAP
#undef AN_TYPE_10_RECORD_FIELD_FIP
#undef AN_TYPE_10_RECORD_FIELD_FPFI

#undef AN_TYPE_10_RECORD_FIELD_SHPS
#undef AN_TYPE_10_RECORD_FIELD_SVPS

#undef AN_TYPE_10_RECORD_FIELD_DIST
#undef AN_TYPE_10_RECORD_FIELD_LAF
#undef AN_TYPE_10_RECORD_FIELD_POS
#undef AN_TYPE_10_RECORD_FIELD_POA
#undef AN_TYPE_10_RECORD_FIELD_PXS
#undef AN_TYPE_10_RECORD_FIELD_PAS

#undef AN_TYPE_10_RECORD_FIELD_SQS

#undef AN_TYPE_10_RECORD_FIELD_SPA
#undef AN_TYPE_10_RECORD_FIELD_SXS
#undef AN_TYPE_10_RECORD_FIELD_SEC
#undef AN_TYPE_10_RECORD_FIELD_SHC
#undef AN_TYPE_10_RECORD_FIELD_FFP

#undef AN_TYPE_10_RECORD_FIELD_DMM

#undef AN_TYPE_10_RECORD_FIELD_TMC
#undef AN_TYPE_10_RECORD_FIELD_3DF
#undef AN_TYPE_10_RECORD_FIELD_FEC
#undef AN_TYPE_10_RECORD_FIELD_ICDR

#undef AN_TYPE_10_RECORD_FIELD_COM
#undef AN_TYPE_10_RECORD_FIELD_T10

#undef AN_TYPE_10_RECORD_FIELD_SMT
#undef AN_TYPE_10_RECORD_FIELD_SMS
#undef AN_TYPE_10_RECORD_FIELD_SMD
#undef AN_TYPE_10_RECORD_FIELD_COL

#undef AN_TYPE_10_RECORD_FIELD_ITX
#undef AN_TYPE_10_RECORD_FIELD_OCC

#undef AN_TYPE_10_RECORD_FIELD_SUB
#undef AN_TYPE_10_RECORD_FIELD_CON

#undef AN_TYPE_10_RECORD_FIELD_PID
#undef AN_TYPE_10_RECORD_FIELD_CID
#undef AN_TYPE_10_RECORD_FIELD_VID
#undef AN_TYPE_10_RECORD_FIELD_RSP

#undef AN_TYPE_10_RECORD_FIELD_ANN
#undef AN_TYPE_10_RECORD_FIELD_DUI
#undef AN_TYPE_10_RECORD_FIELD_MMS

#undef AN_TYPE_10_RECORD_FIELD_T2C

#undef AN_TYPE_10_RECORD_FIELD_SAN
#undef AN_TYPE_10_RECORD_FIELD_EFR
#undef AN_TYPE_10_RECORD_FIELD_ASC
#undef AN_TYPE_10_RECORD_FIELD_HAS
#undef AN_TYPE_10_RECORD_FIELD_SOR
#undef AN_TYPE_10_RECORD_FIELD_GEO

#undef AN_TYPE_10_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_10_RECORD_FIELD_UDF_TO
#undef AN_TYPE_10_RECORD_FIELD_UDF_TO_V5

#undef AN_TYPE_10_RECORD_FIELD_DATA

#undef AN_TYPE_10_RECORD_SAP_UNKNOWN
#undef AN_TYPE_10_RECORD_SAP_SURVEILLANCE_FACIAL_IMAGE
#undef AN_TYPE_10_RECORD_SAP_DRIVERS_LICENSE_IMAGE
#undef AN_TYPE_10_RECORD_SAP_ANSI_FULL_FRONTAL_FACIAL_IMAGE
#undef AN_TYPE_10_RECORD_SAP_ANSI_TOKEN_FACIAL_IMAGE
#undef AN_TYPE_10_RECORD_SAP_ISO_FULL_FRONTAL_FACIAL_IMAGE
#undef AN_TYPE_10_RECORD_SAP_ISO_TOKEN_FACIAL_IMAGE
#undef AN_TYPE_10_RECORD_SAP_PIV_FACIAL_IMAGE
#undef AN_TYPE_10_RECORD_SAP_LEGACY_MUGSHOT
#undef AN_TYPE_10_RECORD_SAP_BPA_LEVEL_30
#undef AN_TYPE_10_RECORD_SAP_BPA_LEVEL_32
#undef AN_TYPE_10_RECORD_SAP_BPA_LEVEL_40
#undef AN_TYPE_10_RECORD_SAP_BPA_LEVEL_42
#undef AN_TYPE_10_RECORD_SAP_BPA_LEVEL_50
#undef AN_TYPE_10_RECORD_SAP_BPA_LEVEL_51
#undef AN_TYPE_10_RECORD_SAP_BPA_LEVEL_52

#undef AN_TYPE_10_RECORD_MAX_PHOTO_DESCRIPTION_COUNT
#undef AN_TYPE_10_RECORD_MAX_QUALITY_METRIC_COUNT
#undef AN_TYPE_10_RECORD_MAX_SUBJECT_FACIAL_DESCRIPTION_COUNT
#undef AN_TYPE_10_RECORD_MAX_NCIC_DESIGNATION_CODE_COUNT
#undef AN_TYPE_10_RECORD_MAX_SMT_COUNT
#undef AN_TYPE_10_RECORD_MAX_SMT_COLOR_COUNT_V5

#undef AN_TYPE_10_RECORD_MAX_FACIAL_FEATURE_POINT_COUNT
#undef AN_TYPE_10_RECORD_MAX_FACIAL_3D_FEATURE_POINT_COUNT

#undef AN_TYPE_10_RECORD_MAX_PHYSICAL_PHOTO_CHARACTERISTIC_LENGTH
#undef AN_TYPE_10_RECORD_MAX_OTHER_PHOTO_CHARACTERISTIC_LENGTH
#undef AN_TYPE_10_RECORD_MIN_SUBJECT_FACIAL_CHARACTERISTIC_LENGTH
#undef AN_TYPE_10_RECORD_MAX_SUBJECT_FACIAL_CHARACTERISTIC_LENGTH

#undef AN_TYPE_10_RECORD_MAX_VENDOR_PHOTO_ACQUISITION_SOURCE_LENGTH
#undef AN_TYPE_10_RECORD_MAX_VENDOR_PHOTO_ACQUISITION_SOURCE_LENGTH_V5

#undef AN_TYPE_10_RECORD_MIN_NCIC_DESIGNATION_CODE_LENGTH
#undef AN_TYPE_10_RECORD_MAX_NCIC_DESIGNATION_CODE_LENGTH

#undef AN_TYPE_10_RECORD_MAX_SMT_SIZE
#undef AN_TYPE_10_RECORD_MAX_SMT_SIZE_V5

#undef AN_TYPE_10_RECORD_MAX_SMT_DESCRIPTION_LENGTH

#undef AN_TYPE_10_RECORD_MIN_IMAGE_PATH_VERTEX_COUNT
#undef AN_TYPE_10_RECORD_MAX_IMAGE_PATH_VERTEX_COUNT

#undef AN_TYPE_10_RECORD_MAX_LIGHTING_ARTIFACTS_COUNT

#undef AN_TYPE_10_RECORD_MAX_FEATURE_CONTOURS_COUNT
#undef AN_TYPE_10_RECORD_MIN_FEATURE_CONTOURS_VERTEX_COUNT
#undef AN_TYPE_10_RECORD_MAX_FEATURE_CONTOURS_VERTEX_COUNT

#undef AN_TYPE_10_RECORD_MAX_IMAGE_TRANSFORM_COUNT

#undef AN_TYPE_10_RECORD_MAX_OCCLUSION_COUNT
#undef AN_TYPE_10_RECORD_MIN_OCCLUSION_VERTEX_COUNT
#undef AN_TYPE_10_RECORD_MAX_OCCLUSION_VERTEX_COUNT

#undef AN_TYPE_10_RECORD_MAX_PATTERNED_INJURY_CODE_LENGTH_V52

#undef AN_TYPE_10_RECORD_MAX_LIPPRINT_CHARACTERIZATION_CODE_COUNT
#undef AN_TYPE_10_RECORD_MAX_LIP_PATALOGY_COUNT
#undef AN_TYPE_10_RECORD_MAX_LIPPRINT_SURFACE_COUNT

#undef AN_TYPE_10_RECORD_MIN_T10_REFERENCE_NUMBER
#undef AN_TYPE_10_RECORD_MAX_T10_REFERENCE_NUMBER

const NInt AN_TYPE_10_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_10_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;

const NInt AN_TYPE_10_RECORD_FIELD_IMT = 3;

const NInt AN_TYPE_10_RECORD_FIELD_SRC = AN_ASCII_BINARY_RECORD_FIELD_SRC;
const NInt AN_TYPE_10_RECORD_FIELD_PHD = AN_ASCII_BINARY_RECORD_FIELD_DAT;
const NInt AN_TYPE_10_RECORD_FIELD_HLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_10_RECORD_FIELD_VLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_10_RECORD_FIELD_SLC = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC;
const NInt AN_TYPE_10_RECORD_FIELD_HPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS;
const NInt AN_TYPE_10_RECORD_FIELD_VPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS;
const NInt AN_TYPE_10_RECORD_FIELD_CGA = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA;

const NInt AN_TYPE_10_RECORD_FIELD_CSP = 12;
const NInt AN_TYPE_10_RECORD_FIELD_SAP = 13;
const NInt AN_TYPE_10_RECORD_FIELD_FIP = 14;
const NInt AN_TYPE_10_RECORD_FIELD_FPFI = 15;

const NInt AN_TYPE_10_RECORD_FIELD_SHPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS;
const NInt AN_TYPE_10_RECORD_FIELD_SVPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS;

const NInt AN_TYPE_10_RECORD_FIELD_DIST = 18;
const NInt AN_TYPE_10_RECORD_FIELD_LAF = 19;
const NInt AN_TYPE_10_RECORD_FIELD_POS = 20;
const NInt AN_TYPE_10_RECORD_FIELD_POA = 21;
const NInt AN_TYPE_10_RECORD_FIELD_PXS = 22;
const NInt AN_TYPE_10_RECORD_FIELD_PAS = 23;

const NInt AN_TYPE_10_RECORD_FIELD_SQS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM;

const NInt AN_TYPE_10_RECORD_FIELD_SPA = 25;
const NInt AN_TYPE_10_RECORD_FIELD_SXS = 26;
const NInt AN_TYPE_10_RECORD_FIELD_SEC = 27;
const NInt AN_TYPE_10_RECORD_FIELD_SHC = 28;
const NInt AN_TYPE_10_RECORD_FIELD_FFP = 29;

const NInt AN_TYPE_10_RECORD_FIELD_DMM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM;

const NInt AN_TYPE_10_RECORD_FIELD_TMC = 31;
const NInt AN_TYPE_10_RECORD_FIELD_3DF = 32;
const NInt AN_TYPE_10_RECORD_FIELD_FEC = 33;
const NInt AN_TYPE_10_RECORD_FIELD_ICDR = 34;

const NInt AN_TYPE_10_RECORD_FIELD_COM = 38;
const NInt AN_TYPE_10_RECORD_FIELD_T10 = 39;

const NInt AN_TYPE_10_RECORD_FIELD_SMT = 40;
const NInt AN_TYPE_10_RECORD_FIELD_SMS = 41;
const NInt AN_TYPE_10_RECORD_FIELD_SMD = 42;
const NInt AN_TYPE_10_RECORD_FIELD_COL = 43;
const NInt AN_TYPE_10_RECORD_FIELD_ITX = 44;
const NInt AN_TYPE_10_RECORD_FIELD_OCC = 45;

const NInt AN_TYPE_10_RECORD_FIELD_SUB = AN_ASCII_BINARY_RECORD_FIELD_SUB;
const NInt AN_TYPE_10_RECORD_FIELD_CON = AN_ASCII_BINARY_RECORD_FIELD_CON;

const NInt AN_TYPE_10_RECORD_FIELD_PID = 48;
const NInt AN_TYPE_10_RECORD_FIELD_CID = 49;
const NInt AN_TYPE_10_RECORD_FIELD_VID = 50;
const NInt AN_TYPE_10_RECORD_FIELD_RSP = 51;

const NInt AN_TYPE_10_RECORD_FIELD_ANN = AN_ASCII_BINARY_RECORD_FIELD_ANN;
const NInt AN_TYPE_10_RECORD_FIELD_DUI = AN_ASCII_BINARY_RECORD_FIELD_DUI;
const NInt AN_TYPE_10_RECORD_FIELD_MMS = AN_ASCII_BINARY_RECORD_FIELD_MMS;

const NInt AN_TYPE_10_RECORD_FIELD_T2C = 992;

const NInt AN_TYPE_10_RECORD_FIELD_SAN = AN_ASCII_BINARY_RECORD_FIELD_SAN;
const NInt AN_TYPE_10_RECORD_FIELD_EFR = AN_ASCII_BINARY_RECORD_FIELD_EFR;
const NInt AN_TYPE_10_RECORD_FIELD_ASC = AN_ASCII_BINARY_RECORD_FIELD_ASC;
const NInt AN_TYPE_10_RECORD_FIELD_HAS = AN_ASCII_BINARY_RECORD_FIELD_HAS;
const NInt AN_TYPE_10_RECORD_FIELD_SOR = AN_ASCII_BINARY_RECORD_FIELD_SOR;
const NInt AN_TYPE_10_RECORD_FIELD_GEO = AN_ASCII_BINARY_RECORD_FIELD_GEO;

const NInt AN_TYPE_10_RECORD_FIELD_UDF_FROM = AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM;
const NInt AN_TYPE_10_RECORD_FIELD_UDF_TO = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO;
const NInt AN_TYPE_10_RECORD_FIELD_UDF_TO_V5 = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5;

const NInt AN_TYPE_10_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

const NUShort AN_TYPE_10_RECORD_SAP_UNKNOWN = 0;
const NUShort AN_TYPE_10_RECORD_SAP_SURVEILLANCE_FACIAL_IMAGE = 1;
const NUShort AN_TYPE_10_RECORD_SAP_DRIVERS_LICENSE_IMAGE = 10;
const NUShort AN_TYPE_10_RECORD_SAP_ANSI_FULL_FRONTAL_FACIAL_IMAGE = 11;
const NUShort AN_TYPE_10_RECORD_SAP_ANSI_TOKEN_FACIAL_IMAGE = 12;
const NUShort AN_TYPE_10_RECORD_SAP_ISO_FULL_FRONTAL_FACIAL_IMAGE = 13;
const NUShort AN_TYPE_10_RECORD_SAP_ISO_TOKEN_FACIAL_IMAGE = 14;
const NUShort AN_TYPE_10_RECORD_SAP_PIV_FACIAL_IMAGE = 15;
const NUShort AN_TYPE_10_RECORD_SAP_LEGACY_MUGSHOT = 20;
const NUShort AN_TYPE_10_RECORD_SAP_BPA_LEVEL_30 = 30;
const NUShort AN_TYPE_10_RECORD_SAP_BPA_LEVEL_32 = 32;
const NUShort AN_TYPE_10_RECORD_SAP_BPA_LEVEL_40 = 40;
const NUShort AN_TYPE_10_RECORD_SAP_BPA_LEVEL_42 = 42;
const NUShort AN_TYPE_10_RECORD_SAP_BPA_LEVEL_50 = 50;
const NUShort AN_TYPE_10_RECORD_SAP_BPA_LEVEL_51 = 51;
const NUShort AN_TYPE_10_RECORD_SAP_BPA_LEVEL_52 = 52;

const NInt AN_TYPE_10_RECORD_MAX_PHOTO_DESCRIPTION_COUNT = 9;
const NInt AN_TYPE_10_RECORD_MAX_QUALITY_METRIC_COUNT = 9;
const NInt AN_TYPE_10_RECORD_MAX_SUBJECT_FACIAL_DESCRIPTION_COUNT = 50;
const NInt AN_TYPE_10_RECORD_MAX_NCIC_DESIGNATION_CODE_COUNT = 3;
const NInt AN_TYPE_10_RECORD_MAX_SMT_COUNT = 9;
const NInt AN_TYPE_10_RECORD_MAX_SMT_COLOR_COUNT_V5 = 6;

const NInt AN_TYPE_10_RECORD_MAX_FACIAL_FEATURE_POINT_COUNT = 88;
const NInt AN_TYPE_10_RECORD_MAX_FACIAL_3D_FEATURE_POINT_COUNT = 88;

const NInt AN_TYPE_10_RECORD_MAX_PHYSICAL_PHOTO_CHARACTERISTIC_LENGTH = 11;
const NInt AN_TYPE_10_RECORD_MAX_OTHER_PHOTO_CHARACTERISTIC_LENGTH = 14;
const NInt AN_TYPE_10_RECORD_MIN_SUBJECT_FACIAL_CHARACTERISTIC_LENGTH = 5;
const NInt AN_TYPE_10_RECORD_MAX_SUBJECT_FACIAL_CHARACTERISTIC_LENGTH = 20;

const NInt AN_TYPE_10_RECORD_MAX_VENDOR_PHOTO_ACQUISITION_SOURCE_LENGTH = 7;
const NInt AN_TYPE_10_RECORD_MAX_VENDOR_PHOTO_ACQUISITION_SOURCE_LENGTH_V5 = 64;

const NInt AN_TYPE_10_RECORD_MIN_NCIC_DESIGNATION_CODE_LENGTH = 3;
const NInt AN_TYPE_10_RECORD_MAX_NCIC_DESIGNATION_CODE_LENGTH = 10;

const NInt AN_TYPE_10_RECORD_MAX_SMT_SIZE = 99;
const NInt AN_TYPE_10_RECORD_MAX_SMT_SIZE_V5 = 999;

const NInt AN_TYPE_10_RECORD_MAX_SMT_DESCRIPTION_LENGTH = 256;

const NByte AN_TYPE_10_RECORD_MIN_IMAGE_PATH_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MIN_CIRCLE_VERTEX_COUNT;
const NByte AN_TYPE_10_RECORD_MAX_IMAGE_PATH_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT;

const NByte AN_TYPE_10_RECORD_MAX_LIGHTING_ARTIFACTS_COUNT = 3;

const NByte AN_TYPE_10_RECORD_MAX_FEATURE_CONTOURS_COUNT = 12;
const NByte AN_TYPE_10_RECORD_MIN_FEATURE_CONTOURS_VERTEX_COUNT = 3;
const NByte AN_TYPE_10_RECORD_MAX_FEATURE_CONTOURS_VERTEX_COUNT = 99;

const NByte AN_TYPE_10_RECORD_MAX_IMAGE_TRANSFORM_COUNT = 18;

const NByte AN_TYPE_10_RECORD_MAX_OCCLUSION_COUNT = 16;
const NByte AN_TYPE_10_RECORD_MIN_OCCLUSION_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MIN_POLYGON_VERTEX_COUNT;
const NByte AN_TYPE_10_RECORD_MAX_OCCLUSION_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT;

const NByte AN_TYPE_10_RECORD_MAX_PATTERNED_INJURY_CODE_LENGTH_V52 = 30;

const NByte AN_TYPE_10_RECORD_MAX_LIPPRINT_CHARACTERIZATION_CODE_COUNT = 5;
const NByte AN_TYPE_10_RECORD_MAX_LIP_PATALOGY_COUNT = 13;
const NByte AN_TYPE_10_RECORD_MAX_LIPPRINT_SURFACE_COUNT = 3;

const NUShort AN_TYPE_10_RECORD_MIN_T10_REFERENCE_NUMBER = 1;
const NUShort AN_TYPE_10_RECORD_MAX_T10_REFERENCE_NUMBER = 255;

class ANSmt : public ANSmt_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANSmt)

public:
	ANSmt(ANSmtSource source, ANTattooClass tattooClass, ANTattooSubclass tattooSubclass, const NStringWrapper & description)
	{
		NCheck(ANSmtCreateN(source, tattooClass, tattooSubclass, description.GetHandle(), this));
	}

	NString GetDescription() const
	{
		return NString(hDescription, false);
	}

	void SetDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hDescription));
	}
};

class ANImageSourceType : public ANImageSourceType_
{
	N_DECLARE_DISPOSABLE_STRUCT_CLASS(ANImageSourceType)

public:
	ANImageSourceType(BdifImageSourceType value, const NStringWrapper & vendorValue)
	{
		NCheck(ANImageSourceTypeCreateN(value, vendorValue.GetHandle(), this));
	}

	NString GetVendorValue() const
	{
		return NString(hVendorValue, false);
	}

	void SetVendorValue(const NStringWrapper & nStringWrapper)
	{
		NCheck(NStringSet(nStringWrapper.GetHandle(), &hVendorValue));
	}
};

class ANPoseAngles : public ANPoseAngles_
{
	N_DECLARE_STRUCT_CLASS(ANPoseAngles)

public:
	ANPoseAngles(NInt yaw, NInt pitch, NInt roll, NInt yawUncertainty, NInt pitchUncertainty, NInt rollUncertainty)
	{
		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;
		this->yawUncertainty = yawUncertainty;
		this->pitchUncertainty = pitchUncertainty;
		this->rollUncertainty = rollUncertainty;
	}
};

class ANHairColor : public ANHairColor_
{
	N_DECLARE_STRUCT_CLASS(ANHairColor)

public:
	ANHairColor(BdifHairColor value, BdifHairColor baldValue)
	{
		this->value = value;
		this->baldValue = baldValue;
	}
};

class ANFaceImageBoundingBox : public ANFaceImageBoundingBox_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANFaceImageBoundingBox)

public:
	ANFaceImageBoundingBox(NUInt leftHorzOffset, NUInt rightHorzOffset, NUInt topVertOffset, NUInt bottomVertOffset, ANFacePosition facePosition)
	{
		this->leftHorzOffset = leftHorzOffset;
		this->rightHorzOffset = rightHorzOffset;
		this->topVertOffset = topVertOffset;
		this->bottomVertOffset = bottomVertOffset;
		this->facePosition = facePosition;
	}
};

class ANDistortion : public ANDistortion_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANDistortion)

public:
	ANDistortion(ANDistortionCode code, ANDistortionMeasurementCode measurementCode, ANDistortionSeverityCode severityCode)
	{
		this->code = code;
		this->measurementCode = measurementCode;
		this->severityCode = severityCode;
	}
};

class ANPatternedInjury : public ANPatternedInjury_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANPatternedInjury)

public:
	ANPatternedInjury(const NStringWrapper & code, const NStringWrapper & descriptiveText)
	{
		NCheck(ANPatternedInjuryCreateN(code.GetHandle(), descriptiveText.GetHandle(), this));
	}

	NString GetCode() const
	{
		return NString(hCode, false);
	}

	void SetCode(const NStringWrapper & code)
	{
		NCheck(NStringSet(code.GetHandle(), &hCode));
	}

	NString GetDescriptiveText() const
	{
		return NString(hDescriptiveText, false);
	}

	void SetDescriptiveText(const NStringWrapper & descriptiveText)
	{
		NCheck(NStringSet(descriptiveText.GetHandle(), &hDescriptiveText));
	}
};

class ANCheiloscopicData : public ANCheiloscopicData_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANCheiloscopicData)

public:
	ANCheiloscopicData(NInt lpWidth, NInt lpHeight, NInt philtrumWidth, NInt philtrumHeight, ANCheiloscopicCharacterizationCode upperLpCharacterization, ANCheiloscopicCharacterizationCode lowerLpCharacterization, 
						ANLPContactLine lpContactLine, const NStringWrapper & lpCharacterizationDescription, ANLipPathology lipPathologies, const NStringWrapper & lipPathologiesDescription, 
						ANLPSurface lpSurface, const NStringWrapper & lpSurfaceDescription, ANLPMedium lpMedium, const NStringWrapper & lpMediumDescription, 
						const NStringWrapper & facialHairDescription, const NStringWrapper & lipPositionDescription, const NStringWrapper & lpAdditionalDescription, const NStringWrapper & lpComparisonDescription)
	{
		NCheck(ANCheiloscopicDataCreateN(lpWidth, lpHeight, philtrumWidth, philtrumHeight, upperLpCharacterization, lowerLpCharacterization,
				lpContactLine, lpCharacterizationDescription.GetHandle(), lipPathologies, lipPathologiesDescription.GetHandle(), lpSurface, lpSurfaceDescription.GetHandle(), 
				lpMedium, lpMediumDescription.GetHandle(), facialHairDescription.GetHandle(), lipPositionDescription.GetHandle(), lpAdditionalDescription.GetHandle(), lpComparisonDescription.GetHandle(), this));
	}

	NString GetLpCharacterizationDescription() const
	{
		return NString(hLpCharacterizationDescription, false);
	}
	void SetLpCharacterizationDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hLpCharacterizationDescription));
	}

	NString GetLipPathologiesDescription() const
	{
		return NString(hLipPathologiesDescription, false);
	}
	void SetLipPathologiesDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hLipPathologiesDescription));
	}

	NString GetLpSurfaceDescription() const
	{
		return NString(hLpSurfaceDescription, false);
	}
	void SetLpSurfaceDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hLpSurfaceDescription));
	}

	NString GetLpMediumDescription() const
	{
		return NString(hLpMediumDescription, false);
	}
	void SetLpMediumDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hLpMediumDescription));
	}

	NString GetFacialHairDescription() const
	{
		return NString(hFacialHairDescription, false);
	}
	void SetFacialHairDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hFacialHairDescription));
	}

	NString GetLipPositionDescription() const
	{
		return NString(hLipPositionDescription, false);
	}
	void SetLipPositionDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hLipPositionDescription));
	}

	NString GetLpAdditionalDescription() const
	{
		return NString(hLpAdditionalDescription, false);
	}
	void SetLpAdditionalDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hLpAdditionalDescription));
	}

	NString GetLpComparisonDescription() const
	{
		return NString(hLpComparisonDescription, false);
	}
	void SetLpComparisonDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hLpComparisonDescription));
	}
};

class ANDentalVisualData : public ANDentalVisualData_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANDentalVisualData)

public:
	ANDentalVisualData(ANDentalImageCode imageViewCode, const NStringWrapper & additionalDescription, const NStringWrapper & comparisonDescription)
	{
		NCheck(ANDentalVisualDataCreateN(imageViewCode, additionalDescription.GetHandle(), comparisonDescription.GetHandle(), this));
	}

	NString GetAdditionalDescription() const
	{
		return NString(hAdditionalDescription, false);
	}
	void SetAdditionalDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hAdditionalDescription));
	}

	NString GetComparisonDescription() const
	{
		return NString(hComparisonDescription, false);
	}
	void SetComparisonDescription(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComparisonDescription));
	}
};

}}}

N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSmt)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANImageSourceType)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANPatternedInjury)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANCheiloscopicData)
N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANDentalVisualData)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANPoseAngles)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANHairColor)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANFaceImageBoundingBox)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANDistortion)

namespace Neurotec { namespace Biometrics { namespace Standards
{

class ANType10Record : public ANImageAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType10Record, ANImageAsciiBinaryRecord)

public:
	class PhysicalPhotoCharacteristicCollection : public ::Neurotec::Collections::NCollectionBase<NString, ANType10Record,
		ANType10RecordGetPhysicalPhotoCharacteristicCount, ANType10RecordGetPhysicalPhotoCharacteristicN>
	{
		PhysicalPhotoCharacteristicCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		void Set(NInt index, const NStringWrapper & value)
		{
			NCheck(ANType10RecordSetPhysicalPhotoCharacteristicN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		NInt Add(const NStringWrapper & value)
		{
			NInt index;
			NCheck(ANType10RecordAddPhysicalPhotoCharacteristicExN(this->GetOwnerHandle(), value.GetHandle(), &index));
			return index;
		}

		void Insert(NInt index, const NStringWrapper & value)
		{
			NCheck(ANType10RecordInsertPhysicalPhotoCharacteristicN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemovePhysicalPhotoCharacteristicAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearPhysicalPhotoCharacteristics(this->GetOwnerHandle()));
		}
	};

	class OtherPhotoCharacteristicCollection : public ::Neurotec::Collections::NCollectionBase<NString, ANType10Record,
		ANType10RecordGetOtherPhotoCharacteristicCount, ANType10RecordGetOtherPhotoCharacteristicN>
	{
		OtherPhotoCharacteristicCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		void Set(NInt index, const NStringWrapper & value)
		{
			NCheck(ANType10RecordSetOtherPhotoCharacteristicN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		NInt Add(const NStringWrapper & value)
		{
			NInt index;
			NCheck(ANType10RecordAddOtherPhotoCharacteristicExN(this->GetOwnerHandle(), value.GetHandle(), &index));
			return index;
		}

		void Insert(NInt index, const NStringWrapper & value)
		{
			NCheck(ANType10RecordInsertOtherPhotoCharacteristicN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveOtherPhotoCharacteristicAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearOtherPhotoCharacteristics(this->GetOwnerHandle()));
		}
	};

	class SubjectQualityScoreCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANQualityMetric, ANType10Record,
		ANType10RecordGetSubjectQualityScoreCount, ANType10RecordGetSubjectQualityScore, ANType10RecordGetSubjectQualityScores>
	{
		SubjectQualityScoreCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANQualityMetric, ANType10Record,
			ANType10RecordGetSubjectQualityScoreCount, ANType10RecordGetSubjectQualityScore, ANType10RecordGetSubjectQualityScores>::GetAll;

		void Set(NInt index, const ANQualityMetric & value)
		{
			NCheck(ANType10RecordSetSubjectQualityScore(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANQualityMetric & value)
		{
			NInt index;
			NCheck(ANType10RecordAddSubjectQualityScoreEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANQualityMetric & value)
		{
			NCheck(ANType10RecordInsertSubjectQualityScore(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveSubjectQualityScoreAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearSubjectQualityScores(this->GetOwnerHandle()));
		}
	};

	class SubjectFacialCharacteristicCollection : public ::Neurotec::Collections::NCollectionBase<NString, ANType10Record,
		ANType10RecordGetSubjectFacialCharacteristicCount, ANType10RecordGetSubjectFacialCharacteristicN>
	{
		SubjectFacialCharacteristicCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		void Set(NInt index, const NStringWrapper & value)
		{
			NCheck(ANType10RecordSetSubjectFacialCharacteristicN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		NInt Add(const NStringWrapper & value)
		{
			NInt index;
			NCheck(ANType10RecordAddSubjectFacialCharacteristicExN(this->GetOwnerHandle(), value.GetHandle(), &index));
			return index;
		}

		void Insert(NInt index, const NStringWrapper & value)
		{
			NCheck(ANType10RecordInsertSubjectFacialCharacteristicN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveSubjectFacialCharacteristicAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearSubjectFacialCharacteristics(this->GetOwnerHandle()));
		}
	};

	class FacialFeaturePointCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<BdifFaceFeaturePoint, ANType10Record,
		ANType10RecordGetFacialFeaturePointCount, ANType10RecordGetFacialFeaturePoint, ANType10RecordGetFacialFeaturePoints>
	{
		FacialFeaturePointCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;

	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<BdifFaceFeaturePoint, ANType10Record,
			ANType10RecordGetFacialFeaturePointCount, ANType10RecordGetFacialFeaturePoint, ANType10RecordGetFacialFeaturePoints>::GetAll;

		void Set(NInt index, const BdifFaceFeaturePoint & value)
		{
			NCheck(ANType10RecordSetFacialFeaturePoint(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const BdifFaceFeaturePoint & value)
		{
			NInt index;
			NCheck(ANType10RecordAddFacialFeaturePointEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const BdifFaceFeaturePoint & value)
		{
			NCheck(ANType10RecordInsertFacialFeaturePoint(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveFacialFeaturePointAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearFacialFeaturePoints(this->GetOwnerHandle()));
		}

		BdifFaceFeaturePoint GetWithCodeN(NInt index, NString * pCode)
		{
			BdifFaceFeaturePoint_ point;
			HNString hCode;
			NCheck(ANType10RecordGetFacialFeaturePointWithCodeN(this->GetOwnerHandle(), index, &point, &hCode));
			*pCode = NString(hCode, true);
			return NTypeTraits<BdifFaceFeaturePoint>::FromNative(point, true);
		}
	};

	class NcicDesignationCodeCollection : public ::Neurotec::Collections::NCollectionBase<NString, ANType10Record,
		ANType10RecordGetNcicDesignationCodeCount, ANType10RecordGetNcicDesignationCodeN>
	{
		NcicDesignationCodeCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		void Set(NInt index, const NStringWrapper & value)
		{
			NCheck(ANType10RecordSetNcicDesignationCodeN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		NInt Add(const NStringWrapper & value)
		{
			NInt index;
			NCheck(ANType10RecordAddNcicDesignationCodeExN(this->GetOwnerHandle(), value.GetHandle(), &index));
			return index;
		}

		void Insert(NInt index, const NStringWrapper & value)
		{
			NCheck(ANType10RecordInsertNcicDesignationCodeN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveNcicDesignationCodeAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearNcicDesignationCodes(this->GetOwnerHandle()));
		}
	};

	class SmtCollection : public ::Neurotec::Collections::NCollectionBase<ANSmt, ANType10Record,
		ANType10RecordGetSmtCount, ANType10RecordGetSmt>
	{
		SmtCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANSmt & value)
		{
			NCheck(ANType10RecordSetSmtEx(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSmt & value)
		{
			NInt index;
			NCheck(ANType10RecordAddSmt(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSmt & value)
		{
			NCheck(ANType10RecordInsertSmtEx(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveSmtAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearSmts(this->GetOwnerHandle()));
		}

		friend class ANType10Record;
	};

	class SmtColorsCollection : public ::Neurotec::NObjectPartBase<ANType10Record>
	{
		SmtColorsCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		NInt GetCount(NInt baseIndex) const
		{
			NInt value;
			NCheck(ANType10RecordGetSmtColorCount(this->GetOwnerHandle(), baseIndex, &value));
			return value;
		}

		ANColor Get(NInt baseIndex, NInt index) const
		{
			ANColor value;
			NCheck(ANType10RecordGetSmtColor(this->GetOwnerHandle(), baseIndex, index, &value));
			return value;
		}

		NArrayWrapper<ANColor> GetAll(NInt baseIndex) const
		{
			ANColor * arValues = NULL;
			NInt valueCount = 0;
			NCheck(ANType10RecordGetSmtColors(this->GetOwnerHandle(), baseIndex, &arValues, &valueCount));
			return NArrayWrapper<ANColor>(arValues, valueCount);
		}

		void Set(NInt baseIndex, NInt index, ANColor value)
		{
			NCheck(ANType10RecordSetSmtColor(this->GetOwnerHandle(), baseIndex, index, value));
		}

		NInt Add(NInt baseIndex, ANColor value)
		{
			NInt index;
			NCheck(ANType10RecordAddSmtColorEx(this->GetOwnerHandle(), baseIndex, value, &index));
			return index;
		}

		void Insert(NInt baseIndex, NInt index, ANColor value)
		{
			NCheck(ANType10RecordInsertSmtColor(this->GetOwnerHandle(), baseIndex, index, value));
		}

		void RemoveAt(NInt baseIndex, NInt index)
		{
			NCheck(ANType10RecordRemoveSmtColorAt(this->GetOwnerHandle(), baseIndex, index));
		}

		void Clear(NInt baseIndex)
		{
			NCheck(ANType10RecordClearSmtColors(this->GetOwnerHandle(), baseIndex));
		}
	};

	class ImagePathVerticesCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, ANType10Record,
		ANType10RecordGetImagePathVertexCount, ANType10RecordGetImagePathVertex, ANType10RecordGetImagePathVertices>
	{
		ImagePathVerticesCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, ANType10Record,
			ANType10RecordGetImagePathVertexCount, ANType10RecordGetImagePathVertex, ANType10RecordGetImagePathVertices>::GetAll;

		void Set(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType10RecordSetImagePathVertex(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType10RecordAddImagePathVertex(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType10RecordInsertImagePathVertex(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveImagePathVertexAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearImagePathVertices(this->GetOwnerHandle()));
		}
	};

	class LightingArtifactCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANLightingArtifact, ANType10Record,
		ANType10RecordGetLightingArtifactCount, ANType10RecordGetLightingArtifact, ANType10RecordGetLightingArtifacts>
	{
		LightingArtifactCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANLightingArtifact, ANType10Record,
			ANType10RecordGetLightingArtifactCount, ANType10RecordGetLightingArtifact, ANType10RecordGetLightingArtifacts>::GetAll;

		void Set(NInt index, ANLightingArtifact value)
		{
			NCheck(ANType10RecordSetLightingArtifact(this->GetOwnerHandle(), index, value));
		}

		NInt Add(ANLightingArtifact value)
		{
			NInt index;
			NCheck(ANType10RecordAddLightingArtifact(this->GetOwnerHandle(), value, &index));
			return index;
		}

		void Insert(NInt index, ANLightingArtifact value)
		{
			NCheck(ANType10RecordInsertLightingArtifact(this->GetOwnerHandle(), index, value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveLightingArtifactAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearLightingArtifacts(this->GetOwnerHandle()));
		}
	};

	class FacialFeature3DPointCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<BdifFaceFeaturePoint, ANType10Record,
		ANType10RecordGetFacialFeature3DPointCount, ANType10RecordGetFacialFeature3DPoint, ANType10RecordGetFacialFeature3DPoints>
	{
		FacialFeature3DPointCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;

	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<BdifFaceFeaturePoint, ANType10Record,
			ANType10RecordGetFacialFeature3DPointCount, ANType10RecordGetFacialFeature3DPoint, ANType10RecordGetFacialFeature3DPoints>::GetAll;

		void Set(NInt index, const BdifFaceFeaturePoint & value)
		{
			NCheck(ANType10RecordSetFacialFeature3DPoint(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const BdifFaceFeaturePoint & value)
		{
			NInt index;
			NCheck(ANType10RecordAddFacialFeature3DPoint(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const BdifFaceFeaturePoint & value)
		{
			NCheck(ANType10RecordInsertFacialFeature3DPoint(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveFacialFeature3DPointAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearFacialFeature3DPoints(this->GetOwnerHandle()));
		}

		BdifFaceFeaturePoint GetWithCodeN(NInt index, NString * pCode)
		{
			BdifFaceFeaturePoint_ point;
			HNString hCode;
			NCheck(ANType10RecordGetFacialFeature3DPointWithCodeN(this->GetOwnerHandle(), index, &point, &hCode));
			*pCode = NString(hCode, true);
			return NTypeTraits<BdifFaceFeaturePoint>::FromNative(point, true);
		}
	};

	class FeatureContourCodeCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANFeatureContourCode, ANType10Record,
		ANType10RecordGetFeatureContourCodeCount, ANType10RecordGetFeatureContourCode, ANType10RecordGetFeatureContourCodes>
	{
		FeatureContourCodeCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANFeatureContourCode, ANType10Record,
			ANType10RecordGetFeatureContourCodeCount, ANType10RecordGetFeatureContourCode, ANType10RecordGetFeatureContourCodes>::GetAll;

		void Set(NInt index, const ANFeatureContourCode & value)
		{
			NCheck(ANType10RecordSetFeatureContourCode(this->GetOwnerHandle(), index, value));
		}

		NInt Add(const ANFeatureContourCode & value)
		{
			NInt index;
			NCheck(ANType10RecordAddFeatureContourCode(this->GetOwnerHandle(), value, &index));
			return index;
		}

		void Insert(NInt index, const ANFeatureContourCode & value)
		{
			NCheck(ANType10RecordInsertFeatureContourCode(this->GetOwnerHandle(), index, value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveFeatureContourCodeAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearFeatureContourCodes(this->GetOwnerHandle()));
		}
	};

	class FeatureContourVerticesCollection : public ::Neurotec::NObjectPartBase<ANType10Record>
	{
		FeatureContourVerticesCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		NInt GetCount(NInt baseIndex) const
		{
			NInt value;
			NCheck(ANType10RecordGetFeatureContourVertexCount(this->GetOwnerHandle(), baseIndex, &value));
			return value;
		}

		void Get(NInt baseIndex, NInt index, ::Neurotec::Geometry::NPoint * pValue) const
		{
			NCheck(ANType10RecordGetFeatureContourVertex(this->GetOwnerHandle(), baseIndex, index, pValue));
		}

		::Neurotec::Geometry::NPoint Get(NInt baseIndex, NInt index) const
		{
			::Neurotec::Geometry::NPoint value;
			NCheck(ANType10RecordGetFeatureContourVertex(this->GetOwnerHandle(), baseIndex, index, &value));
			return value;
		}

		NArrayWrapper< ::Neurotec::Geometry::NPoint> GetAll(NInt baseIndex) const
		{
			::Neurotec::Geometry::NPoint::NativeType * arValues = NULL;
			NInt valueCount = 0;
			NCheck(ANType10RecordGetFeatureContourVertices(this->GetOwnerHandle(), baseIndex, &arValues, &valueCount));
			return NArrayWrapper< ::Neurotec::Geometry::NPoint>(arValues, valueCount);
		}

		void Set(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType10RecordSetFeatureContourVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		NInt Add(NInt baseIndex, const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType10RecordAddFeatureContourVertex(this->GetOwnerHandle(), baseIndex, &value, &index));
			return index;
		}

		void Insert(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType10RecordInsertFeatureContourVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		void RemoveAt(NInt baseIndex, NInt index)
		{
			NCheck(ANType10RecordRemoveFeatureContourVertexAt(this->GetOwnerHandle(), baseIndex, index));
		}

		void Clear(NInt baseIndex)
		{
			NCheck(ANType10RecordClearFeatureContourVertices(this->GetOwnerHandle(), baseIndex));
		}
	};

	class OcclusionCollection : public ::Neurotec::Collections::NCollectionBase<ANOcclusion, ANType10Record,
		ANType10RecordGetOcclusionCount, ANType10RecordGetOcclusion>
	{
		OcclusionCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANOcclusion & value)
		{
			NCheck(ANType10RecordSetOcclusion(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANOcclusion & value)
		{
			NInt index;
			NCheck(ANType10RecordAddOcclusion(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANOcclusion & value)
		{
			NCheck(ANType10RecordInsertOcclusion(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemoveOcclusionAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearOcclusions(this->GetOwnerHandle()));
		}

		friend class ANType10Record;
	};

	class OcclusionVerticesCollection : public ::Neurotec::NObjectPartBase<ANType10Record>
	{
		OcclusionVerticesCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType10Record;
	public:
		NInt GetCount(NInt baseIndex) const
		{
			NInt value;
			NCheck(ANType10RecordGetOcclusionVertexCount(this->GetOwnerHandle(), baseIndex, &value));
			return value;
		}

		void Get(NInt baseIndex, NInt index, ::Neurotec::Geometry::NPoint * pValue) const
		{
			NCheck(ANType10RecordGetOcclusionVertex(this->GetOwnerHandle(), baseIndex, index, pValue));
		}

		::Neurotec::Geometry::NPoint Get(NInt baseIndex, NInt index) const
		{
			::Neurotec::Geometry::NPoint value;
			NCheck(ANType10RecordGetOcclusionVertex(this->GetOwnerHandle(), baseIndex, index, &value));
			return value;
		}

		NArrayWrapper< ::Neurotec::Geometry::NPoint> GetAll(NInt baseIndex) const
		{
			::Neurotec::Geometry::NPoint::NativeType * arValues = NULL;
			NInt valueCount = 0;
			NCheck(ANType10RecordGetOcclusionVertices(this->GetOwnerHandle(), baseIndex, &arValues, &valueCount));
			return NArrayWrapper< ::Neurotec::Geometry::NPoint>(arValues, valueCount);
		}

		void Set(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType10RecordSetOcclusionVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		NInt Add(NInt baseIndex, const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType10RecordAddOcclusionVertex(this->GetOwnerHandle(), baseIndex, &value, &index));
			return index;
		}

		void Insert(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType10RecordInsertOcclusionVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		void RemoveAt(NInt baseIndex, NInt index)
		{
			NCheck(ANType10RecordRemoveOcclusionVertexAt(this->GetOwnerHandle(), baseIndex, index));
		}

		void Clear(NInt baseIndex)
		{
			NCheck(ANType10RecordClearOcclusionVertices(this->GetOwnerHandle(), baseIndex));
		}
	};

	class PatternedInjuryCollection : public ::Neurotec::Collections::NCollectionBase<ANPatternedInjury, ANType10Record,
		ANType10RecordGetPatternedInjuryCount, ANType10RecordGetPatternedInjury>
	{
		PatternedInjuryCollection(const ANType10Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANPatternedInjury & value)
		{
			NCheck(ANType10RecordSetPatternedInjury(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANPatternedInjury & value)
		{
			NInt index;
			NCheck(ANType10RecordAddPatternedInjury(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANPatternedInjury & value)
		{
			NCheck(ANType10RecordInsertPatternedInjury(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType10RecordRemovePatternedInjuryAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType10RecordClearPatternedInjuries(this->GetOwnerHandle()));
		}

		friend class ANType10Record;
	};

private:


public:
	static NType ANImageTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANImageType), true);
	}

	static NType ANSubjectPoseNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSubjectPose), true);
	}

	static NType ANSmtSourceNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSmtSource), true);
	}

	static NType ANTattooClassNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANTattooClass), true);
	}

	static NType ANTattooSubclassNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANTattooSubclass), true);
	}

	static NType ANColorNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANColor), true);
	}

	static NType ANFacePositionNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANFacePosition), true);
	}

	static NType ANDistortionCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANDistortionCode), true);
	}

	static NType ANDistortionMeasurementCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANDistortionMeasurementCode), true);
	}

	static NType ANDistortionSeverityCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANDistortionSeverityCode), true);
	}

	static NType ANLightingArtifactNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANLightingArtifact), true);
	}

	static NType ANTieredMarkupCollectionNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANTieredMarkupCollection), true);
	}
	
	static NType ANFeatureContourCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANFeatureContourCode), true);
	}

	static NType ANCheiloscopicCharacterizationCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANCheiloscopicCharacterizationCode), true);
	}

	static NType ANLPContactLineNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANLPContactLine), true);
	}

	static NType ANLipPathologyNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANLipPathology), true);
	}

	static NType ANLPSurfaceNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANLPSurface), true);
	}

	static NType ANLPMediumNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANLPMedium), true);
	}

	static NType ANDentalImageCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANDentalImageCode), true);
	}

	ANImageType GetImageType() const
	{
		ANImageType value;
		NCheck(ANType10RecordGetImageType(GetHandle(), &value));
		return value;
	}

	void SetImageType(ANImageType value)
	{
		NCheck(ANType10RecordSetImageType(GetHandle(), value));
	}

	NInt GetSubjectAcquisitionProfile() const
	{
		NInt value;
		NCheck(ANType10RecordGetSubjectAcquisitionProfile(GetHandle(), &value));
		return value;
	}

	void SetSubjectAcquisitionProfile(NInt value)
	{
		NCheck(ANType10RecordSetSubjectAcquisitionProfile(GetHandle(), value));
	}

	ANSubjectPose GetSubjectPose() const
	{
		ANSubjectPose value;
		NCheck(ANType10RecordGetSubjectPose(GetHandle(), &value));
		return value;
	}

	void SetSubjectPose(ANSubjectPose value)
	{
		NCheck(ANType10RecordSetSubjectPose(GetHandle(), value));
	}

	bool GetPoseOffsetAngle(NInt * pValue) const
	{
		NBool hasValue;
		NCheck(ANType10RecordGetPoseOffsetAngle(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetPoseOffsetAngle(const NInt * pValue)
	{
		NCheck(ANType10RecordSetPoseOffsetAngle(GetHandle(), pValue));
	}

	BdifFaceProperties GetPhotoAttributes() const
	{
		BdifFaceProperties value;
		NCheck(ANType10RecordGetPhotoAttributes(GetHandle(), &value));
		return value;
	}

	void SetPhotoAttributes(BdifFaceProperties value)
	{
		NCheck(ANType10RecordSetPhotoAttributes(GetHandle(), value));
	}

	bool GetPhotoAcquisitionSource(ANImageSourceType * pValue) const
	{
		NBool hasValue;
		NCheck(ANType10RecordGetPhotoAcquisitionSourceEx(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	BdifImageSourceType GetPhotoAcquisitionSource() const
	{
		BdifImageSourceType value;
		NCheck(ANType10RecordGetPhotoAcquisitionSource(GetHandle(), &value));
		return value;
	}

	NString GetVendorPhotoAcquisitionSource() const
	{
		return GetString(ANType10RecordGetVendorPhotoAcquisitionSourceN);
	}

	void SetPhotoAcquisitionSource(const ANImageSourceType * pValue)
	{
		NCheck(ANType10RecordSetPhotoAcquisitionSourceEx(GetHandle(), pValue));
	}

	void SetPhotoAcquisitionSource(BdifImageSourceType value, const NStringWrapper & vendorValue)
	{
		NCheck(ANType10RecordSetPhotoAcquisitionSourceN(GetHandle(), value, vendorValue.GetHandle()));
	}

	bool GetSubjectPoseAngles(ANPoseAngles * pValue) const
	{
		NBool hasValue;
		NCheck(ANType10RecordGetSubjectPoseAnglesEx(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	NInt GetSubjectPoseAnglesYaw() const
	{
		NInt value;
		NCheck(ANType10RecordGetSubjectPoseAnglesYaw(GetHandle(), &value));
		return value;
	}

	NInt GetSubjectPoseAnglesPitch() const
	{
		NInt value;
		NCheck(ANType10RecordGetSubjectPoseAnglesPitch(GetHandle(), &value));
		return value;
	}

	NInt GetSubjectPoseAnglesRoll() const
	{
		NInt value;
		NCheck(ANType10RecordGetSubjectPoseAnglesRoll(GetHandle(), &value));
		return value;
	}

	NInt GetSubjectPoseAnglesYawUncertainty() const
	{
		NInt value;
		NCheck(ANType10RecordGetSubjectPoseAnglesYawUncertainty(GetHandle(), &value));
		return value;
	}

	NInt GetSubjectPoseAnglesPitchUncertainty() const
	{
		NInt value;
		NCheck(ANType10RecordGetSubjectPoseAnglesPitchUncertainty(GetHandle(), &value));
		return value;
	}

	NInt GetSubjectPoseAnglesRollUncertainty() const
	{
		NInt value;
		NCheck(ANType10RecordGetSubjectPoseAnglesRollUncertainty(GetHandle(), &value));
		return value;
	}

	void GetSubjectPoseAngles(NInt * pYaw, NInt * pPitch, NInt * pRoll, NInt * pYawUncertainty, NInt * pPitchUncertainty, NInt * pRollUncertainty)
	{
		NCheck(ANType10RecordGetSubjectPoseAngles(GetHandle(), pYaw, pPitch, pRoll, pYawUncertainty, pPitchUncertainty, pRollUncertainty));
	}

	void SetSubjectPoseAngles(const ANPoseAngles * pValue)
	{
		NCheck(ANType10RecordSetSubjectPoseAnglesEx(GetHandle(), pValue));
	}

	void SetSubjectPoseAngles(NInt yaw, NInt pitch, NInt roll, NInt yawUncertainty, NInt pitchUncertainty, NInt rollUncertainty)
	{
		NCheck(ANType10RecordSetSubjectPoseAngles(GetHandle(), yaw, pitch, roll, yawUncertainty, pitchUncertainty, rollUncertainty));
	}

	BdifFaceExpressionBitMask GetSubjectFacialExpressionEx() const
	{
		BdifFaceExpressionBitMask value;
		NCheck(ANType10RecordGetSubjectFacialExpressionEx(GetHandle(), &value));
		return value;
	}

	void SetSubjectFacialExpressionEx(BdifFaceExpressionBitMask value)
	{
		NCheck(ANType10RecordSetSubjectFacialExpressionEx(GetHandle(), value));
	}

	BdifFaceProperties GetSubjectFacialAttributes() const
	{
		BdifFaceProperties value;
		NCheck(ANType10RecordGetSubjectFacialAttributes(GetHandle(), &value));
		return value;
	}

	void SetSubjectFacialAttributes(BdifFaceProperties value)
	{
		NCheck(ANType10RecordSetSubjectFacialAttributes(GetHandle(), value));
	}

	BdifEyeColor GetSubjectEyeColor() const
	{
		BdifEyeColor value;
		NCheck(ANType10RecordGetSubjectEyeColor(GetHandle(), &value));
		return value;
	}

	void SetSubjectEyeColor(BdifEyeColor value)
	{
		NCheck(ANType10RecordSetSubjectEyeColor(GetHandle(), value));
	}

	bool GetSubjectHairColor(ANHairColor * pValue) const
	{
		NBool hasValue;
		NCheck(ANType10RecordGetSubjectHairColorEx(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	BdifHairColor GetSubjectHairColor() const
	{
		BdifHairColor value;
		NCheck(ANType10RecordGetSubjectHairColor(GetHandle(), &value));
		return value;
	}

	BdifHairColor GetBaldSubjectHairColor() const
	{
		BdifHairColor value;
		NCheck(ANType10RecordGetBaldSubjectHairColor(GetHandle(), &value));
		return value;
	}

	void SetSubjectHairColor(const ANHairColor * pValue)
	{
		NCheck(ANType10RecordSetSubjectHairColorEx(GetHandle(), pValue));
	}

	void SetSubjectHairColor(BdifHairColor value, BdifHairColor baldValue)
	{
		NCheck(ANType10RecordSetSubjectHairColor(GetHandle(), value, baldValue));
	}

	bool GetSmtSize(::Neurotec::Geometry::NSize * pValue) const
	{
		NBool hasValue;
		NCheck(ANType10RecordGetSmtSize(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetSmtSize(const ::Neurotec::Geometry::NSize * pValue)
	{
		NCheck(ANType10RecordSetSmtSize(GetHandle(), pValue));
	}

	bool GetFaceImageBoundingBox(ANFaceImageBoundingBox * pValue) const
	{
		NBool hasValue;
		NCheck(ANType10RecordGetFaceImageBoundingBox(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetFaceImageBoundingBox(ANFaceImageBoundingBox * pValue)
	{
		NCheck(ANType10RecordSetFaceImageBoundingBox(GetHandle(), pValue));
	}

	ANBoundaryCode GetImagePathBoundaryCode() const
	{
		ANBoundaryCode value;
		NCheck(ANType10RecordGetImagePathBoundaryCode(GetHandle(), &value));
		return value;
	}

	void SetImagePathBoundaryCode(ANBoundaryCode value) const
	{
		NCheck(ANType10RecordSetImagePathBoundaryCode(GetHandle(), value));
	}

	bool GetDistortion(ANDistortion * pValue) const
	{
		NBool hasValue;
		NCheck(ANType10RecordGetDistortion(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetDistortion(ANDistortion * pValue)
	{
		NCheck(ANType10RecordSetDistortion(GetHandle(), pValue));
	}

	ANTieredMarkupCollection GetTieredMarkupCollection() const
	{
		ANTieredMarkupCollection value;
		NCheck(ANType10RecordGetTieredMarkupCollection(GetHandle(), &value));
		return value;
	}

	void SetTieredMarkupCollection(ANTieredMarkupCollection value)
	{
		NCheck(ANType10RecordSetTieredMarkupCollection(GetHandle(), value));
	}

	NString GetCaptureDateRange() const
	{
		return GetString(ANType10RecordGetCaptureDateRangeN);
	}
	void SetCaptureDateRange(const NStringWrapper & value)
	{
		SetString(ANType10RecordSetCaptureDateRangeN, value);
	}

	BdifFacePostAcquisitionProcessing GetImageTransformation() const
	{
		BdifFacePostAcquisitionProcessing value;
		NCheck(ANType10RecordGetImageTransformation(GetHandle(), &value));
		return value;
	}

	void SetImageTransformation(BdifFacePostAcquisitionProcessing value)
	{
		NCheck(ANType10RecordSetImageTransformation(GetHandle(), value));
	}

	bool GetCheiloscopicData(ANCheiloscopicData * pValue) const
	{
		NBool hasValue;
		NCheck(ANType10RecordGetCheiloscopicData(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}
	void SetCheiloscopicData(const ANCheiloscopicData * pValue)
	{
		NCheck(ANType10RecordSetCheiloscopicData(GetHandle(), pValue));
	}

	bool GetDentalVisualData(ANDentalVisualData * pValue) const
	{
		NBool hasValue;
		NCheck(ANType10RecordGetDentalVisualData(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}
	void SetDentalVisualData(const ANDentalVisualData * pValue)
	{
		NCheck(ANType10RecordSetDentalVisualData(GetHandle(), pValue));
	}

	bool GetRuler(ANRuler * pValue) const
	{
		NBool hasValue;
		NCheck(ANType10RecordGetRuler(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}
	void SetRuler(const ANRuler * pValue)
	{
		NCheck(ANType10RecordSetRuler(GetHandle(), pValue));
	}

	NInt GetType10ReferenceNumber() const
	{
		NInt value;
		NCheck(ANType10RecordGetType10ReferenceNumber(GetHandle(), &value));
		return value;
	}

	void SetType10ReferenceNumber(NInt value)
	{
		NCheck(ANType10RecordSetType10ReferenceNumber(GetHandle(), value));
	}

	NInt GetType2ReferenceNumber() const
	{
		NInt value;
		NCheck(ANType10RecordGetType2ReferenceNumber(GetHandle(), &value));
		return value;
	}

	void SetType2ReferenceNumber(NInt value)
	{
		NCheck(ANType10RecordSetType2ReferenceNumber(GetHandle(), value));
	}

	PhysicalPhotoCharacteristicCollection GetPhysicalPhotoCharacteristics()
	{
		return PhysicalPhotoCharacteristicCollection(*this);
	}

	const PhysicalPhotoCharacteristicCollection GetPhysicalPhotoCharacteristics() const
	{
		return PhysicalPhotoCharacteristicCollection(*this);
	}

	OtherPhotoCharacteristicCollection GetOtherPhotoCharacteristics()
	{
		return OtherPhotoCharacteristicCollection(*this);
	}

	const OtherPhotoCharacteristicCollection GetOtherPhotoCharacteristics() const
	{
		return OtherPhotoCharacteristicCollection(*this);
	}

	SubjectQualityScoreCollection GetSubjectQualityScores()
	{
		return SubjectQualityScoreCollection(*this);
	}

	const SubjectQualityScoreCollection GetSubjectQualityScores() const
	{
		return SubjectQualityScoreCollection(*this);
	}

	SubjectFacialCharacteristicCollection GetSubjectFacialCharacteristics()
	{
		return SubjectFacialCharacteristicCollection(*this);
	}

	const SubjectFacialCharacteristicCollection GetSubjectFacialCharacteristics() const
	{
		return SubjectFacialCharacteristicCollection(*this);
	}

	FacialFeaturePointCollection GetFacialFeaturePoints()
	{
		return FacialFeaturePointCollection(*this);
	}

	const FacialFeaturePointCollection GetFacialFeaturePoints() const
	{
		return FacialFeaturePointCollection(*this);
	}

	NcicDesignationCodeCollection GetNcicDesignationCode()
	{
		return NcicDesignationCodeCollection(*this);
	}

	const NcicDesignationCodeCollection GetNcicDesignationCode() const
	{
		return NcicDesignationCodeCollection(*this);
	}

	SmtCollection GetSmts()
	{
		return SmtCollection(*this);
	}

	const SmtCollection GetSmts() const
	{
		return SmtCollection(*this);
	}

	SmtColorsCollection GetSmtsColors()
	{
		return SmtColorsCollection(*this);
	}

	const SmtColorsCollection GetSmtsColors() const
	{
		return SmtColorsCollection(*this);
	}

	ImagePathVerticesCollection GetImagePathVertices()
	{
		return ImagePathVerticesCollection(*this);
	}

	const ImagePathVerticesCollection GetImagePathVertices() const
	{
		return ImagePathVerticesCollection(*this);
	}

	LightingArtifactCollection GetLightingArtifacts()
	{
		return LightingArtifactCollection(*this);
	}

	const LightingArtifactCollection GetLightingArtifacts() const
	{
		return LightingArtifactCollection(*this);
	}

	FacialFeature3DPointCollection GetFacialFeature3DPoints()
	{
		return FacialFeature3DPointCollection(*this);
	}

	const FacialFeature3DPointCollection GetFacialFeature3DPoints() const
	{
		return FacialFeature3DPointCollection(*this);
	}

	FeatureContourCodeCollection GetFeatureContoursCodes()
	{
		return FeatureContourCodeCollection(*this);
	}

	const FeatureContourCodeCollection GetFeatureContoursCodes() const
	{
		return FeatureContourCodeCollection(*this);
	}

	FeatureContourVerticesCollection GetFeatureContoursVertices()
	{
		return FeatureContourVerticesCollection(*this);
	}

	const FeatureContourVerticesCollection GetFeatureContoursVertices() const
	{
		return FeatureContourVerticesCollection(*this);
	}

	OcclusionCollection GetOcclusions()
	{
		return OcclusionCollection(*this);
	}

	const OcclusionCollection GetOcclusions() const
	{
		return OcclusionCollection(*this);
	}

	OcclusionVerticesCollection GetOcclusionVertices()
	{
		return OcclusionVerticesCollection(*this);
	}

	const OcclusionVerticesCollection GetOcclusionVertices() const
	{
		return OcclusionVerticesCollection(*this);
	}

	PatternedInjuryCollection GetPatternedInjuries()
	{
		return PatternedInjuryCollection(*this);
	}

	const PatternedInjuryCollection GetPatternedInjuries() const
	{
		return PatternedInjuryCollection(*this);
	}
};

}}}

#endif // !AN_TYPE_10_RECORD_HPP_INCLUDED
