#ifndef NA_ATTRIBUTES_HPP_INCLUDED
#define NA_ATTRIBUTES_HPP_INCLUDED

#include <Biometrics/NBiometricAttributes.hpp>
namespace Neurotec { namespace Biometrics
{
#include <Biometrics/NAAttributes.h>
}}

namespace Neurotec { namespace Biometrics
{

class NSignature;

class NAAttributes : public NBiometricAttributes
{
	N_DECLARE_OBJECT_CLASS(NAAttributes, NBiometricAttributes)

private:

	static HNAAttributes Create()
	{
		HNAAttributes handle;
		NCheck(NAAttributesCreate(&handle));
		return handle;
	}

public:
	NAAttributes()
		: NBiometricAttributes(Create(), true)
	{
	}

	NSignature GetOwner() const;
};

}}

#include <Biometrics/NSignature.hpp>

namespace Neurotec { namespace Biometrics
{

inline NSignature NAAttributes::GetOwner() const
{
	return NObject::GetOwner<NSignature>();
}

}}

#endif // !NA_ATTRIBUTES_HPP_INCLUDED
