#ifndef AN_SUB_FIELD_H_INCLUDED
#define AN_SUB_FIELD_H_INCLUDED

#include <Core/NObject.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANSubField, NObject)

NResult N_API ANSubFieldGetItemNameN(HANSubField hSubField, NInt index, HNString * phName, HNString * phTypeName);
#ifdef N_DOCUMENTATION
NResult N_API ANSubFieldGetItemName(HANSubField hSubField, NInt index, HNString * phName, HNString * phTypeName);
#endif

NResult N_API ANSubFieldSetItemNameN(HANSubField hSubField, NInt index, HNString hName, HNString hTypeName);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSubFieldSetItemNameA(HANSubField hSubField, NInt index, const NAChar * szName, const NAChar * szTypeName);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSubFieldSetItemNameW(HANSubField hSubField, NInt index, const NWChar * szName, const NWChar * szTypeName);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSubFieldSetItemName(HANSubField hSubField, NInt index, const NChar * szName, const NChar * szTypeName);
#endif
#define ANSubFieldSetItemName N_FUNC_AW(ANSubFieldSetItemName)

NResult N_API ANSubFieldGetItemCount(HANSubField hSubField, NInt * pValue);
NResult N_API ANSubFieldGetItemN(HANSubField hSubField, NInt index, HNString * phValue);
#ifdef N_DOCUMENTATION
NResult N_API ANSubFieldGetItem(HANSubField hSubField, NInt index, HNString * phValue);
#endif
NResult N_API ANSubFieldGetItemCapacity(HANSubField hSubField, NInt * pValue);
NResult N_API ANSubFieldSetItemCapacity(HANSubField hSubField, NInt value);
NResult N_API ANSubFieldGetItemDataN(HANSubField hSubField, NInt index, HNBuffer * phValue);

NResult N_API ANSubFieldSetItemN(HANSubField hSubField, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSubFieldSetItemExA(HANSubField hSubField, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSubFieldSetItemExW(HANSubField hSubField, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSubFieldSetItemEx(HANSubField hSubField, NInt index, const NChar * szValue);
#endif
#define ANSubFieldSetItemEx N_FUNC_AW(ANSubFieldSetItemEx)

NResult N_API ANSubFieldAddItemN(HANSubField hSubField, HNString hValue, NInt * pIndex);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSubFieldAddItemExA(HANSubField hSubField, const NAChar * szValue, NInt * pIndex);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSubFieldAddItemExW(HANSubField hSubField, const NWChar * szValue, NInt * pIndex);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSubFieldAddItemEx(HANSubField hSubField, const NChar * szValue, NInt * pIndex);
#endif
#define ANSubFieldAddItemEx N_FUNC_AW(ANSubFieldAddItemEx)

NResult N_API ANSubFieldAddItemExN(HANSubField hSubField, HNString hItemName, HNString hItemTypeName, HNString hValue, NInt * pIndex);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSubFieldAddItemEx2A(HANSubField hSubField, const NAChar * szItemName, const NAChar * szItemTypeName, const NAChar * szValue, NInt * pIndex);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSubFieldAddItemEx2W(HANSubField hSubField, const NWChar * szItemName, const NWChar * szItemTypeName, const NWChar * szValue, NInt * pIndex);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSubFieldAddItemEx2(HANSubField hSubField, const NChar * szItemName, const NChar * szItemTypeName, const NChar * szValue, NInt * pIndex);
#endif
#define ANSubFieldAddItemEx2 N_FUNC_AW(ANSubFieldAddItemEx2)

NResult N_API ANSubFieldInsertItemN(HANSubField hSubField, NInt index, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSubFieldInsertItemExA(HANSubField hSubField, NInt index, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSubFieldInsertItemExW(HANSubField hSubField, NInt index, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSubFieldInsertItemEx(HANSubField hSubField, NInt index, const NChar * szValue);
#endif
#define ANSubFieldInsertItemEx N_FUNC_AW(ANSubFieldInsertItemEx)

NResult N_API ANSubFieldInsertItemExN(HANSubField hSubField, NInt index, HNString hItemName, HNString hItemTypeName, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSubFieldInsertItemEx2A(HANSubField hSubField, NInt index, const NAChar * szItemName, const NAChar * szItemTypeName, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSubFieldInsertItemEx2W(HANSubField hSubField, NInt index, const NWChar * szItemName, const NWChar * szItemTypeName, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSubFieldInsertItemEx2(HANSubField hSubField, NInt index, const NChar * szItemName, const NChar * szItemTypeName, const NChar * szValue);
#endif
#define ANSubFieldInsertItemEx2 N_FUNC_AW(ANSubFieldInsertItemEx2)


NResult N_API ANSubFieldRemoveItemAt(HANSubField hSubField, NInt index);
NResult N_API ANSubFieldRemoveItemRange(HANSubField hSubField, NInt index, NInt count);

NResult N_API ANSubFieldGetValueN(HANSubField hSubField, HNString * phValue);
NResult N_API ANSubFieldSetValueN(HANSubField hSubField, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSubFieldSetValueExA(HANSubField hSubField, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSubFieldSetValueExW(HANSubField hSubField, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSubFieldSetValueEx(HANSubField hSubField, const NChar * szValue);
#endif
#define ANSubFieldSetValueEx N_FUNC_AW(ANSubFieldSetValueEx)

NResult N_API ANSubFieldGetDataN(HANSubField hSubField, HNBuffer * phValue);

NResult N_API ANSubFieldGetNameN(HANSubField hSubField, HNString * phValue);

NResult N_API ANSubFieldSetNameN(HANSubField hSubField, HNString hName);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANSubFieldSetNameA(HANSubField hSubField, const NAChar * szName);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANSubFieldSetNameW(HANSubField hSubField, const NWChar * szName);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANSubFieldSetName(HANSubField hSubField, const NChar * szName);
#endif
#define ANSubFieldSetName N_FUNC_AW(ANSubFieldSetName)

#ifdef N_CPP
}
#endif

#endif // !AN_SUB_FIELD_H_INCLUDED
