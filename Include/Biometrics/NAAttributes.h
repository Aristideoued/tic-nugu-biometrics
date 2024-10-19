#ifndef NA_ATTRIBUTES_H_INCLUDED
#define NA_ATTRIBUTES_H_INCLUDED

#include <Biometrics/NBiometricAttributes.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NAAttributes, NBiometricAttributes)

NResult N_API NAAttributesCreate(HNAAttributes * phAttributes);

#ifdef N_CPP
}
#endif

#endif // !NA_ATTRIBUTES_H_INCLUDED
