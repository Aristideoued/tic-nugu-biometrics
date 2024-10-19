#ifndef NL_ATTRIBUTES_HPP_INCLUDED
#define NL_ATTRIBUTES_HPP_INCLUDED

#include <Biometrics/NBiometricAttributes.hpp>
#include <Biometrics/NLTemplate.hpp>
#include <Geometry/NGeometry.hpp>
#include <Images/NImage.hpp>
namespace Neurotec { namespace Biometrics
{
using ::Neurotec::Geometry::NRect_;
using ::Neurotec::Images::HNImage;
#include <Biometrics/NLAttributes.h>
}}

namespace Neurotec { namespace Biometrics
{

class NFace;

class NLAttributes : public NBiometricAttributes
{
	N_DECLARE_OBJECT_CLASS(NLAttributes, NBiometricAttributes)

public:
	class FeaturePointCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<NLFeaturePoint, NLAttributes,
		NLAttributesGetFeaturePointCount, NLAttributesGetFeaturePoint, NLAttributesGetFeaturePoints>
	{
		FeaturePointCollection(const NLAttributes & owner)
		{
			SetOwner(owner);
		}

		friend class NLAttributes;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(NLAttributesGetFeaturePointCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(NLAttributesSetFeaturePointCapacity(this->GetOwnerHandle(), value));
		}

		void Set(NInt index, const NLFeaturePoint & value)
		{
			NCheck(NLAttributesSetFeaturePoint(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const NLFeaturePoint & value)
		{
			NInt index;
			NCheck(NLAttributesAddFeaturePoint(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const NLFeaturePoint & value)
		{
			NCheck(NLAttributesInsertFeaturePoint(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(NLAttributesRemoveFeaturePointAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(NLAttributesClearFeaturePoints(this->GetOwnerHandle()));
		}
	};

private:
	static HNLAttributes Create()
	{
		HNLAttributes handle;
		NCheck(NLAttributesCreate(&handle));
		return handle;
	}

public:
	NLAttributes()
		: NBiometricAttributes(Create(), true)
	{
	}

	NFace GetOwner() const;

	::Neurotec::Geometry::NRect GetBoundingRect() const
	{
		::Neurotec::Geometry::NRect value;
		NCheck(NLAttributesGetBoundingRect(GetHandle(), &value));
		return value;
	}

	void SetBoundingRect(const ::Neurotec::Geometry::NRect & value)
	{
		NCheck(NLAttributesSetBoundingRect(GetHandle(), &value));
	}

	NFloat GetYaw() const
	{
		NFloat value;
		NCheck(NLAttributesGetYaw(GetHandle(), &value));
		return value;
	}

	void SetYaw(NFloat value)
	{
		NCheck(NLAttributesSetYaw(GetHandle(), value));
	}

	NFloat GetPitch() const
	{
		NFloat value;
		NCheck(NLAttributesGetPitch(GetHandle(), &value));
		return value;
	}

	void SetPitch(NFloat value)
	{
		NCheck(NLAttributesSetPitch(GetHandle(), value));
	}

	NFloat GetRoll() const
	{
		NFloat value;
		NCheck(NLAttributesGetRoll(GetHandle(), &value));
		return value;
	}

	void SetRoll(NFloat value)
	{
		NCheck(NLAttributesSetRoll(GetHandle(), value));
	}

	NLFeaturePoint GetRightEyeCenter() const
	{
		NLFeaturePoint value;
		NCheck(NLAttributesGetRightEyeCenter(GetHandle(), &value));
		return value;
	}

	void SetRightEyeCenter(const NLFeaturePoint & value)
	{
		NCheck(NLAttributesSetRightEyeCenter(GetHandle(), &value));
	}

	NLFeaturePoint GetLeftEyeCenter() const
	{
		NLFeaturePoint value;
		NCheck(NLAttributesGetLeftEyeCenter(GetHandle(), &value));
		return value;
	}

	void SetLeftEyeCenter(const NLFeaturePoint & value)
	{
		NCheck(NLAttributesSetLeftEyeCenter(GetHandle(), &value));
	}

	NLFeaturePoint GetNoseTip() const
	{
		NLFeaturePoint value;
		NCheck(NLAttributesGetNoseTip(GetHandle(), &value));
		return value;
	}

	void SetNoseTip(const NLFeaturePoint & value)
	{
		NCheck(NLAttributesSetNoseTip(GetHandle(), &value));
	}

	NLFeaturePoint GetMouthCenter() const
	{
		NLFeaturePoint value;
		NCheck(NLAttributesGetMouthCenter(GetHandle(), &value));
		return value;
	}

	void SetMouthCenter(const NLFeaturePoint & value)
	{
		NCheck(NLAttributesSetMouthCenter(GetHandle(), &value));
	}

	NGender GetGender() const
	{
		NGender value;
		NCheck(NLAttributesGetGender(GetHandle(), &value));
		return value;
	}

	void SetGender(NGender value)
	{
		NCheck(NLAttributesSetGender(GetHandle(), value));
	}

	NByte GetGenderConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetGenderConfidence(GetHandle(), &value));
		return value;
	}

	NInt GetBaseFrameIndex() const
	{
		NInt value;
		NCheck(NLAttributesGetBaseFrameIndex(GetHandle(), &value));
		return value;
	}

	void SetBaseFrameIndex(NInt value)
	{
		NCheck(NLAttributesSetBaseFrameIndex(GetHandle(), value));
	}

	::Neurotec::Images::NImage GetThumbnail() const
	{
		return GetObject<HandleType, ::Neurotec::Images::NImage>(NLAttributesGetThumbnail, true);
	}

	void SetThumbnail(const ::Neurotec::Images::NImage & value)
	{
		SetObject(NLAttributesSetThumbnail, value);
	}

	NLTemplate GetTemplate() const
	{
		return GetObject<HandleType, NLTemplate>(NLAttributesGetTemplate, true);
	}

	void SetTemplate(const NLTemplate & value)
	{
		NCheck(NLAttributesSetTemplate(GetHandle(), value.GetHandle()));
	}

	IO::NBuffer GetMocTemplate() const
	{
		return GetObject<HandleType, IO::NBuffer>(NLAttributesGetMocTemplate, true);
	}

	FeaturePointCollection GetFeaturePoints()
	{
		return FeaturePointCollection(*this);
	}

	const FeaturePointCollection GetFeaturePoints() const
	{
		return FeaturePointCollection(*this);
	}

	NLivenessAction GetLivenessAction() const
	{
		NLivenessAction value;
		NCheck(NLAttributesGetLivenessAction(GetHandle(), &value));
		return value;
	}

	NByte GetLivenessScore() const
	{
		NByte value;
		NCheck(NLAttributesGetLivenessScore(GetHandle(), &value));
		return value;
	}

	NFloat GetLivenessTargetYaw() const
	{
		NFloat value;
		NCheck(NLAttributesGetLivenessTargetYaw(GetHandle(), &value));
		return value;
	}

	NFloat GetLivenessTargetPitch() const
	{
		NFloat value;
		NCheck(NLAttributesGetLivenessTargetPitch(GetHandle(), &value));
		return value;
	}

	::Neurotec::Geometry::NRect GetTokenImageRect() const
	{
		::Neurotec::Geometry::NRect value;
		NCheck(NLAttributesGetTokenImageRect(GetHandle(), &value));
		return value;
	}

	void SetTokenImageRect(const ::Neurotec::Geometry::NRect & value)
	{
		NCheck(NLAttributesSetTokenImageRect(GetHandle(), &value));
	}

	NIcaoWarnings GetIcaoWarnings() const
	{
		NIcaoWarnings value;
		NCheck(NLAttributesGetIcaoWarnings(GetHandle(), &value));
		return value;
	}

	void SetIcaoWarnings(NIcaoWarnings value)
	{
		NCheck(NLAttributesSetIcaoWarnings(GetHandle(), value));
	}
};

}}

#include <Biometrics/NFace.hpp>

namespace Neurotec { namespace Biometrics
{

inline NFace NLAttributes::GetOwner() const
{
	return NObject::GetOwner<NFace>();
}

}}

#endif // !NL_ATTRIBUTES_HPP_INCLUDED
