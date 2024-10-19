#ifndef N_FINGER_UNSEGMENTER_HPP_INCLUDED
#define N_FINGER_UNSEGMENTER_HPP_INCLUDED

#include <Core/NObject.hpp>
#include <Images/NImage.hpp>
#include <Biometrics/NBiometricTypes.hpp>

namespace Neurotec { namespace Biometrics
{
using ::Neurotec::Images::HNImage;
#include <Biometrics/NFingerUnsegmenter.h>
}}

namespace Neurotec { namespace Biometrics
{

class NFingerUnsegmenter : public NObject
{
	N_DECLARE_OBJECT_CLASS(NFingerUnsegmenter, NObject)

	static HNFingerUnsegmenter Create()
	{
		HNFingerUnsegmenter handle;
		NCheck(NFingerUnsegmenterCreate(&handle));
		return handle;
	}

public:
	NFingerUnsegmenter()
		: NObject(Create(), true)
	{
	}

	::Neurotec::Images::NImage Process(NFPosition position,
		const ::Neurotec::Images::NImage& image1,
		const ::Neurotec::Images::NImage& image2,
		const ::Neurotec::Images::NImage& image3,
		const ::Neurotec::Images::NImage& image4)
	{
		::Neurotec::Images::HNImage hImage;
		NCheck(NFingerUnsegmenterProcess(GetHandle(), position,
			image1.GetHandle(), image2.GetHandle(), image3.GetHandle(), image4.GetHandle(), &hImage));
		return FromHandle<::Neurotec::Images::NImage>(hImage);
	}
};

}}

#endif // !N_FINGER_UNSEGMENTER_HPP_INCLUDED
