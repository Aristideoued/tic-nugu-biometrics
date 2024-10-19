#ifndef N_GEOMETRY_H_INCLUDED
#define N_GEOMETRY_H_INCLUDED

#include <Core/NTypes.h>

#ifdef N_CPP
extern "C"
{
#endif

struct NPoint_
{
	NInt X;
	NInt Y;
};
#ifndef N_GEOMETRY_HPP_INCLUDED
typedef struct NPoint_ NPoint;
#endif

N_DECLARE_TYPE(NPoint)

#ifndef N_NO_FLOAT

struct NPointF_
{
	NFloat X;
	NFloat Y;
};

struct NPoint3F_
{
	NFloat X;
	NFloat Y;
	NFloat Z;
};

#ifndef N_GEOMETRY_HPP_INCLUDED
typedef struct NPointF_ NPointF;
typedef struct NPoint3F_ NPoint3F;
#endif

N_DECLARE_TYPE(NPointF)
N_DECLARE_TYPE(NPoint3F)

struct NPointD_
{
	NDouble X;
	NDouble Y;
};
#ifndef N_GEOMETRY_HPP_INCLUDED
typedef struct NPointD_ NPointD;
#endif

N_DECLARE_TYPE(NPointD)

#endif

struct NSize_
{
	NInt Width;
	NInt Height;
};
#ifndef N_GEOMETRY_HPP_INCLUDED
typedef struct NSize_ NSize;
#endif

N_DECLARE_TYPE(NSize)

#ifndef N_NO_FLOAT

struct NSizeF_
{
	NFloat Width;
	NFloat Height;
};
#ifndef N_GEOMETRY_HPP_INCLUDED
typedef struct NSizeF_ NSizeF;
#endif

N_DECLARE_TYPE(NSizeF)

struct NSizeD_
{
	NDouble Width;
	NDouble Height;
};
#ifndef N_GEOMETRY_HPP_INCLUDED
typedef struct NSizeD_ NSizeD;
#endif

N_DECLARE_TYPE(NSizeD)

#endif

struct NRect_
{
	NInt X;
	NInt Y;
	NInt Width;
	NInt Height;
};
#ifndef N_GEOMETRY_HPP_INCLUDED
typedef struct NRect_ NRect;
#endif

N_DECLARE_TYPE(NRect)

#ifndef N_NO_FLOAT

struct NRectF_
{
	NFloat X;
	NFloat Y;
	NFloat Width;
	NFloat Height;
};
#ifndef N_GEOMETRY_HPP_INCLUDED
typedef struct NRectF_ NRectF;
#endif

N_DECLARE_TYPE(NRectF)

struct NRectD_
{
	NDouble X;
	NDouble Y;
	NDouble Width;
	NDouble Height;
};
#ifndef N_GEOMETRY_HPP_INCLUDED
typedef struct NRectD_ NRectD;
#endif

N_DECLARE_TYPE(NRectD)

#endif

typedef enum NInterpolationMode_
{
	nimBilinear = 3,
	nimBicubic = 4,
	nimNearestNeighbor = 5,
	nimBox = 6,
	nimTent = 7,
	nimBell = 8,
	nimBspline = 9,
	nimBlackman = 10,
	nimMitchell = 11,
	nimLanczos3 = 12,
	nimLanczos4 = 13,
	nimLanczos6 = 14,
	nimLanczos12 = 15,
	nimKaiser = 16,
	nimGaussian = 17,
	nimCatmullRom = 18,
	nimQuadInterp = 19,
	nimQuadAppr = 20,
	nimQuadMix = 21,
} NInterpolationMode;

N_DECLARE_TYPE(NInterpolationMode)

N_DECLARE_STATIC_OBJECT_TYPE(NGeometry)

#ifdef N_CPP
}
#endif

#endif // !N_GEOMETRY_H_INCLUDED
