#ifndef N_OBJECTBASE_HPP_INCLUDED
#define N_OBJECTBASE_HPP_INCLUDED

#include <cstring>
#include <Core/NCallback.hpp>

namespace Neurotec
{
#define N_CPP_API_HEADER_INCLUDED
#include <Core/NTypes.h>
}

namespace Neurotec
{
namespace IO
{
extern "C"
{
N_DECLARE_OBJECT_TYPE(NBuffer, NObject)
N_DECLARE_OBJECT_TYPE(NStream, NObject)
}
}
namespace Reflection
{
extern "C"
{
N_DECLARE_OBJECT_TYPE(NParameterInfo, NObject)
N_DECLARE_OBJECT_TYPE(NMemberInfo, NObject)
N_DECLARE_OBJECT_TYPE(NEnumConstantInfo, NMemberInfo)
N_DECLARE_OBJECT_TYPE(NConstantInfo, NMemberInfo)
N_DECLARE_OBJECT_TYPE(NMethodInfo, NMemberInfo)
N_DECLARE_OBJECT_TYPE(NPropertyInfo, NMemberInfo)
N_DECLARE_OBJECT_TYPE(NEventInfo, NMemberInfo)
N_DECLARE_OBJECT_TYPE(NObjectPartInfo, NMemberInfo)
N_DECLARE_OBJECT_TYPE(NCollectionInfo, NObjectPartInfo)
N_DECLARE_OBJECT_TYPE(NDictionaryInfo, NObjectPartInfo)
N_DECLARE_OBJECT_TYPE(NArrayCollectionInfo, NObjectPartInfo)
}
}
namespace Collections
{
extern "C"
{
N_DECLARE_OBJECT_TYPE(NCollection, NObjectPart)
N_DECLARE_OBJECT_TYPE(NDictionary, NObjectPart)
N_DECLARE_OBJECT_TYPE(NArrayCollection, NObjectPart)
}
}
using ::Neurotec::IO::HNBuffer;
using ::Neurotec::IO::HNStream;
using ::Neurotec::Reflection::HNMemberInfo;
using ::Neurotec::Reflection::HNConstantInfo;
using ::Neurotec::Reflection::HNEnumConstantInfo;
using ::Neurotec::Reflection::HNMethodInfo;
using ::Neurotec::Reflection::HNPropertyInfo;
using ::Neurotec::Reflection::HNEventInfo;
using ::Neurotec::Reflection::HNObjectPartInfo;
using ::Neurotec::Reflection::HNCollectionInfo;
using ::Neurotec::Reflection::HNDictionaryInfo;
using ::Neurotec::Reflection::HNArrayCollectionInfo;
#include <Core/NObject.h>

class NValue;
class NPropertyBag;
template<typename T> class NArrayWrapper;
namespace IO
{
class NStream;
class NBuffer;
}
}
#include <Interop/NWindows.hpp>
#include <Core/NString.hpp>

namespace Neurotec
{

#undef N_OBJECT_REF_RET

const NUInt N_OBJECT_REF_RET = 0x00000010;

namespace Collections
{
template<typename TOwner> class NStringReadOnlyCollection;
template<typename TOwner> class NStringCollection;
}

class NObjectBase
{
protected:
	NObjectBase()
	{
	}

	NObjectBase(const NObjectBase&)
	{
	}

	NObjectBase& operator=(const NObjectBase&)
	{
		return *this;
	}

public:
	virtual ~NObjectBase()
	{
	}
};

class NType;

class NObject : public NObjectBase
{
private:
	typedef NType (* NativeTypeOfProc)();

private:
	HNObject m_handle;

public:
	class PropertyChangedEventArgs;

protected:
	template<typename F>
	class EventHandler;
	template<typename F>
	class PropertyChangedEventHandler;

	void SetHandle(HNObject handle, bool claimHandle = false)
	{
		if (this->m_handle == handle)
			return;
		if (this->m_handle)
		{
			Unref();
			this->m_handle = NULL;
		}
		this->m_handle = handle;
		if (this->m_handle && !claimHandle)
			Ref();
	}

	template<typename THandle> NString GetString(NResult (N_CALLBACK pGetString)(THandle handle, HNString * phValue)) const;
	template<typename THandle> void SetString(NResult (N_CALLBACK pSetString)(THandle handle, HNString hValue), const NStringWrapper & value);
	template<typename THandle, typename T> T GetObject(NResult (N_CALLBACK pGetObject)(THandle handle, typename T::HandleType * phValue), bool ownsHandle = true) const;

	template<typename THandle, typename T> void SetObject(NResult (N_CALLBACK pSetObject)(THandle handle, typename T::HandleType hValue), const T& value)
	{
		THandle hObj = static_cast<THandle>(GetHandle());
		NCheck(pSetObject(hObj, value.GetHandle()));
	}

	template<typename THandle, typename T> NArrayWrapper<T> GetObjects(NResult (N_CALLBACK pGetObjects)(THandle handle, typename T::HandleType * * parhValues, NInt * pValueCount), bool ownsHandles = true) const;
	template<typename THandle, typename T> NArrayWrapper<T> GetObjects(NResult (N_CALLBACK pGetObjects)(THandle handle, typename T::HandleType * parhValues, NInt valueCount), bool ownsHandles = true) const;

public:
	typedef void (* Callback)(NObject * pObject, void * pParam);
	typedef void (* PropertyChangedCallback)(NObject * pObject, NString propertyName, void * pParam);

	static ::Neurotec::NType NObjectCallbackNativeTypeOf();
	static ::Neurotec::NType NObjectPropertyChangedCallbackNativeTypeOf();

	static void Unref(HNObject handle)
	{
		if (handle) NCheck(NObjectUnref(handle));
	}

	template<typename THandle> static void UnrefElements(THandle * arhObjects, NInt objectCount)
	{
		THandle p0 = NULL;
		HNObject p = p0;
		NCheck(NObjectUnrefElements(reinterpret_cast<HNObject *>(arhObjects), objectCount));
		N_UNREFERENCED_PARAMETER(p);
	}

	template<typename THandle> static void UnrefArray(THandle * arhObjects, NInt objectCount)
	{
		THandle p0 = NULL;
		HNObject p = p0;
		NCheck(NObjectUnrefArray(reinterpret_cast<HNObject *>(arhObjects), objectCount));
		N_UNREFERENCED_PARAMETER(p);
	}

	static bool Equals(const NObject & object1, const NObject & object2)
	{
		return object1.Equals(object2);
	}

	template<typename T> static T FromHandle(typename T::HandleType handle, bool ownsHandle = true)
	{
		return T(handle, ownsHandle);
	}

	template<typename T> static NInt ToHandleArray(const T * arpObjects, NInt objectCount, typename T::HandleType * arhObjects, NInt objectsLength, bool addRef = false);

	template<typename T> static T GetObject(NResult (N_CALLBACK pGetObject)(typename T::HandleType * phValue), bool ownsHandle = true);

	template<typename T> static void SetObject(NResult (N_CALLBACK pSetObject)(typename T::HandleType hValue), const T & value)
	{
		NCheck(pSetObject(value.GetHandle()));
	}

	template<typename T> static NArrayWrapper<T> GetObjects(NResult (N_CALLBACK pGetObjects)(typename T::HandleType * * parhValues, NInt * pValueCount), bool ownsHandle = true);

	static NString GetString(NResult (N_CALLBACK pGetString)(HNString * phValue))
	{
		HNString hValue;
		NCheck(pGetString(&hValue));
		return NString(hValue, true);
	}

	static void SetString(NResult (N_CALLBACK pSetString)(HNString hValue), const NStringWrapper & value)
	{
		NCheck(pSetString(value.GetHandle()));
	}

	static void CopyProperties(NObject & dstObject, const NObject & srcObject)
	{
		NCheck(NObjectCopyProperties(dstObject.GetHandle(), srcObject.GetHandle()));
	}

	template<typename T> static void SaveMany(const T * arpObjects, NInt objectCount, ::Neurotec::IO::NStream & stream, NUInt flags = 0);
	template<typename T> static ::Neurotec::IO::NBuffer SaveMany(const T * arpObjects, NInt objectCount, NUInt flags = 0);
	template<typename T> static NSizeType GetSizeMany(const T * arpObjects, NInt objectCount, NUInt flags = 0);
	template<typename T> static NSizeType SaveMany(const T * arpObjects, NInt objectCount, ::Neurotec::IO::NBuffer & buffer, NUInt flags = 0);
	template<typename T> static NSizeType SaveMany(const T * arpObjects, NInt objectCount, void * pBuffer, NSizeType bufferSize, NUInt flags = 0);

public:
	NObject(HNObject handle, bool claimHandle = false)
		: m_handle(handle)
	{
		if (handle && !claimHandle)
			Ref();
	}

	NObject(const NObject & other)
		: m_handle(NULL)
	{
		SetHandle(other.m_handle);
	}

#ifdef N_CPP11
	NObject(NObject && other) noexcept
		: m_handle(other.m_handle)
	{
		other.m_handle = nullptr;
	}

	NObject& operator=(NObject && other) noexcept
	{
		if (this != &other)
		{
			if (m_handle != NULL)
			{
				NResult nr = NObjectUnref(m_handle);
				m_handle = NULL;
				if (NFailed(nr))
				{
					NErrorSuppress(nr);
				}
			}
			m_handle = other.m_handle;
			other.m_handle = nullptr;
		}
		return *this;
	}
#endif

	NObject& operator=(const NObject & other)
	{
		if (this != &other)
		{
			SetHandle(other.m_handle);
		}
		return *this;
	}

	virtual ~NObject()
	{
		if (m_handle != NULL)
		{
			NResult nr = NObjectUnref(m_handle);
			m_handle = NULL;
			if (NFailed(nr))
			{
				NErrorSuppress(nr);
			}
		}
	}

	HNObject GetHandle() const
	{
		return m_handle;
	}

	NInt Ref()
	{
		return NCheck(NObjectRef(GetHandle()));
	}

	NInt Unref()
	{
		return NCheck(NObjectUnref(GetHandle()));
	}

	HNObject RefHandle() const
	{
		NCheck(NObjectRef(GetHandle()));
		return m_handle;
	}

	NObject RefObject() const
	{
		return FromHandle<NObject>(RefHandle());
	}

	bool IsNull() const
	{
		return m_handle == NULL;
	}

	NType GetNativeType() const;

	template<typename T>
	T GetOwner() const
	{
		typename T::HandleType hOwner;
		NCheck(NObjectGetOwnerEx(GetHandle(), (HNObject *)&hOwner));
		return FromHandle<T>(hOwner, true);
	}

	NUInt GetFlags() const
	{
		NUInt value;
		NCheck(NObjectGetFlags(GetHandle(), &value));
		return value;
	}

	void SetFlags(NUInt value)
	{
		NCheck(NObjectSetFlags(GetHandle(), value));
	}

	bool Equals(const NObject & object) const
	{
		NBool result;
		NCheck(NObjectEquals(GetHandle(), object.GetHandle(), &result));
		return result != 0;
	}

	NInt CompareTo(const NObject & object) const
	{
		NInt result;
		NCheck(NObjectCompareTo(GetHandle(), object.GetHandle(), &result));
		return result;
	}

	NInt GetHashCode() const
	{
		NInt value;
		NCheck(NObjectGetHashCode(GetHandle(), &value));
		return value;
	}

	NString ToString(const NStringWrapper & format = NString()) const
	{
		HNString hValue;
		NCheck(NObjectToStringN(GetHandle(), format.GetHandle(), &hValue));
		return NString(hValue, true);
	}

	NObject Clone() const
	{
		HNObject hClonedObject;
		NCheck(NObjectClone(GetHandle(), &hClonedObject));
		return FromHandle<NObject>(hClonedObject);
	}

	template<typename T>
	T Clone() const
	{
		HNObject hClonedObject;
		NCheck(NObjectClone(GetHandle(), &hClonedObject));
		return FromHandle<T>((typename T::HandleType)hClonedObject);
	}

	void Reset()
	{
		NCheck(NObjectReset(GetHandle()));
	}

	NValue GetProperty(const NStringWrapper & name) const;
	bool GetProperty(const NStringWrapper & name, const NType & valueType, NAttributes attributes, void * arValues, NSizeType valuesSize, NInt valuesLength) const;
	template<typename T> T GetProperty(const NStringWrapper & name, NAttributes attributes = naNone, bool * pHasValue = NULL) const;

	void SetProperty(const NStringWrapper & name, const NValue & value);
	void SetProperty(const NStringWrapper & name, const NType & valueType, NAttributes attributes, const void * arValues, NSizeType valuesSize, NInt valuesLength, bool hasValue = true);
	template<typename T> void SetProperty(const NStringWrapper & name, const T & value, NAttributes attributes = naNone, bool hasValue = true);

	void ResetProperty(const NStringWrapper & name)
	{
		NCheck(NObjectResetPropertyN(GetHandle(), name.GetHandle()));
	}

	template<typename InputIt>
	NValue Invoke(const NStringWrapper & name, InputIt first, InputIt last);
	NValue Invoke(const NStringWrapper & name, const NPropertyBag & parameters);
	NValue Invoke(const NStringWrapper & name, const NStringWrapper & parameters);

	void AddHandler(const NStringWrapper & name, NValue & callback);
	void AddHandler(const NStringWrapper & name, NType & callbackType, const NCallback & callback);
	void RemoveHandler(const NStringWrapper & name, NValue & callback);
	void RemoveHandler(const NStringWrapper & name, NType & callbackType, const NCallback & callback);

	void Save(::Neurotec::IO::NStream & stream, NUInt flags = 0) const;
	::Neurotec::IO::NBuffer Save(NUInt flags = 0) const;

	NSizeType GetSize(NUInt flags = 0) const
	{
		NSizeType value;
		NCheck(NObjectGetSize(GetHandle(), flags, &value));
		return value;
	}

	NSizeType Save(::Neurotec::IO::NBuffer & buffer, NUInt flags = 0) const;

	NSizeType Save(void * pBuffer, NSizeType bufferSize, NUInt flags = 0) const
	{
		NSizeType size;
		NCheck(NObjectSaveToMemoryDst(GetHandle(), pBuffer, bufferSize, flags, &size));
		return size;
	}

	void CaptureProperties(NPropertyBag & properties) const;

	void AddPropertyChangedCallback(const NCallback & callback)
	{
		NCheck(NObjectAddPropertyChanged(GetHandle(), callback.GetHandle()));
	}

	template<typename F>
	NCallback AddPropertyChangedCallback(const F & callback, void * pParam = NULL);

	void RemovePropertyChangedCallback(const NCallback & callback)
	{
		NCheck(NObjectRemovePropertyChanged(GetHandle(), callback.GetHandle()));
	}

	template<typename F>
	NCallback RemovePropertyChangedCallback(const F & callback, void * pParam = NULL);

	template<typename TOwner> friend class ::Neurotec::Collections::NStringReadOnlyCollection;
	template<typename TOwner> friend class ::Neurotec::Collections::NStringCollection;

	typedef HNObject HandleType;
	static ::Neurotec::NType NativeTypeOf();

	template<typename F> class CallbackDelegate;

	friend class NValue;
	friend class NArray;
};

#ifdef N_CPP11
#define N_OBJECT_MOVE_CONSTRUCTOR(name, baseName)\
	name(name && other) noexcept\
		: baseName(std::move(other))\
	{\
	}\
	name& operator=(name && other) noexcept\
	{\
		baseName::operator=(std::move(other));\
		return *this;\
	}
#else
#define N_OBJECT_MOVE_CONSTRUCTOR(name, baseName)
#endif

#define N_DECLARE_STATIC_OBJECT_CLASS(name) \
	N_DECLARE_TYPE_CLASS(name)\
	N_DECLARE_NON_COPYABLE(name)\
	private:\
		name();
#define N_DECLARE_OBJECT_CLASS(name, baseName) \
	private:\
		static ::Neurotec::NObject N_JOIN_SYMBOLS(name, FromHandle)(HNObject handle) { return name(handle, true); }\
	public:\
		typedef H##name HandleType;\
		static ::Neurotec::NType NativeTypeOf()\
		{\
			return ::Neurotec::NObject::GetObject< ::Neurotec::NType>(N_TYPE_OF(name), true);\
		}\
		H##name GetHandle() const { return static_cast<H##name>(baseName::GetHandle()); }\
		H##name RefHandle() const { return static_cast<H##name>(baseName::RefHandle()); }\
		name(HNObject handle, bool ownsHandle = false)\
			: baseName(handle, ownsHandle)\
		{\
		}\
		name(const name & other)\
			: baseName(other)\
		{\
		}\
		N_OBJECT_MOVE_CONSTRUCTOR(name, baseName)\
		name & operator=(const name & other)\
		{\
			baseName::operator=(other);\
			return *this;\
		}\
	private:\

}

#endif // N_OBJECTBASE_HPP_INCLUDED
