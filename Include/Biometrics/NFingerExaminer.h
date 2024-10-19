#ifndef N_FINGER_EXAMINER_H_INCLUDED
#define N_FINGER_EXAMINER_H_INCLUDED

#include <Biometrics/NBiometricEngine.h>
#include <Geometry/NGeometry.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NFingerExaminer, NObject)

NResult N_API NFingerExaminerCreate(HNFingerExaminer * phExaminer);

NResult N_API NFingerExaminerInitializeFromOriginalImageAsync(HNFingerExaminer hExaminer, HNBiometricEngine hEngine, HNImage hImage, HNAsyncOperation * phOperation);
NResult N_API NFingerExaminerInitializeFromOriginalImage(HNFingerExaminer hExaminer, HNBiometricEngine hEngine, HNImage hImage);
NResult N_API NFingerExaminerInitializeFromBinarizedImage(HNFingerExaminer hExaminer, HNImage hImage);

NResult N_API NFingerExaminerGetBinarizedImage(HNFingerExaminer hExaminer, HNImage * phImage);
NResult N_API NFingerExaminerCalculateRidgeCount(HNFingerExaminer hExaminer, NInt x1, NInt y1, NInt x2, NInt y2, NInt * pValue);
NResult N_API NFingerExaminerFindRidgeIntersections(HNFingerExaminer hExaminer, NInt x1, NInt y1, NInt x2, NInt y2, struct NPoint_ * * arPoints, NInt * pPointCount);
NResult N_API NFingerExaminerFindSingularPoints(HNFingerExaminer hExaminer, HNFRecord hRecord);
NResult N_API NFingerExaminerGetSkeletonImage(HNFingerExaminer hExaminer, HNImage * phSkeletonImage);

#ifdef N_CPP
}
#endif

#endif // !N_FINGER_EXAMINER_H_INCLUDED
