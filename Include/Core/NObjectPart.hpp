#include <Core/NTypes.hpp>

#ifndef N_OBJECT_PART_HPP_INCLUDED
#define N_OBJECT_PART_HPP_INCLUDED

#include <Core/NObjectBase.hpp>

namespace Neurotec
{
#define N_CPP_API_HEADER_INCLUDED
#include <Core/NObjectPart.h>
namespace Reflection
{
class NObjectPartInfo;
}
}

namespace Neurotec
{

class NObjectPart : public NObject
{
	N_DECLARE_OBJECT_CLASS(NObjectPart, NObject)

public:
	::Neurotec::Reflection::NObjectPartInfo GetObjectPartInfo() const;
};

}

#include <Reflection/NObjectPartInfo.hpp>

namespace Neurotec
{

inline ::Neurotec::Reflection::NObjectPartInfo NObjectPart::GetObjectPartInfo() const
{
	HNObjectPartInfo hValue;
	NCheck(NObjectPartGetObjectPartInfo(GetHandle(), &hValue));
	return FromHandle< ::Neurotec::Reflection::NObjectPartInfo>(hValue);
}

}

#endif // !N_OBJECT_PART_HPP_INCLUDED
