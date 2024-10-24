#ifndef AN_TYPE_4_RECORD_HPP_INCLUDED
#define AN_TYPE_4_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANFImageBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType4Record.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_4_RECORD_FIELD_LEN
#undef AN_TYPE_4_RECORD_FIELD_IDC
#undef AN_TYPE_4_RECORD_FIELD_IMP
#undef AN_TYPE_4_RECORD_FIELD_FGP
#undef AN_TYPE_4_RECORD_FIELD_ISR
#undef AN_TYPE_4_RECORD_FIELD_HLL
#undef AN_TYPE_4_RECORD_FIELD_VLL
#undef AN_TYPE_4_RECORD_FIELD_GCA
#undef AN_TYPE_4_RECORD_FIELD_DATA

const NInt AN_TYPE_4_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_4_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;
const NInt AN_TYPE_4_RECORD_FIELD_IMP = AN_F_IMAGE_BINARY_RECORD_FIELD_IMP;
const NInt AN_TYPE_4_RECORD_FIELD_FGP = AN_F_IMAGE_BINARY_RECORD_FIELD_FGP;
const NInt AN_TYPE_4_RECORD_FIELD_ISR = AN_IMAGE_BINARY_RECORD_FIELD_ISR;
const NInt AN_TYPE_4_RECORD_FIELD_HLL = AN_IMAGE_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_4_RECORD_FIELD_VLL = AN_IMAGE_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_4_RECORD_FIELD_GCA = AN_F_IMAGE_BINARY_RECORD_FIELD_CA;
const NInt AN_TYPE_4_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;


class ANType4Record : public ANFImageBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType4Record, ANFImageBinaryRecord)

private:

public:

	ANImageCompressionAlgorithm GetCompressionAlgorithm() const
	{
		ANImageCompressionAlgorithm value;
		NCheck(ANType4RecordGetCompressionAlgorithm(GetHandle(), &value));
		return value;
	}

	NByte GetVendorCompressionAlgorithm() const
	{
		NByte value;
		NCheck(ANType4RecordGetVendorCompressionAlgorithm(GetHandle(), &value));
		return value;
	}

	void SetCompressionAlgorithm(ANImageCompressionAlgorithm value, NByte vendorValue)
	{
		NCheck(ANType4RecordSetCompressionAlgorithm(GetHandle(), value, vendorValue));
	}
};

}}}

#endif // !AN_TYPE_4_RECORD_HPP_INCLUDED
