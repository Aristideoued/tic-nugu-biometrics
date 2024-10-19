#ifndef WEBP_H_INCLUDED
#define WEBP_H_INCLUDED

#include "NImage.h"

#ifdef N_CPP
extern "C"
{
#endif

// For lossy, 0 gives the smallest size and 100 the largest
// For lossless, 0 is the fastest but produces larger files, 100 is slower but produces smaller files
#define WEBP_DEFAULT_QUALITY 75

// Quality/speed trade-off (0: fast, 6: slower-better)
#define WEBP_DEFAULT_METHOD 4

N_DECLARE_OBJECT_TYPE(WebPInfo, NImageInfo)

NResult N_API WebPInfoIsLossless(HWebPInfo hInfo, NBool * pValue);
NResult N_API WebPInfoSetLossless(HWebPInfo hInfo, NBool value);
NResult N_API WebPInfoGetQuality(HWebPInfo hInfo, NFloat * pValue);
NResult N_API WebPInfoSetQuality(HWebPInfo hInfo, NFloat value);
NResult N_API WebPInfoGetMethod(HWebPInfo hInfo, NInt * pValue);
NResult N_API WebPInfoSetMethod(HWebPInfo hInfo, NInt value);

// Used in initialization of the encoding configuration to initialize a predefined set of parameters
NResult N_API WebPInfoGetPreset(HWebPInfo hInfo, NInt * pValue);
NResult N_API WebPInfoSetPreset(HWebPInfo hInfo, NInt value);

#ifdef N_CPP
}
#endif

#endif // !WEBP_H_INCLUDED
