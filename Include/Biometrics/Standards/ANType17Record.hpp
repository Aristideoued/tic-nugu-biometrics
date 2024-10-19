#ifndef AN_TYPE_17_RECORD_HPP_INCLUDED
#define AN_TYPE_17_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANImageAsciiBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType17Record.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANIrisAcquisitionLightingSpectrum)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANDamagedEye)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_17_RECORD_FIELD_LEN
#undef AN_TYPE_17_RECORD_FIELD_IDC

#undef AN_TYPE_17_RECORD_FIELD_FID

#undef AN_TYPE_17_RECORD_FIELD_SRC
#undef AN_TYPE_17_RECORD_FIELD_ICD
#undef AN_TYPE_17_RECORD_FIELD_HLL
#undef AN_TYPE_17_RECORD_FIELD_VLL
#undef AN_TYPE_17_RECORD_FIELD_SLC
#undef AN_TYPE_17_RECORD_FIELD_HPS
#undef AN_TYPE_17_RECORD_FIELD_VPS
#undef AN_TYPE_17_RECORD_FIELD_CGA
#undef AN_TYPE_17_RECORD_FIELD_BPX
#undef AN_TYPE_17_RECORD_FIELD_CSP

#undef AN_TYPE_17_RECORD_FIELD_RAE
#undef AN_TYPE_17_RECORD_FIELD_RAU
#undef AN_TYPE_17_RECORD_FIELD_IPC
#undef AN_TYPE_17_RECORD_FIELD_DUI
#undef AN_TYPE_17_RECORD_FIELD_GUI
#undef AN_TYPE_17_RECORD_FIELD_MMS
#undef AN_TYPE_17_RECORD_FIELD_ECL
#undef AN_TYPE_17_RECORD_FIELD_COM
#undef AN_TYPE_17_RECORD_FIELD_SHPS
#undef AN_TYPE_17_RECORD_FIELD_SVPS

#undef AN_TYPE_17_RECORD_FIELD_IQS

#undef AN_TYPE_17_RECORD_FIELD_ALS
#undef AN_TYPE_17_RECORD_FIELD_IRD
#undef AN_TYPE_17_RECORD_FIELD_SSV
#undef AN_TYPE_17_RECORD_FIELD_DME

#undef AN_TYPE_17_RECORD_FIELD_DMM

#undef AN_TYPE_17_RECORD_FIELD_IAP
#undef AN_TYPE_17_RECORD_FIELD_ISF
#undef AN_TYPE_17_RECORD_FIELD_IPB
#undef AN_TYPE_17_RECORD_FIELD_ISB
#undef AN_TYPE_17_RECORD_FIELD_UEB
#undef AN_TYPE_17_RECORD_FIELD_LEB
#undef AN_TYPE_17_RECORD_FIELD_NEO
#undef AN_TYPE_17_RECORD_FIELD_RAN
#undef AN_TYPE_17_RECORD_FIELD_GAZ

#undef AN_TYPE_17_RECORD_FIELD_ANN

#undef AN_TYPE_17_RECORD_FIELD_SAN
#undef AN_TYPE_17_RECORD_FIELD_EFR
#undef AN_TYPE_17_RECORD_FIELD_ASC
#undef AN_TYPE_17_RECORD_FIELD_HAS
#undef AN_TYPE_17_RECORD_FIELD_SOR
#undef AN_TYPE_17_RECORD_FIELD_GEO

#undef AN_TYPE_17_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_17_RECORD_FIELD_UDF_TO
#undef AN_TYPE_17_RECORD_FIELD_UDF_TO_V5

#undef AN_TYPE_17_RECORD_FIELD_DATA

#undef AN_TYPE_17_RECORD_MAX_IRIS_DIAMETER
#undef AN_TYPE_17_RECORD_MIN_IRIS_DIAMETER_V5

#undef AN_TYPE_17_RECORD_MAX_QUALITY_SCORE_COUNT
#undef AN_TYPE_17_RECORD_MAX_QUALITY_SCORE_COUNT_V5

#undef AN_TYPE_17_RECORD_MIN_LOWER_SPECTRUM_BOUND
#undef AN_TYPE_17_RECORD_MAX_LOWER_SPECTRUM_BOUND
#undef AN_TYPE_17_RECORD_MIN_UPPER_SPECTRUM_BOUND
#undef AN_TYPE_17_RECORD_MAX_UPPER_SPECTRUM_BOUND

#undef AN_TYPE_17_RECORD_IAP_20
#undef AN_TYPE_17_RECORD_IAP_30
#undef AN_TYPE_17_RECORD_IAP_40

#undef AN_TYPE_17_RECORD_MIN_IRIS_PUPIL_VERTEX_COUNT
#undef AN_TYPE_17_RECORD_MAX_IRIS_PUPIL_VERTEX_COUNT

#undef AN_TYPE_17_RECORD_MIN_IRIS_SCLERA_VERTEX_COUNT
#undef AN_TYPE_17_RECORD_MAX_IRIS_SCLERA_VERTEX_COUNT

#undef AN_TYPE_17_RECORD_MIN_EYELID_VERTEX_COUNT
#undef AN_TYPE_17_RECORD_MAX_EYELID_VERTEX_COUNT

#undef AN_TYPE_17_RECORD_MIN_OCCLUSION_VERTEX_COUNT
#undef AN_TYPE_17_RECORD_MAX_OCCLUSION_VERTEX_COUNT

#undef AN_TYPE_17_RECORD_MIN_RANGE
#undef AN_TYPE_17_RECORD_MAX_RANGE

#undef AN_TYPE_17_RECORD_MAX_FRONTAL_GAZE_ANGLE

const NInt AN_TYPE_17_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_17_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;

const NInt AN_TYPE_17_RECORD_FIELD_FID = 3;

const NInt AN_TYPE_17_RECORD_FIELD_SRC = AN_ASCII_BINARY_RECORD_FIELD_SRC;
const NInt AN_TYPE_17_RECORD_FIELD_ICD = AN_ASCII_BINARY_RECORD_FIELD_DAT;
const NInt AN_TYPE_17_RECORD_FIELD_HLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_17_RECORD_FIELD_VLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_17_RECORD_FIELD_SLC = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC;
const NInt AN_TYPE_17_RECORD_FIELD_HPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS;
const NInt AN_TYPE_17_RECORD_FIELD_VPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS;
const NInt AN_TYPE_17_RECORD_FIELD_CGA = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA;
const NInt AN_TYPE_17_RECORD_FIELD_BPX = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX;
const NInt AN_TYPE_17_RECORD_FIELD_CSP = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CSP;

const NInt AN_TYPE_17_RECORD_FIELD_RAE = 14;
const NInt AN_TYPE_17_RECORD_FIELD_RAU = 15;
const NInt AN_TYPE_17_RECORD_FIELD_IPC = 16;
const NInt AN_TYPE_17_RECORD_FIELD_DUI = 17;
const NInt AN_TYPE_17_RECORD_FIELD_GUI = 18;
const NInt AN_TYPE_17_RECORD_FIELD_MMS = 19;
const NInt AN_TYPE_17_RECORD_FIELD_ECL = 20;
const NInt AN_TYPE_17_RECORD_FIELD_COM = 21;
const NInt AN_TYPE_17_RECORD_FIELD_SHPS = 22;
const NInt AN_TYPE_17_RECORD_FIELD_SVPS = 23;

const NInt AN_TYPE_17_RECORD_FIELD_IQS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM;

const NInt AN_TYPE_17_RECORD_FIELD_ALS = 25;
const NInt AN_TYPE_17_RECORD_FIELD_IRD = 26;
const NInt AN_TYPE_17_RECORD_FIELD_SSV = 27;
const NInt AN_TYPE_17_RECORD_FIELD_DME = 28;

const NInt AN_TYPE_17_RECORD_FIELD_DMM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM;

const NInt  AN_TYPE_17_RECORD_FIELD_IAP = 31;
const NInt  AN_TYPE_17_RECORD_FIELD_ISF = 32;
const NInt  AN_TYPE_17_RECORD_FIELD_IPB = 33;
const NInt  AN_TYPE_17_RECORD_FIELD_ISB = 34;
const NInt  AN_TYPE_17_RECORD_FIELD_UEB = 35;
const NInt  AN_TYPE_17_RECORD_FIELD_LEB = 36;
const NInt  AN_TYPE_17_RECORD_FIELD_NEO = 37;

const NInt  AN_TYPE_17_RECORD_FIELD_RAN = 40;
const NInt  AN_TYPE_17_RECORD_FIELD_GAZ = 41;

const NInt AN_TYPE_17_RECORD_FIELD_ANN = AN_ASCII_BINARY_RECORD_FIELD_ANN;

const NInt AN_TYPE_17_RECORD_FIELD_SAN = AN_ASCII_BINARY_RECORD_FIELD_SAN;
const NInt AN_TYPE_17_RECORD_FIELD_EFR = AN_ASCII_BINARY_RECORD_FIELD_EFR;
const NInt AN_TYPE_17_RECORD_FIELD_ASC = AN_ASCII_BINARY_RECORD_FIELD_ASC;
const NInt AN_TYPE_17_RECORD_FIELD_HAS = AN_ASCII_BINARY_RECORD_FIELD_HAS;
const NInt AN_TYPE_17_RECORD_FIELD_SOR = AN_ASCII_BINARY_RECORD_FIELD_SOR;
const NInt AN_TYPE_17_RECORD_FIELD_GEO = AN_ASCII_BINARY_RECORD_FIELD_GEO;

const NInt AN_TYPE_17_RECORD_FIELD_UDF_FROM = AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM;
const NInt AN_TYPE_17_RECORD_FIELD_UDF_TO = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO;
const NInt AN_TYPE_17_RECORD_FIELD_UDF_TO_V5 = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5;

const NInt AN_TYPE_17_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

const NUShort AN_TYPE_17_RECORD_MAX_IRIS_DIAMETER = 9999;
const NUShort AN_TYPE_17_RECORD_MIN_IRIS_DIAMETER_V5 = 10;

const NByte AN_TYPE_17_RECORD_MAX_QUALITY_SCORE_COUNT = 1;
const NByte AN_TYPE_17_RECORD_MAX_QUALITY_SCORE_COUNT_V5 = 9;

const NUShort AN_TYPE_17_RECORD_MIN_LOWER_SPECTRUM_BOUND = 500;
const NUShort AN_TYPE_17_RECORD_MAX_LOWER_SPECTRUM_BOUND = 9990;
const NUShort AN_TYPE_17_RECORD_MIN_UPPER_SPECTRUM_BOUND = 510;
const NUShort AN_TYPE_17_RECORD_MAX_UPPER_SPECTRUM_BOUND = 9990;

const NUShort AN_TYPE_17_RECORD_IAP_20 = 20;
const NUShort AN_TYPE_17_RECORD_IAP_30 = 30;
const NUShort AN_TYPE_17_RECORD_IAP_40 = 40;

const NByte AN_TYPE_17_RECORD_MIN_IRIS_PUPIL_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MIN_CIRCLE_VERTEX_COUNT;
const NByte AN_TYPE_17_RECORD_MAX_IRIS_PUPIL_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT;

const NByte AN_TYPE_17_RECORD_MIN_IRIS_SCLERA_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MIN_CIRCLE_VERTEX_COUNT;
const NByte AN_TYPE_17_RECORD_MAX_IRIS_SCLERA_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT;

const NByte AN_TYPE_17_RECORD_MIN_EYELID_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MIN_POLYGON_VERTEX_COUNT;
const NByte AN_TYPE_17_RECORD_MAX_EYELID_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT;

const NByte AN_TYPE_17_RECORD_MIN_OCCLUSION_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MIN_POLYGON_VERTEX_COUNT;
const NByte AN_TYPE_17_RECORD_MAX_OCCLUSION_VERTEX_COUNT = AN_IMAGE_ASCII_BINARY_RECORD_MAX_VERTEX_COUNT;

const NInt AN_TYPE_17_RECORD_MIN_RANGE = 1;
const NInt AN_TYPE_17_RECORD_MAX_RANGE = 9999999;

const NUShort AN_TYPE_17_RECORD_MAX_FRONTAL_GAZE_ANGLE = 90;

class ANIrisImageProperties : public ANIrisImageProperties_
{
	N_DECLARE_STRUCT_CLASS(ANIrisImageProperties)

public:
	ANIrisImageProperties(BdifIrisOrientation horzOrientation, BdifIrisOrientation vertOrientation, BdifIrisScanType scanType)
	{
		HorzOrientation = horzOrientation;
		VertOrientation = vertOrientation;
		ScanType = scanType;
	}
};

class ANSpectrum : public ANSpectrum_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANSpectrum)

public:
	ANSpectrum(NUShort lowerBound, NUShort upperBound)
	{
		this->lowerBound = lowerBound;
		this->upperBound = upperBound;
	}
};

}}}

N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANIrisImageProperties)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSpectrum)

namespace Neurotec { namespace Biometrics { namespace Standards
{

class ANType17Record : public ANImageAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType17Record, ANImageAsciiBinaryRecord)

public:
	class ImageQualityScoreCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANQualityMetric, ANType17Record,
		ANType17RecordGetImageQualityScoreCount, ANType17RecordGetImageQualityScoreEx, ANType17RecordGetImageQualityScores>
	{
		ImageQualityScoreCollection(const ANType17Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType17Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANQualityMetric, ANType17Record,
			ANType17RecordGetImageQualityScoreCount, ANType17RecordGetImageQualityScoreEx, ANType17RecordGetImageQualityScores>::GetAll;

		void Set(NInt index, const ANQualityMetric & value)
		{
			NCheck(ANType17RecordSetImageQualityScoreEx(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANQualityMetric & value)
		{
			NInt index;
			NCheck(ANType17RecordAddImageQualityScore(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANQualityMetric & value)
		{
			NCheck(ANType17RecordInsertImageQualityScore(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType17RecordRemoveImageQualityScoreAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType17RecordClearImageQualityScores(this->GetOwnerHandle()));
		}
	};

	class IrisPupilBoundaryVerticesCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, ANType17Record,
		ANType17RecordGetIrisPupilBoundaryVertexCount, ANType17RecordGetIrisPupilBoundaryVertex, ANType17RecordGetIrisPupilBoundaryVertices>
	{
		IrisPupilBoundaryVerticesCollection(const ANType17Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType17Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, ANType17Record,
			ANType17RecordGetIrisPupilBoundaryVertexCount, ANType17RecordGetIrisPupilBoundaryVertex, ANType17RecordGetIrisPupilBoundaryVertices>::GetAll;

		void Set(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType17RecordSetIrisPupilBoundaryVertex(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType17RecordAddIrisPupilBoundaryVertex(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType17RecordInsertIrisPupilBoundaryVertex(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType17RecordRemoveIrisPupilBoundaryVertexAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType17RecordClearIrisPupilBoundaryVertices(this->GetOwnerHandle()));
		}
	};
	
	class IrisScleraBoundaryVerticesCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, ANType17Record,
		ANType17RecordGetIrisScleraBoundaryVertexCount, ANType17RecordGetIrisScleraBoundaryVertex, ANType17RecordGetIrisScleraBoundaryVertices>
	{
		IrisScleraBoundaryVerticesCollection(const ANType17Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType17Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, ANType17Record,
			ANType17RecordGetIrisScleraBoundaryVertexCount, ANType17RecordGetIrisScleraBoundaryVertex, ANType17RecordGetIrisScleraBoundaryVertices>::GetAll;

		void Set(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType17RecordSetIrisScleraBoundaryVertex(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType17RecordAddIrisScleraBoundaryVertex(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType17RecordInsertIrisScleraBoundaryVertex(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType17RecordRemoveIrisScleraBoundaryVertexAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType17RecordClearIrisScleraBoundaryVertices(this->GetOwnerHandle()));
		}
	};

	class UpperEyelidBoundaryVerticesCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, ANType17Record,
		ANType17RecordGetUpperEyelidBoundaryVertexCount, ANType17RecordGetUpperEyelidBoundaryVertex, ANType17RecordGetUpperEyelidBoundaryVertices>
	{
		UpperEyelidBoundaryVerticesCollection(const ANType17Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType17Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, ANType17Record,
			ANType17RecordGetUpperEyelidBoundaryVertexCount, ANType17RecordGetUpperEyelidBoundaryVertex, ANType17RecordGetUpperEyelidBoundaryVertices>::GetAll;

		void Set(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType17RecordSetUpperEyelidBoundaryVertex(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType17RecordAddUpperEyelidBoundaryVertex(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType17RecordInsertUpperEyelidBoundaryVertex(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType17RecordRemoveUpperEyelidBoundaryVertexAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType17RecordClearUpperEyelidBoundaryVertices(this->GetOwnerHandle()));
		}
	};

	class LowerEyelidBoundaryVerticesCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, ANType17Record,
		ANType17RecordGetLowerEyelidBoundaryVertexCount, ANType17RecordGetLowerEyelidBoundaryVertex, ANType17RecordGetLowerEyelidBoundaryVertices>
	{
		LowerEyelidBoundaryVerticesCollection(const ANType17Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType17Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase< ::Neurotec::Geometry::NPoint, ANType17Record,
			ANType17RecordGetLowerEyelidBoundaryVertexCount, ANType17RecordGetLowerEyelidBoundaryVertex, ANType17RecordGetLowerEyelidBoundaryVertices>::GetAll;

		void Set(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType17RecordSetLowerEyelidBoundaryVertex(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType17RecordAddLowerEyelidBoundaryVertex(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType17RecordInsertLowerEyelidBoundaryVertex(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType17RecordRemoveLowerEyelidBoundaryVertexAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType17RecordClearLowerEyelidBoundaryVertices(this->GetOwnerHandle()));
		}
	};

	class OcclusionCollection : public ::Neurotec::Collections::NCollectionBase<ANOcclusion, ANType17Record,
		ANType17RecordGetOcclusionCount, ANType17RecordGetOcclusion>
	{
		OcclusionCollection(const ANType17Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANOcclusion & value)
		{
			NCheck(ANType17RecordSetOcclusion(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANOcclusion & value)
		{
			NInt index;
			NCheck(ANType17RecordAddOcclusion(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANOcclusion & value)
		{
			NCheck(ANType17RecordInsertOcclusion(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType17RecordRemoveOcclusionAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType17RecordClearOcclusions(this->GetOwnerHandle()));
		}

		friend class ANType17Record;
	};

	class OcclusionVerticesCollection : public ::Neurotec::NObjectPartBase<ANType17Record>
	{
		OcclusionVerticesCollection(const ANType17Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType17Record;
	public:
		NInt GetCount(NInt baseIndex) const
		{
			NInt value;
			NCheck(ANType17RecordGetOcclusionVertexCount(this->GetOwnerHandle(), baseIndex, &value));
			return value;
		}

		void Get(NInt baseIndex, NInt index, ::Neurotec::Geometry::NPoint * pValue) const
		{
			NCheck(ANType17RecordGetOcclusionVertex(this->GetOwnerHandle(), baseIndex, index, pValue));
		}

		::Neurotec::Geometry::NPoint Get(NInt baseIndex, NInt index) const
		{
			::Neurotec::Geometry::NPoint value;
			NCheck(ANType17RecordGetOcclusionVertex(this->GetOwnerHandle(), baseIndex, index, &value));
			return value;
		}

		NArrayWrapper< ::Neurotec::Geometry::NPoint> GetAll(NInt baseIndex) const
		{
			::Neurotec::Geometry::NPoint::NativeType * arValues = NULL;
			NInt valueCount = 0;
			NCheck(ANType17RecordGetOcclusionVertices(this->GetOwnerHandle(), baseIndex, &arValues, &valueCount));
			return NArrayWrapper< ::Neurotec::Geometry::NPoint>(arValues, valueCount);
		}

		void Set(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType17RecordSetOcclusionVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		NInt Add(NInt baseIndex, const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType17RecordAddOcclusionVertex(this->GetOwnerHandle(), baseIndex, &value, &index));
			return index;
		}

		void Insert(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType17RecordInsertOcclusionVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		void RemoveAt(NInt baseIndex, NInt index)
		{
			NCheck(ANType17RecordRemoveOcclusionVertexAt(this->GetOwnerHandle(), baseIndex, index));
		}

		void Clear(NInt baseIndex)
		{
			NCheck(ANType17RecordClearOcclusionVertices(this->GetOwnerHandle(), baseIndex));
		}
	};

private:

public:
	static NType ANIrisAcquisitionLightingSpectrumNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANIrisAcquisitionLightingSpectrum), true);
	}

	BdifEyePosition GetFeatureIdentifier() const
	{
		BdifEyePosition value;
		NCheck(ANType17RecordGetFeatureIdentifier(GetHandle(), &value));
		return value;
	}

	void SetFeatureIdentifier(BdifEyePosition value)
	{
		NCheck(ANType17RecordSetFeatureIdentifier(GetHandle(), value));
	}

	NInt GetRotationAngle() const
	{
		NInt value;
		NCheck(ANType17RecordGetRotationAngle(GetHandle(), &value));
		return value;
	}

	void SetRotationAngle(NInt value)
	{
		NCheck(ANType17RecordSetRotationAngle(GetHandle(), value));
	}

	NInt GetRotationAngleUncertainty() const
	{
		NInt value;
		NCheck(ANType17RecordGetRotationAngleUncertainty(GetHandle(), &value));
		return value;
	}

	void SetRotationAngleUncertainty(NInt value)
	{
		NCheck(ANType17RecordSetRotationAngleUncertainty(GetHandle(), value));
	}

	bool GetImageProperties(ANIrisImageProperties * pValue) const
	{
		NBool hasValue;
		NCheck(ANType17RecordGetImageProperties(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetImageProperties(const ANIrisImageProperties * pValue)
	{
		NCheck(ANType17RecordSetImageProperties(GetHandle(), pValue));
	}

	bool GetGuid(NGuid * pValue) const
	{
		NBool hasValue;
		NCheck(ANType17RecordGetGuid(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetGuid(const NGuid * pValue)
	{
		NCheck(ANType17RecordSetGuid(GetHandle(), pValue));
	}

	BdifEyeColor GetEyeColor() const
	{
		BdifEyeColor value;
		NCheck(ANType17RecordGetEyeColor(GetHandle(), &value));
		return value;
	}

	void SetEyeColor(BdifEyeColor value)
	{
		NCheck(ANType17RecordSetEyeColor(GetHandle(), value));
	}

	ANIrisAcquisitionLightingSpectrum GetAcquisitionLightingSpectrum() const
	{
		ANIrisAcquisitionLightingSpectrum value;
		NCheck(ANType17RecordGetAcquisitionLightingSpectrum(GetHandle(), &value));
		return value;
	}

	void SetAcquisitionLightingSpectrum(ANIrisAcquisitionLightingSpectrum value)
	{
		NCheck(ANType17RecordSetAcquisitionLightingSpectrum(GetHandle(), value));
	}

	NInt GetIrisDiameter() const
	{
		NInt value;
		NCheck(ANType17RecordGetIrisDiameter(GetHandle(), &value));
		return value;
	}

	void SetIrisDiameter(NInt value)
	{
		NCheck(ANType17RecordSetIrisDiameter(GetHandle(), value));
	}

	bool GetSpecifiedSpectrumValues(ANSpectrum * pValue) const
	{
		NBool hasValue;
		NCheck(ANType17RecordGetSpecifiedSpectrumValues(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}
	void SetSpecifiedSpectrumValues(const ANSpectrum * pValue)
	{
		NCheck(ANType17RecordSetSpecifiedSpectrumValues(GetHandle(), pValue));
	}

	ANDamagedEye GetDamagedEye() const
	{
		ANDamagedEye value;
		NCheck(ANType17RecordGetDamagedEye(GetHandle(), &value));
		return value;
	}

	void SetDamagedEye(ANDamagedEye value)
	{
		NCheck(ANType17RecordSetDamagedEye(GetHandle(), value));
	}

	NInt GetSubjectAcquisitionProfile() const
	{
		NInt value;
		NCheck(ANType17RecordGetSubjectAcquisitionProfile(GetHandle(), &value));
		return value;
	}

	void SetSubjectAcquisitionProfile(NInt value)
	{
		NCheck(ANType17RecordSetSubjectAcquisitionProfile(GetHandle(), value));
	}

	BdifIrisImageFormat GetIrisStorageFormat() const
	{
		BdifIrisImageFormat value;
		NCheck(ANType17RecordGetIrisStorageFormat(GetHandle(), &value));
		return value;
	}

	void SetIrisStorageFormat(BdifIrisImageFormat value)
	{
		NCheck(ANType17RecordSetIrisStorageFormat(GetHandle(), value));
	}

	ANBoundaryCode GetIrisPupilBoundaryCode() const
	{
		ANBoundaryCode value;
		NCheck(ANType17RecordGetIrisPupilBoundaryCode(GetHandle(), &value));
		return value;
	}

	void SetIrisPupilBoundaryCode(ANBoundaryCode value) const
	{
		NCheck(ANType17RecordSetIrisPupilBoundaryCode(GetHandle(), value));
	}

	ANBoundaryCode GetIrisScleraBoundaryCode() const
	{
		ANBoundaryCode value;
		NCheck(ANType17RecordGetIrisScleraBoundaryCode(GetHandle(), &value));
		return value;
	}

	void SetIrisScleraBoundaryCode(ANBoundaryCode value) const
	{
		NCheck(ANType17RecordSetIrisScleraBoundaryCode(GetHandle(), value));
	}

	ANBoundaryCode GetUpperEyelidBoundaryCode() const
	{
		ANBoundaryCode value;
		NCheck(ANType17RecordGetUpperEyelidBoundaryCode(GetHandle(), &value));
		return value;
	}

	void SetUpperEyelidBoundaryCode(ANBoundaryCode value) const
	{
		NCheck(ANType17RecordSetUpperEyelidBoundaryCode(GetHandle(), value));
	}

	ANBoundaryCode GetLowerEyelidBoundaryCode() const
	{
		ANBoundaryCode value;
		NCheck(ANType17RecordGetLowerEyelidBoundaryCode(GetHandle(), &value));
		return value;
	}

	void SetLowerEyelidBoundaryCode(ANBoundaryCode value) const
	{
		NCheck(ANType17RecordSetLowerEyelidBoundaryCode(GetHandle(), value));
	}

	NInt GetRange() const
	{
		NInt value;
		NCheck(ANType17RecordGetRange(GetHandle(), &value));
		return value;
	}

	void SetRange(NInt value)
	{
		NCheck(ANType17RecordSetRange(GetHandle(), value));
	}

	NInt GetFrontalGazeAngle() const
	{
		NInt value;
		NCheck(ANType17RecordGetFrontalGazeAngle(GetHandle(), &value));
		return value;
	}

	void SetFrontalGazeAngle(NInt value)
	{
		NCheck(ANType17RecordSetFrontalGazeAngle(GetHandle(), value));
	}

	ImageQualityScoreCollection GetImageQualityScores()
	{
		return ImageQualityScoreCollection(*this);
	}

	const ImageQualityScoreCollection GetImageQualityScores() const
	{
		return ImageQualityScoreCollection(*this);
	}

	IrisPupilBoundaryVerticesCollection GetIrisPupilBoundaryVertices()
	{
		return IrisPupilBoundaryVerticesCollection(*this);
	}

	const IrisPupilBoundaryVerticesCollection GetIrisPupilBoundaryVertices() const
	{
		return IrisPupilBoundaryVerticesCollection(*this);
	}

	IrisScleraBoundaryVerticesCollection GetIrisScleraBoundaryVertices()
	{
		return IrisScleraBoundaryVerticesCollection(*this);
	}

	const IrisScleraBoundaryVerticesCollection GetIrisScleraBoundaryVertices() const
	{
		return IrisScleraBoundaryVerticesCollection(*this);
	}

	UpperEyelidBoundaryVerticesCollection GetUpperEyelidBoundaryVertices()
	{
		return UpperEyelidBoundaryVerticesCollection(*this);
	}

	const UpperEyelidBoundaryVerticesCollection GetUpperEyelidBoundaryVertices() const
	{
		return UpperEyelidBoundaryVerticesCollection(*this);
	}

	LowerEyelidBoundaryVerticesCollection GetLowerEyelidBoundaryVertices()
	{
		return LowerEyelidBoundaryVerticesCollection(*this);
	}

	const LowerEyelidBoundaryVerticesCollection GetLowerEyelidBoundaryVertices() const
	{
		return LowerEyelidBoundaryVerticesCollection(*this);
	}

	OcclusionCollection GetOcclusions()
	{
		return OcclusionCollection(*this);
	}

	const OcclusionCollection GetOcclusions() const
	{
		return OcclusionCollection(*this);
	}

	OcclusionVerticesCollection GetOcclusionVertices()
	{
		return OcclusionVerticesCollection(*this);
	}

	const OcclusionVerticesCollection GetOcclusionVertices() const
	{
		return OcclusionVerticesCollection(*this);
	}
};

}}}

#endif // !AN_TYPE_17_RECORD_HPP_INCLUDED
