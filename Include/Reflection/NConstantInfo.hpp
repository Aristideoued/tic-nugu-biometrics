#include <Reflection/NMemberInfo.hpp>

#ifndef N_CONSTANT_INFO_HPP_INCLUDED
#define N_CONSTANT_INFO_HPP_INCLUDED

#include <Core/NValue.hpp>

namespace Neurotec { namespace Reflection
{
#include <Reflection/NConstantInfo.h>
}}

namespace Neurotec { namespace Reflection
{

class NConstantInfo : public NMemberInfo
{
	N_DECLARE_OBJECT_CLASS(NConstantInfo, NMemberInfo)

public:
	NType GetConstantType() const
	{
		return GetObject<HandleType, NType>(NConstantInfoGetConstantType, true);
	}

	NValue GetValue() const
	{
		return GetObject<HandleType, NValue>(NConstantInfoGetValue);
	}
};

}}

#endif // !N_CONSTANT_INFO_HPP_INCLUDED
