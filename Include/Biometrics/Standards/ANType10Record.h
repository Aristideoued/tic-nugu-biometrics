#ifndef AN_TYPE_10_RECORD_H_INCLUDED
#define AN_TYPE_10_RECORD_H_INCLUDED

#include <Biometrics/Standards/ANImageAsciiBinaryRecord.h>
#include <Geometry/NGeometry.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANType10Record, ANImageAsciiBinaryRecord)

#define AN_TYPE_10_RECORD_FIELD_LEN AN_RECORD_FIELD_LEN
#define AN_TYPE_10_RECORD_FIELD_IDC AN_RECORD_FIELD_IDC

#define AN_TYPE_10_RECORD_FIELD_IMT 3

#define AN_TYPE_10_RECORD_FIELD_SRC AN_ASCII_BINARY_RECORD_FIELD_SRC
#define AN_TYPE_10_RECORD_FIELD_PHD AN_ASCII_BINARY_RECORD_FIELD_DAT
#define AN_TYPE_10_RECORD_FIELD_HLL AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL
#define AN_TYPE_10_RECORD_FIELD_VLL AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL
#define AN_TYPE_10_RECORD_FIELD_SLC AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC
#define AN_TYPE_10_RECORD_FIELD_HPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS
#define AN_TYPE_10_RECORD_FIELD_VPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS
#define AN_TYPE_10_RECORD_FIELD_CGA AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA

#define AN_TYPE_10_RECORD_FIELD_CSP  12
#define AN_TYPE_10_RECORD_FIELD_SAP  13
#define AN_TYPE_10_RECORD_FIELD_FIP  14
#define AN_TYPE_10_RECORD_FIELD_FPFI 15

#define AN_TYPE_10_RECORD_FIELD_SHPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS
#define AN_TYPE_10_RECORD_FIELD_SVPS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS

#define AN_TYPE_10_RECORD_FIELD_DIST 18
#define AN_TYPE_10_RECORD_FIELD_LAF 19
#define AN_TYPE_10_RECORD_FIELD_POS 20
#define AN_TYPE_10_RECORD_FIELD_POA 21
#define AN_TYPE_10_RECORD_FIELD_PXS 22
#define AN_TYPE_10_RECORD_FIELD_PAS 23

#define AN_TYPE_10_RECORD_FIELD_SQS AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM

#define AN_TYPE_10_RECORD_FIELD_SPA 25
#define AN_TYPE_10_RECORD_FIELD_SXS 26
#define AN_TYPE_10_RECORD_FIELD_SEC 27
#define AN_TYPE_10_RECORD_FIELD_SHC 28
#define AN_TYPE_10_RECORD_FIELD_FFP 29

#define AN_TYPE_10_RECORD_FIELD_DMM AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM

#define AN_TYPE_10_RECORD_FIELD_TMC 31
#define AN_TYPE_10_RECORD_FIELD_3DF 32
#define AN_TYPE_10_RECORD_FIELD_FEC 33
#define AN_TYPE_10_RECORD_FIELD_ICDR 34

#define AN_TYPE_10_RECORD_FIELD_COM 38
#define AN_TYPE_10_RECORD_FIELD_T10 39

#define AN_TYPE_10_RECORD_FIELD_SMT 40
#define AN_TYPE_10_RECORD_FIELD_SMS 41
#define AN_TYPE_10_RECORD_FIELD_SMD 42
#define AN_TYPE_10_RECORD_FIELD_COL 43
#define AN_TYPE_10_RECORD_FIELD_ITX 44
#define AN_TYPE_10_RECORD_FIELD_OCC 45

#define AN_TYPE_10_RECORD_FIELD_SUB AN_ASCII_BINARY_RECORD_FIELD_SUB
#define AN_TYPE_10_RECORD_FIELD_CON AN_ASCII_BINARY_RECORD_FIELD_CON

#define AN_TYPE_10_RECORD_FIELD_PID 48
#define AN_TYPE_10_RECORD_FIELD_CID 49
#define AN_TYPE_10_RECORD_FIELD_VID 50
#define AN_TYPE_10_RECORD_FIELD_RSP 51

#define AN_TYPE_10_RECORD_FIELD_ANN AN_ASCII_BINARY_RECORD_FIELD_ANN
#define AN_TYPE_10_RECORD_FIELD_DUI AN_ASCII_BINARY_RECORD_FIELD_DUI
#define AN_TYPE_10_RECORD_FIELD_MMS AN_ASCII_BINARY_RECORD_FIELD_MMS

#define AN_TYPE_10_RECORD_FIELD_T2C 992

#define AN_TYPE_10_RECORD_FIELD_SAN AN_ASCII_BINARY_RECORD_FIELD_SAN
#define AN_TYPE_10_RECORD_FIELD_EFR AN_ASCII_BINARY_RECORD_FIELD_EFR
#define AN_TYPE_10_RECORD_FIELD_ASC AN_ASCII_BINARY_RECORD_FIELD_ASC
#define AN_TYPE_10_RECORD_FIELD_HAS AN_ASCII_BINARY_RECORD_FIELD_HAS
#define AN_TYPE_10_RECORD_FIELD_SOR AN_ASCII_BINARY_RECORD_FIELD_SOR
#define AN_TYPE_10_RECORD_FIELD_GEO AN_ASCII_BINARY_RECORD_FIELD_GEO

#define AN_TYPE_10_RECORD_FIELD_UDF_FROM   AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM
#define AN_TYPE_10_RECORD_FIELD_UDF_TO     AN_ASCII_BINARY_RECORD_FIELD_UDF_TO
#define AN_TYPE_10_RECORD_FIELD_UDF_TO_V5  AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5

#define AN_TYPE_10_RECORD_FIELD_DATA AN_RECORD_FIELD_DATA

#define AN_TYPE_10_RECORD_SAP_UNKNOWN                         0
#define AN_TYPE_10_RECORD_SAP_SURVEILLANCE_FACIAL_IMAGE       1
#define AN_TYPE_10_RECORD_SAP_DRIVERS_LICENSE_IMAGE          10
#define AN_TYPE_10_RECORD_SAP_ANSI_FULL_FRONTAL_FACIAL_IMAGE 11
#define AN_TYPE_10_RECORD_SAP_ANSI_TOKEN_FACIAL_IMAGE        12
#define AN_TYPE_10_RECORD_SAP_ISO_FULL_FRONTAL_FACIAL_IMAGE  13
#define AN_TYPE_10_RECORD_SAP_ISO_TOKEN_FACIAL_IMAGE         14
#define AN_TYPE_10_RECORD_SAP_PIV_FACIAL_IMAGE               15
#define AN_TYPE_10_RECORD_SAP_LEGACY_MUGSHOT                 20
#define AN_TYPE_10_RECORD_SAP_BPA_LEVEL_30                   30
#define AN_TYPE_10_RECORD_SAP_BPA_LEVEL_32                   32
#define AN_TYPE_10_RECORD_SAP_BPA_LEVEL_40                   40
#define AN_TYPE_10_RECORD_SAP_BPA_LEVEL_42                   42
#define AN_TYPE_10_RECORD_SAP_BPA_LEVEL_50                   50
#define AN_TYPE_10_RECORD_SAP_BPA_LEVEL_51                   51
#define AN_TYPE_10_RECORD_SAP_BPA_LEVEL_52                   52

#define AN_TYPE_10_RECORD_MAX_PHOTO_DESCRIPTION_COUNT           9
#define AN_TYPE_10_RECORD_MAX_QUALITY_METRIC_COUNT              9
#define AN_TYPE_10_RECORD_MAX_SUBJECT_FACIAL_DESCRIPTION_COUNT 50
#define AN_TYPE_10_RECORD_MAX_NCIC_DESIGNATION_CODE_COUNT       3
#define AN_TYPE_10_RECORD_MAX_SMT_COUNT                         9
#define AN_TYPE_10_RECORD_MAX_SMT_COLOR_COUNT_V5                6

#define AN_TYPE_10_RECORD_MAX_FACIAL_FEATURE_POINT_COUNT       88
#define AN_TYPE_10_RECORD_MAX_FACIAL_3D_FEATURE_POINT_COUNT    88

#define AN_TYPE_10_RECORD_MAX_PHYSICAL_PHOTO_CHARACTERISTIC_LENGTH   11
#define AN_TYPE_10_RECORD_MAX_OTHER_PHOTO_CHARACTERISTIC_LENGTH      14
#define AN_TYPE_10_RECORD_MIN_SUBJECT_FACIAL_CHARACTERISTIC_LENGTH    5
#define AN_TYPE_10_RECORD_MAX_SUBJECT_FACIAL_CHARACTERISTIC_LENGTH   20

#define AN_TYPE_10_RECORD_MAX_VENDOR_PHOTO_ACQUISITION_SOURCE_LENGTH  7
#define AN_TYPE_10_RECORD_MAX_VENDOR_PHOTO_ACQUISITION_SOURCE_LENGTH_V5 64

#define AN_TYPE_10_RECORD_MIN_NCIC_DESIGNATION_CODE_LENGTH            3
#define AN_TYPE_10_RECORD_MAX_NCIC_DESIGNATION_CODE_LENGTH           10

#define AN_TYPE_10_RECORD_MAX_SMT_SIZE 99
#define AN_TYPE_10_RECORD_MAX_SMT_SIZE_V5 999

#define AN_TYPE_10_RECORD_MAX_SMT_DESCRIPTION_LENGTH 256

#define AN_TYPE_10_RECORD_MIN_IMAGE_PATH_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MIN_CIRCLE_VERTEX_COUNT
#define AN_TYPE_10_RECORD_MAX_IMAGE_PATH_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT

#define AN_TYPE_10_RECORD_MAX_LIGHTING_ARTIFACTS_COUNT 3

#define AN_TYPE_10_RECORD_MAX_FEATURE_CONTOURS_COUNT  12
#define AN_TYPE_10_RECORD_MIN_FEATURE_CONTOURS_VERTEX_COUNT  3
#define AN_TYPE_10_RECORD_MAX_FEATURE_CONTOURS_VERTEX_COUNT 99

#define AN_TYPE_10_RECORD_MAX_IMAGE_TRANSFORM_COUNT 18

#define AN_TYPE_10_RECORD_MAX_OCCLUSION_COUNT 16
#define AN_TYPE_10_RECORD_MIN_OCCLUSION_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MIN_POLYGON_VERTEX_COUNT
#define AN_TYPE_10_RECORD_MAX_OCCLUSION_VERTEX_COUNT AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT

#define AN_TYPE_10_RECORD_MAX_PATTERNED_INJURY_CODE_LENGTH_V52 30

#define AN_TYPE_10_RECORD_MAX_LIPPRINT_CHARACTERIZATION_CODE_COUNT 5
#define AN_TYPE_10_RECORD_MAX_LIP_PATALOGY_COUNT                   13
#define AN_TYPE_10_RECORD_MAX_LIPPRINT_SURFACE_COUNT               3

#define AN_TYPE_10_RECORD_MIN_T10_REFERENCE_NUMBER 1
#define AN_TYPE_10_RECORD_MAX_T10_REFERENCE_NUMBER 255

typedef enum ANImageType_
{
	anitUnspecified = -1,
	anitFace = 0,
	anitScar = 1,
	anitMark = 2,
	anitTattoo = 3,
	anitFrontalC = 4,
	anitRearC = 5,
	anitHead = 6,
	anitFrontalN = 7,
	anitRearN = 8,
	anitTorsoBack = 9,
	anitTorsoFront = 10,
	anitCondition = 11,
	anitMissing = 12,
	anitChest = 13,
	anitFeet = 14,
	anitExtraOral = 15,
	anitIntraOral = 16,
	anitLip = 17,
	anitHandsPalm = 18,
	anitHandsBack= 19,
	anitGenitals = 20,
	anitButtock = 21,
	anitRightLeg = 22,
	anitLeftLeg = 23,
	anitRightArm = 24,
	anitLeftArm = 25,
	anitOther = 255
} ANImageType;

N_DECLARE_TYPE(ANImageType)

typedef enum ANSubjectPose_
{
	anspUnspecified = 0,
	anspFullFaceFrontal = 1,
	anspRightProfile = 2,
	anspLeftProfile = 3,
	anspAngled = 4,
	anspDetermined3D = 5
} ANSubjectPose;

N_DECLARE_TYPE(ANSubjectPose)

typedef enum ANSmtSource_
{
	anssScar = 0,
	anssMark = 1,
	anssTattoo = 2,
	anssChemical = 3,
	anssBranded = 4,
	anssCut = 5,
	anssPiersing = 6,
	anssBirthmark = 7,
	anssZabiba = 8,
	anssImplant = 9
} ANSmtSource;

N_DECLARE_TYPE(ANSmtSource)

typedef enum ANTattooClass_
{
	antcHuman = 0,
	antcAnimal = 1,
	antcPlant = 2,
	antcFlag = 3,
	antcObject = 4,
	antcAbstract = 5,
	antcSymbol = 6,
	antcOther = 7,
	antcUnspecified = 255
} ANTattooClass;

N_DECLARE_TYPE(ANTattooClass)

typedef enum ANTattooSubclass_
{
	antsMiscHuman = antcHuman * 256 + 0,
	antsMaleFace = antcHuman * 256 + 1,
	antsFemaleFace = antcHuman * 256 + 2,
	antsAbstractFace = antcHuman * 256 + 3,
	antsMaleBody = antcHuman * 256 + 4,
	antsFemaleBody = antcHuman * 256 + 5,
	antsAbstractBody = antcHuman * 256 + 6,
	antsRole = antcHuman * 256 + 7,
	antsSportFigure = antcHuman * 256 + 8,
	antsMaleBodyPart = antcHuman * 256 + 9,
	antsFemaleBodyPart = antcHuman * 256 + 10,
	antsAbstractBodyPart = antcHuman * 256 + 11,
	antsSkull = antcHuman * 256 + 12,

	antsMiscAnimal = antcAnimal * 256 + 0,
	antsCat = antcAnimal * 256 + 1,
	antsDog = antcAnimal * 256 + 2,
	antsDomestic = antcAnimal * 256 + 3,
	antsVicious = antcAnimal * 256 + 4,
	antsHorse = antcAnimal * 256 + 5,
	antsWild = antcAnimal * 256 + 6,
	antsSnake = antcAnimal * 256 + 7,
	antsDragon = antcAnimal * 256 + 8,
	antsBird = antcAnimal * 256 + 9,
	antsInsect = antcAnimal * 256 + 10,
	antsAbstractAnimal = antcAnimal * 256 + 11,
	antsAnimalPart = antcAnimal * 256 + 12,

	antsMiscPlant = antcPlant * 256 + 0,
	antsNarcotic = antcPlant * 256 + 1,
	antsRedFlower = antcPlant * 256 + 2,
	antsBlueFlower = antcPlant * 256 + 3,
	antsYellowFlower = antcPlant * 256 + 4,
	antsDrawing = antcPlant * 256 + 5,
	antsRose = antcPlant * 256 + 6,
	antsTulip = antcPlant * 256 + 7,
	antsLily = antcPlant * 256 + 8,

	antsMiscFlag = antcFlag * 256 + 0,
	antsUsa = antcFlag * 256 + 1,
	antsState = antcFlag * 256 + 2,
	antsNazi = antcFlag * 256 + 3,
	antsConfederate = antcFlag * 256 + 4,
	antsBritish = antcFlag * 256 + 5,

	antsMiscObject = antcObject * 256 + 0,
	antsFire = antcObject * 256 + 1,
	antsWeapon = antcObject * 256 + 2,
	antsAirplane = antcObject * 256 + 3,
	antsVessel = antcObject * 256 + 4,
	antsTrain = antcObject * 256 + 5,
	antsVehicle = antcObject * 256 + 6,
	antsMythical = antcObject * 256 + 7,
	antsSporting = antcObject * 256 + 8,
	antsNature = antcObject * 256 + 9,

	antsMiscAbstract = antcAbstract * 256 + 0,
	antsFigure = antcAbstract * 256 + 1,
	antsSleeve = antcAbstract * 256 + 2,
	antsBracelet = antcAbstract * 256 + 3,
	antsAnklet = antcAbstract * 256 + 4,
	antsNecklace = antcAbstract * 256 + 5,
	antsShirt = antcAbstract * 256 + 6,
	antsBodyBand = antcAbstract * 256 + 7,
	antsHeadBand = antcAbstract * 256 + 8,

	antsMiscSymbol = antcSymbol * 256 + 0,
	antsNational = antcSymbol * 256 + 1,
	antsPolitical = antcSymbol * 256 + 2,
	antsMilitary = antcSymbol * 256 + 3,
	antsFraternal = antcSymbol * 256 + 4,
	antsProfessional = antcSymbol * 256 + 5,
	antsGang = antcSymbol * 256 + 6,

	antsMisc = antcOther * 256 + 0,
	antsWording = antcOther * 256 + 1,
	antsFreeform = antcOther * 256 + 2,

	antsUnspecified = antcUnspecified * 256 + 0
} ANTattooSubclass;

N_DECLARE_TYPE(ANTattooSubclass)

struct ANSmt_
{
	ANSmtSource source;
	ANTattooClass tattooClass;
	ANTattooSubclass tattooSubclass;
	HNString hDescription;
};
#ifndef AN_TYPE_10_RECORD_HPP_INCLUDED
typedef struct ANSmt_ ANSmt;
#endif

N_DECLARE_TYPE(ANSmt)

typedef enum ANColor_
{
	ancBlack = 1,
	ancBrown = 2,
	ancGray = 3,
	ancBlue = 4,
	ancGreen = 5,
	ancOrange = 6,
	ancPurple = 7,
	ancRed = 8,
	ancYellow = 9,
	ancWhite = 10,
	ancMultiColored = 11,
	ancOutlined = 12
} ANColor;

N_DECLARE_TYPE(ANColor)

struct ANImageSourceType_
{
	BdifImageSourceType value;
	HNString hVendorValue;
};
#ifndef AN_TYPE_10_RECORD_HPP_INCLUDED
typedef struct ANImageSourceType_ ANImageSourceType;
#endif

N_DECLARE_TYPE(ANImageSourceType)

struct ANPoseAngles_
{
	NInt yaw;
	NInt pitch;
	NInt roll;
	NInt yawUncertainty;
	NInt pitchUncertainty;
	NInt rollUncertainty;
};
#ifndef AN_TYPE_10_RECORD_HPP_INCLUDED
typedef struct ANPoseAngles_ ANPoseAngles;
#endif

N_DECLARE_TYPE(ANPoseAngles)

struct ANHairColor_
{
	BdifHairColor value;
	BdifHairColor baldValue;
};
#ifndef AN_TYPE_10_RECORD_HPP_INCLUDED
typedef struct ANHairColor_ ANHairColor;
#endif

N_DECLARE_TYPE(ANHairColor)

typedef enum ANFacePosition_
{
	anfpUnspecified = 0,
	anfpHeadAndShoulders = 1,
	anfpHead = 2,
	anfpFace = 3,
	anfpNonFrontalHead = 4,
	anfpPartialFace = 5
} ANFacePosition;

N_DECLARE_TYPE(ANFacePosition)

struct ANFaceImageBoundingBox_
{
	NUInt leftHorzOffset;
	NUInt rightHorzOffset;
	NUInt topVertOffset;
	NUInt bottomVertOffset;
	ANFacePosition facePosition;
};
#ifndef AN_TYPE_10_RECORD_HPP_INCLUDED
typedef struct ANFaceImageBoundingBox_ ANFaceImageBoundingBox;
#endif

N_DECLARE_TYPE(ANFaceImageBoundingBox)

typedef enum ANDistortionCode_
{
	andcBarrel = 1,
	andcInflated = 2,
	andcPincushion = 3
} ANDistortionCode;

N_DECLARE_TYPE(ANDistortionCode)

typedef enum ANDistortionMeasurementCode_
{
	andmcEstimated = 1,
	andmcCalculated = 2
} ANDistortionMeasurementCode;

N_DECLARE_TYPE(ANDistortionMeasurementCode)
	
typedef enum ANDistortiSeverityCode_
{
	andscMild = 1,
	andscModerate = 2,
	andscSevere = 3,
} ANDistortionSeverityCode;

N_DECLARE_TYPE(ANDistortionSeverityCode)

struct ANDistortion_
{
	ANDistortionCode code;
	ANDistortionMeasurementCode measurementCode;
	ANDistortionSeverityCode severityCode;
};
#ifndef AN_TYPE_10_RECORD_HPP_INCLUDED
typedef struct ANDistortion_ ANDistortion;
#endif

N_DECLARE_TYPE(ANDistortion)

typedef enum ANLightingArtifact_
{
	anlaFaceShadows = 1,
	anlaHotSpots = 2,
	anlaReflectionsFromEyeGlasses = 3,
} ANLightingArtifact;

N_DECLARE_TYPE(ANLightingArtifact)

typedef enum ANTieredMarkupCollection_
{
	antmcUnspecified = 0,
	antmcEyeCenters = 1,
	antmcEyesMounth = 2,
	antmcEyesNoseMouth = 3,
	antmcEyesNoseMouthHead = 4,
	antmcFeaturePointsAndFaceCountours = 5
} ANTieredMarkupCollection;

N_DECLARE_TYPE(ANTieredMarkupCollection)

typedef enum ANFeatureContourCode_
{
	anfccEyeTop = 1,
	anfccEyeBottom = 2,
	anfccUpperLipTop = 3,
	anfccUpperLipBottom = 4,
	anfccLowerLipTop = 5,
	anfccLowerLipBottom = 6,
	anfccRightNostril = 7,
	anfccLeftNostril = 8,
	anfccLeftEyebrow = 9,
	anfccRightEyebrow = 10,
	anfccChin = 11,
	anfccFaceOutline = 12
} ANFeatureContourCode;

N_DECLARE_TYPE(ANFeatureContourCode)

struct ANPatternedInjury_
{
	HNString hCode;
	HNString hDescriptiveText;
};
#ifndef AN_TYPE_10_RECORD_HPP_INCLUDED
typedef struct ANPatternedInjury_ ANPatternedInjury;
#endif

N_DECLARE_TYPE(ANPatternedInjury)

typedef enum ANCheiloscopicCharacterizationCode_
{
	ancccUnspecified                      = 0x000000,
	ancccLeftVerticalGroove               = 0x000001,
	ancccLeftPartialLengthVerticalGroove  = 0x000002,
	ancccLeftBranchedGroove               = 0x000004,
	ancccLeftIntersectedGroove            = 0x000008,
	ancccLeftReticularGroove              = 0x000010,
	ancccLeftOtherPattern                 = 0x000020,
	ancccCenterLipindicator               = 0x000100,
	ancccRightVerticalGroove              = 0x001000,
	ancccRightPartialLengthVerticalGroove = 0x002000,
	ancccRightBranchedGroove              = 0x004000,
	ancccRightIntersectedGroove           = 0x008000,
	ancccRightReticularGroove             = 0x010000,
	ancccRightOtherPattern                = 0x020000
} ANCheiloscopicCharacterizationCode;

N_DECLARE_TYPE(ANCheiloscopicCharacterizationCode)

typedef enum ANLPContactLine_
{
	anlclUnspecified = 0,
	anlclLinearContactLine = 1,
	anlclCurvedContactLine = 2,
	anlclMixedShapeContactLine = 3
} ANLPContactLine;

N_DECLARE_TYPE(ANLPContactLine)

typedef enum ANLipPathology_
{
	anlpUnspecified                       = 0x000000,
	anlpHerpeticLesions                   = 0x000001,
	anlpScars                             = 0x000002,
	anlpSevereCracking                    = 0x000004,
	anlpBloodVaricosities                 = 0x000008,
	anlpIntenseWhirls                     = 0x000010,
	anlpMole                              = 0x000020,
	anlpCutsAndScabs                      = 0x000040,
	anlpCleftLipUnilateralIncompleteLeft  = 0x000080,
	anlpCleftLipUnilateralIncompleteRight = 0x000100,
	anlpCleftLipUnilateralCompleteLeft    = 0x000200,
	anlpCleftLipUnilateralCompleteRight   = 0x000400,
	anlpCleftLipBilateralIncomplete       = 0x000800,
	anlpCleftLipBilateralComplete         = 0x001000,
	anlpPiercingUpperLip                  = 0x002000,
	anlpPiercingLowerLip                  = 0x004000,
	anlpTattooUpperLip                    = 0x008000,
	anlpTattooLowerLip                    = 0x010000,
	anlpOther                             = 0x800000
} ANLipPathology;

N_DECLARE_TYPE(ANLipPathology)

typedef enum ANLPSurface_
{
	anlpsUnspecified            = 0x0000,
	anlpsGlassPhotographicMount = 0x0001,
	anlpsHumanSkin              = 0x0002,
	anlpsClothing               = 0x0004,
	anlpsOther                  = 0x0800
} ANLPSurface;

N_DECLARE_TYPE(ANLPSurface)

typedef enum ANLPMedium_
{
	anlpmUnspecified = 0,
	anlpmLipstick = 1,
	anlpmMoisture = 2,
	anlpmFoodResidue = 3,
	anlpmOther = 9
} ANLPMedium;

N_DECLARE_TYPE(ANLPMedium)

struct ANCheiloscopicData_
{
	NInt lpWidth;
	NInt lpHeight;
	NInt philtrumWidth;
	NInt philtrumHeight;
	ANCheiloscopicCharacterizationCode upperLpCharacterization;
	ANCheiloscopicCharacterizationCode lowerLpCharacterization;
	ANLPContactLine lpContactLine;
	HNString hLpCharacterizationDescription;
	ANLipPathology lipPathologies;
	HNString hLipPathologiesDescription;
	ANLPSurface lpSurface;
	HNString hLpSurfaceDescription;
	ANLPMedium lpMedium;
	HNString hLpMediumDescription;
	HNString hFacialHairDescription;
	HNString hLipPositionDescription;
	HNString hLpAdditionalDescription;
	HNString hLpComparisonDescription;
};
#ifndef AN_TYPE_10_RECORD_HPP_INCLUDED
typedef struct ANCheiloscopicData_ ANCheiloscopicData;
#endif

N_DECLARE_TYPE(ANCheiloscopicData)

typedef enum ANDentalImageCode_
{
	andicExtraOralFrontalNaturalState = 1,
	andicExtraOralFrontalWithIncisionsPresent = 2,
	andicExtraOralFrontalLipsRetracted = 3,
	andicExtraOralObliqueLeft = 4,
	andicExtraOralObliqueRight = 5,
	andicExtraOralProfileLeft = 6,
	andicExtraOralProfileRight = 7,
	andicIntraOralFrontalJawsOpenUpperTeeth = 8,
	andicIntraOralFrontalJawsOpenLowerTeeth = 9,
	andicIntraOralFrontalJawsOpenBothTeeth = 10,
	andicIntraOralFacialUpperRightTeeth = 11,
	andicIntraOralFacialUpperLeftTeeth = 12,
	andicIntraOralFacialLowerRightTeeth = 13,
	andicIntraOralFacialLowerLeftTeeth = 14,
	andicIntraOralFacialBothRightTeeth = 15,
	andicIntraOralFacialBothLeftTeeth = 16,
	andicIntraOralLingualUpperRightTeeth = 17,
	andicIntraOralLingualUpperLeftTeeth = 18,
	andicIntraOralLingualLowerRightTeeth = 19,
	andicIntraOralLingualLowerLeftTeeth = 20,
	andicIntraOralLingualBothRightTeeth = 21,
	andicIntraOralLingualBothLeftTeeth = 22,
	andicIntraOralLingualUpperFrontTeeth = 23,
	andicIntraOralLingualLowerFrontTeeth = 24,
	andicIntraOralOcclusalFullUpperTeeth = 25,
	andicIntraOralOcclusalFullLowerTeeth = 26,
	andicIntraOralOcclusalUpperRightTeeth = 27,
	andicIntraOralOcclusalUpperLeftTeeth = 28,
	andicIntraOralOcclusalLowerRightTeeth = 29,
	andicIntraOralOcclusalLowerLeftTeeth = 30,
	andicIntraOralOcclusalUpperFrontTeeth = 31,
	andicIntraOralOcclusalLowerFrontTeeth = 32,
	andicIntraOralPalate = 33,
	andicIntraOralTongueUpperSurface = 34,
	andicIntraOralTongueLowerArea = 35,
	andicIntraOralCheekRightInterior = 36,
	andicIntraOralCheekLeftInterior = 37,
	andicIntraOralPharynx = 38,
	andicIntraOralLipsInsideUpper = 39,
	andicIntraOralLipsInsideLower = 40
} ANDentalImageCode;

N_DECLARE_TYPE(ANDentalImageCode)

struct ANDentalVisualData_
{
	ANDentalImageCode imageViewCode;
	HNString hAdditionalDescription;
	HNString hComparisonDescription;
};
#ifndef AN_TYPE_10_RECORD_HPP_INCLUDED
typedef struct ANDentalVisualData_ ANDentalVisualData;
#endif

N_DECLARE_TYPE(ANDentalVisualData)


NResult N_API ANSmtCreateN(ANSmtSource source, ANTattooClass tattooClass, ANTattooSubclass tattooSubclass, HNString hDescription, struct ANSmt_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSmtCreateA(ANSmtSource source, ANTattooClass tattooClass, ANTattooSubclass tattooSubclass, const NAChar * szDescription, struct ANSmt_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSmtCreateW(ANSmtSource source, ANTattooClass tattooClass, ANTattooSubclass tattooSubclass, const NWChar * szDescription, struct ANSmt_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSmtCreate(ANSmtSource source, ANTattooClass tattooClass, ANTattooSubclass tattooSubclass, const NChar * szDescription, ANSmt * pValue);
#endif
#define ANSmtCreate N_FUNC_AW(ANSmtCreate)

NResult N_API ANSmtDispose(struct ANSmt_ * pValue);
NResult N_API ANSmtCopy(const struct ANSmt_ * pSrcValue, struct ANSmt_ * pDstValue);
NResult N_API ANSmtSet(const struct ANSmt_ * pSrcValue, struct ANSmt_ * pDstValue);

NResult N_API ANImageSourceTypeCreateN(BdifImageSourceType value, HNString hVendorValue, struct ANImageSourceType_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANImageSourceTypeCreateA(BdifImageSourceType value, const NAChar * szVendorValue, struct ANImageSourceType_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANImageSourceTypeCreateW(BdifImageSourceType value, const NWChar * szVendorValue, struct ANImageSourceType_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANImageSourceTypeCreate(BdifImageSourceType value, const NChar * szVendorValue, ANImageSourceType * pValue);
#endif
#define ANImageSourceTypeCreate N_FUNC_AW(ANImageSourceTypeCreate)

NResult N_API ANImageSourceTypeDispose(struct ANImageSourceType_ * pValue);
NResult N_API ANImageSourceTypeCopy(const struct ANImageSourceType_ * pSrcValue, struct ANImageSourceType_ * pDstValue);
NResult N_API ANImageSourceTypeSet(const struct ANImageSourceType_ * pSrcValue, struct ANImageSourceType_ * pDstValue);


NResult N_API ANPatternedInjuryCreateN(HNString hCode, HNString hDescriptiveText, struct ANPatternedInjury_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANPatternedInjuryCreateA(const NAChar * szCode, const NAChar * szDescriptiveText, struct ANPatternedInjury_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANPatternedInjuryCreateW(const NWChar * szCode, const NWChar * szDescriptiveText, struct ANPatternedInjury_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANPatternedInjuryCreate(const NWChar * szCode, const NChar * szDescriptiveText, ANPatternedInjury * pValue);
#endif
#define ANPatternedInjuryCreate N_FUNC_AW(ANPatternedInjuryCreate)

NResult N_API ANPatternedInjuryDispose(struct ANPatternedInjury_ * pValue);
NResult N_API ANPatternedInjuryCopy(const struct ANPatternedInjury_ * pSrcValue, struct ANPatternedInjury_ * pDstValue);
NResult N_API ANPatternedInjurySet(const struct ANPatternedInjury_ * pSrcValue, struct ANPatternedInjury_ * pDstValue);


NResult N_API ANCheiloscopicDataCreateN(NInt lpWidth, NInt lpHeight, NInt philtrumWidth, NInt philtrumHeight, ANCheiloscopicCharacterizationCode upperLpCharacterization, ANCheiloscopicCharacterizationCode lowerLpCharacterization, 
										ANLPContactLine lpContactLine, HNString hLpCharacterizationDescription, ANLipPathology lipPathologies, HNString hLipPathologiesDescription, ANLPSurface lpSurface, HNString hLpSurfaceDescription,
										ANLPMedium lpMedium, HNString hLpMediumDescription, HNString hFacialHairDescription, HNString hLipPositionDescription, HNString hLpAdditionalDescription, HNString hLpComparisonDescription, struct ANCheiloscopicData_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANCheiloscopicDataCreateA(NInt lpWidth, NInt lpHeight, NInt philtrumWidth, NInt philtrumHeight, ANCheiloscopicCharacterizationCode upperLpCharacterization, ANCheiloscopicCharacterizationCode lowerLpCharacterization,
										ANLPContactLine lpContactLine, const NAChar * szLpCharacterizationDescription, ANLipPathology lipPathologies, const NAChar * szLipPathologiesDescription, ANLPSurface lpSurface, const NAChar * szLpSurfaceDescription, 
										ANLPMedium lpMedium, const NAChar * szLpMediumDescription, const NAChar * szFacialHairDescription, const NAChar * szLipPositionDescription, const NAChar * szLpAdditionalDescription, const NAChar * szLpComparisonDescription, struct ANCheiloscopicData_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANCheiloscopicDataCreateW(NInt lpWidth, NInt lpHeight, NInt philtrumWidth, NInt philtrumHeight, ANCheiloscopicCharacterizationCode upperLpCharacterization, ANCheiloscopicCharacterizationCode lowerLpCharacterization,
										ANLPContactLine lpContactLine, const NWChar * szLpCharacterizationDescription, ANLipPathology lipPathologies, const NWChar * szLipPathologiesDescription, ANLPSurface lpSurface, const NWChar * szLpSurfaceDescription, 
										ANLPMedium lpMedium, const NWChar * szLpMediumDescription, const NWChar * szFacialHairDescription, const NWChar * szLipPositionDescription, const NWChar * szLpAdditionalDescription, const NWChar * szLpComparisonDescription, struct ANCheiloscopicData_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANCheiloscopicDataCreate(NInt lpWidth, NInt lpHeight, NInt philtrumWidth, NInt philtrumHeight, ANCheiloscopicCharacterizationCode upperLpCharacterization, ANCheiloscopicCharacterizationCode lowerLpCharacterization,
										ANLPContactLine lpContactLine, const NChar * szLpCharacterizationDescription, ANLipPathology lipPathologies, const NChar * szLipPathologiesDescription, ANLPSurface lpSurface, const NChar * szLpSurfaceDescription, 
										ANLPMedium lpMedium, const NChar * szLpMediumDescription, const NChar * szFacialHairDescription, const NChar * szLipPositionDescription, const NChar * szLpAdditionalDescription, const NChar * szLpComparisonDescription, ANCheiloscopicData * pValue);
#endif
#define ANCheiloscopicDataCreate N_FUNC_AW(ANCheiloscopicDataCreate)

NResult N_API ANCheiloscopicDataDispose(struct ANCheiloscopicData_ * pValue);
NResult N_API ANCheiloscopicDataCopy(const struct ANCheiloscopicData_ * pSrcValue, struct ANCheiloscopicData_ * pDstValue);
NResult N_API ANCheiloscopicDataSet(const struct ANCheiloscopicData_ * pSrcValue, struct ANCheiloscopicData_ * pDstValue);


NResult N_API ANDentalVisualDataCreateN(ANDentalImageCode imageViewCode, HNString hAdditionalDescription, HNString hComparisonDescription, struct ANDentalVisualData_ * pValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANDentalVisualDataCreateA(ANDentalImageCode imageViewCode, const NAChar * szAdditionalDescription, const NAChar * szComparisonDescription, struct ANDentalVisualData_ * pValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANDentalVisualDataCreateW(ANDentalImageCode imageViewCode, const NWChar * szAdditionalDescription, const NWChar * szComparisonDescription, struct ANDentalVisualData_ * pValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANDentalVisualDataCreate(ANDentalImageCode imageViewCode, const NChar * szAdditionalDescription, const NChar * szComparisonDescription, ANDentalVisualData * pValue);
#endif
#define ANDentalVisualDataCreate N_FUNC_AW(ANDentalVisualDataCreate)

NResult N_API ANDentalVisualDataDispose(struct ANDentalVisualData_ * pValue);
NResult N_API ANDentalVisualDataCopy(const struct ANDentalVisualData_ * pSrcValue, struct ANDentalVisualData_ * pDstValue);
NResult N_API ANDentalVisualDataSet(const struct ANDentalVisualData_ * pSrcValue, struct ANDentalVisualData_ * pDstValue);


NResult N_API ANType10RecordGetPhysicalPhotoCharacteristicCount(HANType10Record hRecord, NInt * pValue);

NResult N_API ANType10RecordGetPhysicalPhotoCharacteristicN(HANType10Record hRecord, NInt index, HNString * phValue);

NResult N_API ANType10RecordSetPhysicalPhotoCharacteristicN(HANType10Record hRecord, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordSetPhysicalPhotoCharacteristicA(HANType10Record hRecord, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordSetPhysicalPhotoCharacteristicW(HANType10Record hRecord, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordSetPhysicalPhotoCharacteristic(HANType10Record hRecord, NInt index, const NChar * szValue);
#endif
#define ANType10RecordSetPhysicalPhotoCharacteristic N_FUNC_AW(ANType10RecordSetPhysicalPhotoCharacteristic)

NResult N_API ANType10RecordAddPhysicalPhotoCharacteristicExN(HANType10Record hRecord, HNString hValue, NInt * pIndex);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordAddPhysicalPhotoCharacteristicExA(HANType10Record hRecord, const NAChar * szValue, NInt * pIndex);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordAddPhysicalPhotoCharacteristicExW(HANType10Record hRecord, const NWChar * szValue, NInt * pIndex);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordAddPhysicalPhotoCharacteristicEx(HANType10Record hRecord, const NChar * szValue, NInt * pIndex);
#endif
#define ANType10RecordAddPhysicalPhotoCharacteristicEx N_FUNC_AW(ANType10RecordAddPhysicalPhotoCharacteristicEx)

NResult N_API ANType10RecordInsertPhysicalPhotoCharacteristicN(HANType10Record hRecord, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordInsertPhysicalPhotoCharacteristicA(HANType10Record hRecord, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordInsertPhysicalPhotoCharacteristicW(HANType10Record hRecord, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordInsertPhysicalPhotoCharacteristic(HANType10Record hRecord, NInt index, const NChar * szValue);
#endif
#define ANType10RecordInsertPhysicalPhotoCharacteristic N_FUNC_AW(ANType10RecordInsertPhysicalPhotoCharacteristic)

NResult N_API ANType10RecordRemovePhysicalPhotoCharacteristicAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearPhysicalPhotoCharacteristics(HANType10Record hRecord);

NResult N_API ANType10RecordGetOtherPhotoCharacteristicCount(HANType10Record hRecord, NInt * pValue);

NResult N_API ANType10RecordGetOtherPhotoCharacteristicN(HANType10Record hRecord, NInt index, HNString * phValue);

NResult N_API ANType10RecordSetOtherPhotoCharacteristicN(HANType10Record hRecord, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordSetOtherPhotoCharacteristicA(HANType10Record hRecord, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordSetOtherPhotoCharacteristicW(HANType10Record hRecord, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordSetOtherPhotoCharacteristic(HANType10Record hRecord, NInt index, const NChar * szValue);
#endif
#define ANType10RecordSetOtherPhotoCharacteristic N_FUNC_AW(ANType10RecordSetOtherPhotoCharacteristic)

NResult N_API ANType10RecordAddOtherPhotoCharacteristicExN(HANType10Record hRecord, HNString hValue, NInt * pIndex);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordAddOtherPhotoCharacteristicExA(HANType10Record hRecord, const NAChar * szValue, NInt * pIndex);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordAddOtherPhotoCharacteristicExW(HANType10Record hRecord, const NWChar * szValue, NInt * pIndex);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordAddOtherPhotoCharacteristicEx(HANType10Record hRecord, const NChar * szValue, NInt * pIndex);
#endif
#define ANType10RecordAddOtherPhotoCharacteristicEx N_FUNC_AW(ANType10RecordAddOtherPhotoCharacteristicEx)

NResult N_API ANType10RecordInsertOtherPhotoCharacteristicN(HANType10Record hRecord, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordInsertOtherPhotoCharacteristicA(HANType10Record hRecord, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordInsertOtherPhotoCharacteristicW(HANType10Record hRecord, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordInsertOtherPhotoCharacteristic(HANType10Record hRecord, NInt index, const NChar * szValue);
#endif
#define ANType10RecordInsertOtherPhotoCharacteristic N_FUNC_AW(ANType10RecordInsertOtherPhotoCharacteristic)

NResult N_API ANType10RecordRemoveOtherPhotoCharacteristicAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearOtherPhotoCharacteristics(HANType10Record hRecord);

NResult N_API ANType10RecordGetSubjectQualityScoreCount(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetSubjectQualityScore(HANType10Record hRecord, NInt index, struct ANQualityMetric_ * pValue);
NResult N_API ANType10RecordGetSubjectQualityScores(HANType10Record hRecord, struct ANQualityMetric_ * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetSubjectQualityScore(HANType10Record hRecord, NInt index, const struct ANQualityMetric_ * pValue);
NResult N_API ANType10RecordAddSubjectQualityScoreEx(HANType10Record hRecord, const struct ANQualityMetric_ * pValue, NInt * pIndex);
NResult N_API ANType10RecordInsertSubjectQualityScore(HANType10Record hRecord, NInt index, const struct ANQualityMetric_ * pValue);
NResult N_API ANType10RecordRemoveSubjectQualityScoreAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearSubjectQualityScores(HANType10Record hRecord);

NResult N_API ANType10RecordGetSubjectFacialCharacteristicCount(HANType10Record hRecord, NInt * pValue);

NResult N_API ANType10RecordGetSubjectFacialCharacteristicN(HANType10Record hRecord, NInt index, HNString * phValue);

NResult N_API ANType10RecordSetSubjectFacialCharacteristicN(HANType10Record hRecord, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordSetSubjectFacialCharacteristicA(HANType10Record hRecord, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordSetSubjectFacialCharacteristicW(HANType10Record hRecord, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordSetSubjectFacialCharacteristic(HANType10Record hRecord, NInt index, const NChar * szValue);
#endif
#define ANType10RecordSetSubjectFacialCharacteristic N_FUNC_AW(ANType10RecordSetSubjectFacialCharacteristic)

NResult N_API ANType10RecordAddSubjectFacialCharacteristicExN(HANType10Record hRecord, HNString hValue, NInt * pIndex);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordAddSubjectFacialCharacteristicExA(HANType10Record hRecord, const NAChar * szValue, NInt * pIndex);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordAddSubjectFacialCharacteristicExW(HANType10Record hRecord, const NWChar * szValue, NInt * pIndex);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordAddSubjectFacialCharacteristicEx(HANType10Record hRecord, const NChar * szValue, NInt * pIndex);
#endif
#define ANType10RecordAddSubjectFacialCharacteristicEx N_FUNC_AW(ANType10RecordAddSubjectFacialCharacteristicEx)

NResult N_API ANType10RecordInsertSubjectFacialCharacteristicN(HANType10Record hRecord, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordInsertSubjectFacialCharacteristicA(HANType10Record hRecord, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordInsertSubjectFacialCharacteristicW(HANType10Record hRecord, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordInsertSubjectFacialCharacteristic(HANType10Record hRecord, NInt index, const NChar * szValue);
#endif
#define ANType10RecordInsertSubjectFacialCharacteristic N_FUNC_AW(ANType10RecordInsertSubjectFacialCharacteristic)

NResult N_API ANType10RecordRemoveSubjectFacialCharacteristicAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearSubjectFacialCharacteristics(HANType10Record hRecord);

NResult N_API ANType10RecordGetFacialFeaturePointCount(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetFacialFeaturePoint(HANType10Record hRecord, NInt index, struct BdifFaceFeaturePoint_ * pValue);
NResult N_API ANType10RecordGetFacialFeaturePointWithCodeN(HANType10Record hRecord, NInt index, struct BdifFaceFeaturePoint_ * pValue, HNString * phCode);
NResult N_API ANType10RecordGetFacialFeaturePoints(HANType10Record hRecord, struct BdifFaceFeaturePoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetFacialFeaturePoint(HANType10Record hRecord, NInt index, const struct BdifFaceFeaturePoint_ * pValue);
NResult N_API ANType10RecordAddFacialFeaturePointEx(HANType10Record hRecord, const struct BdifFaceFeaturePoint_ * pValue, NInt * pIndex);
NResult N_API ANType10RecordInsertFacialFeaturePoint(HANType10Record hRecord, NInt index, const struct BdifFaceFeaturePoint_ * pValue);
NResult N_API ANType10RecordRemoveFacialFeaturePointAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearFacialFeaturePoints(HANType10Record hRecord);

NResult N_API ANType10RecordGetNcicDesignationCodeCount(HANType10Record hRecord, NInt * pValue);

NResult N_API ANType10RecordGetNcicDesignationCodeN(HANType10Record hRecord, NInt index, HNString * phValue);

NResult N_API ANType10RecordSetNcicDesignationCodeN(HANType10Record hRecord, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordSetNcicDesignationCodeA(HANType10Record hRecord, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordSetNcicDesignationCodeW(HANType10Record hRecord, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordSetNcicDesignationCode(HANType10Record hRecord, NInt index, const NChar * szValue);
#endif
#define ANType10RecordSetNcicDesignationCode N_FUNC_AW(ANType10RecordSetNcicDesignationCode)

NResult N_API ANType10RecordAddNcicDesignationCodeExN(HANType10Record hRecord, HNString hValue, NInt * pIndex);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordAddNcicDesignationCodeExA(HANType10Record hRecord, const NAChar * szValue, NInt * pIndex);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordAddNcicDesignationCodeExW(HANType10Record hRecord, const NWChar * szValue, NInt * pIndex);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordAddNcicDesignationCodeEx(HANType10Record hRecord, const NChar * szValue, NInt * pIndex);
#endif
#define ANType10RecordAddNcicDesignationCodeEx N_FUNC_AW(ANType10RecordAddNcicDesignationCodeEx);

NResult N_API ANType10RecordInsertNcicDesignationCodeN(HANType10Record hRecord, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordInsertNcicDesignationCodeA(HANType10Record hRecord, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordInsertNcicDesignationCodeW(HANType10Record hRecord, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordInsertNcicDesignationCode(HANType10Record hRecord, NInt index, const NChar * szValue);
#endif
#define ANType10RecordInsertNcicDesignationCode N_FUNC_AW(ANType10RecordInsertNcicDesignationCode)

NResult N_API ANType10RecordRemoveNcicDesignationCodeAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearNcicDesignationCodes(HANType10Record hRecord);

NResult N_API ANType10RecordGetSmtCount(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetSmt(HANType10Record hRecord, NInt index, struct ANSmt_ * pValue);
NResult N_API ANType10RecordSetSmtEx(HANType10Record hRecord, NInt index, const struct ANSmt_ * pValue);
NResult N_API ANType10RecordAddSmt(HANType10Record hRecord, const struct ANSmt_ * pValue, NInt * pIndex);
NResult N_API ANType10RecordInsertSmtEx(HANType10Record hRecord, NInt index, const struct ANSmt_ * pValue);
NResult N_API ANType10RecordRemoveSmtAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearSmts(HANType10Record hRecord);

NResult N_API ANType10RecordGetSmtColorCount(HANType10Record hRecord, NInt smtIndex, NInt * pValue);
NResult N_API ANType10RecordGetSmtColor(HANType10Record hRecord, NInt smtIndex, NInt index, ANColor * pValue);
NResult N_API ANType10RecordGetSmtColors(HANType10Record hRecord, NInt smtIndex, ANColor * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetSmtColor(HANType10Record hRecord, NInt smtIndex, NInt index, ANColor value);
NResult N_API ANType10RecordAddSmtColorEx(HANType10Record hRecord, NInt smtIndex, ANColor value, NInt * pIndex);
NResult N_API ANType10RecordInsertSmtColor(HANType10Record hRecord, NInt smtIndex, NInt index, ANColor value);
NResult N_API ANType10RecordRemoveSmtColorAt(HANType10Record hRecord, NInt smtIndex, NInt index);
NResult N_API ANType10RecordClearSmtColors(HANType10Record hRecord, NInt smtIndex);

NResult N_API ANType10RecordGetImageType(HANType10Record hRecord, ANImageType * pValue);
NResult N_API ANType10RecordSetImageType(HANType10Record hRecord, ANImageType value);
NResult N_API ANType10RecordGetSubjectAcquisitionProfile(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordSetSubjectAcquisitionProfile(HANType10Record hRecord, NInt value);
NResult N_API ANType10RecordGetSubjectPose(HANType10Record hRecord, ANSubjectPose * pValue);
NResult N_API ANType10RecordSetSubjectPose(HANType10Record hRecord, ANSubjectPose value);
NResult N_API ANType10RecordGetPoseOffsetAngle(HANType10Record hRecord, NInt * pValue, NBool * pHasValue);
NResult N_API ANType10RecordSetPoseOffsetAngle(HANType10Record hRecord, const NInt * pValue);
NResult N_API ANType10RecordGetPhotoAttributes(HANType10Record hRecord, BdifFaceProperties * pValue);
NResult N_API ANType10RecordSetPhotoAttributes(HANType10Record hRecord, BdifFaceProperties value);
NResult N_API ANType10RecordGetPhotoAcquisitionSourceEx(HANType10Record hRecord, struct ANImageSourceType_ * pValue, NBool * pHasValue);
NResult N_API ANType10RecordGetPhotoAcquisitionSource(HANType10Record hRecord, BdifImageSourceType * pValue);

NResult N_API ANType10RecordGetVendorPhotoAcquisitionSourceN(HANType10Record hRecord, HNString * phValue);

NResult N_API ANType10RecordSetPhotoAcquisitionSourceEx(HANType10Record hRecord, const struct ANImageSourceType_ * pValue);

NResult N_API ANType10RecordSetPhotoAcquisitionSourceN(HANType10Record hRecord, BdifImageSourceType value, HNString hVendorValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordSetPhotoAcquisitionSourceA(HANType10Record hRecord, BdifImageSourceType value, const NAChar * szVendorValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordSetPhotoAcquisitionSourceW(HANType10Record hRecord, BdifImageSourceType value, const NWChar * szVendorValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordSetPhotoAcquisitionSource(HANType10Record hRecord, BdifImageSourceType value, const NChar * szVendorValue);
#endif
#define ANType10RecordSetVendorPhotoAcquisitionSource N_FUNC_AW(ANType10RecordSetVendorPhotoAcquisitionSource)

NResult N_API ANType10RecordGetSubjectPoseAnglesEx(HANType10Record hRecord, struct ANPoseAngles_ * pValue, NBool * pHasValue);
NResult N_API ANType10RecordGetSubjectPoseAnglesYaw(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetSubjectPoseAnglesPitch(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetSubjectPoseAnglesRoll(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetSubjectPoseAnglesYawUncertainty(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetSubjectPoseAnglesPitchUncertainty(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetSubjectPoseAnglesRollUncertainty(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetSubjectPoseAngles(HANType10Record hRecord, NInt * pYaw, NInt * pPitch, NInt * pRoll, NInt * pYawUncertainty, NInt * pPitchUncertainty, NInt * pRollUncertainty);
NResult N_API ANType10RecordSetSubjectPoseAnglesEx(HANType10Record hRecord, const struct ANPoseAngles_ * pValue);
NResult N_API ANType10RecordSetSubjectPoseAngles(HANType10Record hRecord, NInt yaw, NInt pitch, NInt roll, NInt yawUncertainty, NInt pitchUncertainty, NInt rollUncertainty);

NResult N_API ANType10RecordGetSubjectFacialExpressionEx(HANType10Record hRecord, BdifFaceExpressionBitMask * pValue);
NResult N_API ANType10RecordSetSubjectFacialExpressionEx(HANType10Record hRecord, BdifFaceExpressionBitMask value);

NResult N_API ANType10RecordGetSubjectFacialAttributes(HANType10Record hRecord, BdifFaceProperties * pValue);
NResult N_API ANType10RecordSetSubjectFacialAttributes(HANType10Record hRecord, BdifFaceProperties value);
NResult N_API ANType10RecordGetSubjectEyeColor(HANType10Record hRecord, BdifEyeColor * pValue);
NResult N_API ANType10RecordSetSubjectEyeColor(HANType10Record hRecord, BdifEyeColor value);
NResult N_API ANType10RecordGetSubjectHairColorEx(HANType10Record hRecord, struct ANHairColor_ * pValue, NBool * pHasValue);
NResult N_API ANType10RecordGetSubjectHairColor(HANType10Record hRecord, BdifHairColor * pValue);
NResult N_API ANType10RecordGetBaldSubjectHairColor(HANType10Record hRecord, BdifHairColor * pValue);
NResult N_API ANType10RecordSetSubjectHairColorEx(HANType10Record hRecord, const struct ANHairColor_ * pValue);
NResult N_API ANType10RecordSetSubjectHairColor(HANType10Record hRecord, BdifHairColor value, BdifHairColor baldValue);
NResult N_API ANType10RecordGetSmtSize(HANType10Record hRecord, struct NSize_ * pValue, NBool * pHasValue);
NResult N_API ANType10RecordSetSmtSize(HANType10Record hRecord, const struct NSize_ * pValue);
NResult N_API ANType10RecordGetFaceImageBoundingBox(HANType10Record hRecord, struct ANFaceImageBoundingBox_ * pValue, NBool * pHasValue);
NResult N_API ANType10RecordSetFaceImageBoundingBox(HANRecord hRecord, const struct ANFaceImageBoundingBox_ * pValue);
NResult N_API ANType10RecordGetImagePathBoundaryCode(HANType10Record hRecord, ANBoundaryCode * pValue);
NResult N_API ANType10RecordSetImagePathBoundaryCode(HANType10Record hRecord, ANBoundaryCode value);

NResult N_API ANType10RecordGetImagePathVertexCount(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetImagePathVertex(HANType10Record hRecord, NInt index, struct NPoint_ * pValue);
NResult N_API ANType10RecordGetImagePathVertices(HANType10Record hRecord, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetImagePathVertex(HANType10Record hRecord, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType10RecordAddImagePathVertex(HANType10Record hRecord, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API ANType10RecordInsertImagePathVertex(HANType10Record hRecord, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType10RecordRemoveImagePathVertexAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearImagePathVertices(HANType10Record hRecord);

NResult N_API ANType10RecordGetDistortion(HANType10Record hRecord, struct ANDistortion_ * pValue, NBool * pHasValue);
NResult N_API ANType10RecordSetDistortion(HANRecord hRecord, const struct ANDistortion_ * pValue);

NResult N_API ANType10RecordGetLightingArtifactCount(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetLightingArtifact(HANType10Record hRecord, NInt index, ANLightingArtifact * pValue);
NResult N_API ANType10RecordGetLightingArtifacts(HANType10Record hRecord, ANLightingArtifact * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetLightingArtifact(HANType10Record hRecord, NInt index, ANLightingArtifact value);
NResult N_API ANType10RecordAddLightingArtifact(HANType10Record hRecord, ANLightingArtifact value, NInt * pIndex);
NResult N_API ANType10RecordInsertLightingArtifact(HANType10Record hRecord, NInt index, ANLightingArtifact value);
NResult N_API ANType10RecordRemoveLightingArtifactAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearLightingArtifacts(HANType10Record hRecord);

NResult N_API ANType10RecordGetFacialFeature3DPointCount(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetFacialFeature3DPoint(HANType10Record hRecord, NInt index, struct BdifFaceFeaturePoint_ * pValue);
NResult N_API ANType10RecordGetFacialFeature3DPointWithCodeN(HANType10Record hRecord, NInt index, struct BdifFaceFeaturePoint_ * pValue, HNString * phCode);
NResult N_API ANType10RecordGetFacialFeature3DPoints(HANType10Record hRecord, struct BdifFaceFeaturePoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetFacialFeature3DPoint(HANType10Record hRecord, NInt index, const struct BdifFaceFeaturePoint_ * pValue);
NResult N_API ANType10RecordAddFacialFeature3DPoint(HANType10Record hRecord, const struct BdifFaceFeaturePoint_ * pValue, NInt * pIndex);
NResult N_API ANType10RecordInsertFacialFeature3DPoint(HANType10Record hRecord, NInt index, const struct BdifFaceFeaturePoint_ * pValue);
NResult N_API ANType10RecordRemoveFacialFeature3DPointAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearFacialFeature3DPoints(HANType10Record hRecord);

NResult N_API ANType10RecordGetTieredMarkupCollection(HANType10Record hRecord, ANTieredMarkupCollection * pValue);
NResult N_API ANType10RecordSetTieredMarkupCollection(HANType10Record hRecord, ANTieredMarkupCollection value);

NResult N_API ANType10RecordGetFeatureContourCodeCount(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetFeatureContourCode(HANType10Record hRecord, NInt index, ANFeatureContourCode * pValue);
NResult N_API ANType10RecordGetFeatureContourCodes(HANType10Record hRecord, ANFeatureContourCode * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetFeatureContourCode(HANType10Record hRecord, NInt index, ANFeatureContourCode value);
NResult N_API ANType10RecordAddFeatureContourCode(HANType10Record hRecord, ANFeatureContourCode value, NInt * pIndex);
NResult N_API ANType10RecordInsertFeatureContourCode(HANType10Record hRecord, NInt index, ANFeatureContourCode value);
NResult N_API ANType10RecordRemoveFeatureContourCodeAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearFeatureContourCodes(HANType10Record hRecord);

NResult N_API ANType10RecordGetFeatureContourVertexCount(HANType10Record hRecord, NInt featureCountourIndex, NInt * pValue);
NResult N_API ANType10RecordGetFeatureContourVertex(HANType10Record hRecord, NInt featureCountourIndex, NInt index, struct NPoint_ * pValue);
NResult N_API ANType10RecordGetFeatureContourVertices(HANType10Record hRecord, NInt featureCountourIndex, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetFeatureContourVertex(HANType10Record hRecord, NInt featureCountourIndex, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType10RecordAddFeatureContourVertex(HANType10Record hRecord, NInt featureCountourIndex, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API ANType10RecordInsertFeatureContourVertex(HANType10Record hRecord, NInt featureCountourIndex, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType10RecordRemoveFeatureContourVertexAt(HANType10Record hRecord, NInt featureCountourIndex, NInt index);
NResult N_API ANType10RecordClearFeatureContourVertices(HANType10Record hRecord, NInt featureCountourIndex);

NResult N_API ANType10RecordGetCaptureDateRangeN(HANType10Record hRecord, HNString * phValue);
NResult N_API ANType10RecordSetCaptureDateRangeN(HANType10Record hRecord, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANType10RecordSetCaptureDateRangeA(HANType10Record hRecord, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANType10RecordSetCaptureDateRangeW(HANType10Record hRecord, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANType10RecordSetCaptureDateRange(HANType10Record hRecord, const NChar * szValue);
#endif
#define ANType10RecordSetCaptureDateRange N_FUNC_AW(ANType21RecordSetCaptureDateRange)

NResult N_API ANType10RecordGetImageTransformation(HANType10Record hRecord, BdifFacePostAcquisitionProcessing * pValue);
NResult N_API ANType10RecordSetImageTransformation(HANType10Record hRecord, BdifFacePostAcquisitionProcessing value);

NResult N_API ANType10RecordGetOcclusionCount(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetOcclusion(HANType10Record hRecord, NInt index, struct ANOcclusion_ * pValue);
NResult N_API ANType10RecordGetOcclusions(HANType10Record hRecord, struct ANOcclusion_ * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetOcclusion(HANType10Record hRecord, NInt index, const struct ANOcclusion_ * pValue);
NResult N_API ANType10RecordAddOcclusion(HANType10Record hRecord, const struct ANOcclusion_ * pValue, NInt * pIndex);
NResult N_API ANType10RecordInsertOcclusion(HANType10Record hRecord, NInt index, const struct ANOcclusion_ * pValue);
NResult N_API ANType10RecordRemoveOcclusionAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearOcclusions(HANType10Record hRecord);

NResult N_API ANType10RecordGetOcclusionVertexCount(HANType10Record hRecord, NInt occlusionIndex, NInt * pValue);
NResult N_API ANType10RecordGetOcclusionVertex(HANType10Record hRecord, NInt occlusionIndex, NInt index, struct NPoint_ * pValue);
NResult N_API ANType10RecordGetOcclusionVertices(HANType10Record hRecord, NInt occlusionIndex, struct NPoint_ * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetOcclusionVertex(HANType10Record hRecord, NInt occlusionIndex, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType10RecordAddOcclusionVertex(HANType10Record hRecord, NInt occlusionIndex, const struct NPoint_ * pValue, NInt * pIndex);
NResult N_API ANType10RecordInsertOcclusionVertex(HANType10Record hRecord, NInt occlusionIndex, NInt index, const struct NPoint_ * pValue);
NResult N_API ANType10RecordRemoveOcclusionVertexAt(HANType10Record hRecord, NInt occlusionIndex, NInt index);
NResult N_API ANType10RecordClearOcclusionVertices(HANType10Record hRecord, NInt occlusionIndex);

NResult N_API ANType10RecordGetPatternedInjuryCount(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordGetPatternedInjury(HANType10Record hRecord, NInt index, struct ANPatternedInjury_ * pValue);
NResult N_API ANType10RecordGetPatternedInjuries(HANType10Record hRecord, struct ANPatternedInjury_ * * parValues, NInt * pValueCount);
NResult N_API ANType10RecordSetPatternedInjury(HANType10Record hRecord, NInt index, const struct ANPatternedInjury_ * pValue);
NResult N_API ANType10RecordAddPatternedInjury(HANType10Record hRecord, const struct ANPatternedInjury_ * pValue, NInt * pIndex);
NResult N_API ANType10RecordInsertPatternedInjury(HANType10Record hRecord, NInt index, const struct ANPatternedInjury_ * pValue);
NResult N_API ANType10RecordRemovePatternedInjuryAt(HANType10Record hRecord, NInt index);
NResult N_API ANType10RecordClearPatternedInjuries(HANType10Record hRecord);

NResult N_API ANType10RecordGetCheiloscopicData(HANType10Record hRecord, struct ANCheiloscopicData_ * pValue, NBool * pHasValue);
NResult N_API ANType10RecordSetCheiloscopicData(HANType10Record hRecord, const struct ANCheiloscopicData_ * pValue);
NResult N_API ANType10RecordGetDentalVisualData(HANType10Record hRecord, struct ANDentalVisualData_ * pValue, NBool * pHasValue);
NResult N_API ANType10RecordSetDentalVisualData(HANType10Record hRecord, const struct ANDentalVisualData_ * pValue);
NResult N_API ANType10RecordGetRuler(HANType10Record hRecord, struct ANRuler_ * pValue, NBool * pHasValue);
NResult N_API ANType10RecordSetRuler(HANType10Record hRecord, const struct ANRuler_ * pValue);
NResult N_API ANType10RecordGetType10ReferenceNumber(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordSetType10ReferenceNumber(HANType10Record hRecord, NInt value);
NResult N_API ANType10RecordGetType2ReferenceNumber(HANType10Record hRecord, NInt * pValue);
NResult N_API ANType10RecordSetType2ReferenceNumber(HANType10Record hRecord, NInt value);

#ifdef N_CPP
}
#endif

#endif // !AN_TYPE_10_RECORD_H_INCLUDED
