#ifndef AN_TYPE_7_RECORD_HPP_INCLUDED
#define AN_TYPE_7_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType7Record.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_7_RECORD_FIELD_LEN
#undef AN_TYPE_7_RECORD_FIELD_IDC
#undef AN_TYPE_7_RECORD_FIELD_UDF

#undef AN_TYPE_7_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_7_RECORD_FIELD_UDF_TO

const NInt AN_TYPE_7_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_7_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;
const NInt AN_TYPE_7_RECORD_FIELD_UDF = AN_RECORD_FIELD_DATA;

const NInt AN_TYPE_7_RECORD_FIELD_UDF_FROM = AN_TYPE_7_RECORD_FIELD_IDC + 1;
const NInt AN_TYPE_7_RECORD_FIELD_UDF_TO = AN_RECORD_FIELD_DATA;

class ANType7Record : public ANBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType7Record, ANBinaryRecord)

private:

public:

};

}}}

#endif // !AN_TYPE_7_RECORD_HPP_INCLUDED
