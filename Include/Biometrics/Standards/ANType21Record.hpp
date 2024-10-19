#ifndef AN_TYPE_21_RECORD_HPP_INCLUDED
#define AN_TYPE_21_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANAsciiBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType21Record.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_21_RECORD_FIELD_LEN
#undef AN_TYPE_21_RECORD_FIELD_IDC

#undef AN_TYPE_21_RECORD_FIELD_SRC
#undef AN_TYPE_21_RECORD_FIELD_ACD

#undef AN_TYPE_21_RECORD_FIELD_MDI
#undef AN_TYPE_21_RECORD_FIELD_AFT
#undef AN_TYPE_21_RECORD_FIELD_SEG
#undef AN_TYPE_21_RECORD_FIELD_TIX

#undef AN_TYPE_21_RECORD_FIELD_COM

#undef AN_TYPE_21_RECORD_FIELD_ACN
#undef AN_TYPE_21_RECORD_FIELD_ICDR
#undef AN_TYPE_21_RECORD_FIELD_SUB
#undef AN_TYPE_21_RECORD_FIELD_CON

#undef AN_TYPE_21_RECORD_FIELD_ANN

#undef AN_TYPE_21_RECORD_FIELD_SAN
#undef AN_TYPE_21_RECORD_FIELD_EFR
#undef AN_TYPE_21_RECORD_FIELD_HAS
#undef AN_TYPE_21_RECORD_FIELD_GEO

#undef AN_TYPE_21_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_21_RECORD_FIELD_UDF_TO_V5

#undef AN_TYPE_21_RECORD_FIELD_DATA

#undef AN_TYPE_21_RECORD_MIN_MDI_LENGTH
#undef AN_TYPE_21_RECORD_MAX_MDI_LENGTH

#undef AN_TYPE_21_RECORD_MIN_ASSOCIATED_CONTEXT_NUMBER
#undef AN_TYPE_21_RECORD_MAX_ASSOCIATED_CONTEXT_NUMBER
#undef AN_TYPE_21_RECORD_ASSOCIATED_CONTEXT_LENGTH

#undef AN_TYPE_21_RECORD_MIN_SEGMENT_COUNT
#undef AN_TYPE_21_RECORD_MAX_SEGMENT_COUNT
#undef AN_TYPE_21_RECORD_MIN_SEGMENT_VERTEX_COUNT
#undef AN_TYPE_21_RECORD_MAX_SEGMENT_VERTEX_COUNT
#undef AN_TYPE_21_RECORD_MIN_SEGMENT_INTERNAL_FILE_POINTER_LENGTH
#undef AN_TYPE_21_RECORD_MAX_SEGMENT_INTERNAL_FILE_POINTER_LENGTH

#undef AN_TYPE_21_RECORD_MAX_COMMENT_LENGTH

const NInt AN_TYPE_21_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_21_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;

const NInt AN_TYPE_21_RECORD_FIELD_SRC = AN_ASCII_BINARY_RECORD_FIELD_SRC;
const NInt AN_TYPE_21_RECORD_FIELD_ACD = AN_ASCII_BINARY_RECORD_FIELD_DAT;

const NInt AN_TYPE_21_RECORD_FIELD_MDI = 6;
const NInt AN_TYPE_21_RECORD_FIELD_AFT = 15;
const NInt AN_TYPE_21_RECORD_FIELD_SEG = 16;
const NInt AN_TYPE_21_RECORD_FIELD_TIX = 19;
const NInt AN_TYPE_21_RECORD_FIELD_COM = 20;
const NInt AN_TYPE_21_RECORD_FIELD_ACN = 21;
const NInt AN_TYPE_21_RECORD_FIELD_ICDR = 22;
const NInt AN_TYPE_21_RECORD_FIELD_SUB = AN_ASCII_BINARY_RECORD_FIELD_SUB;
const NInt AN_TYPE_21_RECORD_FIELD_CON = AN_ASCII_BINARY_RECORD_FIELD_CON;

const NInt AN_TYPE_21_RECORD_FIELD_ANN = AN_ASCII_BINARY_RECORD_FIELD_ANN;
const NInt AN_TYPE_21_RECORD_FIELD_SAN = AN_ASCII_BINARY_RECORD_FIELD_SAN;
const NInt AN_TYPE_21_RECORD_FIELD_EFR = AN_ASCII_BINARY_RECORD_FIELD_EFR;
const NInt AN_TYPE_21_RECORD_FIELD_HAS = AN_ASCII_BINARY_RECORD_FIELD_HAS;
const NInt AN_TYPE_21_RECORD_FIELD_GEO = AN_ASCII_BINARY_RECORD_FIELD_GEO;

const NInt AN_TYPE_21_RECORD_FIELD_UDF_FROM   = AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM;
const NInt AN_TYPE_21_RECORD_FIELD_UDF_TO_V5 = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5;

const NInt AN_TYPE_21_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

const NInt AN_TYPE_21_RECORD_MIN_MDI_LENGTH = 1;
const NInt AN_TYPE_21_RECORD_MAX_MDI_LENGTH = 500;

const NInt AN_TYPE_21_RECORD_MIN_ASSOCIATED_CONTEXT_NUMBER = 1;
const NInt AN_TYPE_21_RECORD_MAX_ASSOCIATED_CONTEXT_NUMBER = 255;
const NInt AN_TYPE_21_RECORD_ASSOCIATED_CONTEXT_LENGTH     = 3;

const NByte AN_TYPE_21_RECORD_MIN_SEGMENT_COUNT = 1;
const NByte AN_TYPE_21_RECORD_MAX_SEGMENT_COUNT = 99;
const NByte AN_TYPE_21_RECORD_MIN_SEGMENT_VERTEX_COUNT = 3;
const NByte AN_TYPE_21_RECORD_MAX_SEGMENT_VERTEX_COUNT = 99;
const NByte AN_TYPE_21_RECORD_MIN_SEGMENT_INTERNAL_FILE_POINTER_LENGTH = 1;
const NByte AN_TYPE_21_RECORD_MAX_SEGMENT_INTERNAL_FILE_POINTER_LENGTH = 15;

const NInt AN_TYPE_21_RECORD_MAX_COMMENT_LENGTH = 126;

class ANMedicalDevice : public ANMedicalDevice_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANMedicalDevice)

public:
	ANMedicalDevice(const NStringWrapper & deviceType, const NStringWrapper & deviceManufacturer, const NStringWrapper & deviceMake,
		const NStringWrapper & deviceModel, const NStringWrapper & deviceSerialNumber, const NStringWrapper & comment)
	{
		NCheck(ANMedicalDeviceCreateN(deviceType.GetHandle(), deviceManufacturer.GetHandle(), deviceMake.GetHandle(), deviceModel.GetHandle(), deviceSerialNumber.GetHandle(), comment.GetHandle(), this));
	}

	NString GetDeviceType() const
	{
		return NString(hDeviceType, false);
	}
	void SetDeviceType(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hDeviceType));
	}

	NString GetDeviceManufacturer() const
	{
		return NString(hDeviceManufacturer, false);
	}
	void SetDeviceManufacturer(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hDeviceManufacturer));
	}

	NString GetDeviceMake() const
	{
		return NString(hDeviceMake, false);
	}
	void SetDeviceMake(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hDeviceMake));
	}

	NString GetDeviceModel() const
	{
		return NString(hDeviceModel, false);
	}
	void SetDeviceModel(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hDeviceModel));
	}

	NString GetDeviceSerialNumber() const
	{
		return NString(hDeviceSerialNumber, false);
	}
	void SetDeviceSerialNumber(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hDeviceSerialNumber));
	}

	NString GetComment() const
	{
		return NString(hComment, false);
	}
	void SetComment(const NStringWrapper & value)
	{
		NCheck(NStringSet(value.GetHandle(), &hComment));
	}
};

}}}

N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANMedicalDevice)

namespace Neurotec { namespace Biometrics { namespace Standards
{

class ANType21Record : public ANAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType21Record, ANAsciiBinaryRecord)

public:
	class MedicalDeviceCollection : public ::Neurotec::Collections::NCollectionBase<ANMedicalDevice, ANType21Record,
		ANType21RecordGetMedicalDeviceCount, ANType21RecordGetMedicalDevice>
	{
		MedicalDeviceCollection(const ANType21Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANMedicalDevice & value)
		{
			NCheck(ANType21RecordSetMedicalDevice(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANMedicalDevice & value)
		{
			NInt index;
			NCheck(ANType21RecordAddMedicalDevice(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANMedicalDevice & value)
		{
			NCheck(ANType21RecordInsertMedicalDevice(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType21RecordRemoveMedicalDeviceAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType21RecordClearMedicalDevices(this->GetOwnerHandle()));
		}

		friend class ANType21Record;
	};

	class SegmentCollection : public ::Neurotec::Collections::NCollectionBase<ANSegment, ANType21Record,
		ANType21RecordGetSegmentCount, ANType21RecordGetSegment>
	{
		SegmentCollection(const ANType21Record & owner)
		{
			SetOwner(owner);
		}

	public:
		void Set(NInt index, const ANSegment & value)
		{
			NCheck(ANType21RecordSetSegment(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANSegment & value)
		{
			NInt index;
			NCheck(ANType21RecordAddSegment(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANSegment & value)
		{
			NCheck(ANType21RecordInsertSegment(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType21RecordRemoveSegmentAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType21RecordClearSegments(this->GetOwnerHandle()));
		}

		friend class ANType21Record;
	};

	class SegmentVerticesCollection : public ::Neurotec::NObjectPartBase<ANType21Record>
	{
		SegmentVerticesCollection(const ANType21Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType21Record;
	public:
		NInt GetCount(NInt baseIndex) const
		{
			NInt value;
			NCheck(ANType21RecordGetSegmentVertexCount(this->GetOwnerHandle(), baseIndex, &value));
			return value;
		}

		void Get(NInt baseIndex, NInt index, ::Neurotec::Geometry::NPoint * pValue) const
		{
			NCheck(ANType21RecordGetSegmentVertex(this->GetOwnerHandle(), baseIndex, index, pValue));
		}

		::Neurotec::Geometry::NPoint Get(NInt baseIndex, NInt index) const
		{
			::Neurotec::Geometry::NPoint value;
			NCheck(ANType21RecordGetSegmentVertex(this->GetOwnerHandle(), baseIndex, index, &value));
			return value;
		}

		NArrayWrapper< ::Neurotec::Geometry::NPoint> GetAll(NInt baseIndex) const
		{
			::Neurotec::Geometry::NPoint::NativeType * arValues = NULL;
			NInt valueCount = 0;
			NCheck(ANType21RecordGetSegmentVertices(this->GetOwnerHandle(), baseIndex, &arValues, &valueCount));
			return NArrayWrapper< ::Neurotec::Geometry::NPoint>(arValues, valueCount);
		}

		void Set(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType21RecordSetSegmentVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		NInt Add(NInt baseIndex, const ::Neurotec::Geometry::NPoint & value)
		{
			NInt index;
			NCheck(ANType21RecordAddSegmentVertex(this->GetOwnerHandle(), baseIndex, &value, &index));
			return index;
		}

		void Insert(NInt baseIndex, NInt index, const ::Neurotec::Geometry::NPoint & value)
		{
			NCheck(ANType21RecordInsertSegmentVertex(this->GetOwnerHandle(), baseIndex, index, &value));
		}

		void RemoveAt(NInt baseIndex, NInt index)
		{
			NCheck(ANType21RecordRemoveSegmentVertexAt(this->GetOwnerHandle(), baseIndex, index));
		}

		void Clear(NInt baseIndex)
		{
			NCheck(ANType21RecordClearSegmentVertices(this->GetOwnerHandle(), baseIndex));
		}
	};

	class TimeIndexCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANTimeIndex, ANType21Record,
		ANType21RecordGetTimeIndexCount, ANType21RecordGetTimeIndex, ANType21RecordGetTimeIndexes>
	{
		TimeIndexCollection(const ANType21Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType21Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANTimeIndex, ANType21Record,
			ANType21RecordGetTimeIndexCount, ANType21RecordGetTimeIndex, ANType21RecordGetTimeIndexes>::GetAll;

		void Set(NInt index, const ANTimeIndex & value)
		{
			NCheck(ANType21RecordSetTimeIndex(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANTimeIndex & value)
		{
			NInt index;
			NCheck(ANType21RecordAddTimeIndex(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANTimeIndex & value)
		{
			NCheck(ANType21RecordInsertTimeIndex(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType21RecordRemoveTimeIndexAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType21RecordClearTimeIndexes(this->GetOwnerHandle()));
		}
	};

private:


public:
	static NType ANSubjectStatusCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSubjectStatusCode), true);
	}
	static NType ANSubjectBodyStatusCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSubjectBodyStatusCode), true);
	}
	static NType ANSubjectBodyClassCodeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSubjectBodyClassCode), true);
	}

	bool GetAssociatedContextFormat(ANFileFormat * pValue) const
	{
		NBool hasValue;
		NCheck(ANType21RecordGetAssociatedContextFormat(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}
	NString GetAssociatedContextFormatFileType() const
	{
		return GetString(ANType21RecordGetAssociatedContextFormatFileTypeN);
	}
	NString GetAssociatedContextFormatDecodingInstructions() const
	{
		return GetString(ANType21RecordGetAssociatedContextFormatDecodingInstructionsN);
	}
	void SetAssociatedContextFormat(const ANFileFormat * pValue)
	{
		NCheck(ANType21RecordSetAssociatedContextFormatEx(GetHandle(), pValue));
	}
	void SetAssociatedContextFormat(const NStringWrapper & fileType, const NStringWrapper & decodingInstructions)
	{
		NCheck(ANType21RecordSetAssociatedContextFormatN(GetHandle(), fileType.GetHandle(), decodingInstructions.GetHandle()));
	}

	NString GetComment() const
	{
		return GetString(ANType21RecordGetCommentN);
	}
	void SetComment(const NStringWrapper & value)
	{
		SetString(ANType21RecordSetCommentN, value);
	}

	NUInt GetAssociatedContextNumber() const
	{
		NUInt value;
		NCheck(ANType21RecordGetAssociatedContextNumber(GetHandle(), &value));
		return value;
	}
	void SetAssociatedContextNumber(NUInt value)
	{
		NCheck(ANType21RecordSetAssociatedContextNumber(GetHandle(), value));
	}

	NString GetCaptureDateRange() const
	{
		return GetString(ANType21RecordGetCaptureDateRangeN);
	}
	void SetCaptureDateRange(const NStringWrapper & value)
	{
		SetString(ANType21RecordSetCaptureDateRangeN, value);
	}

	MedicalDeviceCollection GetMedicalDevices()
	{
		return MedicalDeviceCollection(*this);
	}
	const MedicalDeviceCollection GetMedicalDevices() const
	{
		return MedicalDeviceCollection(*this);
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

#endif // !AN_TYPE_21_RECORD_HPP_INCLUDED
