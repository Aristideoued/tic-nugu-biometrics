#ifndef AN_TYPE_16_RECORD_HPP_INCLUDED
#define AN_TYPE_16_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANImageAsciiBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType16Record.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_16_RECORD_FIELD_LEN
#undef AN_TYPE_16_RECORD_FIELD_IDC

#undef AN_TYPE_16_RECORD_FIELD_UDI

#undef AN_TYPE_16_RECORD_FIELD_SRC
#undef AN_TYPE_16_RECORD_FIELD_UTD
#undef AN_TYPE_16_RECORD_FIELD_HLL
#undef AN_TYPE_16_RECORD_FIELD_VLL
#undef AN_TYPE_16_RECORD_FIELD_SLC
#undef AN_TYPE_16_RECORD_FIELD_HPS
#undef AN_TYPE_16_RECORD_FIELD_VPS
#undef AN_TYPE_16_RECORD_FIELD_CGA
#undef AN_TYPE_16_RECORD_FIELD_BPX
#undef AN_TYPE_16_RECORD_FIELD_CSP
#undef AN_TYPE_16_RECORD_FIELD_SHPS
#undef AN_TYPE_16_RECORD_FIELD_SVPS
#undef AN_TYPE_16_RECORD_FIELD_COM
#undef AN_TYPE_16_RECORD_FIELD_UQS
#undef AN_TYPE_16_RECORD_FIELD_DMM

#undef AN_TYPE_16_RECORD_FIELD_ANN
#undef AN_TYPE_16_RECORD_FIELD_DUI
#undef AN_TYPE_16_RECORD_FIELD_MMS

#undef AN_TYPE_16_RECORD_FIELD_SAN
#undef AN_TYPE_16_RECORD_FIELD_EFR
#undef AN_TYPE_16_RECORD_FIELD_ASC
#undef AN_TYPE_16_RECORD_FIELD_HAS
#undef AN_TYPE_16_RECORD_FIELD_SOR
#undef AN_TYPE_16_RECORD_FIELD_GEO

#undef AN_TYPE_16_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_16_RECORD_FIELD_UDF_TO
#undef AN_TYPE_16_RECORD_FIELD_UDF_TO_V5

#undef AN_TYPE_16_RECORD_FIELD_DATA

#undef AN_TYPE_16_RECORD_MAX_USER_DEFINED_IMAGE_LENGTH

#undef AN_TYPE_16_RECORD_MAX_USER_DEFINED_QUALITY_SCORE_COUNT
#undef AN_TYPE_16_RECORD_MAX_USER_DEFINED_QUALITY_SCORE_COUNT_V5

const NInt AN_TYPE_16_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_16_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;

const NInt AN_TYPE_16_RECORD_FIELD_UDI = 3;

const NInt AN_TYPE_16_RECORD_FIELD_SRC = AN_ASCII_BINARY_RECORD_FIELD_SRC;
const NInt AN_TYPE_16_RECORD_FIELD_UTD = AN_ASCII_BINARY_RECORD_FIELD_DAT;
const NInt AN_TYPE_16_RECORD_FIELD_HLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_16_RECORD_FIELD_VLL = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_16_RECORD_FIELD_SLC = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SLC;
const NInt AN_TYPE_16_RECORD_FIELD_HPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_HPS;
const NInt AN_TYPE_16_RECORD_FIELD_VPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_VPS;
const NInt AN_TYPE_16_RECORD_FIELD_CGA = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CGA;
const NInt AN_TYPE_16_RECORD_FIELD_BPX = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_BPX;
const NInt AN_TYPE_16_RECORD_FIELD_CSP = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_CSP;
const NInt AN_TYPE_16_RECORD_FIELD_SHPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SHPS;
const NInt AN_TYPE_16_RECORD_FIELD_SVPS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_SVPS;
const NInt AN_TYPE_16_RECORD_FIELD_COM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_COM;
const NInt AN_TYPE_16_RECORD_FIELD_UQS = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_IQM;
const NInt AN_TYPE_16_RECORD_FIELD_DMM = AN_IMAGE_ASCII_BINARY_RECORD_FIELD_DMM;

const NInt AN_TYPE_16_RECORD_FIELD_ANN = AN_ASCII_BINARY_RECORD_FIELD_ANN;
const NInt AN_TYPE_16_RECORD_FIELD_DUI = AN_ASCII_BINARY_RECORD_FIELD_DUI;
const NInt AN_TYPE_16_RECORD_FIELD_MMS = AN_ASCII_BINARY_RECORD_FIELD_MMS;

const NInt AN_TYPE_16_RECORD_FIELD_SAN = AN_ASCII_BINARY_RECORD_FIELD_SAN;
const NInt AN_TYPE_16_RECORD_FIELD_EFR = AN_ASCII_BINARY_RECORD_FIELD_EFR;
const NInt AN_TYPE_16_RECORD_FIELD_ASC = AN_ASCII_BINARY_RECORD_FIELD_ASC;
const NInt AN_TYPE_16_RECORD_FIELD_HAS = AN_ASCII_BINARY_RECORD_FIELD_HAS;
const NInt AN_TYPE_16_RECORD_FIELD_SOR = AN_ASCII_BINARY_RECORD_FIELD_SOR;
const NInt AN_TYPE_16_RECORD_FIELD_GEO = AN_ASCII_BINARY_RECORD_FIELD_GEO;

const NInt AN_TYPE_16_RECORD_FIELD_UDF_FROM = AN_ASCII_BINARY_RECORD_FIELD_UDF_FROM;
const NInt AN_TYPE_16_RECORD_FIELD_UDF_TO = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO;
const NInt AN_TYPE_16_RECORD_FIELD_UDF_TO_V5 = AN_ASCII_BINARY_RECORD_FIELD_UDF_TO_V5;

const NInt AN_TYPE_16_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

const NInt AN_TYPE_16_RECORD_MAX_USER_DEFINED_IMAGE_LENGTH = 35;

const NByte AN_TYPE_16_RECORD_MAX_USER_DEFINED_QUALITY_SCORE_COUNT = 1;
const NByte AN_TYPE_16_RECORD_MAX_USER_DEFINED_QUALITY_SCORE_COUNT_V5 = 9;

class ANType16Record : public ANImageAsciiBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType16Record, ANImageAsciiBinaryRecord)

public:
	class UserDefinedQualityScoreCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<ANQualityMetric, ANType16Record,
		ANType16RecordGetUserDefinedQualityScoreCount, ANType16RecordGetUserDefinedQualityScoreEx, ANType16RecordGetUserDefinedQualityScores>
	{
		UserDefinedQualityScoreCollection(const ANType16Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType16Record;
	public:
		using ::Neurotec::Collections::NCollectionWithAllOutBase<ANQualityMetric, ANType16Record,
			ANType16RecordGetUserDefinedQualityScoreCount, ANType16RecordGetUserDefinedQualityScoreEx, ANType16RecordGetUserDefinedQualityScores>::GetAll;

		void Set(NInt index, const ANQualityMetric & value)
		{
			NCheck(ANType16RecordSetUserDefinedQualityScoreEx(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANQualityMetric & value)
		{
			NInt index;
			NCheck(ANType16RecordAddUserDefinedQualityScore(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANQualityMetric & value)
		{
			NCheck(ANType16RecordInsertUserDefinedQualityScore(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType16RecordRemoveUserDefinedQualityScoreAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType16RecordClearUserDefinedQualityScores(this->GetOwnerHandle()));
		}
	};

private:

public:

	NString GetUserDefinedImage() const
	{
		return GetString(ANType16RecordGetUserDefinedImageN);
	}

	void SetUserDefinedImage(const NStringWrapper & value)
	{
		return SetString(ANType16RecordSetUserDefinedImageN, value);
	}

	UserDefinedQualityScoreCollection GetUserDefinedQualityScores()
	{
		return UserDefinedQualityScoreCollection(*this);
	}

	const UserDefinedQualityScoreCollection GetUserDefinedQualityScores() const
	{
		return UserDefinedQualityScoreCollection(*this);
	}
};

}}}

#endif // !AN_TYPE_16_RECORD_HPP_INCLUDED
