#include <Reflection/NMemberInfo.hpp>

#ifndef N_ENUM_CONSTANT_INFO_HPP_INCLUDED
#define N_ENUM_CONSTANT_INFO_HPP_INCLUDED

#include <Core/NValue.hpp>

namespace Neurotec { namespace Reflection
{
#include <Reflection/NEnumConstantInfo.h>
}}

namespace Neurotec { namespace Reflection
{

class NEnumConstantInfo : public NMemberInfo
{
	N_DECLARE_OBJECT_CLASS(NEnumConstantInfo, NMemberInfo)

public:
	NValue GetValue() const
	{
		return GetObject<HandleType, NValue>(NEnumConstantInfoGetValue);
	}
};

}}

#endif // !N_ENUM_CONSTANT_INFO_HPP_INCLUDED
