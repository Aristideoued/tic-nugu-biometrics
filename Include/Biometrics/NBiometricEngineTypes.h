#ifndef N_BIOMETRIC_ENGINE_TYPES_H_INCLUDED
#define N_BIOMETRIC_ENGINE_TYPES_H_INCLUDED

#include <Core/NTypes.h>

#ifdef N_CPP
extern "C"
{
#endif

typedef enum NMatchingSpeed_
{
	nmsLow    =   0,
	nmsMedium = 128,
	nmsHigh   = 256,
} NMatchingSpeed;

N_DECLARE_TYPE(NMatchingSpeed)

typedef enum NMFusionType_
{
	nmftFuseAlways = 0,
	nmftSelectByFaceThenFuse = 1,
	nmftSelectByIrisThenFuse = 2
} NMFusionType;

N_DECLARE_TYPE(NMFusionType)

typedef enum NAnomalousMatchingMode_
{
	nammNone = 0,
	nammSingleRecord = 1,
	nammSourceImage = 2,
	nammModality = 3,
} NAnomalousMatchingMode;

N_DECLARE_TYPE(NAnomalousMatchingMode)

typedef enum NTemplateSize_
{
	ntsCompact = 0,
	ntsSmall = 64,
	ntsMedium = 128,
	ntsLarge = 256
} NTemplateSize;

N_DECLARE_TYPE(NTemplateSize)

typedef enum BiometricTemplateFormat_
{
	btfProprietary = 0,
	btfMocCompact = 1,
	btfMocNormal = 2
} BiometricTemplateFormat;

N_DECLARE_TYPE(BiometricTemplateFormat)

typedef enum NExtractionScenario_
{
	nesNotUsed = 0,
	nesLowestUsableQualityExtraction = 1,
	nesOptimizedSpeed = 2,
	nesMinex = 3,
	nesMocMinex = 4,
	nesLatentFinger = 5,
	nesSelfCheck = 999,
} NExtractionScenario;

N_DECLARE_TYPE(NExtractionScenario)

typedef enum NMatchingScenario_
{
	nmsNotUsed = 0,
	nmsLatentFinger = 1,
} NMatchingScenario;

N_DECLARE_TYPE(NMatchingScenario)

N_DECLARE_STATIC_OBJECT_TYPE(NBiometricEngineTypes)

#ifdef N_CPP
}
#endif

#endif // !N_BIOMETRIC_ENGINE_TYPES_H_INCLUDED
