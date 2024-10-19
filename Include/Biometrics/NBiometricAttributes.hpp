#ifndef N_BIOMETRIC_ATTRIBUTES_HPP_INCLUDED
#define N_BIOMETRIC_ATTRIBUTES_HPP_INCLUDED

#include <Biometrics/NBiometricTypes.hpp>
#include <Core/NObject.hpp>
namespace Neurotec { namespace Biometrics
{
#include <Biometrics/NBiometricAttributes.h>
}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics, NBiometricAttributeId)

namespace Neurotec { namespace Biometrics
{

class NBiometricAttributes : public NObject
{
	N_DECLARE_OBJECT_CLASS(NBiometricAttributes, NObject)

public:
	class Attribute
	{
		NBiometricAttributeId id;
		NByte value;
		NByte threshold;
	public:
		Attribute(NBiometricAttributeId id, NByte value, NByte threshold)
			: id(id), value(value), threshold(threshold)
		{
		}

		NBiometricAttributeId GetId() const
		{
			return id;
		}

		NString GetName() const
		{
			HNString hValue;
			NCheck(NBiometricAttributesAttributeIdToNameN(id, &hValue));
			return NString(hValue, true);
		}

		NByte GetValue() const
		{
			return value;
		}

		NByte GetThreshold() const
		{
			return threshold;
		}
	};

	class AttributeIterator : public std::iterator<std::random_access_iterator_tag, Attribute>
	{
		const NBiometricAttributes * pAttributes;
		NInt index;
		NInt count;
		Attribute current;

		Attribute GetAttribute(NInt attrIndex) const
		{
			if (attrIndex >= 0 && attrIndex < count)
			{
				return Attribute(pAttributes->GetAttributeId(attrIndex),
					pAttributes->GetAttributeValue(attrIndex),
					pAttributes->GetAttributeThreshold(attrIndex));
			}
			else
			{
				return Attribute(nbaiQuality, 254, 50);
			}
		}

	public:
		using difference_type = NInt;

		AttributeIterator()
			: pAttributes(nullptr),
			index(0),
			count(0),
			current(GetAttribute(index))
		{
		}

		AttributeIterator(const NBiometricAttributes * pAttributes, NInt index)
			: pAttributes(pAttributes),
			index(index),
			count(pAttributes->GetAttributeCount()),
			current(GetAttribute(index))
		{
		}

		AttributeIterator& operator+=(difference_type rhs)
		{
			index += rhs;
			return *this;
		}

		AttributeIterator& operator-=(difference_type rhs)
		{
			index += rhs;
			return *this;
		}

		Attribute& operator*()
		{
			this->current = GetAttribute(index);
			return this->current;
		}

		Attribute* operator->()
		{
			this->current = GetAttribute(index);
			return &this->current;
		}

		Attribute operator[](NInt offset) const
		{
			return GetAttribute(index + offset);
		}

		AttributeIterator& operator++()
		{
			index++;
			return *this;
		}

		AttributeIterator& operator--()
		{
			index--;
			return *this;
		}

		AttributeIterator operator++(int)
		{
			AttributeIterator tmp = *this;
			index++;
			return tmp;
		}

		AttributeIterator operator--(int)
		{
			AttributeIterator tmp = *this;
			index--;
			return tmp;
		}

		difference_type operator-(const AttributeIterator& rhs) const
		{
			return index - rhs.index;
		}

		AttributeIterator operator+(difference_type rhs) const
		{
			AttributeIterator tmp = *this;
			tmp.index += rhs;
			return tmp;
		}

		AttributeIterator operator-(difference_type rhs) const
		{
			AttributeIterator tmp = *this;
			tmp.index -= rhs;
			return tmp;
		}

		bool operator==(const AttributeIterator& other) const
		{
			return this->index == other.index;
		}

		bool operator!=(const AttributeIterator& other) const
		{
			return this->index != other.index;
		}

		bool operator>(const AttributeIterator& other) const
		{
			return this->index > other.index;
		}

		bool operator<(const AttributeIterator& other) const
		{
			return this->index < other.index;
		}

		bool operator>=(const AttributeIterator& other) const
		{
			return this->index >= other.index;
		}

		bool operator<=(const AttributeIterator& other) const
		{
			return this->index <= other.index;
		}
	};

	static NType NBiometricAttributeIdNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(NBiometricAttributeId), true);
	}

	static NBiometricAttributeId AttributeNameToId(const NStringWrapper & name)
	{
		NBiometricAttributeId value;
		NCheck(NBiometricAttributesAttributeNameToIdN(name.GetHandle(), &value));
		return value;
	}

	NBiometricType GetBiometricType() const
	{
		NBiometricType value;
		NCheck(NBiometricAttributesGetBiometricType(GetHandle(), &value));
		return value;
	}

	NBiometricStatus GetStatus() const
	{
		NBiometricStatus value;
		NCheck(NBiometricAttributesGetStatus(GetHandle(), &value));
		return value;
	}

	void SetStatus(NBiometricStatus value)
	{
		NCheck(NBiometricAttributesSetStatus(GetHandle(), value));
	}

	NByte GetQuality() const
	{
		NByte value;
		NCheck(NBiometricAttributesGetQuality(GetHandle(), &value));
		return value;
	}

	void SetQuality(NByte value)
	{
		NCheck(NBiometricAttributesSetQuality(GetHandle(), value));
	}

	NByte GetDetectionConfidence() const
	{
		NByte value;
		NCheck(NBiometricAttributesGetDetectionConfidence(GetHandle(), &value));
		return value;
	}

	void SetDetectionConfidence(NByte value)
	{
		NCheck(NBiometricAttributesSetDetectionConfidence(GetHandle(), value));
	}

	NByte GetLivenessConfidence() const
	{
		NByte value;
		NCheck(NBiometricAttributesGetLivenessConfidence(GetHandle(), &value));
		return value;
	}

	void SetLivenessConfidence(NByte value)
	{
		NCheck(NBiometricAttributesSetLivenessConfidence(GetHandle(), value));
	}

	NInt GetAttributeCount() const
	{
		NInt value;
		NCheck(NBiometricAttributesGetAttributeCount(GetHandle(), &value));
		return value;
	}

	NBiometricAttributeId GetAttributeId(NInt index) const
	{
		NBiometricAttributeId value;
		NCheck(NBiometricAttributesGetAttributeId(GetHandle(), index, &value));
		return value;
	}

	NByte GetAttributeValue(NInt index) const
	{
		NByte value;
		NCheck(NBiometricAttributesGetAttributeValue(GetHandle(), index, &value));
		return value;
	}

	NByte GetAttributeThreshold(NInt index) const
	{
		NByte value;
		NCheck(NBiometricAttributesGetAttributeThreshold(GetHandle(), index, &value));
		return value;
	}

	NInt GetAttributeIndexOf(NBiometricAttributeId id) const
	{
		NInt value;
		NCheck(NBiometricAttributesGetAttributeIndexOf(GetHandle(), id, &value));
		return value;
	}

	NByte GetAttributeValue(NBiometricAttributeId id) const
	{
		NByte value;
		NCheck(NBiometricAttributesGetAttributeValueById(GetHandle(), id, &value));
		return value;
	}

	void SetAttributeValue(NBiometricAttributeId id, NByte value)
	{
		NCheck(NBiometricAttributesSetAttributeValueById(GetHandle(), id, value));
	}

	NObject GetChild()
	{
		HNObject hValue;
		NCheck(NBiometricAttributesGetChild(GetHandle(), &hValue));
		return FromHandle<NObject>(hValue);
	}

	NObject GetChildSubject()
	{
		HNObject hValue;
		NCheck(NBiometricAttributesGetChildSubject(GetHandle(), &hValue));
		return FromHandle<NObject>(hValue);
	}

	Attribute GetAttribute(NInt index) const
	{
		return Attribute(GetAttributeId(index), GetAttributeValue(index), GetAttributeThreshold(index));
	}

	Attribute operator[](NInt index) const
	{
		return GetAttribute(index);
	}

	Attribute operator[](NBiometricAttributeId id) const
	{
		NInt index = GetAttributeIndexOf(id);
		if (index >= 0)
		{
			return GetAttribute(index);
		}
		else
		{
			return Attribute(id, 254, 50);
		}
	}

	AttributeIterator begin() const
	{
		return AttributeIterator(this, 0);
	}

	AttributeIterator end() const
	{
		return AttributeIterator(this, GetAttributeCount());
	}

	AttributeIterator cbegin() const
	{
		return AttributeIterator(this, 0);
	}

	AttributeIterator cend() const
	{
		return AttributeIterator(this, GetAttributeCount());
	}
};

}}

#endif // !N_BIOMETRIC_ATTRIBUTES_HPP_INCLUDED
