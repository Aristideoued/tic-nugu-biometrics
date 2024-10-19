#ifndef WEBP_HPP_INCLUDED
#define WEBP_HPP_INCLUDED

#include <Images/NImage.hpp>
namespace Neurotec { namespace Images
{
#include <Images/WebP.h>
}}

namespace Neurotec { namespace Images
{

#undef WEBP_DEFAULT_QUALITY
#undef WEBP_DEFAULT_METHOD

const NFloat WEBP_DEFAULT_QUALITY = 75;
const NInt WEBP_DEFAULT_METHOD = 4;

class WebPInfo : public NImageInfo
{
	N_DECLARE_OBJECT_CLASS(WebPInfo, NImageInfo)

public:

	bool IsLossless() const
	{
		NBool value;
		NCheck(WebPInfoIsLossless(GetHandle(), &value));
		return value != 0;
	}

	void SetLossless(bool value)
	{
		NCheck(WebPInfoSetLossless(GetHandle(), value ? NTrue : NFalse));
	}
	NFloat GetQuality() const
	{
		NFloat value;
		NCheck(WebPInfoGetQuality(GetHandle(), &value));
		return value;
	}

	void SetQuality(NFloat value)
	{
		NCheck(WebPInfoSetQuality(GetHandle(), value));
	}

	NInt GetMethod() const
	{
		NInt value;
		NCheck(WebPInfoGetMethod(GetHandle(), &value));
		return value;
	}

	void SetMethod(NInt value)
	{
		NCheck(WebPInfoSetMethod(GetHandle(), value));
	}

	NInt GetPreset() const
	{
		NInt value;
		NCheck(WebPInfoGetPreset(GetHandle(), &value));
		return value;
	}

	void SetPreset(NInt value)
	{
		NCheck(WebPInfoSetPreset(GetHandle(), value));
	}
};

}}

#endif // !WEBP_HPP_INCLUDED
