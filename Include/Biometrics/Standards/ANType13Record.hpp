#ifndef AN_TYPE_13_RECORD_HPP_INCLUDED
#define AN_TYPE_13_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANFPImageAsciiBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType13Record.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANResolutionDetermination)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_13_RECORD_FIELD_LEN
#undef AN_TYPE_13_RECORD_FIELD_IDC
#undef AN_TYPE_13_RECORD_FIELD_IMP
#undef AN_TYPE_13_RECORD_FIELD_SRC
#undef AN_TYPE_13_RECORD_FIELD_LCD
#undef AN_TYPE_13_RECORD_FIELD_HLL
#undef AN_TYPE_13_RECORD_FIELD_VLL
#undef AN_TYPE_13_RECORD_FIELD_SLC
#undef AN_TYPE_13_RECORD_FIELD_HPS
#undef AN_TYPE_13_RECORD_FIELD_VPS
#undef AN_TYPE_13_RECORD_FIELD_CGA
#undef AN_TYPE_13_RECORD_FIELD_BPX
#undef AN_TYPE_13_RECORD_FIELD_FGP
#undef AN_TYPE_13_RECORD_FIELD_SPD
#undef AN_TYPE_13_RECORD_FIELD_PPC
#undef AN_TYPE_13_RECORD_FIELD_SHPS
#undef AN_TYPE_13_RECORD_FIELD_SVPS
#undef AN_TYPE_13_RECORD_FIELD_RSP
#undef AN_TYPE_13_RECORD_FIELD_REM
#undef AN_TYPE_13_RECORD_FIELD_COM
#undef AN_TYPE_13_RECORD_FIELD_LQM

#undef AN_TYPE_13_RECORD_FIELD_SUB
#undef AN_TYPE_13_RECORD_FIELD_CON

#undef AN_TYPE_13_RECORD_FIELD_FCT
#undef AN_TYPE_13_RECORD_FIELD_ANN
#undef AN_TYPE_13_RECORD_FIELD_DUI
#undef AN_TYPE_13_RECORD_FIELD_MMS

#undef AN_TYPE_13_RECORD_FIELD_SAN
#undef AN_TYPE_13_RECORD_FIELD_EFR
#undef AN_TYPE_13_RECORD_FIELD_ASC
#undef AN_TYPE_13_RECORD_FIELD_HAS
#undef AN_TYPE_13_RECORD_FIELD_SOR
#undef AN_TYPE_13_RECORD_FIELD_GEO

#undef AN_TYPE_13_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_13_RECORD_FIELD_UDF_TO
#undef AN_TYPE_13_RECORD_FIELD_UDF_TO_V5

#undef AN_TYPE_13_RECORD_FIELD_DATA

#undef AN_TYPE_13_RECORD_MAX_SEARCH_POSITION_DESCRIPTOR_COUNT
#undef AN_TYPE_13_RECORD_MAX_QUALITY_METRIC_COUNT
#undef AN_TYPE_13_RECORD_MAX_QUALITY_METRIC_COUNT_V5

#undef AN_TYPE_13_RECORD_MIN_RESOUTION_SCALE_LENGTH
#undef AN_TYPE_13_RECORD_MAX_RESOUTION_SCALE_LENGTH

#undef AN_TYPE_13_RECORD_MAX_RESOUTION_COORDINATE
#undef AN_TYPE_13_RECORD_MAX_RESOUTION_COMMENT_LENGTH

const NInt AN_TYPE_13_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_13_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;
const NInt AN_TYPE_13_RECORD_FIELD_IMP = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_IMP;
const NInt AN_TYPE_13_RECORD_FIELD_SRC = AN_ASCII_BINARY_RECORD_FIELD_SRC;
const NInt AN_TYPE_13_RECORD_FIELD_LCD = AN_ASCII_BINARY_RECORD_FIELD_DAT;
const NInt AN_TYPE_13_RECORD_FIELD_HLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_13_RECORD_FIELD_VLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_13_RECORD_FIELD_SLC = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC;
const NInt AN_TYPE_13_RECORD_FIELD_HPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS;
const NInt AN_TYPE_13_RECORD_FIELD_VPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS;
const NInt AN_TYPE_13_RECORD_FIELD_CGA = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA;
const NInt AN_TYPE_13_RECORD_FIELD_BPX = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX;
const NInt AN_TYPE_13_RECORD_FIELD_FGP = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FGP;
const NInt AN_TYPE_13_RECORD_FIELD_SPD = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_PD;
const NInt AN_TYPE_13_RECORD_FIELD_PPC = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_PPC;
const NInt AN_TYPE_13_RECORD_FIELD_SHPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS;
const NInt AN_TYPE_13_RECORD_FIELD_SVPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS;;

const NInt AN_TYPE_13_RECORD_FIELD_RSP = 18;
const NInt AN_TYPE_13_RECORD_FIELD_REM = 19;

const NInt AN_TYPE_13_RECORD_FIELD_COM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM;
const NInt AN_TYPE_13_RECORD_FIELD_LQM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM;

const NInt AN_TYPE_13_RECORD_FIELD_SUB = AN_ASCII_BINARY_RECORD_FIELD_SUB;
const NInt AN_TYPE_13_RECORD_FIELD_CON = AN_ASCII_BINARY_RECORD_FIELD_CON;

const NInt AN_TYPE_13_RECORD_FIELD_FCT = AN_FP_IMAGE_ASCII_BINARY_RECORD_FIELD_FCT;
const NInt AN_TYPE_13_RECORD_FIELD_ANN = AN_ASCII_BINARY_RECORD_FIELD_ANN;
const NInt AN_TYPE_13_RECORD_FIELD_DUI = AN_ASCII_BINARY_RECORD_FIELD_DUI;
const NInt AN_TYPE_13_RECORD_FIELD_MMS = AN_ASCII_BINARY_RECORD_FIELD_MMS;

const NInt AN_TYPE_13_RECORD_FIELD_SAN = AN_ASCII_BINARY_RECORD_FIELD_SAN;
const NInt AN_TYPE_13_RECORD_FIELD_EFR = AN_ASCII_BINARY_RECORD_FIELD_EFR;
const NInt AN_TYPE_13_RECORD_FIELD_ASC = AN_ASCII_BINARY_RECORD_FIELD_ASC;
const NInt AN_TYPE_13_RECORD_FIELD_HAS = AN_ASCII_BINARY_RECORD_FIELD_HAS;
const NInt AN_TYPE_13_RECORD_FIELD_SOR = AN_ASCII_BINARY_RECORD_FIELD_SOR;
const NInt AN_TYPE_13_RECORD_FIELD_GEO = AN_ASCII_BINARY_RECORD_FIELD_GEO;

const NInt AN_TYPE_13_RECORD_FIELD_UDF_FROM = AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM;
const NInt AN_TYPE_13_RECORD_FIELD_UDF_TO = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO;
const NInt AN_TYPE_13_RECORD_FIELD_UDF_TO_V5 = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5;

const NInt AN_TYPE_13_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

const NInt AN_TYPE_13_RECORD_MAX_SEARCH_POSITION_DESCRIPTOR_COUNT = 9;
const NInt AN_TYPE_13_RECORD_MAX_QUALITY_METRIC_COUNT = 4;
const NInt AN_TYPE_13_RECORD_MAX_QUALITY_METRIC_COUNT_V5 = 9;

const NInt AN_TYPE_13_RECORD_MIN_RESOUTION_SCALE_LENGTH = 1;
const NInt AN_TYPE_13_RECORD_MAX_RESOUTION_SCALE_LENGTH = 99900;

const NInt AN_TYPE_13_RECORD_MAX_RESOUTION_COORDINATE = 99999;
const NInt AN_TYPE_13_RECORD_MAX_RESOUTION_COMMENT_LENGTH = 99;

class ANResolutionMethod : public ANResolutionMethod_
{
	N_DECLARE_EQUATABLE_DISPOSABLE_STRUCT_CLASS(ANResolutionMethod)

public:
	ANResolutionMethod(ANResolutionDetermination resolutionDetermination, NInt scaleLength, ANMeasurementUnits scaleUnits, 
						NInt pointAX, NInt pointAY, NInt pointBX, NInt pointBY, const NStringWrapper & comment)
	{
		NCheck(ANResolutionMethodCreateN(resolutionDetermination, scaleLength, scaleUnits, pointAX, pointAY, 
			pointBX, pointBY, comment.GetHandle(), this));
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

N_DEFINE_DISPOSABLE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANResolutionMethod)

namespace Neurotec { namespace Biometrics { namespace Standards
{
class ANType13Record : public ANFPImageAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType13Record, ANFPImageAsciiBinaryRecord)

public:
	class SearchPositionDescriptorCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANFPositionDescriptor, ANType13Record,
		ANType13RecordGetSearchPositionDescriptorCount, ANType13RecordGetSearchPositionDescriptor, ANType13RecordGetSearchPositionDescriptors>
	{
		SearchPositionDescriptorCollection(const ANType13Record & owner)
		{
			SetOwner(owner);
		}

	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANFPositionDescriptor, ANType13Record,
			ANType13RecordGetSearchPositionDescriptorCount, ANType13RecordGetSearchPositionDescriptor, ANType13RecordGetSearchPositionDescriptors>::GetAll;

		void Set(NInt index, const ANFPositionDescriptor & value)
		{
			NCheck(ANType13RecordSetSearchPositionDescriptor(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANFPositionDescriptor & value)
		{
			NInt index;
			NCheck(ANType13RecordAddSearchPositionDescriptorEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANFPositionDescriptor & value)
		{
			NCheck(ANType13RecordInsertSearchPositionDescriptor(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType13RecordRemoveSearchPositionDescriptorAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType13RecordClearSearchPositionDescriptors(this->GetOwnerHandle()));
		}

		friend class ANType13Record;
	};

private:

public:

	bool GetRuler(ANRuler * pValue) const
	{
		NBool hasValue;
		NCheck(ANType13RecordGetRuler(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}
	void SetRuler(const ANRuler * pValue)
	{
		NCheck(ANType13RecordSetRuler(GetHandle(), pValue));
	}

	bool GetResolutionMethod(ANResolutionMethod * pValue) const
	{
		NBool hasValue;
		NCheck(ANType13RecordGetResolutionMethod(GetHandle(), pValue, &hasValue));
		return hasValue != 0;
	}
	void SetResolutionMethod(const ANResolutionMethod * pValue)
	{
		NCheck(ANType13RecordSetResolutionMethod(GetHandle(), pValue));
	}

	SearchPositionDescriptorCollection GetSearchPositionDescriptors()
	{
		return SearchPositionDescriptorCollection(*this);
	}

	const SearchPositionDescriptorCollection GetSearchPositionDescriptors() const
	{
		return SearchPositionDescriptorCollection(*this);
	}
};
}}}

#endif // !AN_TYPE_13_RECORD_HPP_INCLUDED
