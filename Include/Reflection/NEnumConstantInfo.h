#ifndef N_ENUM_CONSTANT_INFO_H_INCLUDED
#define N_ENUM_CONSTANT_INFO_H_INCLUDED

#include <Reflection/NMemberInfo.h>
#include <Core/NValue.h>

#ifdef N_CPP
extern "C"
{
#endif

NResult N_API NEnumConstantInfoGetValue(HNEnumConstantInfo hEnumConstantInfo, HNValue * phValue);

#ifdef N_CPP
}
#endif

#endif // !N_ENUM_CONSTANT_INFO_H_INCLUDED
