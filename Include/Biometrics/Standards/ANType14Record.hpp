#ifndef AN_TYPE_14_RECORD_HPP_INCLUDED
#define AN_TYPE_14_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANFPImageAsciiBinaryRecord.hpp>
#include <Geometry/NGeometry.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
using ::Neurotec::Geometry::NPoint_;
#include <Biometrics/Standards/ANType14Record.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_14_RECORD_FIELD_LEN
#undef AN_TYPE_14_RECORD_FIELD_IDC
#undef AN_TYPE_14_RECORD_FIELD_IMP
#undef AN_TYPE_14_RECORD_FIELD_SRC
#undef AN_TYPE_14_RECORD_FIELD_FCD
#undef AN_TYPE_14_RECORD_FIELD_HLL
#undef AN_TYPE_14_RECORD_FIELD_VLL
#undef AN_TYPE_14_RECORD_FIELD_SLC
#undef AN_TYPE_14_RECORD_FIELD_HPS
#undef AN_TYPE_14_RECORD_FIELD_VPS
#undef AN_TYPE_14_RECORD_FIELD_CGA
#undef AN_TYPE_14_RECORD_FIELD_BPX
#undef AN_TYPE_14_RECORD_FIELD_FGP
#undef AN_TYPE_14_RECORD_FIELD_PPD
#undef AN_TYPE_14_RECORD_FIELD_PPC
#undef AN_TYPE_14_RECORD_FIELD_SHPS
#undef AN_TYPE_14_RECORD_FIELD_SVPS

#undef AN_TYPE_14_RECORD_FIELD_AMP

#undef AN_TYPE_14_RECORD_FIELD_COM

#undef AN_TYPE_14_RECORD_FIELD_SEG
#undef AN_TYPE_14_RECORD_FIELD_NQM
#undef AN_TYPE_14_RECORD_FIELD_SQM

#undef AN_TYPE_14_RECORD_FIELD_FQM

#undef AN_TYPE_14_RECORD_FIELD_ASEG
#undef AN_TYPE_14_RECORD_FIELD_SCF
#undef AN_TYPE_14_RECORD_FIELD_SIF

#undef AN_TYPE_14_RECORD_FIELD_DMM
#undef AN_TYPE_14_RECORD_FIELD_FAP

#undef AN_TYPE_14_RECORD_FIELD_SUB
#undef AN_TYPE_14_RECORD_FIELD_CON

#undef AN_TYPE_14_RECORD_FIELD_FCT
#undef AN_TYPE_14_RECORD_FIELD_ANN
#undef AN_TYPE_14_RECORD_FIELD_DUI
#undef AN_TYPE_14_RECORD_FIELD_MMS

#undef AN_TYPE_14_RECORD_FIELD_SAN
#undef AN_TYPE_14_RECORD_FIELD_EFR
#undef AN_TYPE_14_RECORD_FIELD_ASC
#undef AN_TYPE_14_RECORD_FIELD_HAS
#undef AN_TYPE_14_RECORD_FIELD_SOR
#undef AN_TYPE_14_RECORD_FIELD_GEO

#undef AN_TYPE_14_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_14_RECORD_FIELD_UDF_TO
#undef AN_TYPE_14_RECORD_FIELD_UDF_TO_V5

#undef AN_TYPE_14_RECORD_FIELD_DATA

#undef AN_TYPE_14_RECORD_MAX_AMPUTATION_COUNT
#undef AN_TYPE_14_RECORD_MAX_AMPUTATION_COUNT_V5
#undef AN_TYPE_14_RECORD_MAX_SEGMENT_COUNT_V5
#undef AN_TYPE_14_RECORD_MAX_NIST_QUALITY_METRIC_COUNT
#undef AN_TYPE_14_RECORD_MAX_NIST_QUALITY_METRIC_COUNT_V5
#undef AN_TYPE_14_RECORD_MAX_ALTERNATE_SEGMENT_COUNT
#undef AN_TYPE_14_RECORD_MAX_ALTERNATE_SEGMENT_COUNT_V5

#undef AN_TYPE_14_RECORD_MIN_ALTERNATE_SEGMENT_VERTEX_COUNT
#undef AN_TYPE_14_RECORD_MAX_ALTERNATE_SEGMENT_VERTEX_COUNT

#undef AN_TYPE_14_RECORD_MAX_SEGMENTATION_QUALITY_METRIC_COUNT_V5
#undef AN_TYPE_14_RECORD_MAX_SEGMENTATION_QUALITY_METRIC_COUNT_V52
#undef AN_TYPE_14_RECORD_MAX_FINGERPRINT_QUALITY_METRIC_COUNT_V5
#undef AN_TYPE_14_RECORD_MAX_FINGERPRINT_QUALITY_METRIC_COUNT_V52

#undef AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_EXCELLENT
#undef AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_VERY_GOOD
#undef AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_GOOD
#undef AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_FAIR
#undef AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_POOR
#undef AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_NOT_AVAILABLE
#undef AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_FAILED

#undef AN_TYPE_14_RECORD_MIN_SIMULTANEOUS_CAPTURE_ID
#undef AN_TYPE_14_RECORD_MAX_SIMULTANEOUS_CAPTURE_ID

#undef AN_TYPE_14_RECORD_FAP_10
#undef AN_TYPE_14_RECORD_FAP_20
#undef AN_TYPE_14_RECORD_FAP_30
#undef AN_TYPE_14_RECORD_FAP_40
#undef AN_TYPE_14_RECORD_FAP_45
#undef AN_TYPE_14_RECORD_FAP_50
#undef AN_TYPE_14_RECORD_FAP_60
#undef AN_TYPE_14_RECORD_FAP_145
#undef AN_TYPE_14_RECORD_FAP_150
#undef AN_TYPE_14_RECORD_FAP_160

const NInt AN_TYPE_14_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_14_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;
const NInt AN_TYPE_14_RECORD_FIELD_IMP = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_IMP;
const NInt AN_TYPE_14_RECORD_FIELD_SRC = AN_ASCII_BINARY_RECORD_FIELD_SRC;
const NInt AN_TYPE_14_RECORD_FIELD_FCD = AN_ASCII_BINARY_RECORD_FIELD_DAT;
const NInt AN_TYPE_14_RECORD_FIELD_HLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_14_RECORD_FIELD_VLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_14_RECORD_FIELD_SLC = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC;
const NInt AN_TYPE_14_RECORD_FIELD_HPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS;
const NInt AN_TYPE_14_RECORD_FIELD_VPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS;
const NInt AN_TYPE_14_RECORD_FIELD_CGA = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA;
const NInt AN_TYPE_14_RECORD_FIELD_BPX = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX;
const NInt AN_TYPE_14_RECORD_FIELD_FGP = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FGP;
const NInt AN_TYPE_14_RECORD_FIELD_PPD = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_PD;
const NInt AN_TYPE_14_RECORD_FIELD_PPC = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_PPC;
const NInt AN_TYPE_14_RECORD_FIELD_SHPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS;
const NInt AN_TYPE_14_RECORD_FIELD_SVPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS;

const NInt AN_TYPE_14_RECORD_FIELD_AMP = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_AMP;
const NInt AN_TYPE_14_RECORD_FIELD_COM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM;
const NInt AN_TYPE_14_RECORD_FIELD_SEG = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_SEG;

const NInt AN_TYPE_14_RECORD_FIELD_NQM = 22;
const NInt AN_TYPE_14_RECORD_FIELD_SQM = 23;

const NInt AN_TYPE_14_RECORD_FIELD_FQM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM;

const NInt AN_TYPE_14_RECORD_FIELD_ASEG = 25;
const NInt AN_TYPE_14_RECORD_FIELD_SCF = 26;
const NInt AN_TYPE_14_RECORD_FIELD_SIF = 27;

const NInt AN_TYPE_14_RECORD_FIELD_DMM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM;
const NInt AN_TYPE_14_RECORD_FIELD_FAP = 31;

const NInt AN_TYPE_14_RECORD_FIELD_SUB = AN_ASCII_BINARY_RECORD_FIELD_SUB;
const NInt AN_TYPE_14_RECORD_FIELD_CON = AN_ASCII_BINARY_RECORD_FIELD_CON;

const NInt AN_TYPE_14_RECORD_FIELD_FCT = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FCT;
const NInt AN_TYPE_14_RECORD_FIELD_ANN = AN_ASCII_BINARY_RECORD_FIELD_ANN;
const NInt AN_TYPE_14_RECORD_FIELD_DUI = AN_ASCII_BINARY_RECORD_FIELD_DUI;
const NInt AN_TYPE_14_RECORD_FIELD_MMS = AN_ASCII_BINARY_RECORD_FIELD_MMS;

const NInt AN_TYPE_14_RECORD_FIELD_SAN = AN_ASCII_BINARY_RECORD_FIELD_SAN;
const NInt AN_TYPE_14_RECORD_FIELD_EFR = AN_ASCII_BINARY_RECORD_FIELD_EFR;
const NInt AN_TYPE_14_RECORD_FIELD_ASC = AN_ASCII_BINARY_RECORD_FIELD_ASC;
const NInt AN_TYPE_14_RECORD_FIELD_HAS = AN_ASCII_BINARY_RECORD_FIELD_HAS;
const NInt AN_TYPE_14_RECORD_FIELD_SOR = AN_ASCII_BINARY_RECORD_FIELD_SOR;
const NInt AN_TYPE_14_RECORD_FIELD_GEO = AN_ASCII_BINARY_RECORD_FIELD_GEO;

const NInt AN_TYPE_14_RECORD_FIELD_UDF_FROM = AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM;
const NInt AN_TYPE_14_RECORD_FIELD_UDF_TO = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO;
const NInt AN_TYPE_14_RECORD_FIELD_UDF_TO_V5 = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5;

const NInt AN_TYPE_14_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

const NInt AN_TYPE_14_RECORD_MAX_AMPUTATION_COUNT = 4;
const NInt AN_TYPE_14_RECORD_MAX_AMPUTATION_COUNT_V5 = 5;
const NInt AN_TYPE_14_RECORD_MAX_SEGMENT_COUNT_V5 = 5;
const NInt AN_TYPE_14_RECORD_MAX_NIST_QUALITY_METRIC_COUNT = 4;
const NInt AN_TYPE_14_RECORD_MAX_NIST_QUALITY_METRIC_COUNT_V5 = 5;
const NInt AN_TYPE_14_RECORD_MAX_ALTERNATE_SEGMENT_COUNT = 4;
const NInt AN_TYPE_14_RECORD_MAX_ALTERNATE_SEGMENT_COUNT_V5 = 5;

const NInt AN_TYPE_14_RECORD_MIN_ALTERNATE_SEGMENT_VERTEX_COUNT = 3;
const NInt AN_TYPE_14_RECORD_MAX_ALTERNATE_SEGMENT_VERTEX_COUNT = 99;

const NByte AN_TYPE_14_RECORD_MAX_SEGMENTATION_QUALITY_METRIC_COUNT_V5 = 5;
const NByte AN_TYPE_14_RECORD_MAX_SEGMENTATION_QUALITY_METRIC_COUNT_V52 = 45;
const NByte AN_TYPE_14_RECORD_MAX_FINGERPRINT_QUALITY_METRIC_COUNT_V5 = 5;
const NByte AN_TYPE_14_RECORD_MAX_FINGERPRINT_QUALITY_METRIC_COUNT_V52 = 45;

const NByte AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_EXCELLENT = 1;
const NByte AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_VERY_GOOD = 2;
const NByte AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_GOOD = 3;
const NByte AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_FAIR = 4;
const NByte AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_POOR = 5;
const NByte AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_NOT_AVAILABLE = 254;
const NByte AN_TYPE_14_RECORD_NIST_QUALITY_METRIC_SCORE_FAILED = 255;

const NInt AN_TYPE_14_RECORD_MIN_SIMULTANEOUS_CAPTURE_ID = 1;
const NInt AN_TYPE_14_RECORD_MAX_SIMULTANEOUS_CAPTURE_ID = 255;

const NByte AN_TYPE_14_RECORD_FAP_10 = 10;
const NByte AN_TYPE_14_RECORD_FAP_20 = 20;
const NByte AN_TYPE_14_RECORD_FAP_30 = 30;
const NByte AN_TYPE_14_RECORD_FAP_40 = 40;
const NByte AN_TYPE_14_RECORD_FAP_45 = 45;
const NByte AN_TYPE_14_RECORD_FAP_50 = 50;
const NByte AN_TYPE_14_RECORD_FAP_60 = 60;
const NByte AN_TYPE_14_RECORD_FAP_145 = 145;
const NByte AN_TYPE_14_RECORD_FAP_150 = 150;
const NByte AN_TYPE_14_RECORD_FAP_160 = 160;

class ANNistQualityMetric : public ANNistQualityMetric_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANNistQualityMetric)

public:
	ANNistQualityMetric(BdifFPPosition position, NByte score)
	{
		Position = position;
		Score = score;
	}
};

class ANFAlternateSegment : public ANFAlternateSegment_
{
	N_DECLARE_EQUATABLE_STRUCT_CLASS(ANFAlternateSegment)

public:
	ANFAlternateSegment(BdifFPPosition position)
	{
		Position = position;
	}
};

}}}

N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANNistQualityMetric)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANFAlternateSegment)

namespace Neurotec { namespace Biometrics { namespace Standards
{

class ANType14Record : public ANFPImageAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType14Record, ANFPImageAsciiBinaryRecord)

public:
	class NistQualityMetricCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANNistQualityMetric, ANType14Record,
		ANType14RecordGetNistQualityMetricCount, ANType14RecordGetNistQualityMetric, ANType14RecordGetNistQualityMetrics>
	{
		NistQualityMetricCollection(const ANType14Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType14Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANNistQualityMetric, ANType14Record,
			ANType14RecordGetNistQualityMetricCount, ANType14RecordGetNistQualityMetric, ANType14RecordGetNistQualityMetrics>::GetAll;

		void Set(NInt index, const ANNistQualityMetric & value)
		{
			NCheck(ANType14RecordSetNistQualityMetric(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANNistQualityMetric & value)
		{
			NInt index;
			NCheck(ANType14RecordAddNistQualityMetricEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANNistQualityMetric & value)
		{
			NCheck(ANType14RecordInsertNistQualityMetric(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType14RecordRemoveNistQualityMetricAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType14RecordClearNistQualityMetrics(this->GetOwnerHandle()));
		}
	};

	class SegmentationQualityMetricCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANFPQualityMetric, ANType14Record,
		ANType14RecordGetSegmentationQualityMetricCount, ANType14RecordGetSegmentationQualityMetric, ANType14RecordGetSegmentationQualityMetrics>
	{
		SegmentationQualityMetricCollection(const ANType14Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType14Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANFPQualityMetric, ANType14Record,
			ANType14RecordGetSegmentationQualityMetricCount, ANType14RecordGetSegmentationQualityMetric, ANType14RecordGetSegmentationQualityMetrics>::GetAll;

		void Set(NInt index, const ANFPQualityMetric & value)
		{
			NCheck(ANType14RecordSetSegmentationQualityMetric(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANFPQualityMetric & value)
		{
			NInt index;
			NCheck(ANType14RecordAddSegmentationQualityMetricEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANFPQualityMetric & value)
		{
			NCheck(ANType14RecordInsertSegmentationQualityMetric(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType14RecordRemoveSegmentationQualityMetricAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType14RecordClearSegmentationQualityMetrics(this->GetOwnerHandle()));
		}
	};

	class AlternateSegmentCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANFAlternateSegment, ANType14Record,
		ANType14RecordGetAlternateSegmentCount, ANType14RecordGetAlternateSegment, ANType14RecordGetAlternateSegments>
	{
		AlternateSegmentCollection(const ANType14Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType14Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANFAlternateSegment, ANType14Record,
			ANType14RecordGetAlternateSegmentCount, ANType14RecordGetAlternateSegment, ANType14RecordGetAlternateSegments>::GetAll;

		void Set(NInt index, const ANFAlternateSegment & value)
		{
			NCheck(ANType14RecordSetAlternateSegment(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANFAlternateSegment & value)
		{
			NInt index;
			NCheck(ANType14RecordAddAlternateSegmentEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANFAlternateSegment & value)
		{
			NCheck(ANType14RecordInsertAlternateSegment(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType14RecordRemoveAlternateSegmentAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType14RecordClearAlternateSegments(this->GetOwnerHandle()));
		}
	};

	class AlternateSegmentVerticesCollection : public ::Neurotec::NObjectPartBase<ANType14Record>
	{
		AlternateSegmentVerticesCollection(const ANType14Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType14Record;
	public:
		NInt GetCount(NInt baseIndex) const
		{
			NInt value;
			NCheck(ANType14RecordGetAlternateSegmentVertexCount(this->GetOwnerHandle(), baseIndex, &value));
			return value;
		}

		void Get(NInt baseIndex, NInt index, ::Neurotec::Geometry::NPoint * pValue) const
		{
			NCheck(ANType14RecordGetAlternateSegmentVertex(this->GetOwnerHandle(), baseIndex, index, pValue));
		}

		::Neurotec::Geometry::NPoint Get(NInt baseIndex, NInt index) const
		{
			::Neurotec::Geometry::NPoint value;
			NCheck(ANType14RecordGetAlternateSegmentVertex(this->GetOwnerHandle(), baseIndex, index, &value));
			return value;
		}

		NArrayWrapper< ::Neurotec::Geometry::NPoint> GetAll(NInt baseIndex) const
		{
			::Neurotec::Geometry::NPoint::NativeType * arValues = NULL;
			NInt valueCount = 0;
			NCheck(ANType14RecordGetAlternateSegmentVertices(this->GetOwnerHandle(), baseIndex, &arValues, &valueCount));
			return NArrayWrapper< ::Neurotec::Geometry::NPoint>(arValues, valueCount);
		}

		void Set(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType14RecordSetAlternateSegmentVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		NInt Add(NInt baseIndex, const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType14RecordAddAlternateSegmentVertexEx(this->GetOwnerHandle(), baseIndex, &value, &index));
			return index;
		}

		void Insert(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType14RecordInsertAlternateSegmentVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		void RemoveAt(NInt baseIndex, NInt index)
		{
			NCheck(ANType14RecordRemoveAlternateSegmentVertexAt(this->GetOwnerHandle(), baseIndex, index));
		}

		void Clear(NInt baseIndex)
		{
			NCheck(ANType14RecordClearAlternateSegmentVertices(this->GetOwnerHandle(), baseIndex));
		}
	};

private:

public:

	bool GetPrintPositionDescriptor(ANFPositionDescriptor * pValue) const
	{
		NBool hasValue;
		NCheck(ANType14RecordGetPrintPositionDescriptor(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	void SetPrintPositionDescriptor(const ANFPositionDescriptor * pValue)
	{
		NCheck(ANType14RecordSetPrintPositionDescriptor(GetHandle(), pValue));
	}

	NInt GetSimultaneousCaptureId() const
	{
		NInt value;
		NCheck(ANType14RecordGetSimultaneousCaptureId(GetHandle(), &value));
		return value;
	}

	void SetSimultaneousCaptureId(NInt value)
	{
		NCheck(ANType14RecordSetSimultaneousCaptureId(GetHandle(), value));
	}

	bool GetStitchedImageFlag() const
	{
		NBool value;
		NCheck(ANType14RecordGetStitchedImageFlag(GetHandle(), &value));
		return value != 0;
	}

	void SetStitchedImageFlag(bool value)
	{
		NCheck(ANType14RecordSetStitchedImageFlag(GetHandle(), value != 0));
	}

	NInt GetSubjectAcquisitionProfile() const
	{
		NInt value;
		NCheck(ANType14RecordGetSubjectAcquisitionProfile(GetHandle(), &value));
		return value;
	}

	void SetSubjectAcquisitionProfile(NInt value)
	{
		NCheck(ANType14RecordSetSubjectAcquisitionProfile(GetHandle(), value));
	}

	NistQualityMetricCollection GetNistQualityMetrics()
	{
		return NistQualityMetricCollection(*this);
	}

	const NistQualityMetricCollection GetNistQualityMetrics() const
	{
		return NistQualityMetricCollection(*this);
	}

	SegmentationQualityMetricCollection GetSegmentationQualityMetrics()
	{
		return SegmentationQualityMetricCollection(*this);
	}

	const SegmentationQualityMetricCollection GetSegmentationQualityMetrics() const
	{
		return SegmentationQualityMetricCollection(*this);
	}

	AlternateSegmentCollection GetAlternateSegments()
	{
		return AlternateSegmentCollection(*this);
	}

	const AlternateSegmentCollection GetAlternateSegments() const
	{
		return AlternateSegmentCollection(*this);
	}

	AlternateSegmentVerticesCollection GetAlternateSegmentsVertices()
	{
		return AlternateSegmentVerticesCollection(*this);
	}

	const AlternateSegmentVerticesCollection GetAlternateSegmentsVertices() const
	{
		return AlternateSegmentVerticesCollection(*this);
	}
};
}}}

#endif // !AN_TYPE_14_RECORD_HPP_INCLUDED
