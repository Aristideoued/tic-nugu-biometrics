#ifndef NL_ATTRIBUTES_H_INCLUDED
#define NL_ATTRIBUTES_H_INCLUDED

#include <Biometrics/NBiometricAttributes.h>
#include <Biometrics/NLTemplate.h>
#include <Geometry/NGeometry.h>
#include <Images/NImage.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NLAttributes, NBiometricAttributes)

NResult N_API NLAttributesCreate(HNLAttributes * phAttributes);

NResult N_API NLAttributesGetTemplate(HNLAttributes hAttributes, HNLTemplate * phValue);
NResult N_API NLAttributesSetTemplate(HNLAttributes hAttributes, HNLTemplate hTemplate);
NResult N_API NLAttributesGetMocTemplate(HNLAttributes hAttributes, HNBuffer * phValue);
NResult N_API NLAttributesGetBoundingRect(HNLAttributes hAttributes, struct NRect_ * pValue);
NResult N_API NLAttributesSetBoundingRect(HNLAttributes hAttributes, const struct NRect_ * pValue);
NResult N_API NLAttributesGetYaw(HNLAttributes hAttributes, NFloat * pValue);
NResult N_API NLAttributesSetYaw(HNLAttributes hAttributes, NFloat value);
NResult N_API NLAttributesGetPitch(HNLAttributes hAttributes, NFloat * pValue);
NResult N_API NLAttributesSetPitch(HNLAttributes hAttributes, NFloat value);
NResult N_API NLAttributesSetRoll(HNLAttributes hAttributes, NFloat value);
NResult N_API NLAttributesGetRoll(HNLAttributes hAttributes, NFloat * pValue);

NResult N_API NLAttributesGetRightEyeCenter(HNLAttributes hAttributes, NLFeaturePoint * pValue);
NResult N_API NLAttributesSetRightEyeCenter(HNLAttributes hAttributes, const NLFeaturePoint * pValue);
NResult N_API NLAttributesGetLeftEyeCenter(HNLAttributes hAttributes, NLFeaturePoint * pValue);
NResult N_API NLAttributesSetLeftEyeCenter(HNLAttributes hAttributes, const NLFeaturePoint * pValue);
NResult N_API NLAttributesGetNoseTip(HNLAttributes hAttributes, NLFeaturePoint * pValue);
NResult N_API NLAttributesSetNoseTip(HNLAttributes hAttributes, const NLFeaturePoint * pValue);
NResult N_API NLAttributesGetMouthCenter(HNLAttributes hAttributes, NLFeaturePoint * pValue);
NResult N_API NLAttributesSetMouthCenter(HNLAttributes hAttributes, const NLFeaturePoint * pValue);

NResult N_API NLAttributesGetGender(HNLAttributes hAttributes, NGender * pValue);
NResult N_API NLAttributesSetGender(HNLAttributes hAttributes, NGender value);

NResult N_API NLAttributesGetGenderConfidence(HNLAttributes hAttributes, NByte * pValue);

NResult N_API NLAttributesGetBaseFrameIndex(HNLAttributes hAttributes, NInt * pValue);
NResult N_API NLAttributesSetBaseFrameIndex(HNLAttributes hAttributes, NInt value);

NResult N_API NLAttributesGetThumbnail(HNLAttributes hAttributes, HNImage * phValue);
NResult N_API NLAttributesSetThumbnail(HNLAttributes hAttributes, HNImage hValue);

NResult N_API NLAttributesGetFeaturePointCount(HNLAttributes hAttributes, NInt * pValue);
NResult N_API NLAttributesGetFeaturePoint(HNLAttributes hAttributes, NInt index, struct NLFeaturePoint_ * pValue);
NResult N_API NLAttributesGetFeaturePoints(HNLAttributes hAttributes, struct NLFeaturePoint_ * * parValues, NInt * pValueCount);
NResult N_API NLAttributesGetFeaturePointCapacity(HNLAttributes hAttributes, NInt * pValue);
NResult N_API NLAttributesSetFeaturePointCapacity(HNLAttributes hAttributes, NInt value);
NResult N_API NLAttributesSetFeaturePoint(HNLAttributes hAttributes, NInt index, const struct NLFeaturePoint_ * pValue);
NResult N_API NLAttributesAddFeaturePoint(HNLAttributes hAttributes, const struct NLFeaturePoint_ * pValue, NInt * pIndex);
NResult N_API NLAttributesInsertFeaturePoint(HNLAttributes hAttributes, NInt index, const struct NLFeaturePoint_ * pValue);
NResult N_API NLAttributesRemoveFeaturePointAt(HNLAttributes hAttributes, NInt index);
NResult N_API NLAttributesClearFeaturePoints(HNLAttributes hAttributes);

NResult N_API NLAttributesGetLivenessAction(HNLAttributes hAttributes, NLivenessAction * pValue);
NResult N_API NLAttributesGetLivenessScore(HNLAttributes hAttributes, NByte * pValue);
NResult N_API NLAttributesGetLivenessTargetYaw(HNLAttributes hAttributes, NFloat * pValue);
NResult N_API NLAttributesGetLivenessTargetPitch(HNLAttributes hAttributes, NFloat * pValue);

NResult N_API NLAttributesGetTokenImageRect(HNLAttributes hAttributes, struct NRect_ * pValue);
NResult N_API NLAttributesSetTokenImageRect(HNLAttributes hAttributes, const struct NRect_ * pValue);

NResult N_API NLAttributesGetIcaoWarnings(HNLAttributes hAttributes, NIcaoWarnings * pValue);
NResult N_API NLAttributesSetIcaoWarnings(HNLAttributes hAttributes, NIcaoWarnings value);

#ifdef N_CPP
}
#endif

#endif // !NL_ATTRIBUTES_H_INCLUDED
