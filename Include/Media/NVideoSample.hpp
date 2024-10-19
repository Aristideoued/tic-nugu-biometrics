#ifndef N_VIDEO_SAMPLE_HPP_INCLUDED
#define N_VIDEO_SAMPLE_HPP_INCLUDED

#include <Core/NObject.hpp>
#include <Core/NTimeSpan.hpp>
#include <Images/NImage.hpp>
#include <Images/NImageInfo.hpp>

namespace Neurotec { namespace Media {
using ::Neurotec::Images::HNImage;
using ::Neurotec::Images::NImageRotateFlipType;
#include <Media/NVideoSample.h>
}}

namespace Neurotec { namespace Media {

class NVideoSample : public NObject
{
	N_DECLARE_OBJECT_CLASS(NVideoSample, NObject)
public:
	NVideoFormat GetFormat() const
	{
		HNVideoFormat hFormat;
		NCheck(NVideoSampleGetFormat(GetHandle(), &hFormat));
		return NObject::FromHandle<NVideoFormat>(hFormat);
	}

	::Neurotec::IO::NBuffer GetBuffer() const
	{
		HNBuffer hBuffer;
		NCheck(NVideoSampleGetBuffer(GetHandle(), &hBuffer));
		return NObject::FromHandle< ::Neurotec::IO::NBuffer>(hBuffer);
	}

	void * GetPtr() const
	{
		void * ptr;
		NCheck(NVideoSampleGetPtr(GetHandle(), &ptr));
		return ptr;
	}

	NSizeType GetSize() const
	{
		NSizeType size;
		NCheck(NVideoSampleGetSize(GetHandle(), &size));
		return size;
	}

	::Neurotec::Images::NImage ToImage() const
	{
		HNImage image;
		NCheck(NVideoSampleToImage(GetHandle(), &image));
		return FromHandle< ::Neurotec::Images::NImage>(image, true);
	}

	::Neurotec::Images::NImageRotateFlipType GetTrasnsform() const
	{
		::Neurotec::Images::NImageRotateFlipType transform;
		NCheck(NVideoSampleGetTransform(GetHandle(), &transform));
		return transform;
	}

	::Neurotec::NTimeSpan GetTimeSamp() const
	{
		::Neurotec::NTimeSpan timeStamp;
		NCheck(NVideoSampleGetTimeStamp(GetHandle(), &timeStamp));
		return timeStamp;
	}

	::Neurotec::NTimeSpan GetDuration() const
	{
		::Neurotec::NTimeSpan duration;
		NCheck(NVideoSampleGetTimeStamp(GetHandle(), &duration));
		return duration;
	}
};

}}

#endif // !N_VIDEO_SAMPLE_HPP_INCLUDED