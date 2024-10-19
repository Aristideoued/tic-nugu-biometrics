#ifndef AN_SUB_FIELD_HPP_INCLUDED
#define AN_SUB_FIELD_HPP_INCLUDED

#include <Core/NObject.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANSubField.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

class ANField;

class ANSubField : public NObject
{
	N_DECLARE_OBJECT_CLASS(ANSubField, NObject)

public:
	class ItemCollection : public ::Neurotec::Collections::NCollectionBase<NString, ANSubField,
		ANSubFieldGetItemCount, ANSubFieldGetItemN>
	{
		ItemCollection(const ANSubField & owner)
		{
			SetOwner(owner);
		}

		friend class ANSubField;
	
	public:
		NString GetName(NInt index, NString * pTypeName) const
		{
			HNString hName;
			HNString hTypeName;
			NCheck(ANSubFieldGetItemNameN(this->GetOwnerHandle(), index, &hName, &hTypeName));
			*pTypeName = NString(hTypeName, true);
			return NString(hName, true);
		}

		void SetName(NInt index, const NStringWrapper & name, const NStringWrapper & typeName)
		{
			NCheck(ANSubFieldSetItemNameN(this->GetOwnerHandle(), index, name.GetHandle(), typeName.GetHandle()));
		}

		NInt GetCapacity() const
		{
			NInt value;
			NCheck(ANSubFieldGetItemCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(ANSubFieldSetItemCapacity(this->GetOwnerHandle(), value));
		}

		void Set(NInt index, const NStringWrapper & value)
		{
			NCheck(ANSubFieldSetItemN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		NInt Add(const NStringWrapper & value)
		{
			NInt index;
			NCheck(ANSubFieldAddItemN(this->GetOwnerHandle(), value.GetHandle(), &index));
			return index;
		}

		NInt Add(const NStringWrapper & name, const NStringWrapper & typeName, const NStringWrapper & value)
		{
			NInt index;
			NCheck(ANSubFieldAddItemExN(this->GetOwnerHandle(), name.GetHandle(), typeName.GetHandle(), value.GetHandle(), &index));
			return index;
		}

		void Insert(NInt index, const NStringWrapper & value)
		{
			NCheck(ANSubFieldInsertItemN(this->GetOwnerHandle(), index, value.GetHandle()));
		}

		void Insert(NInt index, const NStringWrapper & name, const NStringWrapper & typeName, const NStringWrapper & value)
		{
			NCheck(ANSubFieldInsertItemExN(this->GetOwnerHandle(), index, name.GetHandle(), typeName.GetHandle(), value.GetHandle()));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANSubFieldRemoveItemAt(this->GetOwnerHandle(), index));
		}

		void RemoveRange(NInt index, NInt count)
		{
			NCheck(ANSubFieldRemoveItemRange(this->GetOwnerHandle(), index, count));
		}

		::Neurotec::IO::NBuffer GetData(NInt index) const
		{
			HNBuffer hBuffer;
			NCheck(ANSubFieldGetItemDataN(this->GetOwnerHandle(), index, &hBuffer));
			return NTypeTraits< ::Neurotec::IO::NBuffer>::FromNative(hBuffer, true);
		}
	};

public:

	NString GetName() const
	{
		return GetString(ANSubFieldGetNameN);
	}

	void SetName(const NStringWrapper & name)
	{
		SetString(ANSubFieldSetNameN, name);
	}

	NString GetValue() const
	{
		return GetString(ANSubFieldGetValueN);
	}

	void SetValue(const NStringWrapper & value)
	{
		SetString(ANSubFieldSetValueN, value);
	}

	::Neurotec::IO::NBuffer GetData() const
	{
		return GetObject<HandleType, ::Neurotec::IO::NBuffer>(ANSubFieldGetDataN, true);
	}

	ItemCollection GetItems()
	{
		return ItemCollection(*this);
	}

	const ItemCollection GetItems() const
	{
		return ItemCollection(*this);
	}

	ANField GetOwner() const;
};

}}}

#include <Biometrics/Standards/ANField.hpp>

namespace Neurotec { namespace Biometrics { namespace Standards
{

inline ANField ANSubField::GetOwner() const
{
	return NObject::GetOwner<ANField>();
}

}}}

#endif // !AN_SUB_FIELD_HPP_INCLUDED
