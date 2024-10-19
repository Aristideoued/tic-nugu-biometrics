#ifndef N_PROCESSOR_INFO_H_INCLUDED
#define N_PROCESSOR_INFO_H_INCLUDED

#include <Core/NObject.h>

#ifdef N_CPP
extern "C"
{
#endif

typedef enum NProcessorVendor_
{
	npvUnknown = 0,
	npvAmd = 1,
	npvCentaur = 2,
	npvCyrix = 3,
	npvIntel = 4,
	npvNationalSemiconductor = 5,
	npvNexGen = 6,
	npvRiseTechnology = 7,
	npvSiS = 8,
	npvTransmeta = 9,
	npvUmc = 10,
	npvVia = 11
} NProcessorVendor;

N_DECLARE_TYPE(NProcessorVendor)

typedef enum NProcessorFeature_
{
	npftX86Sse = 0,
	npftX86Sse2 = 1,
	npftX86Sse3 = 2,
	npftX86Ssse3 = 3,
	npftX86LZCnt = 4,
	npftX86PopCnt = 5,
	npftX86Sse41 = 6,
	npftX86Sse42 = 7,
	npftX86Sse4a = 8,
	npftX86Avx = 9,
	npftX86Avx2 = 10,
	npftX86pclmulqdq = 11,
	npftX86fma = 12,
	npftX86cmpxchg16b = 13,
	npftX86movbe = 14,
	npftX86aesni = 15,
	npftX86f16c = 16,
	npftX86rdrand = 17,
	npftX86bmi1 = 18,
	npftX86bmi2 = 19,
	npftX86hle = 20,
	npftX86rtm = 21,
	npftX86rdseed = 22,
	npftX86adx = 23,
	npftX86clflushopt = 24,
	npftX86clwb = 25,
	npftX86sha = 26,
	npftX86gfni = 27,
	npftX86vaes = 28,
	npftX86vpclmulqdq = 29,
	npftX86Avx512f = 30,
	npftX86Avx512cd = 31,
	npftX86Avx512er = 32,
	npftX86Avx512pf = 33,
	npftX86Avx512dq = 34,
	npftX86Avx512bw = 35,
	npftX86Avx512vl = 36,
	npftX86Avx512_ifma = 37,
	npftX86Avx512_vbmi = 38,
	npftX86Avx512_4vnniw = 39,
	npftX86Avx512_4fmaps = 40,
	npftX86Avx512_vpopcntdq = 41,
	npftX86Avx512_vnni = 42,
	npftX86Avx512_vbmi2 = 43,
	npftX86Avx512_bitalg = 44,
	npftX86Avx512_vp2intersect = 45,
	npftX86Avx512_fp16 = 46,
	npftX86Avx512_bf16 = 47,
	npftX86Avx_vnni = 48,
	npftX86cldemote = 49,
	npftX86Amx_bf16 = 50,
	npftX86Amx_tile = 51,
	npftX86Amx_int8 = 52,
	npftArmNeon = 1000,
	npftArmCrc32 = 1001,
	npftArmVfp4 = 1002,
} NProcessorFeature;

N_DECLARE_TYPE(NProcessorFeature)

N_DECLARE_STATIC_OBJECT_TYPE(NProcessorInfo)

NResult N_API NProcessorInfoGetCount(NInt * pValue);

NResult N_API NProcessorInfoGetVendorNameN(HNString * phValue);
NResult N_API NProcessorInfoGetVendor(NProcessorVendor * pValue);
NResult N_API NProcessorInfoGetModelInfo(NInt * pFamily, NInt * pModel, NInt * pStepping);
NResult N_API NProcessorInfoGetModelNameN(HNString * phValue);

NResult N_API NProcessorInfoIsFeatureSupported(NProcessorFeature feature, NBool * pValue);

#ifdef N_CPP
}
#endif

#endif // !N_PROCESSOR_INFO_H_INCLUDED
