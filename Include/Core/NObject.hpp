#ifndef N_OBJECT_HPP_INCLUDED
#define N_OBJECT_HPP_INCLUDED

#include <Core/NTypes.hpp>
#include <Core/NObjectBase.hpp>

#include <Core/NType.hpp>
#include <Core/NError.hpp>

namespace Neurotec
{
template<typename T>
NType NTypeTraitsBase<T, true>::GetNativeType()
{
	return T::NativeTypeOf();
}

inline ::Neurotec::NType NObject::NObjectCallbackNativeTypeOf()
{
	return NObject::GetObject< ::Neurotec::NType>(N_TYPE_OF(NObjectCallback), true);
}

inline ::Neurotec::NType NObject::NObjectPropertyChangedCallbackNativeTypeOf()
{
	return NObject::GetObject< ::Neurotec::NType>(N_TYPE_OF(NObjectPropertyChangedCallback), true);
}

inline ::Neurotec::NType NObject::NativeTypeOf()
{
	return NObject::GetObject< ::Neurotec::NType>(N_TYPE_OF(NObject), true);
}

inline void NObject::AddHandler(const NStringWrapper & name, NValue & callback)
{
	NCheck(NObjectAddHandlerN(GetHandle(), name.GetHandle(), callback.GetHandle()));
}

inline void NObject::AddHandler(const NStringWrapper & name, NType & callbackType, const NCallback & callback)
{
	NCheck(NObjectAddHandlerNN(GetHandle(), name.GetHandle(), callbackType.GetHandle(), callback.GetHandle()));
}

inline void NObject::RemoveHandler(const NStringWrapper & name, NValue & callback)
{
	NCheck(NObjectRemoveHandlerN(GetHandle(), name.GetHandle(), callback.GetHandle()));
}

inline void NObject::RemoveHandler(const NStringWrapper & name, NType & callbackType, const NCallback & callback)
{
	NCheck(NObjectRemoveHandlerNN(GetHandle(), name.GetHandle(), callbackType.GetHandle(), callback.GetHandle()));
}

inline bool operator==(const NObject & value1, const NObject & value2)
{
	return NObject::Equals(value1, value2);
}

inline bool operator!=(const NObject & value1, const NObject & value2)
{
	return !NObject::Equals(value1, value2);
}

#ifdef N_CPP11
inline bool operator==(const NObject & value1, std::nullptr_t)
{
	return value1.IsNull();
}

inline bool operator!=(const NObject & value1, std::nullptr_t)
{
	return !value1.IsNull();
}
#endif

}

#include <Core/NType.hpp>
#include <Core/NPropertyBag.hpp>
#include <IO/NBuffer.hpp>
#include <IO/NStream.hpp>

namespace Neurotec
{

template<typename T> inline NInt NObject::ToHandleArray(const T * arpObjects, NInt objectCount, typename T::HandleType * arhObjects, NInt objectsLength, bool addRef)
{
	if (!arpObjects && objectCount != 0) NThrowArgumentNullException(N_T("arpObjects"));
	if (objectCount < 0) NThrowArgumentLessThanZeroException(N_T("objectCount"));
	if (arhObjects)
	{
		if (objectsLength < objectCount) NThrowArgumentInsufficientException(N_T("objectsLength"));
		const T * pObject = arpObjects;
		typename T::HandleType * phObject = arhObjects;
		NInt i = 0;
		try
		{
			for (; i < objectCount; i++, pObject++, phObject++)
			{
				if (pObject->GetHandle() == NULL)
				{
					*phObject = NULL;
				}
				else
				{
					*phObject = addRef ? pObject->RefHandle() : pObject->GetHandle();
				}
			}
		}
		catch (...)
		{
			if (addRef)
			{
				for (; i >= 0; i--, phObject--)
				{
					Unref(*phObject);
				}
			}
			throw;
		}
	}
	return objectCount;
}

template<typename T> inline T NObject::GetObject(NResult (N_CALLBACK pGetObject)(typename T::HandleType * phValue), bool ownsHandle)
{
	typename T::HandleType hValue;
	NCheck(pGetObject(&hValue));
	return FromHandle<T>(hValue, ownsHandle);
}

template<typename T> inline NArrayWrapper<T> NObject::GetObjects(NResult (N_CALLBACK pGetObjects)(typename T::HandleType * * parhValues, NInt * pValueCount), bool ownsHandles)
{
	typename T::HandleType * arhValues = NULL;
	NInt valueCount = 0;
	NCheck(pGetObjects(&arhValues, &valueCount));
	return NArrayWrapper<T>(arhValues, valueCount, true, ownsHandles);
}

template<typename THandle> inline NString NObject::GetString(NResult (N_CALLBACK pGetString)(THandle handle, HNString * phValue)) const
{
	HNString hValue;
	NCheck(pGetString(static_cast<THandle>(GetHandle()), &hValue));
	return NString(hValue, true);
}

template<typename THandle> inline void NObject::SetString(NResult (N_CALLBACK pSetString)(THandle handle, HNString hValue), const NStringWrapper & value)
{
	NCheck(pSetString(static_cast<THandle>(GetHandle()), value.GetHandle()));
}

template<typename THandle, typename T> inline T NObject::GetObject(NResult (N_CALLBACK pGetObject)(THandle handle, typename T::HandleType * phValue), bool ownsHandle) const
{
	THandle hObj = static_cast<THandle>(GetHandle());
	typename T::HandleType hValue;
	NCheck(pGetObject(hObj, &hValue));
	return FromHandle<T>(hValue, ownsHandle);
}

template<typename THandle, typename T> inline NArrayWrapper<T> NObject::GetObjects(NResult (N_CALLBACK pGetObjects)(THandle handle, typename T::HandleType * * parhValues, NInt * pValueCount), bool ownsHandles) const
{
	typename T::HandleType * arhValues = NULL;
	NInt valueCount = 0;
	NCheck(pGetObjects(static_cast<THandle>(GetHandle()), &arhValues, &valueCount));
	return NArrayWrapper<T>(arhValues, valueCount, true, ownsHandles);
}

template<typename THandle, typename T> inline NArrayWrapper<T> NObject::GetObjects(NResult (N_CALLBACK pGetObjects)(THandle handle, typename T::HandleType * parhValues, NInt valueCount), bool ownsHandles) const
{
	THandle hObj = static_cast<THandle>(GetHandle());
	NInt valueCount = 0;
	valueCount = NCheck(pGetObjects(hObj, NULL, 0));
	NArrayWrapper<T> objects(valueCount, ownsHandles);
	valueCount = NCheck(pGetObjects(hObj, objects.GetPtr(), valueCount));
	objects.SetCount(valueCount);
	return objects;
}

inline NValue NObject::GetProperty(const NStringWrapper & name) const
{
	HNValue hValue;
	NCheck(NObjectGetPropertyN(GetHandle(), name.GetHandle(), &hValue));
	return FromHandle<NValue>(hValue);
}

inline bool NObject::GetProperty(const NStringWrapper & name, const NType & valueType, NAttributes attributes, void * arValues, NSizeType valuesSize, NInt valuesLength) const
{
	NBool hasValue;
	NCheck(NObjectGetPropertyNN(GetHandle(), name.GetHandle(), valueType.GetHandle(), attributes, arValues, valuesSize, valuesLength, &hasValue));
	return hasValue != 0;
}

template<typename T> inline T NObject::GetProperty(const NStringWrapper & name, NAttributes attributes, bool * pHasValue) const
{
	typename NTypeTraits<T>::NativeType value;
	NBool hasValue = NFalse;
	NCheck(NObjectGetPropertyNN(GetHandle(), name.GetHandle(), NTypeTraits<T>::GetNativeType().GetHandle(), attributes, &value, sizeof(value), 1, pHasValue ? &hasValue : NULL));
	T v = NTypeTraits<T>::FromNative(value, true);
	if (pHasValue) *pHasValue = hasValue != 0;
	return v;
}

inline void NObject::SetProperty(const NStringWrapper & name, const NValue & value)
{
	NCheck(NObjectSetPropertyN(GetHandle(), name.GetHandle(), value.GetHandle()));
}

inline void NObject::SetProperty(const NStringWrapper & name, const NType & valueType, NAttributes attributes, const void * arValues, NSizeType valuesSize, NInt valuesLength, bool hasValue)
{
	NCheck(NObjectSetPropertyNN(GetHandle(), name.GetHandle(), valueType.GetHandle(), attributes, arValues, valuesSize, valuesLength, hasValue ? NTrue : NFalse));
}

template<typename T> inline void NObject::SetProperty(const NStringWrapper & name, const T & value, NAttributes attributes, bool hasValue)
{
	typename NTypeTraits<T>::NativeType v = NTypeTraits<T>::ToNative(value);
	NCheck(NObjectSetPropertyNN(GetHandle(), name.GetHandle(), NTypeTraits<T>::GetNativeType().GetHandle(), attributes, &v, sizeof(v), 1, hasValue ? NTrue : NFalse));
}

template<typename InputIt>
inline NValue NObject::Invoke(const NStringWrapper & name, InputIt firstParameter, InputIt lastParameter)
{
	NArrayWrapper<NValue> parameters(firstParameter, lastParameter);
	HNValue hResult;
	NCheck(NObjectInvokeN(GetHandle(), name.GetHandle(), parameters.GetPtr(), parameters.GetCount(), &hResult));
	return FromHandle<NValue>(hResult);
}

inline NValue NObject::Invoke(const NStringWrapper & name, const NPropertyBag & parameters)
{
	HNValue hResult;
	NCheck(NObjectInvokeWithPropertyBagN(GetHandle(), name.GetHandle(), parameters.GetHandle(), &hResult));
	return FromHandle<NValue>(hResult);
}

inline NValue NObject::Invoke(const NStringWrapper & name, const NStringWrapper & parameters)
{
	HNValue hResult;
	NCheck(NObjectInvokeWithStringN(GetHandle(), name.GetHandle(), parameters.GetHandle(), &hResult));
	return FromHandle<NValue>(hResult);
}

template<typename T> inline void NObject::SaveMany(const T * arpObjects, NInt objectCount, ::Neurotec::IO::NStream & stream, NUInt flags)
{
	NArrayWrapper<T> objects(arpObjects, objectCount);
	NCheck(NObjectSaveManyToStream(objects.GetPtr(), objects.GetCount(), stream.GetHandle(), flags));
}

template<typename T> inline ::Neurotec::IO::NBuffer NObject::SaveMany(const T * arpObjects, NInt objectCount, NUInt flags)
{
	NArrayWrapper<T> objects(arpObjects, objectCount);
	HNBuffer hBuffer;
	NCheck(NObjectSaveManyToMemoryN(objects.GetPtr(), objects.GetCount(), flags, &hBuffer));
	return FromHandle< ::Neurotec::IO::NBuffer>(hBuffer);
}

template<typename T> inline NSizeType GetSizeMany(const T * arpObjects, NInt objectCount, NUInt flags)
{
	NArrayWrapper<T> objects(arpObjects, objectCount);
	NSizeType size;
	NCheck(NObjectGetSizeMany(objects.GetPtr(), objects.GetCount(), flags, &size));
	return size;
}

template<typename T> inline NSizeType NObject::SaveMany(const T * arpObjects, NInt objectCount, ::Neurotec::IO::NBuffer & buffer, NUInt flags)
{
	NArrayWrapper<T> objects(arpObjects, objectCount);
	NSizeType size;
	NCheck(NObjectSaveManyToMemoryDstN(objects.GetPtr(), objects.GetCount(), buffer.GetHandle(), flags, &size));
	return size;
}

template<typename T> inline NSizeType SaveMany(const T * arpObjects, NInt objectCount, void * pBuffer, NSizeType bufferSize, NUInt flags)
{
	NArrayWrapper<T> objects(arpObjects, objectCount);
	NSizeType size;
	NCheck(NObjectSaveManyToMemoryDst(objects.GetPtr(), objects.GetCount(), pBuffer, bufferSize, flags, &size));
	return size;
}

inline void NObject::Save(::Neurotec::IO::NStream & stream, NUInt flags) const
{
	NCheck(NObjectSaveToStream(GetHandle(), stream.GetHandle(), flags));
}

inline ::Neurotec::IO::NBuffer NObject::Save(NUInt flags) const
{
	HNBuffer hBuffer;
	NCheck(NObjectSaveToMemoryN(GetHandle(), flags, &hBuffer));
	return FromHandle< ::Neurotec::IO::NBuffer>(hBuffer);
}

inline NSizeType NObject::Save(::Neurotec::IO::NBuffer & buffer, NUInt flags) const
{
	NSizeType size;
	NCheck(NObjectSaveToMemoryDstN(GetHandle(), buffer.GetHandle(), flags, &size));
	return size;
}

inline void NObject::CaptureProperties(NPropertyBag & properties) const
{
	NCheck(NObjectCaptureProperties(GetHandle(), properties.GetHandle()));
}

template<typename F>
class NObject::EventHandler : public EventHandlerBase<F>
{
public:
	EventHandler(F f)
		: EventHandlerBase<F>(f)
	{
	}

	static NResult N_API NativeCallback(HNObject hObject, void * pParam)
	{
		NResult result = N_OK;
		try
		{
			EventHandler<F> * pHandler = static_cast<EventHandler *>(pParam);
			EventArgs e(hObject, pHandler->pParam);
			pHandler->callback(e);
		}
		N_EXCEPTION_CATCH_AND_SET_LAST(result);
		return result;
	}
};

class NObject::PropertyChangedEventArgs : public EventArgs
{
private:
	HNString hPropertyName;

public:
	PropertyChangedEventArgs(HNObject hObject, HNString hPropertyName, void * pParam)
		: EventArgs(hObject, pParam), hPropertyName(hPropertyName)
	{
	}

	NString GetPropertyName() const
	{
		return NString(hPropertyName, false);
	}
};

template<typename F>
class NObject::PropertyChangedEventHandler : public EventHandlerBase<F>
{
public:
	PropertyChangedEventHandler(F f)
		: EventHandlerBase<F>(f)
	{
	}

	static NResult N_API NativeCallback(HNObject hObject, HNString hPropertyName, void * pParam)
	{
		NResult result = N_OK;
		try
		{
			PropertyChangedEventHandler<F> * pHandler = static_cast<PropertyChangedEventHandler *>(pParam);
			NObject::PropertyChangedEventArgs e(hObject, hPropertyName, pHandler->pParam);
			pHandler->callback(e);
		}
		N_EXCEPTION_CATCH_AND_SET_LAST(result);
		return result;
	}
};

template<typename F>
NCallback NObject::AddPropertyChangedCallback(const F & callback, void * pParam)
{
	NCallback cb = NTypes::CreateCallback<PropertyChangedEventHandler<F> >(callback, pParam);
	AddPropertyChangedCallback(cb);
	return cb;
}

template<typename F>
NCallback NObject::RemovePropertyChangedCallback(const F & callback, void * pParam)
{
	NCallback cb = NTypes::CreateCallback<PropertyChangedEventHandler<F> >(callback, pParam);
	RemovePropertyChangedCallback(cb);
	return cb;
}

inline NType NObject::GetNativeType() const
{
	return GetObject<HandleType, NType>(NObjectGetType, true);
}

template<typename T>
inline T NObjectDynamicCast(const NObject & obj)
{
	if (!obj.IsNull() && !T::NativeTypeOf().IsInstanceOfType(obj))
		NThrowInvalidCastException();
	return NObject::FromHandle<T>((typename T::HandleType)(obj.GetHandle()), false);
}

}

#endif // !N_OBJECT_HPP_INCLUDED
