#ifndef N_PROCESSOR_INFO_HPP_INCLUDED
#define N_PROCESSOR_INFO_HPP_INCLUDED

#include <Core/NObject.hpp>
namespace Neurotec
{
#include <Core/NProcessorInfo.h>
}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec, NProcessorVendor)

namespace Neurotec
{

class NProcessorInfo
{
	N_DECLARE_STATIC_OBJECT_CLASS(NProcessorInfo)

public:
	static NType NProcessorVendorNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(NProcessorVendor), true);
	}

	static NInt GetCount()
	{
		NInt value;
		NCheck(NProcessorInfoGetCount(&value));
		return value;
	}

	static void GetModelInfo(NInt * pFamily, NInt * pModel, NInt * pStepping)
	{
		NCheck(NProcessorInfoGetModelInfo(pFamily, pModel, pStepping));
	}

	static NString GetVendorName()
	{
		return NObject::GetString(NProcessorInfoGetVendorNameN);
	}

	static NProcessorVendor GetVendor()
	{
		NProcessorVendor value;
		NCheck(NProcessorInfoGetVendor(&value));
		return value;
	}

	static NString GetModelName()
	{
		return NObject::GetString(NProcessorInfoGetModelNameN);
	}

	static bool IsFeatureSupported(NProcessorFeature feature)
	{
		NBool value;
		NCheck(NProcessorInfoIsFeatureSupported(feature, &value));
		return value != 0;
	}
};

}

#endif // !N_PROCESSOR_INFO_HPP_INCLUDED
