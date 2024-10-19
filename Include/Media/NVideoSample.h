#ifndef N_VIDEO_SAMPLE_H_INCLUDED
#define N_VIDEO_SAMPLE_H_INCLUDED

#include <IO/NBuffer.h>
#include <Images/NImage.h>
#include <Media/NVideoFormat.h>
#include <Images/NImageInfo.h>
#include <Core/NTimeSpan.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NVideoSample, NObject)

NResult N_API NVideoSampleGetFormat(HNVideoSample hSample, HNVideoFormat * phValue);
NResult N_API NVideoSampleGetBuffer(HNVideoSample hSample, HNBuffer * phValue);
NResult N_API NVideoSampleGetPtr(HNVideoSample hSample, void * * ppValue);
NResult N_API NVideoSampleGetSize(HNVideoSample hSample, NSizeType * pValue);
NResult N_API NVideoSampleToImage(HNVideoSample hSample, HNImage * phValue);
NResult N_API NVideoSampleGetTransform(HNVideoSample hSample, NImageRotateFlipType * pValue);
NResult N_API NVideoSampleGetTimeStamp(HNVideoSample hSample, NTimeSpan * pValue);
NResult N_API NVideoSampleGetDuration(HNVideoSample hSample, NTimeSpan * pValue);

#ifdef N_CPP
}
#endif

#endif // !N_VIDEO_SAMPLE_H_INCLUDED