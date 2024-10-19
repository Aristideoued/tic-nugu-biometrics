#ifndef N_FINGER_H_INCLUDED
#define N_FINGER_H_INCLUDED

#include <Biometrics/NFrictionRidge.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NFinger, NFrictionRidge)

NResult N_API NFingerCreate(HNFinger * phFinger);
NResult N_API NFingerGetWrongHandWarning(HNFrictionRidge hFrictionRidge, NBool * pValue);
NResult N_API NFingerSetWrongHandWarning(HNFrictionRidge hFrictionRidge, NBool value);
NResult N_API NFingerGetTipsWarning(HNFrictionRidge hFrictionRidge, NBool * pValue);
NResult N_API NFingerSetTipsWarning(HNFrictionRidge hFrictionRidge, NBool value);
NResult N_API NFingerGetFingerAngleWarning(HNFrictionRidge hFrictionRidge, NBool * pValue);
NResult N_API NFingerSetFingerAngleWarning(HNFrictionRidge hFrictionRidge, NBool value);
NResult N_API NFingerGetUnnaturalHandGeometryWarning(HNFrictionRidge hFrictionRidge, NBool * pValue);
NResult N_API NFingerSetUnnaturalHandGeometryWarning(HNFrictionRidge hFrictionRidge, NBool value);
NResult N_API NFingerGetUnnaturalHandGeometryConfidence(HNFrictionRidge hFrictionRidge, NByte * pValue);
NResult N_API NFingerSetUnnaturalHandGeometryConfidence(HNFrictionRidge hFrictionRidge, NByte value);

#ifdef N_CPP
}
#endif

#endif // !N_FINGER_H_INCLUDED
