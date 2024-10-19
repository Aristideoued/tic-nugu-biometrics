#ifndef N_BIOMETRIC_ATTRIBUTES_H_INCLUDED
#define N_BIOMETRIC_ATTRIBUTES_H_INCLUDED

#include <Biometrics/NBiometricTypes.h>
#include <Core/NObject.h>

#ifdef N_CPP
extern "C"
{
#endif

typedef enum NBiometricAttributeId_
{
	nbaiQuality = 1,
	nbaiDetectionConfidence = 2,
	nbaiLiveness = 3,
	nbaiOcclusion = 4,
	nbaiResolution = 5,
	nbaiMotionBlur = 6,
	nbaiCompressionArtifacts = 7,
	nbaiOverexposure = 8,
	nbaiUnderexposure = 9,
	nbaiGrayscaleDensity = 10,
	nbaiSharpness = 11,
	nbaiContrast = 12,
	nbaiBackgroundUniformity = 13,
	nbaiSaturation = 14,
	nbaiNoise = 15,
	nbaiWashedOut = 16,
	nbaiPixelation = 17,
	nbaiInterlace = 18,
	nbaiLivenessQuality = 19,

	nbaiTooWet = 200,
	nbaiTooDry = 201,
	nbaiPressedTooHard = 202,
	nbaiPressedTooSoft = 203,
	nbaiFingerTip = 204,
	nbaiSlapWrongHand = 205,
	nbaiSlapUnnaturalHandGeometry = 206,
	nbaiSlapFingerAngleTooDifferent = 207,
	nbaiGhostFinger = 299,
	nbaiNfiq10 = 380,
	nbaiNfiq20 = 381,
	nbaiNfiq21 = 382,

	nbaiAge = 400,
	nbaiPose = 401,
	nbaiEyesOpen = 402,
	nbaiDarkGlasses = 403,
	nbaiGlasses = 404,
	nbaiMouthOpen = 405,
	nbaiBeard = 406,
	nbaiMustache = 407,
	nbaiHeadCovering = 408,
	nbaiHeavyFrameGlasses = 409,
	nbaiLookingAway = 410,
	nbaiRedEye = 411,
	nbaiFaceDarkness = 412,
	nbaiSkinTone = 413,
	nbaiSkinReflection = 414,
	nbaiGlassesReflection = 415,
	nbaiFaceMask = 416,
	nbaiAdditionalFacesDetected = 417,
	nbaiGenderMale = 418,
	nbaiGenderFemale = 419,
	nbaiSmile = 420,
	nbaiTokenImageQuality = 421,
	nbaiEmotionNeutral = 540,
	nbaiEmotionAnger = 541,
	nbaiEmotionContempt = 542,
	nbaiEmotionDisgust = 543,
	nbaiEmotionFear = 544,
	nbaiEmotionHappiness = 545,
	nbaiEmotionSadness = 546,
	nbaiEmotionSurprise = 547,
	nbaiEthnicityWhite = 560,
	nbaiEthnicityBlack = 561,
	nbaiEthnicityAsian = 562,
	nbaiEthnicityIndian = 563,
	nbaiEthnicityHispanic = 564,
	nbaiEthnicityArabian = 565,
	nbaiEyesSize = 580,
	nbaiNoseSize = 581,
	nbaiMouthSize = 582,

	nbaiUsableIrisArea = 600,
	nbaiIrisScleraContrast = 601,
	nbaiIrisPupilContrast = 602,
	nbaiPupilBoundaryCircularity = 603,
	nbaiIrisBoundaryCircularity = 604,
	nbaiGrayscaleUtilisation = 605,
	nbaiPupilToIrisRatio = 606,
	nbaiIrisPupilConcentricity = 607,
	nbaiMarginAdequacy = 608,
	nbaiCosmeticLenses = 609,
} NBiometricAttributeId;

N_DECLARE_TYPE(NBiometricAttributeId)

N_DECLARE_OBJECT_TYPE(NBiometricAttributes, NObject)

NResult N_API NBiometricAttributesGetBiometricType(HNBiometricAttributes hAttributes, NBiometricType * pValue);
NResult N_API NBiometricAttributesGetStatus(HNBiometricAttributes hAttributes, NBiometricStatus * pValue);
NResult N_API NBiometricAttributesSetStatus(HNBiometricAttributes hAttributes, NBiometricStatus value);
NResult N_API NBiometricAttributesGetQuality(HNBiometricAttributes hAttributes, NByte * pValue);
NResult N_API NBiometricAttributesSetQuality(HNBiometricAttributes hAttributes, NByte value);
NResult N_API NBiometricAttributesGetDetectionConfidence(HNBiometricAttributes hAttributes, NByte * pValue);
NResult N_API NBiometricAttributesSetDetectionConfidence(HNBiometricAttributes hAttributes, NByte value);
NResult N_API NBiometricAttributesGetLivenessConfidence(HNBiometricAttributes hAttributes, NByte * pValue);
NResult N_API NBiometricAttributesSetLivenessConfidence(HNBiometricAttributes hAttributes, NByte value);
NResult N_API NBiometricAttributesGetAttributeCount(HNBiometricAttributes hAttributes, NInt * pValue);
NResult N_API NBiometricAttributesGetAttributeId(HNBiometricAttributes hAttributes, NInt index, NBiometricAttributeId * pValue);
NResult N_API NBiometricAttributesGetAttributeValue(HNBiometricAttributes hAttributes, NInt index, NByte * pValue);
NResult N_API NBiometricAttributesGetAttributeThreshold(HNBiometricAttributes hAttributes, NInt index, NByte * pValue);
NResult N_API NBiometricAttributesGetAttributeIndexOf(HNBiometricAttributes hAttributes, NBiometricAttributeId id, NInt * pIndex);
NResult N_API NBiometricAttributesGetAttributeValueById(HNBiometricAttributes hAttributes, NBiometricAttributeId id, NByte * pValue);
NResult N_API NBiometricAttributesSetAttributeValueById(HNBiometricAttributes hAttributes, NBiometricAttributeId id, NByte value);
NResult N_API NBiometricAttributesAttributeIdToNameN(NBiometricAttributeId id, HNString * phValue);
NResult N_API NBiometricAttributesAttributeNameToIdN(HNString hValue, NBiometricAttributeId * pId);

NResult N_API NBiometricAttributesGetChild(HNBiometricAttributes hAttributes, HNObject * phValue);
NResult N_API NBiometricAttributesGetChildSubject(HNBiometricAttributes hAttributes, HNObject * phValue);

#ifdef N_CPP
}
#endif

#endif // !N_BIOMETRIC_ATTRIBUTES_H_INCLUDED
