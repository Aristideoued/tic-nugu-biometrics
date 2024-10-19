#ifndef AN_TYPE_20_RECORD_HPP_INCLUDED
#define AN_TYPE_20_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANImageAsciiBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType20Record.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSrnCardinality)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_20_RECORD_FIELD_LEN
#undef AN_TYPE_20_RECORD_FIELD_IDC

#undef AN_TYPE_20_RECORD_FIELD_CAR

#undef AN_TYPE_20_RECORD_FIELD_SRC
#undef AN_TYPE_20_RECORD_FIELD_SRD
#undef AN_TYPE_20_RECORD_FIELD_HLL
#undef AN_TYPE_20_RECORD_FIELD_VLL
#undef AN_TYPE_20_RECORD_FIELD_SLC
#undef AN_TYPE_20_RECORD_FIELD_THPS
#undef AN_TYPE_20_RECORD_FIELD_TVPS
#undef AN_TYPE_20_RECORD_FIELD_CGA
#undef AN_TYPE_20_RECORD_FIELD_BPX
#undef AN_TYPE_20_RECORD_FIELD_CSP

#undef AN_TYPE_20_RECORD_FIELD_AQS
#undef AN_TYPE_20_RECORD_FIELD_SFT
#undef AN_TYPE_20_RECORD_FIELD_SEG
#undef AN_TYPE_20_RECORD_FIELD_SHPS
#undef AN_TYPE_20_RECORD_FIELD_SVPS
#undef AN_TYPE_20_RECORD_FIELD_TIX

#undef AN_TYPE_20_RECORD_FIELD_COM

#undef AN_TYPE_20_RECORD_FIELD_SRN
#undef AN_TYPE_20_RECORD_FIELD_ICDR

#undef AN_TYPE_20_RECORD_FIELD_ANN
#undef AN_TYPE_20_RECORD_FIELD_DUI
#undef AN_TYPE_20_RECORD_FIELD_MMS

#undef AN_TYPE_20_RECORD_FIELD_SAN
#undef AN_TYPE_20_RECORD_FIELD_EFR
#undef AN_TYPE_20_RECORD_FIELD_ASC
#undef AN_TYPE_20_RECORD_FIELD_HAS
#undef AN_TYPE_20_RECORD_FIELD_SOR
#undef AN_TYPE_20_RECORD_FIELD_GEO

#undef AN_TYPE_20_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_20_RECORD_FIELD_UDF_TO_V5

#undef AN_TYPE_20_RECORD_FIELD_DATA

#undef AN_TYPE_20_RECORD_MAX_ACQUISITION_SOURCE_COUNT

#undef AN_TYPE_20_RECORD_MIN_SEGMENT_COUNT
#undef AN_TYPE_20_RECORD_MAX_SEGMENT_COUNT
#undef AN_TYPE_20_RECORD_MIN_SEGMENT_VERTEX_COUNT
#undef AN_TYPE_20_RECORD_MAX_SEGMENT_VERTEX_COUNT
#undef AN_TYPE_20_RECORD_MIN_SEGMENT_INTERNAL_FILE_POINTER_LENGTH
#undef AN_TYPE_20_RECORD_MAX_SEGMENT_INTERNAL_FILE_POINTER_LENGTH

#undef AN_TYPE_20_RECORD_MIN_AQS_ANALOG_TO_DIGITAL_CONVERSION_LENGTH
#undef AN_TYPE_20_RECORD_MAX_AQS_ANALOG_TO_DIGITAL_CONVERSION_LENGTH
#undef AN_TYPE_20_RECORD_MIN_AQS_RADIO_TRANSMISSION_FORMAT_LENGTH
#undef AN_TYPE_20_RECORD_MAX_AQS_RADIO_TRANSMISSION_FORMAT_LENGTH
#undef AN_TYPE_20_RECORD_MIN_AQS_SPECIAL_CHARACTERISTICS_LENGTH
#undef AN_TYPE_20_RECORD_MAX_AQS_SPECIAL_CHARACTERISTICS_LENGTH

#undef AN_TYPE_20_RECORD_MIN_REPRESENTATION_NUMBER
#undef AN_TYPE_20_RECORD_MAX_REPRESENTATION_NUMBER
#undef AN_TYPE_20_RECORD_REPRESENTATION_LENGTH


const NInt AN_TYPE_20_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_20_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;

const NInt AN_TYPE_20_RECORD_FIELD_CAR = 3;

const NInt AN_TYPE_20_RECORD_FIELD_SRC = AN_ASCII_BINARY_RECORD_FIELD_SRC;
const NInt AN_TYPE_20_RECORD_FIELD_SRD = AN_ASCII_BINARY_RECORD_FIELD_DAT;
const NInt AN_TYPE_20_RECORD_FIELD_HLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_20_RECORD_FIELD_VLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_20_RECORD_FIELD_SLC = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC;
const NInt AN_TYPE_20_RECORD_FIELD_THPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS;
const NInt AN_TYPE_20_RECORD_FIELD_TVPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS;
const NInt AN_TYPE_20_RECORD_FIELD_CGA = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA;
const NInt AN_TYPE_20_RECORD_FIELD_BPX = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX;
const NInt AN_TYPE_20_RECORD_FIELD_CSP = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CSP;

const NInt AN_TYPE_20_RECORD_FIELD_AQS = 14;
const NInt AN_TYPE_20_RECORD_FIELD_SFT = 15;
const NInt AN_TYPE_20_RECORD_FIELD_SEG = 16;
const NInt AN_TYPE_20_RECORD_FIELD_SHPS = 17;
const NInt AN_TYPE_20_RECORD_FIELD_SVPS = 18;
const NInt AN_TYPE_20_RECORD_FIELD_TIX = 19;

const NInt AN_TYPE_20_RECORD_FIELD_COM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM;

const NInt AN_TYPE_20_RECORD_FIELD_SRN = 21;
const NInt AN_TYPE_20_RECORD_FIELD_ICDR = 22;

const NInt AN_TYPE_20_RECORD_FIELD_ANN = AN_ASCII_BINARY_RECORD_FIELD_ANN;
const NInt AN_TYPE_20_RECORD_FIELD_DUI = AN_ASCII_BINARY_RECORD_FIELD_DUI;
const NInt AN_TYPE_20_RECORD_FIELD_MMS = AN_ASCII_BINARY_RECORD_FIELD_MMS;

const NInt AN_TYPE_20_RECORD_FIELD_SAN = AN_ASCII_BINARY_RECORD_FIELD_SAN;
const NInt AN_TYPE_20_RECORD_FIELD_EFR = AN_ASCII_BINARY_RECORD_FIELD_EFR;
const NInt AN_TYPE_20_RECORD_FIELD_ASC = AN_ASCII_BINARY_RECORD_FIELD_ASC;
const NInt AN_TYPE_20_RECORD_FIELD_HAS = AN_ASCII_BINARY_RECORD_FIELD_HAS;
const NInt AN_TYPE_20_RECORD_FIELD_GEO = AN_ASCII_BINARY_RECORD_FIELD_GEO;

const NInt AN_TYPE_20_RECORD_FIELD_UDF_FROM = AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM;
const NInt AN_TYPE_20_RECORD_FIELD_UDF_TO_V5 = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5;

const NInt AN_TYPE_20_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

const NInt AN_TYPE_20_RECORD_MAX_ACQUISITION_SOURCE_COUNT = 9;

const NInt AN_TYPE_20_RECORD_MIN_AQS_ANALOG_TO_DIGITAL_CONVERSION_LENGTH = 1;
const NInt AN_TYPE_20_RECORD_MAX_AQS_ANALOG_TO_DIGITAL_CONVERSION_LENGTH = 200;
const NInt AN_TYPE_20_RECORD_MIN_AQS_RADIO_TRANSMISSION_FORMAT_LENGTH    = 1;
const NInt AN_TYPE_20_RECORD_MAX_AQS_RADIO_TRANSMISSION_FORMAT_LENGTH    = 200;
const NInt AN_TYPE_20_RECORD_MIN_AQS_SPECIAL_CHARACTERISTICS_LENGTH      = 1;
const NInt AN_TYPE_20_RECORD_MAX_AQS_SPECIAL_CHARACTERISTICS_LENGTH      = 200;

const NInt AN_TYPE_20_RECORD_MIN_REPRESENTATION_NUMBER = 1;
const NInt AN_TYPE_20_RECORD_MAX_REPRESENTATION_NUMBER = 255;
const NInt AN_TYPE_20_RECORD_REPRESENTATION_LENGTH     = 3;

const NByte AN_TYPE_20_RECORD_MIN_SEGMENT_COUNT = 1;
const NByte AN_TYPE_20_RECORD_MAX_SEGMENT_COUNT = 99;
const NByte AN_TYPE_20_RECORD_MIN_SEGMENT_VERTEX_COUNT = 3;
const NByte AN_TYPE_20_RECORD_MAX_SEGMENT_VERTEX_COUNT = 99;
const NByte AN_TYPE_20_RECORD_MIN_SEGMENT_INTERNAL_FILE_POINTER_LENGTH = 1;
const NByte AN_TYPE_20_RECORD_MAX_SEGMENT_INTERNAL_FILE_POINTER_LENGTH = 15;

}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{
class ANType20Record : public ANImageAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType20Record, ANImageAsciiBinaryRecord)

public:
	class AcquisitionSourceCollection : public ::Neurotec::Collections::NCollectionBase<ANAcquisitionSource, ANType20Record,
		ANType20RecordGetAcquisitionSourceCount, ANType20RecordGetAcquisitionSource>
	{
		AcquisitionSourceCollection(const ANType20Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANAcquisitionSource & value)
		{
			NCheck(ANType20RecordSetAcquisitionSource(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANAcquisitionSource & value)
		{
			NInt index;
			NCheck(ANType20RecordAddAcquisitionSource(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANAcquisitionSource & value)
		{
			NCheck(ANType20RecordInsertAcquisitionSource(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType20RecordRemoveAcquisitionSourceAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType20RecordClearAcquisitionSources(this->GetOwnerHandle()));
		}

		friend class ANType20Record;
	};

	class SegmentCollection : public ::Neurotec::Collections::NCollectionBase<ANSegment, ANType20Record,
		ANType20RecordGetSegmentCount, ANType20RecordGetSegment>
	{
		SegmentCollection(const ANType20Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANSegment & value)
		{
			NCheck(ANType20RecordSetSegment(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSegment & value)
		{
			NInt index;
			NCheck(ANType20RecordAddSegment(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSegment & value)
		{
			NCheck(ANType20RecordInsertSegment(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType20RecordRemoveSegmentAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType20RecordClearSegments(this->GetOwnerHandle()));
		}

		friend class ANType20Record;
	};

	class SegmentVerticesCollection : public ::Neurotec::NObjectPartBase<ANType20Record>
	{
		SegmentVerticesCollection(const ANType20Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType20Record;
	public:
		NInt GetCount(NInt baseIndex) const
		{
			NInt value;
			NCheck(ANType20RecordGetSegmentVertexCount(this->GetOwnerHandle(), baseIndex, &value));
			return value;
		}

		void Get(NInt baseIndex, NInt index, ::Neurotec::Geometry::NPoint * pValue) const
		{
			NCheck(ANType20RecordGetSegmentVertex(this->GetOwnerHandle(), baseIndex, index, pValue));
		}

		::Neurotec::Geometry::NPoint Get(NInt baseIndex, NInt index) const
		{
			::Neurotec::Geometry::NPoint value;
			NCheck(ANType20RecordGetSegmentVertex(this->GetOwnerHandle(), baseIndex, index, &value));
			return value;
		}

		NArrayWrapper< ::Neurotec::Geometry::NPoint> GetAll(NInt baseIndex) const
		{
			::Neurotec::Geometry::NPoint::NativeType * arValues = NULL;
			NInt valueCount = 0;
			NCheck(ANType20RecordGetSegmentVertices(this->GetOwnerHandle(), baseIndex, &arValues, &valueCount));
			return NArrayWrapper< ::Neurotec::Geometry::NPoint>(arValues, valueCount);
		}

		void Set(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType20RecordSetSegmentVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		NInt Add(NInt baseIndex, const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType20RecordAddSegmentVertex(this->GetOwnerHandle(), baseIndex, &value, &index));
			return index;
		}

		void Insert(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType20RecordInsertSegmentVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		void RemoveAt(NInt baseIndex, NInt index)
		{
			NCheck(ANType20RecordRemoveSegmentVertexAt(this->GetOwnerHandle(), baseIndex, index));
		}

		void Clear(NInt baseIndex)
		{
			NCheck(ANType20RecordClearSegmentVertices(this->GetOwnerHandle(), baseIndex));
		}
	};

	class TimeIndexCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANTimeIndex, ANType20Record,
		ANType20RecordGetTimeIndexCount, ANType20RecordGetTimeIndex, ANType20RecordGetTimeIndexes>
	{
		TimeIndexCollection(const ANType20Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType20Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANTimeIndex, ANType20Record,
			ANType20RecordGetTimeIndexCount, ANType20RecordGetTimeIndex, ANType20RecordGetTimeIndexes>::GetAll;

		void Set(NInt index, const ANTimeIndex & value)
		{
			NCheck(ANType20RecordSetTimeIndex(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANTimeIndex & value)
		{
			NInt index;
			NCheck(ANType20RecordAddTimeIndex(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANTimeIndex & value)
		{
			NCheck(ANType20RecordInsertTimeIndex(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType20RecordRemoveTimeIndexAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType20RecordClearTimeIndexes(this->GetOwnerHandle()));
		}
	};

private:

public:
	static NType ANSrnCardinalityNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSrnCardinality), true);
	}

	ANSrnCardinality GetSrnCardinality() const
	{
		ANSrnCardinality value;
		NCheck(ANType20RecordGetSrnCardinality(GetHandle(), &value));
		return value;
	}

	void SetSrnCardinality(ANSrnCardinality value)
	{
		NCheck(ANType20RecordSetSrnCardinality(GetHandle(), value));
	}

	bool GetSourceRepresentationFormat(ANFileFormat * pValue) const
	{
		NBool hasValue;
		NCheck(ANType20RecordGetSourceRepresentationFormat(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}

	NString GetSourceRepresentationFormatFileType() const
	{
		return GetString(ANType20RecordGetSourceRepresentationFormatFileTypeN);
	}

	NString GetSourceRepresentationFormatDecodingInstructions() const
	{
		return GetString(ANType20RecordGetSourceRepresentationFormatDecodingInstructionsN);
	}

	void SetSourceRepresentationFormat(const ANFileFormat * pValue)
	{
		NCheck(ANType20RecordSetSourceRepresentationFormatEx(GetHandle(), pValue));
	}

	void SetSourceRepresentationFormat(const NStringWrapper & fileType, const NStringWrapper & decodingInstructions)
	{
		NCheck(ANType20RecordSetSourceRepresentationFormatN(GetHandle(), fileType.GetHandle(), decodingInstructions.GetHandle()));
	}

	NUInt GetRepresentationNumber() const
	{
		NUInt value;
		NCheck(ANType20RecordGetRepresentationNumber(GetHandle(), &value));
		return value;
	}

	void SetRepresentationNumber(NUInt value)
	{
		NCheck(ANType20RecordSetRepresentationNumber(GetHandle(), value));
	}

	NString GetCaptureDateRange() const
	{
		return GetString(ANType20RecordGetCaptureDateRangeN);
	}

	void SetCaptureDateRange(const NStringWrapper & value)
	{
		SetString(ANType20RecordSetCaptureDateRangeN, value);
	}

	AcquisitionSourceCollection GetAcquisitionSources()
	{
		return AcquisitionSourceCollection(*this);
	}

	const AcquisitionSourceCollection GetAcquisitionSources() const
	{
		return AcquisitionSourceCollection(*this);
	}

	SegmentCollection GetSegments()
	{
		return SegmentCollection(*this);
	}

	const SegmentCollection GetSegments() const
	{
		return SegmentCollection(*this);
	}


	SegmentVerticesCollection GetSegmentVertices()
	{
		return SegmentVerticesCollection(*this);
	}

	const SegmentVerticesCollection GetSegmentVertices() const
	{
		return SegmentVerticesCollection(*this);
	}


	TimeIndexCollection GetTimeIndexes()
	{
		return TimeIndexCollection(*this);
	}

	const TimeIndexCollection GetTimeIndexes() const
	{
		return TimeIndexCollection(*this);
	}
};
}}}

#endif // !AN_TYPE_20_RECORD_HPP_INCLUDED
