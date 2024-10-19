#ifndef N_FINGER_UNSEGMENTER_H_INCLUDED
#define N_FINGER_UNSEGMENTER_H_INCLUDED

#include <Core/NObject.h>
#include <Images/NImage.h>
#include <Biometrics/NBiometricTypes.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NFingerUnsegmenter, NObject)

NResult N_API NFingerUnsegmenterCreate(HNFingerUnsegmenter * phExaminer);

NResult N_API NFingerUnsegmenterProcess(HNFingerUnsegmenter hUnsegmenter, NFPosition position, HNImage hImage1, HNImage hImage2, HNImage hImage3, HNImage hImage4, HNImage * phImage);

#ifdef N_CPP
}
#endif

#endif // !N_FINGER_UNSEGMENTER_H_INCLUDED
