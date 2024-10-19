#include <Biometrics/NBiometric.hpp>
#include <Biometrics/NAAttributes.hpp>

#ifndef N_SIGNATURE_HPP_INCLUDED
#define N_SIGNATURE_HPP_INCLUDED

#include <Images/NImage.hpp>
namespace Neurotec { namespace Biometrics
{
using ::Neurotec::Images::HNImage;
#include <Biometrics/NSignature.h>
}}

namespace Neurotec { namespace Biometrics
{

class NPenVector : public NPenVector_
{
	N_DECLARE_STRUCT_CLASS(NPenVector)

public:
	NPenVector(NUShort x, NUShort y, NByte pressure)
	{
		X = x;
		Y = y;
		Pressure = pressure;
	}
};

}}

N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics, NPenVector)

namespace Neurotec { namespace Biometrics
{

class NSignature : public NBiometric
{
	N_DECLARE_OBJECT_CLASS(NSignature, NBiometric)

public:
	class ObjectCollection : public ::Neurotec::Collections::NCollectionWithChangeNotifications<NAAttributes, NSignature,
		NSignatureGetObjectCount, NSignatureGetObject, NSignatureGetObjects,
		NSignatureAddObjectsCollectionChanged, NSignatureRemoveObjectsCollectionChanged>
	{
		ObjectCollection(const NSignature & owner)
		{
			SetOwner(owner);
		}

		friend class NSignature;
	};

	class VectorCollection : public ::Neurotec::Collections::NCollectionBase<NPenVector, NSignature,
		NSignatureGetVectorCount, NSignatureGetVector>
	{
		VectorCollection(const NSignature & owner)
		{
			SetOwner(owner);
		}

		friend class NSignature;
	public:
		NArrayWrapper<NPenVector> GetAll() const
		{
			NPenVector::NativeType * arValues = NULL;
			NInt valueCount = 0;
			NCheck(NSignatureGetVectors(this->GetOwnerHandle(), &arValues, &valueCount));
			return NArrayWrapper<NPenVector>(arValues, valueCount);
		}

		void Set(NInt index, const NPenVector & value)
		{
			NCheck(NSignatureSetVector(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const NPenVector & value)
		{
			NInt index;
			NCheck(NSignatureAddVector(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const NPenVector & value)
		{
			NCheck(NSignatureInsertVector(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(NSignatureRemoveVectorAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(NSignatureClearVectors(this->GetOwnerHandle()));
		}
	};

private:
	static HNSignature Create()
	{
		HNSignature handle;
		NCheck(NSignatureCreate(&handle));
		return handle;
	}

public:
	NSignature()
		: NBiometric(Create(), true)
	{
	}

	void SetImage(const Images::NImage & value)
	{
		NCheck(NSignatureSetImage(GetHandle(), value.GetHandle()));
	}

	Images::NImage GetImage() const
	{
		HNImage hImage;
		NCheck(NSignatureGetImage(GetHandle(), &hImage));
		return FromHandle<Images::NImage>(hImage);
	}

	ObjectCollection GetObjects()
	{
		return ObjectCollection(*this);
	}

	const ObjectCollection GetObjects() const
	{
		return ObjectCollection(*this);
	}

	VectorCollection GetVectors()
	{
		return VectorCollection(*this);
	}

	const VectorCollection GetVectors() const
	{
		return VectorCollection(*this);
	}
};

}}

#endif // !N_SIGNATURE_HPP_INCLUDED
