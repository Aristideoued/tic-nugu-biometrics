#include <Biometrics/NFrictionRidge.hpp>

#ifndef N_FINGER_HPP_INCLUDED
#define N_FINGER_HPP_INCLUDED

namespace Neurotec { namespace Biometrics
{
#include <Biometrics/NFinger.h>
}}

namespace Neurotec { namespace Biometrics
{

class NFinger : public NFrictionRidge
{
	N_DECLARE_OBJECT_CLASS(NFinger, NFrictionRidge)

private:
	static HNFinger Create()
	{
		HNFinger handle;
		NCheck(NFingerCreate(&handle));
		return handle;
	}

public:
	NFinger()
		: NFrictionRidge(Create(), true)
	{
	}

	bool GetWrongHandWarning() const
	{
		NBool value;
		NCheck(NFingerGetWrongHandWarning(GetHandle(), &value));
		return value != NFalse;
	}

	void SetWrongHandWarning(bool value)
	{
		NCheck(NFingerSetWrongHandWarning(GetHandle(), value ? NTrue : NFalse));
	}

	bool GetTipsWarning() const
	{
		NBool value;
		NCheck(NFingerGetTipsWarning(GetHandle(), &value));
		return value != NFalse;
	}

	void SetTipsWarning(bool value)
	{
		NCheck(NFingerSetTipsWarning(GetHandle(), value ? NTrue : NFalse));
	}

	bool GetFingerAngleWarning() const
	{
		NBool value;
		NCheck(NFingerGetFingerAngleWarning(GetHandle(), &value));
		return value != NFalse;
	}

	void SetFingerAngleWarning(bool value)
	{
		NCheck(NFingerSetFingerAngleWarning(GetHandle(), value ? NTrue : NFalse));
	}

	bool GetUnnaturalHandGeometryWarning() const
	{
		NBool value;
		NCheck(NFingerGetUnnaturalHandGeometryWarning(GetHandle(), &value));
		return value != NFalse;
	}

	void SetUnnaturalHandGeometryWarning(bool value)
	{
		NCheck(NFingerSetUnnaturalHandGeometryWarning(GetHandle(), value ? NTrue : NFalse));
	}

	NByte GetUnnaturalHandGeometryConfidence() const
	{
		NByte value;
		NCheck(NFingerGetUnnaturalHandGeometryConfidence(GetHandle(), &value));
		return value;
	}

	void SetUnnaturalHandGeometryConfidence(NByte value)
	{
		NCheck(NFingerSetUnnaturalHandGeometryConfidence(GetHandle(), value));
	}
};

}}

#endif // !N_FINGER_HPP_INCLUDED
