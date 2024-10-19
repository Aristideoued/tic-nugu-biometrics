#ifndef N_OBJECT_PART_BASE_HPP_INCLUDED
#define N_OBJECT_PART_BASE_HPP_INCLUDED

#include <Core/NObjectBase.hpp>

namespace Neurotec
{
template<typename TOwner> class NObjectPartBase : public NObjectBase
{
public:
	typedef TOwner OwnerType;
	typedef typename TOwner::HandleType OwnerHandleType;

protected:
	NObject m_owner;

	NObjectPartBase()
		: m_owner(NULL)
	{
	}

	void SetOwner(const TOwner & owner)
	{
		this->m_owner = owner.GetHandle();
	}

public:
	OwnerType & GetOwner()
	{
		return static_cast<OwnerType &>(m_owner);
	}

	const OwnerType & GetOwner() const
	{
		return static_cast<const OwnerType &>(m_owner);
	}

	OwnerHandleType GetOwnerHandle() const
	{
		return (OwnerHandleType)m_owner.GetHandle();
	}

	bool operator==(const NObjectPartBase & other) const
	{
		return this->GetOwnerHandle() == other.GetOwnerHandle();
	}

	bool operator!=(const NObjectPartBase & other) const
	{
		return this->GetOwnerHandle() != other.GetOwnerHandle();
	}
};

}

#endif // !N_OBJECT_PART_BASE_HPP_INCLUDED
